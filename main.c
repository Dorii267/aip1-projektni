#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
int main()
{
    int izbor;

    while (1)
    {
        printf("Dobrodošli u Damu\n");
        printf("Kako bi ovaj kod radio tema mora biti svijetla!!!\n");
        printf("1. Start\n");
        printf("2. Meni\n");
        printf("3. Izlaz\n");
        scanf("%d", &izbor);

        if (izbor == 1)
        {
            printf("Poštovanje, započeli ste igru Dame\n");
        }
        else if (izbor == 2)
        {
            printf("Današnji meni: (Vau puno opcija!)\n");
            printf("Kako igrati?\n");
            printf("1. Prvi igrač je crven(🔴).\n");
            printf("2. Oba igrača se kreću na način da upisuju početni red i stupac, a zatim red i stupac u koji se žele pomaknuti.\n");
            printf("3. Kada pijun igrača dođe do zadnjeg reda pijun će se pretvoriti u damu.\n");
            printf("4. Dama se može slobodno kretati (lijevo, desno, gore, dolje, dijagonale...)");
            printf("5. Dama jede protivničke pijune");
            printf("6. Cilj je pojesti sve protivničke pijune");
        }

        else if (izbor == 3)
        {
            printf("Izlaz iz programa!\n");
            break;
        }
    }

    int ploca[8][8] = {0};

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if ((i + j) % 2 == 0)
            {
                if (i < 3)
                {
                    ploca[i][j] = 1; // Crveni igrač 🔴
                }
                else if (i > 4)
                {
                    ploca[i][j] = 2; // Crni igrač ⚫
                }
            }
        }
    }

    int trenutniigrac = 1;
    int zavrsetak = 0;

    while (!zavrsetak)
    {
        // ploca ⬛⬜
        printf("   ");

        for (int j = 0; j < 8; j++)
        {
            printf("%2d ", j + 1);
        }

        printf("\n");

        for (int i = 0; i < 8; i++)
        {
            printf("%2d ", i + 1);

            for (int j = 0; j < 8; j++)
            {
                if ((i + j) % 2 == 0)
                {
                    if (ploca[i][j] == 1)
                    {
                        printf("🔴 ");
                    }

                    else if (ploca[i][j] == 2)
                    {
                        printf("⚫ ");
                    }

                    else if (ploca[i][j] == 3)
                    {
                        printf("🟠 ");
                    }

                    else if (ploca[i][j] == 4)
                    {
                        printf("🟤 ");
                    }

                    else
                    {
                        printf("⬛ ");
                    }
                }

                else
                {
                    printf("⬜ ");
                }
            }

            printf("\n");
        }

        // kretanje
        int izred, izstupac, ured, ustupac;
        int trenutni_igrac = trenutniigrac;

        if (trenutni_igrac == 3)
            trenutni_igrac = 1;
        if (trenutni_igrac == 4)
            trenutni_igrac = 2;

        printf("Igrac(%d) (1=🔴, 2=⚫), Unesite potez (red stupac red stupac): ", trenutni_igrac);
        scanf("%d %d %d %d", &izred, &izstupac, &ured, &ustupac);

        // micanje 0 reda i stupca
        izred--;
        izstupac--;
        ured--;
        ustupac--;

        // provjera poteza
        if (izred >= 0 && izred < 8 && izstupac >= 0 && izstupac < 8 &&
            ured >= 0 && ured < 8 && ustupac >= 0 && ustupac < 8 &&
            (izred + izstupac) % 2 == 0 && (ured + ustupac) % 2 == 0 &&
            (ploca[izred][izstupac] == trenutniigrac ||
             (trenutniigrac == 1 && ploca[izred][izstupac] == 3) ||
             (trenutniigrac == 2 && ploca[izred][izstupac] == 4)) &&
            ploca[ured][ustupac] == 0)
        {
            int novired = ured - izred;
            int novistupac = ustupac - izstupac;
            int jeDama = (ploca[izred][izstupac] == 3 || ploca[izred][izstupac] == 4);

            // Dama
            if (jeDama && abs(novistupac) == abs(novired))
            {
                int potezred, potezstupac;

                if (novired > 0)
                {
                    potezstupac = 1;
                }

                else
                {
                    potezred = -1;
                }

                if (novistupac > 0)
                {
                    potezstupac = 1;
                }

                else
                {
                    potezstupac = -1;
                }

                int Pijunnaputu = 0;
                int redjedenja = -1, stupacjedenja = -1;

                // provjera puta
                int r = izred + potezred;
                int s = izstupac + potezstupac;
                while (r != ured && s != ustupac)
                {
                    if (ploca[r][s] != 0)
                    {
                        Pijunnaputu++;
                        redjedenja = r;
                        stupacjedenja = s;
                    }
                    r += potezred;
                    s += potezstupac;
                }

                // potez dame
                if (Pijunnaputu == 0)
                {
                    ploca[ured][ustupac] = ploca[izred][izstupac];
                    ploca[izred][izstupac] = 0;

                    // mijenjanje igrača
                    if (trenutniigrac == 1 || trenutniigrac == 3)
                    {
                        trenutniigrac = 2;
                    }

                    else
                    {
                        trenutniigrac = 1;
                    }
                }
                // jedenje dame
                else if (Pijunnaputu == 1)
                {
                    int protivnik;
                    if (trenutniigrac == 1 || trenutniigrac == 3)
                    {
                        protivnik = 2;
                    }

                    else
                    {
                        protivnik = 1;
                    }

                    int protivnikDama = protivnik + 2;

                    if (ploca[redjedenja][stupacjedenja] == protivnik ||
                        ploca[redjedenja][stupacjedenja] == protivnikDama)
                    {
                        ploca[ured][ustupac] = ploca[izred][izstupac];
                        ploca[izred][izstupac] = 0;
                        ploca[redjedenja][stupacjedenja] = 0;
                        printf("Pojeden protivnicki pijun!\n");

                        // mijenjanje igrača
                        if (trenutniigrac == 1 || trenutniigrac == 3)
                        {
                            trenutniigrac = 2;
                        }

                        else
                        {
                            trenutniigrac = 1;
                        }
                    }

                    else
                    {
                        printf("Možete preskociti samo protivnicke pijune!\n");
                    }
                }

                else
                {
                    printf("Neispravan potez! Dama može preskočiti samo jedan protivnički pijun.\n");
                }
            }

            // običan potez
            else if (abs(novistupac) == 1 && abs(novired) == 1)
            {
                if (jeDama ||
                    (trenutniigrac == 1 && novired == 1) ||
                    (trenutniigrac == 2 && novired == -1))
                {
                    // provjera poteza
                    ploca[ured][ustupac] = ploca[izred][izstupac];
                    ploca[izred][izstupac] = 0;

                    // promocija dame
                    if (!jeDama)
                    {
                        if ((ploca[ured][ustupac] == 1 && ured == 7) ||
                            (ploca[ured][ustupac] == 2 && ured == 0))
                        {
                            ploca[ured][ustupac] += 2; // 1 u 3 ili 2 u 4
                            printf("Pijun je postao dama!\n");
                        }
                    }

                    // mijenja igrača
                    if (trenutniigrac == 1 || trenutniigrac == 3)
                    {
                        trenutniigrac = 2;
                    }

                    else
                    {
                        trenutniigrac = 1;
                    }
                }

                else
                {
                    printf("Neispravan smjer kretanja!\n");
                }
            }
            // jedenje
            else if (abs(novistupac) == 2 && abs(novired) == 2)
            {
                int srednjiRed = izred + novired / 2;
                int srednjiStupac = izstupac + novistupac / 2;
                int protivnik;

                if (trenutniigrac == 1 || trenutniigrac == 3)
                {
                    protivnik = 2;
                }

                else
                {
                    protivnik = 1;
                }

                int protivnikDama = protivnik + 2;

                if (ploca[srednjiRed][srednjiStupac] == protivnik ||
                    ploca[srednjiRed][srednjiStupac] == protivnikDama)
                {
                    // uzimanje pijuna
                    ploca[ured][ustupac] = ploca[izred][izstupac];
                    ploca[izred][izstupac] = 0;
                    ploca[srednjiRed][srednjiStupac] = 0;

                    printf("Pojeden protivnicki pijun!\n");

                    // mijenjaje dame
                    if (!jeDama)
                    {
                        if ((ploca[ured][ustupac] == 1 && ured == 7) ||
                            (ploca[ured][ustupac] == 2 && ured == 0))
                        {
                            ploca[ured][ustupac] += 2; // 1 u 3 or 2 u 4
                            printf("Pijun je postao dama!\n");
                        }
                    }

                    // mijenjanje igaca
                    if (trenutniigrac == 1 || trenutniigrac == 3)
                    {
                        trenutniigrac = 2;
                    }

                    else
                    {
                        trenutniigrac = 1;
                    }
                }

                else
                {
                    printf("Možete preskociti samo protivnicke pijune!\n");
                }
            }

            else
            {
                printf("Neispravan potez! Pijuni se moraju kretati dijagonalno.\n");
            }
        }

        else
        {
            printf("Neispravan potez! Provjerite unesene pozicije.\n");
        }
    }

    return 0;
}