# ifj-59
ifj-059-b/2/I

================= OBSAH PŘEDNÁŠEK =================

Jedná se o přednášky ve wisu https://wis.fit.vutbr.cz/FIT/st/cwk.php?id=11438&csid=610913

PDF přednášek lze stáhnout zde: https://wis.fit.vutbr.cz/…/course-f…/course/IFJ-IT/lectures…

--------------------------- Úvody do překladačů----------------------------

PŘEDNÁŠKA 2- 19. 9. 2011

0:00:00 - 0:38:00 ... Úvod k předmětu

0:38:00 - 1:47:00 ... Definice, Abecedy, Řetězce (podřetězce, délka řetězců, ...)

1:47:00 - 2:16:00 ... Překladač, Struktura překladače, Logické fáze překladače

2:16:00 - END ... Informace k projektu (z roku 2011, ovšem údaje stále aktuální)



PŘEDNÁŠKA 2- 26.10. 2011

0:00:00 - 0:16:00 ... Úvod, zopakování

0:16:00 - 0:34:00 ... Obecné fungování překladače, struktura překladače !!! DŮLEŽITÉ !!!

0:35:00 - 0:46:00 ... Lexikální analyzátor- jak funguje !!! DŮLEŽITÉ !!!

0:46:00 - 1:14:00 ... Syntaktický analyzátor !!! DŮLEŽITÉ !!!

TODO, zbytek doplním až to dokoukám

------------------------- Modely regulárních jazyků-------------------------

PŘEDNÁŠKA 3- 26.10. 2011

TODO

PŘEDNÁŠKA 3- 3.10.

TODO

------------------------- Speciální konečné automaty-----------------------



















===========================================================================

[ Návod ]

1. Je třeba si vytvořit účet na GitHubu a kontaktovat mě (@Skalin), abych Vás přidal
2. Následně je třeba si nainstalovat Git (debian/ubuntu: `apt-get install git`, redhat/centos: `yum install git`; windows: https://desktop.github.com/ nebo https://git-scm.com/downloads)
3. Následně je třeba mít nainstalováno GCC (v linuxu standardně je, jinak instalace `apt-get install gcc*` nebo `yum install gcc*`; ve windows: doporučuji držet se tohoto návodu: https://www.jetbrains.com/help/clion/2016.1/quick-tutorial-on-configuring-clion-on-windows.html#d10151e64)
4. Také je třeba nainstalovat clion, viz odkaz výše. Existuje i instalace pro Linux, tedy doporučuji použít tu, pokud jste linuxáři (POZOR! INSTALACE POD LINUXEM A CLONE PROJEKTU VYŽADUJE ROOTA!)
5. Vytvoříme si složku např. `C:\Programming`, příp. u Linuxu: `/home/Programming`

Tato část je pro Linux
 1. Vstoupíme do dané složky `cd /home/Programming` a na linuxu provedeme jako root tento příkaz: `sudo git clone https://github.com/Skalin/ifj-59`
 2. Git požádá o údaje ke githubu, zadáme správné údaje
 3. Po přihlášení se nám zkopíruje obsah repozitáře do námi vybrané složky
 4. Stále jako root provedeme úpravu souborů a uložíme
 5. Po uložení napíšeme: `git commit -a`, otevře se VI, ve kterém bude commit zpráva, kterou zapíšeme. Uložíme.
 6. Na základě rozhodnutí buď upravujeme dále a provádíme další commity, nebo si je ukládáme do repozítáře: `git push`
 7. POZOR! Po dnešním dni se začnou tvořit větve, o těch dám další briefing později.
 
Tato část je pro Windows
 1. Po instalaci CLionu jej spustíme
 2. Vybereme Preferences a v sekci: `Version Control` vybereme `Git` a nastavíme cestu k Git aplikaci. Pokud jste nainstalovali Git, cesta je: `C:\Program Files\Git\bin\git.exe` , pokud jste nainstalovali GitHub aplikaci, cesta je: `C:\Users\<username>\AppData\Local\GitHub\PortableGit_<numbersandletters>\bin\git.exe`
 3. Následně vybereme o dva řádky výše v sekci `Version Control` položku `GitHub`, přihlásíme se ke GitHubu a zatrhneme položku `clone git repositores using SSH`. Testneme připojení, mělo by projít, poté uložíme.
 4. V sekci: `Build, Executions and Deployment` vybereme `Toolchains`, zde v sekci `Environment` nastavíme cestu k MinGW, standardně `C:\MinGW`
 5. Uložíme, klepneme na `Import Project` (případně `File->Import project` a naimportujeme cestu `C:\Programming\ifj-59` a můžeme začít editovat.
 6. Po editaci a uložení (CTRL+S) klepneme pravým vlevo na celý projekt `ifj-59`, vybereme `Git -> Commit Directory`, vepíšeme commit message. Podle toho,zda-li chceme dále pracovat, vybereme pouze "commit..", pokud chceme vše uložit na server, doporučuji "commit and push".
 7. POZOR! Po dnešním dni se začnou tvořit větve, o těch dám další briefing později.
