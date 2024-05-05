Stručná dokumentace k projektu ICP Epic Robot Simulator.
Autoři: Marek Effenberger a Samuel Hejníček

Stručný popis programu:
Epic Robot Simulator je mini 2D hra, ve které je hráčem ovládán právě 1 robot, se kterým je možné se libovolně pohybovat po mapě a vyhýbat se překážkám. Cílem hry je zůstat naživu do vypršení časovače. Hráč má 3 životy, které mu mohou být sebrány nepřátelskými roboty, kteří se autonomně pohybují po mapě, vyhýbají se překážkám a otáčejí o určitý úhel. Mapu lze uložit a načíst ve formátu JSON a lze ji editovat v podobě přidání překážek a dalších autonomních robotů, stejně tak lze měnit časový limit.

Požadavky na spuštění:
Ubuntu Linux 64bit s nainstalovanými knihovnami Qt verze alespoň 5.5.

Spuštění programu:
Po rozbalení adresáře stačí v kořenové složce spustit příkaz make run, který vytvoří spustitelný soubor EpicRobotSimulator a následně jej spustí.
Přiložený makefile umí ještě zabalit archiv pomocí 'make pack' vygenerovat dokumentaci pomocí 'make doxygen' a vymazat pomocnou sloužku build a spustitelný soubor pomocí 'make clean'.

Ovládání programu:
Hru lze ovládat šipkami na klávesnici nebo myší pomocí tlačítek v herním okně (viz popis jednotlivých komponent hry).

Popis jednotlivých komponent hry:
(Všechny pomocné obrázky jsou ve složce readme_images).

1) Hlavní Okno

Hlavní okno (MainWindow) je spuštěno hned po startu hry, na výběr je Vytvoření mapy (možnost A), která uživatele zanese do editoru mapy, možnost načíst již uloženou hru ze souboru (možnost B) nebo ukončení programu (možnost C).

2) Okno editoru mapy
Pojem robot značí hráčem kontrolovaného robota.

Toto okno slouží k vytvoření/editaci mapy pro hru. Jednotlivé části jsou popsány níže:
A - Po kliknutí na ikonu překážky a následně kliknutí do mapy lze přidat překážku, ukazatel po levé straně ukazuje zbývající počet překážek k umístění
B - Po kliknutí na ikonu robota a následně kliknutí do mapy lze přidat robota, ukazatel po levé straně ukazuje zbývající počet robotů k umístění *
C - Po kliknutí na ikonu nepřátelského robota a následně kliknutí do mapy lze přidat nepřátelského robota, ukazatel po levé straně ukazuje zbývající počet nepřátel k umístění *
D - Tlačítko nastavující časový limit pro mapu v rozsahu 1 sekundy až 180 sekund. Stavový ukazatel vedle něj značí aktuální stav.
E - Tlačítko, kterým se vybere level obtížnosti. V případě jeho navýšení je přídán maximální počet překážek a nepřátelských robotů
F - Políčko v mapě, ve kterém může být umístěn objekt.
G - Tlačítko, které načte uloženou mapu ze souboru a je možno ji editovat.
H - Tlačítko, které spustí hru s aktuální mapou v editoru.
I - Tlačítko, které uloží mapu do JSON souboru

*Po kliknutí na mapu se otevře dialogové okénko, kde lze zadat parametry jaok výchozí orientace a  rychlost robota. V případě nepřátelského robota ještě směr a úhel otočení po detekce kolize rovněž jako vzdálenost samotné detekce.

3) Herní okno

V tomto okně probíhá samotná hra. Jednotlivé části jsou popsány níže:
A - Tlačítko pauzy, které pozastaví hru. Zároveň je možné v kontextové nabídce zvolit možnost konce hry, pokračování návratu do hlavního menu nebo ukončení hry
B - Živý text měnící se podle stavu hry.
C - Uběhnutý čas / Časový limit mapy, obojí v sekundách
D - Tlačítko, které rotuje robotem doleva
E - Tlačítko, které rotuje robotem doprava
F - Tlačítko, které pohybuje robotem dopředu
G - Po najetí tlačítkem myši na tuto část textu a jeho puštění dojde k aktivaci autopilota, tedy robot se sám pohybuje určitým směrem.


