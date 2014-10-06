
# Makefile for P1 and P2.
# (Note that this makefile may not work with Microsoft's MAKE.  It does
#  work with PAMAKE 1.9 and will probably work with Microsoft's NMAKE.)
# EXE files are targeted for OS/2 and bound for use under MSDOS

# Add /Lp to the next line if your default libraries are the real-mode ones.

COPT = /AS /G0 /Fb /W3

both: p1.exe p2.exe

p1.exe:	 p1.c
	@echo NAME P1 WINDOWCOMPAT >p1.def
	cl $(COPT) p1.c p1.def
	del p1.obj
	del p1.def

p2.exe:	 p2.c
	@echo NAME P2 WINDOWCOMPAT >p2.def
	cl $(COPT) p2.c p2.def
	del p2.obj
	del p2.def
