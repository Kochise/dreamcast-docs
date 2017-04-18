Dreamcast ADPCM Encoder Console Version Ver1.20

1. Overview
The Dreamcast ADPCM Encoder (or ADPCM encoder hereafter) is a tool 
which converts sound materials from the 16-bit WAVE file format to 
the 4-bit WAVE file format (ADPCM).

2. Material
The ADPCM encoder supports the following format of material.
	- File format : WAVE file (stereo/monaural)
						AIFF file (stereo/monaural)
	- Sampling frequency : 11025[Hz], 22050[Hz], 44100[Hz]
	- Quantum bit        : 16 bit

3. Operation method

  (1) Copying files
      Copy all files required to run the ADPCM encoder to the hard disk, etc.

  (2) Running the encoder
      In the directory where the material is stored, secure free disk 
      space equivalent to about 25% or more of the material data. 
      Then run the encoder as follows:

      DADENC infile[.WAV] [outfile[.WAV]]

      infile  : name of material file. Default file extension is [.WAV]
                For material files with different file extensions, 
                be sure to enter the file extensions as well.
      outfile : name of output file. When omitted, the output file 
                is name of the material file with "_B4" added after 
                the name.

When the above steps are performed, the encoded data is output to the 
directory where the material file is stored. 

-END-



