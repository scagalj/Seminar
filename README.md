## Uputstva:

u Control Panel-u dodajte ODBC data source (System DSN) koji pokazuje na tu bazu
koristite "Data Sources (ODBC)" tool iz Control Panel \ Administrative Tools
na 64-bitnim Windowsima koristite 32-bitnu verziju (c:\Windows\SysWOW64\odbcad32.exe)
DSN name koji odgovara projektu je: seminar_baza

## Podaci za logiranje u aplikaciju: 
- **Korisničko ime:** *admin*
- **Lozinka:** *12345*
 
## Korištenje aplikacije

- Prilikom pokretanja same aplikacije potrebno je unijeti korisničko ime i lozinku pojedinog zaposlenika. Nakon čega nam se otvara novi prozor. U samom prozoru imamo listu gdje se nalaze rezervacije s današnjim datumom odjave. Pritiskom na botune Zaposlenik / Gost, otvara se novi prozor s popisom Zaposlenika / Gostiju, te imamo mogućnost dodavanja odnosno brisanje istih.
- Pritiskom na Hotel otvara nam se novi prozor gdje imamo popis svih hotela, te mogućnost dodavanj odnosno brisanja istih. Označavanjem jednog od hotela dobijamo mogućnost dodavanja soba za pojedini hotel i ispisom soba za odabrani hotel te brisanje istih. Isto tako imamo mogućnost pretraživanja hotela prema imenu.
- Klikom na Slobodne sobe otvara nam se novi prozor gdje možemo odabrati hotel te željeni datum dolaska i odlaska te nam se ispišu sve slobodne sobe u odabranom rasponu za hotel. Nakon čega imamo mogućnost kreiranja nove rezervacije, ukoliko se gost ne nalazi u bazi možemo ga automatski kreirati ili jednostavno prema oibu pronaći postojećeg. Upisujemo broj gostiju i dodajemo željene sobe prema ID sobe iz prethodnom prozora. Ispisuje se ukupna cijena, koja je za vrijeme sezone uvećana za 1.2 puta.
- Klikom na Rezervacije otvara nam se prozor sa svim aktualnim rezervacijama, pritiskom na pojedinu ispisuju nam se odabrane sobe prema rezervaciji te imamo mogućnost brisanja odnosno printanje iste.
- Stare rezervacije možemo vidjeti pritiskom na Stare rezervacije.
