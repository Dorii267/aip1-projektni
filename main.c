#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>

int CRVENI = 1;
int ZELENI = 2;
int DAMA_CRVENI = 3;
int DAMA_ZELENI = 4;

int ispisiPlocu(int ploca[8][8])
{
    int red, stupac;

    printf("   ");

    for (stupac = 0; stupac < 8; stupac++)
    {
        printf("%2d ", stupac + 1);
    }

    printf("\n");

    for (red = 0; red < 8; red++)
    {
        printf("%2d ", red + 1);

        for (stupac = 0; stupac < 8; stupac++)
        {
            if ((red + stupac) % 2 == 0)
            {
                if (ploca[red][stupac] == CRVENI)
                {
                    printf("🔴 ");
                }

                else if (ploca[red][stupac] == ZELENI)
                {
                    printf("🟢 ");
                }

                else if (ploca[red][stupac] == DAMA_CRVENI)
                {
                    printf("🟠 ");
                }

                else if (ploca[red][stupac] == DAMA_ZELENI)
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

    printf("\n");
    return 0;
}

int promijeniIgraca(int trenutni_igrac)
{
    if (trenutni_igrac == CRVENI || trenutni_igrac == DAMA_CRVENI)
    {
        return ZELENI;
    }

    else
    {
        return CRVENI;
    }
}

int imaFigure(int ploca[8][8], int igrac)
{
    for (int red = 0; red < 8; red++)
    {
        for (int stupac = 0; stupac < 8; stupac++)
        {
            if (ploca[red][stupac] == igrac || ploca[red][stupac] == igrac + 2)
            {
                return 1;
            }
        }
    }
    return 0;
}

int main()
{
    int izbor;
    char ime1[100], ime2[100];

    printf("Unesite ime igraca 1: ");
    fgets(ime1, 100, stdin);
    ime1[strcspn(ime1, "\n")] = '\0';

    printf("Unesite ime igraca 2: ");
    fgets(ime2, 100, stdin);
    ime2[strcspn(ime2, "\n")] = '\0';

    while (1)
    {
        printf("Dobrodošli u Damu\n");
        printf("Kako bi ovaj kod radio, tema mora biti svijetla!!!\n");
        printf("1. Start\n");
        printf("2. Meni\n");
        printf("3. Pravila\n");
        printf("4. Izlaz\n");
        printf("Unesite svoj izbor (1-4): ");

        char unos[100];
        fgets(unos, sizeof(unos), stdin);
        if (sscanf(unos, "%d", &izbor) != 1)
        {
            printf("Neispravan unos! Unesite broj od 1 do 4.\n\n");
            continue;
        }

        if (izbor == 1)
        {
            printf("\nPoštovanje, započeli ste igru Dame\n\n");
            break;
        }

        else if (izbor == 2)
        {
            printf("\n=== Meni ===\n");
            printf("Prvi igrač je crven (🔴), a drugi zelen (🟢).\n");
            printf("Oba igrača se kreću upisivanjem početne i krajnje pozicije.\n");
            printf("Kada pijun dođe do zadnjeg reda, postaje dama.\n");
            printf("Dama se može kretati dijagonalno u svim smjerovima.\n");
            printf("Dama jede protivničke pijune.\n");
            printf("Cilj je pojesti ili blokirati sve protivničke pijune.\n\n");
        }

        else if (izbor == 3)
        {
            printf("\n=== Pravila igre ===\n");
            printf("Igra se na 8x8 ploči.\n");
            printf("Svaki igrač ima 12 pijuna.\n");
            printf("Pijuni se kreću dijagonalno prema naprijed.\n");
            printf("Ako je protivnički pijun ispred, a iza njega prazno polje, skače se.\n");
            printf("Skakanje je moguće, ali nije obavezno.\n");
            printf("Dama se kreće dijagonalno naprijed i unatrag.\n");
            printf("Može pojesti protivničke figure u oba smjera.\n\n");
        }

        else if (izbor == 4)
        {
            printf("\nIzlaz iz programa. Doviđenja!\n");
            return 0;
        }

        else
        {
            printf("\nNepoznata opcija! Unesite broj od 1 do 4.\n\n");
        }
    }

    int ploca[8][8] = {0};

    for (int red = 0; red < 8; red++)
    {
        for (int stupac = 0; stupac < 8; stupac++)
        {
            if ((red + stupac) % 2 == 0)
            {
                if (red < 3)
                {
                    ploca[red][stupac] = CRVENI;
                }

                else if (red > 4)
                {
                    ploca[red][stupac] = ZELENI;
                }
            }
        }
    }

    int trenutni_igrac = CRVENI;

    while (1)
    {
        ispisiPlocu(ploca);

        if (!imaFigure(ploca, trenutni_igrac))
        {
            if (trenutni_igrac == CRVENI || trenutni_igrac == DAMA_CRVENI)
            {
                printf("\033[0;31mIgrac %s nema vise figura. Igra zavrsena!\033[0m\n", ime1);
                printf("\033[0;32mPobjednik je %s\033[0m\n", ime2);
            }

            else
            {
                printf("\033[0;32mIgrac %s nema vise figura. Igra zavrsena!\033[0m\n", ime2);
                printf("\033[0;31mPobjednik je %s\033[0m\n", ime1);
            }
            break;
        }

        int red_pocetak, stupac_pocetak, red_kraj, stupac_kraj;
        int ispravan_unos = 0;

        while (!ispravan_unos)
        {
            if (trenutni_igrac == CRVENI || trenutni_igrac == DAMA_CRVENI)
            {
                printf("\033[0;31m%s (🔴), Unesite potez (red stupac red stupac): \033[0m", ime1);
            }

            else
            {
                printf("\033[0;32m%s (🟢), Unesite potez (red stupac red stupac): \033[0m", ime2);
            }

            char unos[100];
            fgets(unos, sizeof(unos), stdin);

            if (sscanf(unos, "%d %d %d %d", &red_pocetak, &stupac_pocetak, &red_kraj, &stupac_kraj) != 4)
            {
                printf("Neispravan unos! Unesite 4 broja (npr. '2 3 3 4').\n");
                continue;
            }

            red_pocetak--;
            stupac_pocetak--;
            red_kraj--;
            stupac_kraj--;

            if (red_pocetak < 0 || red_pocetak >= 8 || stupac_pocetak < 0 || stupac_pocetak >= 8 ||
                red_kraj < 0 || red_kraj >= 8 || stupac_kraj < 0 || stupac_kraj >= 8)
            {
                printf("Neispravne koordinate! Unesite brojeve od 1 do 8.\n");
                continue;
            }

            if ((red_pocetak + stupac_pocetak) % 2 != 0 || (red_kraj + stupac_kraj) % 2 != 0)

            {
                printf("Potez mora biti na tamnim poljima!\n");
                continue;
            }

            int figura_sa = ploca[red_pocetak][stupac_pocetak];

            if (figura_sa != trenutni_igrac && figura_sa != trenutni_igrac + 2)
            {
                printf("Na odabranoj početnoj poziciji nema vaše figure!\n");
                continue;
            }

            if (ploca[red_kraj][stupac_kraj] != 0)
            {
                printf("Ciljna pozicija nije prazna!\n");
                continue;
            }

            ispravan_unos = 1;
        }

        int figura_sa = ploca[red_pocetak][stupac_pocetak];
        int razlika_red = red_kraj - red_pocetak;
        int razlika_stupac = stupac_kraj - stupac_pocetak;
        int apsolutna_razlika_red = abs(razlika_red);
        int apsolutna_razlika_stupac = abs(razlika_stupac);

        // Pravila za pijuna crvenog
        if (figura_sa == CRVENI)
        {
            if (apsolutna_razlika_red == 1 && apsolutna_razlika_stupac == 1 && razlika_red == 1)
            {
                ploca[red_kraj][stupac_kraj] = figura_sa;
                ploca[red_pocetak][stupac_pocetak] = 0;
            }

            else if (apsolutna_razlika_red == 2 && apsolutna_razlika_stupac == 2 && razlika_red == 2)
            {
                int red_skok = red_pocetak + 1;
                int stupac_skok = stupac_pocetak + (razlika_stupac / 2);

                if (ploca[red_skok][stupac_skok] == ZELENI || ploca[red_skok][stupac_skok] == DAMA_ZELENI)
                {
                    ploca[red_kraj][stupac_kraj] = figura_sa;
                    ploca[red_pocetak][stupac_pocetak] = 0;
                    ploca[red_skok][stupac_skok] = 0;
                }

                else
                {
                    printf("Nema protivničke figure za preskakanje!\n");
                    continue;
                }
            }

            else
            {
                printf("Neispravan potez za crveni pijun!\n");
                continue;
            }
        }
        // Pravila za pijuna zelenog
        else if (figura_sa == ZELENI)
        {
            if (apsolutna_razlika_red == 1 && apsolutna_razlika_stupac == 1 && razlika_red == -1)
            {
                ploca[red_kraj][stupac_kraj] = figura_sa;
                ploca[red_pocetak][stupac_pocetak] = 0;
            }

            else if (apsolutna_razlika_red == 2 && apsolutna_razlika_stupac == 2 && razlika_red == -2)
            {
                int red_skok = red_pocetak - 1;
                int stupac_skok = stupac_pocetak + (razlika_stupac / 2);

                if (ploca[red_skok][stupac_skok] == CRVENI || ploca[red_skok][stupac_skok] == DAMA_CRVENI)
                {
                    ploca[red_kraj][stupac_kraj] = figura_sa;
                    ploca[red_pocetak][stupac_pocetak] = 0;
                    ploca[red_skok][stupac_skok] = 0;
                }

                else
                {
                    printf("Nema protivničke figure za preskakanje!\n");
                    continue;
                }
            }

            else
            {
                printf("Neispravan potez za zeleni pijun!\n");
                continue;
            }
        }
        // Pravila za damu
        else if (figura_sa == DAMA_CRVENI || figura_sa == DAMA_ZELENI)
        {
            if (apsolutna_razlika_red == apsolutna_razlika_stupac && apsolutna_razlika_red > 0)
            {
                int smjer_red = (razlika_red > 0) ? 1 : -1;
                int smjer_stupac = (razlika_stupac > 0) ? 1 : -1;
                int protivnicke_figure = 0;
                int red_protivnik = -1, stupac_protivnik = -1;
                int red_prolaz = red_pocetak + smjer_red;
                int stupac_prolaz = stupac_pocetak + smjer_stupac;

                while (red_prolaz != red_kraj && stupac_prolaz != stupac_kraj)
                {
                    if (ploca[red_prolaz][stupac_prolaz] != 0)
                    {
                        if (ploca[red_prolaz][stupac_prolaz] == trenutni_igrac ||
                            ploca[red_prolaz][stupac_prolaz] == trenutni_igrac + 2)
                        {
                            break;
                        }

                        else
                        {
                            protivnicke_figure++;
                            red_protivnik = red_prolaz;
                            stupac_protivnik = stupac_prolaz;
                        }
                    }
                    red_prolaz += smjer_red;
                    stupac_prolaz += smjer_stupac;
                }

                if (protivnicke_figure > 1)
                {
                    printf("Dama može pojesti samo jednu figuru po potezu!\n");
                    continue;
                }

                if (protivnicke_figure == 1)
                {
                    ploca[red_protivnik][stupac_protivnik] = 0;
                }

                ploca[red_kraj][stupac_kraj] = figura_sa;
                ploca[red_pocetak][stupac_pocetak] = 0;
            }

            else
            {
                printf("Neispravan potez za damu!\n");
                continue;
            }
        }

        // Promjena u damu
        if (figura_sa == CRVENI && red_kraj == 7)
        {
            ploca[red_kraj][stupac_kraj] = DAMA_CRVENI;
        }

        else if (figura_sa == ZELENI && red_kraj == 0)
        {
            ploca[red_kraj][stupac_kraj] = DAMA_ZELENI;
        }

        trenutni_igrac = promijeniIgraca(trenutni_igrac);
    }

    return 0;
}