#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "inputs.h"
#include "Controller.h"
#include "hermanos.h"
#include "asignaciones.h"
#include <windows.h>

void showLogo(void);

int main()
{

    char *option;
    option = (char*) malloc (sizeof(char));
    LinkedList* listaHermanos = ll_newLinkedList();
    LinkedList* listaAsignaciones = ll_newLinkedList();
    eConfiguracion* config = (eConfiguracion*)malloc(sizeof(eConfiguracion));
    if(listaHermanos == NULL)
    {
        printf("No se ha podido crear la lista de hermanos. Reinicie el programa.\n\n");
        system("pause");
    }
    harcodearHermanos(listaHermanos);
    harcodearAsignaciones(listaAsignaciones);


    if((config = cargarConfiguracion("config.bin",1))!=NULL)
    {
        if(controller_aplicarConfiguracion(config,listaHermanos,listaAsignaciones)==0)
        {
            if(config->arranqueLogo==1)
            {
                showLogo();
                Sleep(2000);
            }
            do
            {
                system("cls");
                fflush(stdin);
                printf("\n***** MENU *****\n");
                printf("\n1.  Crear nueva asignacion");
                printf("\n2.  Agrega hermano");
                printf("\n3.  Buscar asignacion");
                printf("\n4.  Buscar hermano");
                printf("\n5.  Ver lista de hermanos"); ///tiene que poder ordenarse segun se desee
                printf("\n6.  Ver lista de asignaciones");
                printf("\n7.  Modificar hermano");
                printf("\n8.  Modificar asignacion");
                printf("\n9.  Configuracion");
                printf("\n10. Salir\n");
                fflush(stdin);
                scanf("%s",option);


                switch(atoi(option))
                {

                case 1:
                    controller_addAsignacion(listaAsignaciones,listaHermanos);
                    break;
                case 2:
                    controller_addHermano(listaHermanos);
                    break;
                case 3:
                    controller_searchAsignacion(listaAsignaciones,listaHermanos);
                    break;
                case 4:
                    controller_searchHermano(listaHermanos);
                    break;
                case 5:
                    printHermanos(listaHermanos);
                    system("pause");
                    system("cls");
                    break;
                case 6:
                    printAsignaciones(listaAsignaciones);
                    system("pause");
                    system("cls");
                    break;
                case 7:
                    controller_editHermanos(listaHermanos);
                    break;
                case 8:
                    controller_editAsignaciones(listaAsignaciones,listaHermanos);
                    break;
                case 9:
                    //controller_configuracion()
                    break;
                case 10:
                    //controller_saveHermanosAsignaciones(listaHermanos,listaAsignaciones,config);
                    printf("\n Hasta luego! :)\n");
                    Sleep(1000);
                    break;
                default:
                    printf("\nOpcion invalida");
                    system("cls");
                    break;
                }
            }
            while((atoi(option)) != 10);
            free(listaHermanos);
            free(listaAsignaciones);
            free(option);

        }
        else
        {
            printf("\n ERROR FATAL! No se pudo aplicar la configuracion de arranque\n");
            system("pause");
        }
    }
    else
    {
        printf("\nERROR FATAL! No se ha podido cargar la configuracion de arranque.\n");
        system("pause");
    }
    return 0;
}


void showLogo(void)
{
    printf("\n                                                                    ```                               \n");
    printf("                            .---.                             -ohMMMmy+`                           \n");
    printf("                          +hMMMMNm+.                        -yMMMMMMMMMh:                          \n");
    printf("                        `hMMMMMMMMMNs`                    `oNMMMMMMMMMMMN/                         \n");
    printf("                        hMMMMMMMMMMMMd-                  .mMMMMMMMMMMMMMMM                         \n");
    printf("                        MMMMMMMMMMMMMMN+                .mMMMMMMMMMMMMMMMM:                        \n");
    printf("                       MMMMMMMMMdMMMMMMy.             -NMMMMMMNMMMMMMMMMMh                         \n");
    printf("                       -MMMMMMMMMMMMMMMMMd.           .dMMMMMNhmMMMMMMMMMMM`                       \n");
    printf("                       oMMMMMMMMMMMMMMMMMMN:         .dMMMMMMMMMMMMMMMMMMMN`                       \n");
    printf("                       oMMMMMMMMMMMMMMMMMMMd.       `yMMMMMMMMMMMMMMMMMMMMs                        \n");
    printf("                       `MMMMMMMMMMMMMMMMMMMMd.      yMMMMMMMMMMMMMMMMMMMMMo                        \n");
    printf("                        dMMMMMMMMMMMMMNMNMMMMy     :MMMMMMNmMMMMMMMMMMMMMM:                        \n");
    printf("                        oMMMMMMMMMMMMMMMNNNhNN/`  `dMymNNMMNMMMMMMMMMMMMMMm`                       \n");
    printf("                        hMMMMMMMMMMMMMMMNs-`:+/o :omy`./sNmMMMMMdyMMMMMMMMM`                       \n");
    printf("                        MMMMMMMMMMMMMMMmh+`   `- d:/`   /hoMmh+dddMoyMMMMMh                        \n");
    printf("                        NMMMMMMMMMMMMMMyo.  `s/-:..+`   `-yhoomMMMMNNMMMMM                         \n");
    printf("                        :mMMMMMMMMMMNm/:s+   yNhy+.d.   `o/.sohNMMMMMMMMMM                         \n");
    printf("                         +MMMMMMMMNmho`hh   /-shmohs.`/` yNs/sshMMMMMMMMMs                         \n");
    printf("                         +MMMMMMMMMyo: -s  /Ndysomh+/sM: `h../+oNMMMMMMMh.                         \n");
    printf("                         /MMMMMMMMmys.``/: mMMMMNMMMMMM/ `-``+mshhmmMMMm-                          \n");
    printf("                         `NhyMMdMyyNm+-:./:dMMMMMMMMMMm````  +NN/+my+mMm/                          \n");
    printf("                          dmdMo`MNms.   `  :NMMMMMMMMMs` .  ``yMNNh`od/oh                          \n");
    printf("                          /MMMd/NMMm+   `   dMMMMMMMMm`:-  `--NMMMs-+:`o-                          \n");
    printf("                          `sNNNNdMMMNy-``   +MMMMMMMMd  .`.:sdMMMm.:``                             \n");
    printf("                            .:.s/yMMMMNmd/  .dMN+hMMy/  .dNNMMMdd+oy` `                            \n");
    printf("                               ohhNdMMMMM``` -h/  hd- `  MMMMMMddyd:.+y`                           \n");
    printf("                              `dhyNmydMMd.s+  .       :h:hMMNmmdysy-../                            \n");
    printf("                           `/:yo`ymh::MM+mMd+.      -smMMdMMd++o:`` `:h                            \n");
    printf("                           -ysd- .oNNmMMMMMMMd:`  .+NMMMMMMMMdso. `` `.                            \n");
    printf("                           :Nh+shh++hNMMMMMMMMNh .mMMMMMMMMNd-   `y+                               \n");
    printf("                         `:sMm`/dMy:.+omMMMMNho/..+ohNNNNds/-..:o/-                                \n");
    printf("                  `.``  +hMMMMy`/mmmm+ `+hmMNdNMNNMNmd:-:.   sddd/                                 \n");
    printf("                 -ys. `:/-sNMMMmy.-/My  y `/yNNNMMNmh+.  -  omNNh.                                 \n");
    printf("              -o+   `+mMMNmNMNNMd:`sd-../    -:://:`     -. +y:.`/                                 \n");
    printf("            .yNm:  `hMMhmNMMMosMmhdMmy`.-                 --:s+-                                   \n");
    printf("          .ymMMy `  hMmsymMms+yohNMMNy` ``               -.:do/-/-                                 \n");
    printf("         :NMMMy `s/`yMMMs:yms-   `Nmyhhyyh/:``.  ` ``.--+++sdNdhN-                                 \n");
    printf("        sNNsdo  hMMNNMNm.`hMMN-``/mMMMMm--./hms-.oyhydMMMMMNmMMN-                                  \n");
    printf("`./.  .+Mhydh `sMmhmh/-`.sMNNMNddNNMMMMMdhydmo-`hNhmMMMMMMMmmmMN.                                  \n");
    printf(".-:` .sNMh-hs` +MmsdNy`` mMd::mMMMMMMm+-ohmMMd/+dMMMMMMMMMMhNMMMm-                                 \n");
    printf(" `.+NMMmNm.   -ms+/`    `hsdNMMNMMMMd+.  -oodMMMMMMMMMMMMMyshNs-                                   \n");
    printf("/y1mMMN+MMh.   -dyMMMd-:ydo+Nmms- oMMMMMMdo:` +NMMMMMMMMMMMMMMMN-                                  \n");
    printf("MMMMMMMh.   /ymhds++mMMMM: ` ` :mmNo:/yhMMMmhosyN:+ymmMNNMMMMm+`/h-                                \n");
    printf("MNNNMMm/    dMds-    yMMh.-` .oms-y/` `/MMMMMMMMMdo:.`.``-h/.`-+mNy                                \n");
    printf("MmNMd/`    :MMN+  `` -NMMMNhymo-/+mNdmNNMMMMMdNMMMMMNdsydshssmMMMm/                                \n");
    printf("MMMMMh`  ./dMMho:. shNMMMo -Nd.-m-./+mmooMMhodysydMMmMMMMMMMMMMMMM/                                \n");
    printf("ooy/-   -MMMMMMm+ ydhd+.:/odNsoys-m:ysodMMd+/hy`omMM+oNMNMdyNMMMMMs                                \n");
    printf("\n\n SERVAL TECHNOLOGIES 2019\t by Lucas Carbone\n");
}
