# ifj-59
ifj-059-b/2/I
================= ZÁKLADNÍ INFORMACE =================

Vedoucí: Jan Hrbotický
Správce serveru: Dominik Skála
Správce makefile: Dominik Skála
Tvůrce dokumentace: David Hél

Verze:
Číselné označení rozpětí verzí obsahující dané prvky
0.1-0.2- Hotové základy projektu
-0.99- Kompletní a plně funkční lexikální analyzátor

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
•[Štábní kultura]

1. K příslušnému .c souboru VŽDY vytvořte i .h soubor obsahující PROTOTYPY FUNKCÍ a jejich DOKUMENTACE (Co je to za funkci, jaké má parametry, co vrací atp.)
2. Složené závorky umísťovat ZA statement. (Například u ifů, funkcí atp., nikoli až na nový řádek)
3. Celý kód (vyjma dokumentace) BUDE V ANGLIČTINĚ. (Veškeré proměnné, názvy funkcí atp.)
4. Styl zapisování pointeru bude *p_VariableName (pro rozeznání pointeru na první pohled). např. *p_This
5. Názvy metod (funkcí) začínají malým písmenem. Každé další slovo v názvu má pak první velké písmeno. např. getToken()
6. Názvy metod a proměnných MUSÍ VYSTIHOVAT jejich podstatu. Tzn., že z nich usí být na první pohled čitelné, k čemu slouží. Např. function15415(variable2, smth4); je špatně.
7. Víceslovné proměnné píšeme BEZ PODTRŽÍTEK. Každé slovo v proměnné začíná velkým písmenem (i to první). např. VeryVeryVeryLongVariable
8. Veškerá makra se píší VELKÝMI PÍSMENY například ERROR-01, STATEMENT-F atp. 
9. Mezery v případě závorek se píší následovně (something == true); ((something == true) || (position != null));

•[Štábní kultura GIT]
 I v gitu musí být pořádek, hlavně tedy u commitů, respektive v jejich komentářích

- Každý commit musí mít v názvu [IDENTIFIKÁTOR] verze Komentář

- IDENTIFIKÁTORY: ADD/MODIFY/DELETE
- ADD: Používáme v případě, že přidáváme ZCELA NOVÉ SOUBORY (V případě, že víte, že budete přidávat nové soubory a ZÁROVEŇ upravovat ty staré, proveďte 2 commity- první s ADD se zařazením nového souboru do systému. Posléze pak MODIFY)
- MODIFY: Používáme v případě, že jsme upravili stávající soubor/y
- DELETE: Používáme v případě, že jste smazali některé subory (optimalizace, ladící soubory, atp.). Identifikátor DELETE užívejte prosím POUZE V PŘÍPADĚ, kdy jste všechny soubory zařazené v COMMITU MAZALI (Aby se v commitu s DELETE nenalézely i MODIFY operace atp.)

- verze: Označuje verzi, nad kterou jste dělali úpravy (Stanoví se plán verzí, např. lexikální analyzátor bude hotov do verze 1.0, pak tedy vše co se týká lexkálního analyzátoru bude mít verzi nižší než 1)

- Komentář: Stručně charakterizujte, jaké úpravy jste udělali ( Není třeba se nějak dlouze rozepisovat, stačí jen, abyste napsali s čím jste pracovali. Aby se v případě chyb po commitu dalo snadno poznat, od koho chyba pochází)

- Příklad commitů:
[ADD] 0.8 Přidání souborů parser.c, parser.h 

[MODIFY] 0.8 Úprava souborů parser.c/.h, přidány funkce pro získávání tokenů getToken(), mírná optimalizace funkce printToken(token Token)

[MODIFY] 0.81 Úprava souborů parser.c, opravena chyba ve funkci getToken(), která pro null vracela špatné hodnoty

• U KAŽDÉHO COMMITU UVÁDĚJTE I SVŮJ NICK NA GITHUBU (nebo vaše jméno)



===========================================================================

      [ Návod ]

1. Je třeba si vytvořit účet na GitHubu a kontaktovat mě ( @Skalin ), abych Vás přidal
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
 6. Po editaci a uložení (`CTRL+S`) klepneme pravým vlevo na celý projekt `ifj-59`, vybereme `Git -> Commit Directory`, vepíšeme commit message. Podle toho,zda-li chceme dále pracovat, vybereme pouze `Commit`, pokud chceme vše uložit na server, doporučuji `commit and push`.
 7. POZOR! Po dnešním dni se začnou tvořit větve, o těch dám další briefing později.
