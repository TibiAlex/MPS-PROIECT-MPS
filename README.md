# MPS-PROIECT-MPS
PROIECT MPS
* Google Drive: https://drive.google.com/drive/folders/1-G8h9piH-X3IQZn_m17fs_1DVSkWlBGU?usp=sharing

# Echipa:
Product Manager: Iordache Ionut 343C2<br/>
Tech Leader: Grigoras Adrian 344C2<br/>
Tester: Basaraba Razvan 341C2<br/>
Developer: Buzera Tiberiu 341C2<br/>
Ledezeu: Robert Andrei 343C2<br/>

![msedge_KtfaprshqE](https://user-images.githubusercontent.com/56930275/199531630-030e0ae0-58e8-41df-b86b-1b43bfce72ff.png)

# Scopul Proiectului
Gasirea unui algoritm ce obtime in urma unor calcule asupra mai multor seturi de date (15 reultate a 15 algoritmi de stergere a background-ului dintr-o poza pentru a ramane doar textul) un rezultat cat mai apropiat posibil de o valoare primita la input. Algoritmul trebuie sa fie precis pentru toate seturile de date, de asemenea acesta trebuie sa aibe o complexitate temporala buna. In functie de rezultatul obtinut, se va calcula o valoare cu formula: floor(result * 255) care va fi asociat cu un scor. Scopul final al priectului este obtinerea unui scor cat mai bun.

# Descrierea proiectului
Crearea unui algoritm ce citeste seturile de date de intrare din fisierele .csv, si anume valoarea ideala a threshhold-ului si cele 15 valori obtinute prin folosirea a 15 algoritmi diferiti. Dupa care se vor incerca operatii pe seturile de date astfel incat sa se obtina un rezultat cat mai apropiat de cel ideal odata aplicat pe toate seturile de date. In final se calculeaza scorul obtinut.

## Binarizare globală
Binarizarea globală reprezintă aplicarea unui singur prag de binarizare pe întreaga imagine și transformarea pixelilor din cadrul acesteia în valori de alb (255) sau negru (0) în funcție de valoarea pragului.
Soluția primește la intrare un set de fișiere în format CSV. Fișierele conțin informații de binarizare asociate unui set de imagini. Soluția prelucrează acest set de date, combină multitudinea de praguri de binarizare asociate fiecărei imagini sub forma unui arbore care are drept frunze pragurile de binarizare utilizate, drept noduri diverse operații programatice pentru combinarea acestora (if, else, for etc.) iar drept rădăcină un prag de binarizare final rezultat în urma aplicării acestor operații.

### Input binarizare globală
- set de fișiere în format CSV
- fiecare fișier este asociat unei imagini din setul de date
  - fișierele vor conține următoarele intrări:
  - un număr de praguri de binarizare obținute în urma rulării unei varietăți de algoritmi euristici (e.g. Otsu, Niblack etc.)
  - un prag de binarizare considerat optim pentru imaginea respectivă
  - 256 de valori care reprezintă F-measure obținut prin aplicarea unui prag de binarizare în acel punct în cadrul histogramei (valorile sunt normate în intervalul 0-1)
- Observații
  - setul de date nu conține imagini, toate informațiile necesare obținerii unui output valid, precum și metrici pentru evaluarea acestora pentru a determina care este cel mai bun sunt incluse în CSV-uri
  - F-measure = TP/(TP+0.5*(FP+FN)), metrică pentru măsurarea acurateții unei operații de binarizare (rezultatul este evaluat contra unei imagini de ground truth)
    - TP = true positives - pixeli clasificați “albi” care sunt albi în ground truth
    - FP = false positives - pixeli clasificați “albi” care sunt negri în ground truth
    - TN = true negatives - pixeli clasificați “negri” care sunt negri în ground truth
    - FN = false negatives - pixeli clasificați “negri” care sunt albi în ground truth
    
## Binarizare locală
Soluția pentru binarizarea locală presupune aplicarea unei valori prag diferită pentru ferestre determinate din cadrul imaginii.

### Input binarizare locală
- set de fișiere în format CSV
- fiecare fișier este asociat unei imagini din data set
- fișierele conțin următoarele date:
  - pixelii din cadrul imaginii și valorile lor, fiecărui pixel îi este asociată ca și intrare în fișier:
    - pragurile obținute de algoritmi pentru pixelul respectiv
    - valoarea pixelului în imaginea de ground truth
### Output soluții
- fișier text care să conțină modul de generare al arborelui de operații programatice
- poate fi un set de caractere unde fiecare caracter reprezintă o anumită operație utilizată, în acest caz se recomandă folosirea unui dicționar care să mapeze setul de caractere peste setul de operații utilizat
- se recomandă utilizarea următorilor operatori:
  - AND/OR
  - IF/ELSE
  - FOR
    - Pot fi adăugați și alți operatori.
   
## Concepte
**Binarizarea** este preprocesarea imagini ce presupune clasificarea pixelilor în două categorii: pixel de fundal și pixeli ce conțin obiectul (text sau alte obiecte), fiind o metodă de segmentare.

**Thresholding** sau nivel/valoare de prag este folosit pentru determinarea clasei unui pixel.

**Histograma** redă distribuția nivelurilor de gri din imagine. Este funcția care asociază fiecărui nivel de gri frecvența de apariție în imagine.

**Ground** truth este imaginea ideală binarizată asociată imaginii de input. Aceasta este folosită pentru evaluarea performanței algoritmului aplicat.


## Task-uri
- [x] setare repo pe github
- [x] implementare diagrama Gantt
- [x] implementare diagrama wbs
- [x] organizare la nivel de echipa
- [x] alegerea metodologia de dezvotare folosita
- [ ] creare raport text organizare
- [ ] cercetare asupra algoritmului MonteCarlo
- [ ] citire set de date din fisierele .csv
- [ ] implementarea unui algoritm ineficient
- [ ] gasirea de optimizari asupra algoritmului
