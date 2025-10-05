
# Laborator POO 2025-2026, semestrul I
Laborator de Programare Orientată pe Obiecte, Facultatea de Matematică și Informatică @ Universitatea din București

### Acknowledgements
> Mulțumiri lui [@mcmarius](https://github.com/mcmarius) pentru materialele puse la dispoziție pentru buna desfășurare a acestui laborator!

## Cuprins
1. [Despre Evaluare](#despre-evaluare)
2. [Despre Prezențe](#despre-prezențe)
3. [Despre Proiect](#despre-proiect)
4. [Despre Colocviu](#despre-colocviu)
5. [Calendar Laborator](#calendar-activități)
6. [Materiale Laborator](#materiale-laborator)
7. [Alte Materiale Utile](#alte-materiale-utile)
8. [Contact](#contact)


## Despre Evaluare
Componenta de laborator reprezintă **50%** din nota finală de la această disciplină. Ea se obține din alte două sub-componente: *o parte practică* (care se va implementa pe parcursul întregului semestru) și *un colocviu* (la final de semestru).

Fiecare dintre cele două componente ale laboratorului valorează câte **50%** din nota de laborator. Altfel spus, notarea la această disciplină se face în felul următor:

- 50% examen de curs;
- **25% proiect (P)** - *aici vom lucra noi*;
- **25% colocviu de laborator (C)** - *aici vom lucra noi*;
- **0.5 puncte bonus din seminar (S)** - *aici vom lucra noi*.

Notele maxime pe care le puteți obține în cadrul acestui laborator:

- **P = max. 12 puncte** (2p reprezintă *bonus*);
- **C = max. 1x puncte** (*rămâne de stabilit conform baremului*).

---
Există prag pentru fiecare componentă a evaluarii:

```cpp
    nota_P = evaluare_proiect(P1, P2, P3, bonus_P);
    if (nota_P < 5) {
        return "PICAT LA POO! Nu mergem la colocviu... :(";
    } // dacă luăm peste 5, mergem mai departe la colocviu

    nota_C = evaluare_colocviu(C, bonus_C);
    if (nota_C < 5) {
        return "PICAT LA POO! Nu mergem la examenul de curs... :(";
    } // dacă luăm peste 5, mergem mai departe la examenul de curs

    nota_curs = evaluare_curs(curs);
    if (nota_curs < 5) {
        return "PICAT LA POO! :(";
    }

    return "TRECUT LA POO! :);
```

## Despre Prezențe
- În cadrul laboratorului ***SUNT* obligatorii minim 10 prezențe**.
- În cazul seminarului, prezențele nu sunt obligatorii, dar *sunt recomandate*.

Voi face prezența, voi nota și activitatea: *pot (nu garantez) ține cont de aceste aspecte și la evaluare*.

**Este obligatoriu** să fiți prezenți la orele de prezentări în care se va evalua munca depusă în cadrul componentei practice. Dacă nu veniți la prezentările de proiecte, veți primi **0 puncte** pe milestone-ul respectiv:

```cpp
    P1 = prezent_P1 ? evaluare_P1() : 0;
    P2 = prezent_P2 ? evaluare_P2() : 0;
    P3 = prezent_P3 ? evaluare_P3() : 0;
    bonus_P = evaluare_bonus_P();
    // nota finala proiect
    nota_P = evaluare_proiect(P1, P2, P3, bonus_P);
```

Calendarul activităților se regăsește [aici](#calendar-laborator).

### ALTE REGULI IMPORTANTE!
- Prezența la laborator **NU** garantează promovarea acestuia!

- **NU** se acceptă prezentarea proiectului la final de semestru: **(P = 0)**.

- Pentru întârzieri se aplică penalizări: **(2.5p / laborator de întârizere)**.

- Pentru neîntrunirea numărului de prezențe se aplică penalizări, după cum urmează:

    ```cpp
        nof_prezente = get_nof_prezente();
        if (nof_prezente >= 10) return;

        // calculeaza coeficientul de penalizare
        nof_absente = 10 - nof_prezente;
        coef_penalizare = (nof_absente < 4) ? 1.5 : 2.0;

        // calculeaza nota finala
        nota_P = nota_P - nof_absente * coef_penalizare;
    ```

> Acest laborator este o componentă mai mult autodidactă. Sunteți responsabili *(într-o oarecare măsură)* pentru succesul vostru la colocviu.

## Despre Proiect
Componenta practică a acestui laborator constă în realizarea unui proiect care îndeplinește o serie de cerințe.

Temele de proiect se pot alege în mod independent. Nu sunt restricții, însă trebuie să vă asigurați că aceste criterii pot fi îndeplinite prin tema pe care decideți să o alegeți.

Există această pagină în care puteți observa câteva idei de teme care au fost alese în trecut: [HoF.md](https://github.com/mcmarius/poo/blob/master/HoF.md). **Există și proiecte interzise!**

***
Etapele de realizare a acestei componente sunt:

[Configurarea mediului de lucru](https://github.com/mcmarius/poo/tree/master/env)

[Milestone 1](https://github.com/mcmarius/poo/tree/master/tema-1) - **compunere, constructori, cc, op=, destr, op<<**

[Milestone 2](https://github.com/mcmarius/poo/tree/master/tema-2) - **moștenire, virtual, excepții, dynamic_cast**

[Milestone 3](https://github.com/mcmarius/poo/tree/master/tema-3) - **templates (șabloane), design patterns (șabloane de proiectare)**

> Găsiți informații utile în fișierele markdown aferente fiecărui milestone. Vă recomand să treceți prin acestea.

Bonusul pentru proiect se acordă pentru cele mai faine proiecte din grupa respectivă:
- 1-2 bonusuri de 2 puncte;
- 1-2 bonusuri de 1.5 puncte;
- 1-2 bonusuri de 1 punct;
- 1-2 bonusuri de 0.5 puncte.

Proiectele trebuie să fie ceva mai complexe în comparație cu restul proiectelor din grupă. Nu este obligatoriu ca acest bonus să fie acordat cuiva, acesta fiind acordat doar dacă proiectul chiar este complex.

***

Pentru gestionarea și evaluarea facilă a proiectului, se va utiliza un [template](https://github.com/tibmax01/oop-template). Detalii despre acesta puteți găsi [aici](https://github.com/mcmarius/poo/blob/master/env/setup.md).

***

Evaluarea proiectului se face pentru fiecare milestone. Acestă evaluare constă în prezentarea + explicarea, în câteva minute, a progresului din respectivul milestone, într-o serie de întrebări la care trebuie să răspundeți.

După fiecare feedback, aveți șansa să vă reparați o parte din muncă. Acest lucru poate afecta nota **pozitiv** sau ***negativ***, în funcție de ce ați făcut sau nu ați făcut în urma feedback-ului primit: *nu puteți primi punctajul maxim, ci doar un mic punctaj parțial*.

> În cazul în care nu respectați cerințele generale impuse în template sau veniți la cu întârziere **NU acord feedback**, ci direct nota.

## Despre Colocviu
Colocviul reprezintă un examen de laborator prin care vi se vor testa conoștințele dobândite în cadrul acestui laborator prin implementarea unor cerințe folosind tehnici POO.

Mai multe detalii, vor fi anunțate în proximitatea acestuia. Până atunci, câteva sfaturi pentru colocviu puteți găsi [aici](https://github.com/mcmarius/poo/blob/master/colocviu/README.md).

## Calendar Activități
| Activitate         | Săptămâna         | Calendar          | Action Item     |
| :----------------: | :---------------: | :---------------: | :-------------: |
| Laborator 1 (263)  | Săptămâna 1       | 29 septembrie     | pierdut         |
| Laborator 1 (262)  | Săptămâna 1       | 30 septembrie     | pierdut         |
| Seminar 1 (263)    | Saptămâna 1       | 30 septembrie     | pierdut         |
|                                                                              |
| Laborator 2 (263)  | Săptămâna 2       | 6 octombrie       | N/A             |
| Laborator 2 (262)  | Săptămâna 2       | 7 octombrie       | N/A             |
| Seminar 1 (264)    | Saptămâna 2       | 7 octombrie       | N/A             |
|                                                                              |
| Laborator 3 (263)  | Săptămâna 3       | 13 octombrie      | N/A             |
| Laborator 3 (262)  | Săptămâna 3       | 14 octombrie      | N/A             |
| Seminar 2 (263)    | Saptămâna 3       | 14 octombrie      | N/A             |
|                                                                              |
| Laborator 4 (263)  | Săptămâna 4       | 20 octombrie      | de reprogramat! |
| Laborator 4 (262)  | Săptămâna 4       | 21 octombrie      | de reprogramat! |
| Seminar 2 (264)    | Saptămâna 4       | 21 octombrie      | de reprogramat! |
|                                                                              |
| Laborator 5 (263)  | Săptămâna 5       | 27 octombrie      | M1 - de reprogramat! |
| Laborator 5 (262)  | Săptămâna 5       | 28 octombrie      | M1 - de reprogramat! |
| Seminar 3 (263)    | Saptămâna 5       | 28 octombrie      | de reprogramat! |
|                                                                              |
| Laborator 6 (263)  | Săptămâna 6       | 3 noiembrie       | de reprogramat! |
| Laborator 6 (262)  | Săptămâna 6       | 4 noiembrie       | N/A             |
| Seminar 3 (264)    | Saptămâna 6       | 4 noiembrie       | N/A             |
|                                                                              |
| Laborator 7 (263)  | Săptămâna 7       | 10 noiembrie      | N/A             |
| Laborator 7 (262)  | Săptămâna 7       | 11 noiembrie      | N/A             |
| Seminar 4 (263)    | Saptămâna 7       | 11 noiembrie      | N/A             |
|                                                                              |
| Laborator 8 (263)  | Săptămâna 8       | 17 noiembrie      | N/A             |
| Laborator 8 (262)  | Săptămâna 8       | 18 noiembrie      | N/A             |
| Seminar 4 (264)    | Saptămâna 8       | 18 noiembrie      | N/A             |
|                                                                              |
| Laborator 9 (263)  | Săptămâna 9       | 24 noiembrie      | M2              |
| Laborator 9 (262)  | Săptămâna 9       | 25 noiembrie      | M2              |
| Seminar 5 (263)    | Saptămâna 9       | 25 noiembrie      | N/A             |
|                                                                              |
| Laborator 10 (263) | Săptămâna 10      | 1 decembrie       | pierdut         |
| Laborator 10 (262) | Săptămâna 10      | 2 decembrie       | N/A             |
| Seminar 5 (264)    | Saptămâna 10      | 2 decembrie       | N/A             |
|                                                                              |
| Laborator 11 (263) | Săptămâna 11      | 8 decembrie       | N/A             |
| Laborator 11 (262) | Săptămâna 11      | 9 decembrie       | N/A             |
| Seminar 6 (263)    | Saptămâna 11      | 9 decembire       | N/A             |
|                                                                              |
| Laborator 12 (263) | Săptămâna 12      | 15 decembrie      | N/A             |
| Laborator 12 (262) | Săptămâna 12      | 16 decembrie      | N/A             |
| Seminar 6 (264)    | Saptămâna 12      | 16 decembrie      | N/A             |
|                                                                              |
| Laborator 13 (263) | Săptămâna 13      | 22 decembrie      | N/A             |
| Laborator 13 (262) | Săptămâna 13      | 23 decembrie      | N/A             |
| Seminar 7 (263)    | Saptămâna 13      | 23 decembire      | N/A             |
|                                                                              |
| Vacanță         | Vacanță              | 24.12 - 04.01     | Vacanță         |
|                                                                              |
| Laborator 14 (263) | Săptămâna 14      | 5 ianuarie        | N/A             |
| Laborator 14 (262) | Săptămâna 14      | 6 ianuarie        | pierdut         |
| Seminar 7 (264)    | Saptămâna 14      | 6 ianuarie        | pierdut         |
|                                                                              |
| Laborator 15 (263) | Săptămâna 15      | 12 ianuarie       | M3              |
| Laborator 15 (262) | Săptămâna 15      | 13 ianuarie       | M3              |
| Seminar 8 (263)    | Saptămâna 15      | 13 ianuarie       | N/A             |

## Materiale Laborator
Materialele și codurile utilizate în cadrul laboratoarelor pot fi găsite [aici](https://github.com/tibmax01/oop-lab/tree/main/materiale/).

## Alte Materiale Utile
În repo-ul lui Marius găsiți o multitudine de informații structurate pe categorii. Pentru a vă fi mai ușor, las aici câte un link pentru fiecare dintre acestea:

- [Resurse](https://github.com/mcmarius/poo/blob/master/README.md#resurse)
- [Exerciții](https://github.com/mcmarius/poo/tree/master/exercitii)
- [Erori frecvente](https://github.com/mcmarius/poo/blob/master/erori.md)
- [Observații](https://github.com/mcmarius/poo/blob/master/obs.md)
- [Biblioteci externe](https://github.com/mcmarius/poo/blob/master/libs)

## Contact
Pentru orice problemă pe care o întâmpinați, mă puteți contacta pe Teams și vă voi răspunde cât mai repede posibil.

#### License
[The Unlicense](https://github.com/MaximTiberiu/oop-lab/blob/main/LICENSE)

