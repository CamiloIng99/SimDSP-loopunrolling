# SimDSP-FIRtest
## Test an FIR filter on SimDSP for Android

This program implements a FIR filter using a block-processing strategy. To run this program, you need to install SimDSP for Android and the compiler toolchain as described in [SimDSP Project WebSite](https://github.com/parrado/SimDSP-Android). 

Once SimDSP is installed, download or clone this repository, and choose the option *Terminal > Run Build Task* on *VisualStudio Code*.  

By default, it implements a low-pass filter with a cutoff frequency of 5kHz @ fs = 44100Hz. You can redesign the FIR filter by using the Matlab code provided on the *matlab* folder.
