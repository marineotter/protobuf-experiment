main.exe: main.c sample.pb.c pb.h nanopb.proto
	gcc *.c -o main.exe -lwsock32 -lws2_32 -I . 

pb.h: nanopb-0.4.5-windows-x86/nanopb-0.4.5-windows-x86/spm_headers/pb.h
	copy /Y nanopb-0.4.5-windows-x86\nanopb-0.4.5-windows-x86\spm_headers\nanopb\*.h .\

nanopb.proto: nanopb-0.4.5-windows-x86/nanopb-0.4.5-windows-x86/generator/proto/nanopb.proto
	copy /Y nanopb-0.4.5-windows-x86\nanopb-0.4.5-windows-x86\generator\proto\nanopb.proto nanopb.proto

sample.pb.c: nanopb-0.4.5-windows-x86/nanopb-0.4.5-windows-x86/generator-bin/nanopb_generator.exe
	nanopb-0.4.5-windows-x86\nanopb-0.4.5-windows-x86\generator-bin\nanopb_generator.exe sample.proto

nanopb-0.4.5-windows-x86: nanopb-0.4.5-windows-x86.zip
	powershell -Command 'Expand-Archive -Path .\nanopb-0.4.5-windows-x86.zip -DestinationPath .\nanopb-0.4.5-windows-x86 -Force'

nanopb-0.4.5-windows-x86.zip:
	curl https://jpa.kapsi.fi/nanopb/download/nanopb-0.4.5-windows-x86.zip -o nanopb-0.4.5-windows-x86.zip
