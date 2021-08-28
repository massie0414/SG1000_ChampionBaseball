sdcc -c -mz80 ChampionBaseball.c

:sdcc -c -mz80 --peep-file peep-rules.txt SGlib.c
:sdasz80 -g -o crt0_sg.s

sdcc -o ChampionBaseball.ihx -mz80 --no-std-crt0 --data-loc 0xC000 crt0_sg.rel ChampionBaseball.rel SGlib.rel PSGlib.rel

ihx2sms ChampionBaseball.ihx ChampionBaseball.sg

del *.asm > nul
del *.ihx > nul
del *.lk > nul
del *.lst > nul
del *.map > nul
del *.noi > nul
del *.sym > nul

pause