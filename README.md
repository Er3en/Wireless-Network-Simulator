# Wireless-Network-Simulator
Rozważmy łącze w dół pojedynczej komórki sieci mobilnej, w której znajduje się stacja bazowa
dysponująca pasmem podzielonym na k bloków zasobów RB (ang. Resource Block). W losowych
odstępach czasu t w obszarze komórki pojawiają się użytkownicy, z których każdy odbiera losową
ilość danych d. W chwili pojawienia się nowego użytkownika są ustalane jego warunki propagacyjne,
wyrażone jako przepływność rk
losowana niezależnie dla k kolejnych bloków zasobów. Warunki propagacyjne dla każdego użytkownika zmieniają się w losowych odstępach czasu τ. W stałych odstępach
czasu s stacja bazowa przydziela użytkownikom bloki zasobów zgodnie z algorytmem A Round Robin. Użytkownikowi można przydzielić jednocześnie nie więcej niż l bloków zasobów. 
Dodatkowo każda transmisja może zakończyć się błędem z prawdopodobieństwem ε. W takim przypadku dane należy przesyłać aż do momentu, kiedy zostaną poprawnie odebrane. 
Po odebraniu wszystkich danych, użytkownik jest usuwany z systemu.
Opracuj symulator sieci bezprzewodowej zgodnie z metodą planowania zdarzeń.

● Za pomocą symulacji wyznacz intensywność zgłoszeń λ, która zapewnia średni czas oczekiwania nie większy niż 50 ms, oraz:

o średnią przepływność systemu mierzoną liczbą danych przesłanych poprawnie przez stację bazową w jednostce czasu,
o średnią przepływność użytkownika mierzoną liczbą danych odebranych poprawnie od stacji bazowej w jednostce czasu, uśrednioną po wszystkich użytkownikach sieci; ta wartość uwzględnia okresy kiedy użytkownik nie miał przydzielonego żadnego bloku
zasobów,
o średni czas oczekiwania, tzn. czas między pojawieniem się użytkownika w sieci, a zakończeniem odbierania danych,
o histogram średnich przepływności dla wszystkich użytkowników sieci.
● Sporządź wykres zależności średniej przepływności systemu oraz średniego czasu oczekiwania w funkcji wartości λ.
● Porównaj wyniki z osobą implementującą inny algorytm przydziału zasobów, z inną maksymalną liczbą bloków zasobów przypisaną pojedynczemu użytkownikowi l, lub z inną liczbą
dostępnych bloków zasobów k.
