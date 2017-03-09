# v2.0

1. 2 tablice 1-wymiarowe 
struct:
  - wiersze 
  - kolumny
  - dane
2. przepisywanie krawędzi na ukrytą ramkę dookoła
3. wczytywanie:
  - 0 i 1 
  - współrzędne
  - bitmapa
  - png
4. zapis to samo?
  - bitmapa--;
  - gif++;

> ./life -typ_sąsiedztwa[N,M] <liczba_generacji> -input_method[c,b,p] \<input\> -output_method[c,b,p] \<output\> [-g \<gif_name\>]

Podział plików:
- main.c
- grid_struct.h
- simulator.c?h
- neighbours.c?h
- png_rw.c?h
- bin_rw.c?h
- crs_rw.c?h
- gif.c?h?