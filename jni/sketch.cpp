//Archivo de cabecera de SimDSP
#include <simdsp.h>

//Archivo de cabecera para medir el tiempo
#include <time.h>
#include <math.h>


//Frecuencia de muestreo
#define F_S 44100

//Carga los coeficientes del filtro y la longitud de la respuesta al impulso (Nh)
#include "../matlab/coefs.h"

//Tamaño del bloque de datos
#define N_DATA (1<<12)

//Segunda señal de comparación
short *x2; 


//Función que devuelve el tiempo en milisegundos
double now_ms(void) {
  struct timespec res;
  clock_gettime(CLOCK_REALTIME, &res);
  return 1000.0 * res.tv_sec + (double)res.tv_nsec / 1e6;
}
int n_blocks = 0;


//Rutina que simulará la ISR que se invoca una vez ha finalizado
//la transferencia por DMA, audio apunta a los datos que se procesarán
void process_data(short *x){

  //Para medir el tiempo
  double t_start0, t_proc0;
  double t_start1, t_proc1;
  double t_start, t_proc;

  //Para los ciclos for
  int n;
  int32_t yt0, yt1;
  int32_t yt;

  //Invoca captura por DMA nuevamente
  captureBlock(process_data );

  //Código BASE SIN OPTIMIZACIÓN
  t_start0 = now_ms();
  yt0 = 0;
  for(n=0;n<N_DATA;n++){
    yt0 += (int32_t)x[n] * (int32_t)x2[n]; 
  }
  t_proc0 = now_ms()-t_start0;

 //Código optimizado con loop-unrolling automático 
  t_start1 = now_ms();
  yt1 = 0;
  #pragma GCC unroll 4
  for(n=0;n<N_DATA;n++){
    yt1 += (int32_t)x[n] * (int32_t)x2[n]; 
  }
  t_proc1 = now_ms()-t_start1;

  //Código optimizado con loop-unrolling explícito a mano
  t_start = now_ms();

  int y1, y2, y3, y4;  
  y1 = 0;
  y2 = 0;
  y3 = 0;
  y4 = 0;
  #pragma GCC unroll 4
  for(n=0;n<N_DATA;n+=4){
    y1 += x[n] * x2[n]; 
    y2 += x[n+1] * x2[n+1]; 
    y3 += x[n+2] * x2[n+2]; 
    y4 += x[n+3] * x2[n+3];
  }
  yt = y1+y2+y3+y4;
  
  t_proc = now_ms()-t_start;

  //Muestra el resultado del procesamiento
  n_blocks++;
  if (n_blocks == 20) {  //Muestra el tiempo de ejecución cada 20 bloques para evitar que se bloquee la app
    println( "Resultado: Sin opt: %d | LU-auto: %d | LU-man: %d", (yt0+16384) >> 15, (yt1+16384) >> 15, (yt+16384) >> 15 );
    println("Tiempo: Sin opt(%g ms) LU-auto(%g ms) LU-man(%g ms) Speedup: LU-auto: %.2gx | LU-man: %.2gx", 
        t_proc0, t_proc1, t_proc, t_proc0/t_proc1, t_proc0/t_proc);
    n_blocks = 0;
  }
}


//Función de inicialización
void dsp_setup()
{
  //Habilita sistema de audio del teléfono
  enableAudio(N_DATA,F_S);

  //Imprime tasa de muestreo actual
  println("Sampling frequency is %d Hz and buffer size is %d samples",F_S,N_DATA);

  //Crea la señal de comparación
  x2 = new short[N_DATA];
  for(int n=0; n<N_DATA; n++) {
    x2[n] = 16384 * sin( 2*M_PI*1000.0*n/F_S );
  }

  //Inicia captura por DMA
  captureBlock(process_data );
}
