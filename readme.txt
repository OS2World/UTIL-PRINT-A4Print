A couple of programs to print things on a laser printer in such a
way as to just about maximise the amount of stuff on an A4 page.

   ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
   ³ In accordance with the principles of encouraging a    ³
   ³ source-rich environment in OS/2 world like that which ³
   ³ we enjoyed in CP/M days and which we lost with the    ³
   ³ advent of the IBM PC and MSDOS, full source code is   ³
   ³ provided so you can tailor these programs to suit     ³
   ³ your own needs and preferences instead of being tied  ³
   ³ to mine.                                              ³
   ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ

These programs were written for a Sharp JX-9300 which emulates an
HP LaserJet II very closely.  To adapt the programs to other
printers you'll need to change the various control strings which
occur throughout each program and recompile.  (OK, I accept your
rebuke, but these programs were never intended for distribution
so the "quick and dirty" method was appropriate at the time!)

P1 is for printing fairly wide stuff on an A4 page in portrait
mode.  P2 is for printing narrower stuff such as program listings
in two columns in landscape mode.

Both programs use the internal 16.5 pitch line printer font at 9
lines per inch.  On an A4 page P1 prints just over 90 lines of
about 130 characters per page whereas P2 prints just over 120
lines of about 80 chars.

If you use imperial paper sizes then you'll have to tweak the
number of lines per page in each of the programs.  A4 paper is
210x297mm.  American "letter" paper is 8.5x11" which is slightly
wider and shorter (216x279mm).

Nine lines per inch is a bit congested for normal text but it is
OK for program listings provided that your programs are not all
UPPER CASE.  Upper case lettering is visually violent anyway; in
closely spaced text it will be just about unreadable.

Each program has a help screen which is invoked if you run the
program with no parameters.  If you don't like the names (P1 and
P2) then you can rename the .EXE files and the help screen will
know about the new names.

As you will see from the help screens the programs allow for
line numbering and for varying the tab interval.  If you want
to use these programs to print their own listings then you
should use a tab interval of 4 otherwise you'll have the text
disappearing past the right margin; e.g.:

	p2 /4 p?.c

Each program behaves fairly sensibly with respect to form feeds
embedded in the files being printed.

There is no copyright on these programs.  All I ask is that you
do not distribute them in executable form alone.  I gave you the
source code; please don't withhold it from anyone else.

     Jon Saxton
     Sydney, NSW
     Australia
     September 1990.
