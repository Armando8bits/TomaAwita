/* Codigo sacado de: https://www.codigazo.com/en-c/codigo-ejemplo-crear-ventana-en-c
 */

#define _WIN32_WINNT 0x0500 // Es necesaria esta definicion para esconder ventana de consola
#include <iostream>         //no se x q pero parece necesario para los hilos
#include <thread>           //para hablitar hilos
#include <windows.h>        // Libreria que contiene las funciones de Winapi
// declaraciones de controles con eventos:
#define Btn1 101
#define ID_EDIT1 102
#define ID_EDIT2 103
// #define ID_Label 104
//  #define BTN2 102.. y así sucesivamente con cada nuevo boton o control

void Reloj(int, int);

HWND CmdGo;
HWND LblDatos;
HWND LblDatos2;
HWND LblTiempo;

bool ProgramaActivo = false;
/*  Declaracion del procedimiento de windows  */

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

/*  Declaramos una variable de tipo char para guardar el nombre de nuestra aplicacion  */

char NombreClase[] = "Estilos";

HWND ventana1;       /* Manejador de la ventana*/
MSG mensajecomunica; /* Mensajes internos que se envian a la aplicacion */
WNDCLASSEX estilo1;  /* Nombre de la clase para los estilos de ventana */

int WINAPI WinMain(HINSTANCE hThisInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpszArgument,
                   int nCmdShow)

{
    /* Creamos la estructura de la ventana indicando varias caracteristicas */
    estilo1.hInstance = hThisInstance;
    estilo1.lpszClassName = NombreClase;
    estilo1.lpfnWndProc = WindowProcedure;
    estilo1.style = CS_DBLCLKS;
    estilo1.cbSize = sizeof(WNDCLASSEX);
    estilo1.hIcon = LoadIcon(NULL, IDI_EXCLAMATION); // ASIGNA ICONO
    estilo1.hIconSm = LoadIcon(NULL, IDI_INFORMATION);
    estilo1.hCursor = LoadCursor(NULL, IDC_ARROW);
    estilo1.lpszMenuName = NULL; /* Sin Menu */
    estilo1.cbClsExtra = 0;
    estilo1.cbWndExtra = 0;
    estilo1.hbrBackground = (HBRUSH)COLOR_WINDOW; /* Color del fondo de ventana */

    /* Registramos la clase de la ventana */

    if (!RegisterClassEx(&estilo1))

        return 0;

    /* Ahora creamos la ventana a partir de la clase anterior */

    ventana1 = CreateWindowEx(
        0,
        NombreClase,                              /* Nombre de la clase */
        ("Toma Awuita! uwu V3.0"),                /* Titulo de la ventana */
        WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, /* Ventana por defecto : WS_OVERLAPPEDWINDOW | WS_BORDER  la que está ejecutandose no permite modificar tamaño de ventana*/
        400,                                      /* Posicion de la ventana en el eje X (de izquierda a derecha) */
        70,                                       /* Posicion de la ventana, eje Y (arriba abajo) */
        310,                                      /* Ancho de la ventana */
        190,                                      /* Alto de la ventana */
        HWND_DESKTOP,
        NULL, /* Sin menu */
        hThisInstance,
        NULL);
    // CREA LOS LABELS QUE NO SE MODIFICAN:
    CreateWindowW(L"Static", L"Su peso en KG:", WS_VISIBLE | WS_CHILD | ES_LEFT, 5, 5, 150, 20, ventana1, 0, 0, 0);
    CreateWindowW(L"Static", L"MiliLitro por vaso:", WS_VISIBLE | WS_CHILD | ES_LEFT, 5, 30, 200, 20, ventana1, 0, 0, 0);
    CreateWindowW(L"Static", L"Creado por: Armando Ramírez", WS_VISIBLE | WS_CHILD, 40, 140, 200, 20, ventana1, 0, 0, 0);
    LblTiempo = CreateWindowW(L"Static", L"-", WS_VISIBLE | WS_CHILD, 115, 95, 200, 20, ventana1, 0, 0, 0); //(HMENU)ID_Label
    LblDatos = CreateWindowW(L"Static", L"-", WS_VISIBLE | WS_CHILD, 5, 75, 200, 20, ventana1, 0, 0, 0);
    LblDatos2 = CreateWindowW(L"Static", L"-", WS_VISIBLE | WS_CHILD, 5, 55, 200, 20, ventana1, 0, 0, 0);
    // CREA LOS TEXTBOX:
    CreateWindowEx(0, "EDIT", "85", ES_NUMBER | ES_AUTOHSCROLL | ES_CENTER | WS_CHILD | WS_VISIBLE | WS_BORDER, 150, 5, 70, 20, ventana1, (HMENU)ID_EDIT1, 0, 0);
    CreateWindowEx(0, "EDIT", "500", ES_NUMBER | ES_AUTOHSCROLL | ES_CENTER | WS_CHILD | WS_VISIBLE | WS_BORDER, 150, 30, 70, 20, ventana1, (HMENU)ID_EDIT2, 0, 0);

    /* Hacemos que la ventana sea visible */

    ShowWindow(ventana1, nCmdShow);
    ShowWindow(GetConsoleWindow(), SW_HIDE); // Funcion para esconder la ventana de consola
    /* Hacemos que la ventan se ejecute hasta que se obtenga resturn 0 */

    while (GetMessage(&mensajecomunica, NULL, 0, 0))
    {
        /* Traduce mensajes virtual-key */
        TranslateMessage(&mensajecomunica);
        /* Envia mensajes a WindowProcedure */
        DispatchMessage(&mensajecomunica);
    }
    return mensajecomunica.wParam;
}

LRESULT CALLBACK WindowProcedure(HWND ventana1, UINT mensajecomunica, WPARAM wParam, LPARAM lParam)
{
    switch (mensajecomunica) /* Manejamos los mensajes */
    {
    case WM_CLOSE: /* Que hacer en caso de recibir el mensaje WM_CLOSE*/
        if (ProgramaActivo == false || (MessageBox(ventana1, "Desea Dejar de recibir el recordatorio? No te olvides de seguir tomando Aguita uwu", "Salir.", MB_OKCANCEL | MB_ICONQUESTION) == IDOK))
        {//cierra el programa si no se está ejecutando el cronometro.... caso contrario pregunta antes de cerrar
            DestroyWindow(ventana1); /* Destruir la ventana */
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_CREATE: // se ejecuta al crearse la ventana, aqui se agregan componentes...
        // LblLabel1=CreateWindowEx(L"STATIC",L"Su peso en KG:",WS_VISIBLE|WS_CHILD|0,20,20,80,25,ventana1,0,0,0);
        CmdGo = CreateWindowEx(0, "button", "Go!", WS_VISIBLE | WS_CHILD | 0, 100, 115, 80, 25, ventana1, (HMENU)Btn1, 0, 0);
        break;
    case WM_COMMAND: // Ejecuta las los eventos de los controles ...
        if (LOWORD(Btn1) == wParam)
        {
            // printf("hola");
            char StrPeso[6], StrMilitro[6];
            GetDlgItemText(ventana1, ID_EDIT1, StrPeso, 6);
            GetDlgItemText(ventana1, ID_EDIT2, StrMilitro, 6);
            int FPeso = atoi(StrPeso);         // py: DoubleKG
            int FMililitro = atoi(StrMilitro); // py: VasoAgua
            int FLitros;                       // py:LitrosAgua
            if (FPeso > 1 && FMililitro > 1)
            {
                // printf("\nhasta ahora peso es %i Y los ML del Vaso son: %i",FPeso, FMililitro);
                FLitros = FPeso * 35; // Mililitros de Agua a tomar en un día (35ml x cada kilo)
                if (MessageBox(ventana1, "Todo calculo del agua a tomar se hace en base al peso introducido", "Aclaración", MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
                {
                    EnableWindow(GetDlgItem(ventana1, Btn1), false);     // inhabilita los controles
                    EnableWindow(GetDlgItem(ventana1, ID_EDIT1), false); // se le pone True y se habilitan
                    EnableWindow(GetDlgItem(ventana1, ID_EDIT2), false);
                    std::thread hilo(Reloj, FMililitro, FLitros); // inicia el Hilo
                    hilo.detach();                                // para que se siga ejecutando el programa sin esperar al Hilo
                    ShowWindow(ventana1, SW_MINIMIZE);            // minimiza la ventana
                }
            }
        }
        break;
    default: /* Tratamiento por defecto para mensajes que no especificamos */
        return DefWindowProc(ventana1, mensajecomunica, wParam, lParam);
    }
    return 0;
}

void Reloj(int FMililitro, int FLitros)
{
    /*float FPeso = atof(StrPeso);         // py: DoubleKG
    float FMililitro = atof(StrMilitro); // py: VasoAgua
    float FLitros;                       // py:LitrosAgua
    */
    // char textoA[] = "Levantate, camina, estirate, dobla el tronco (como saludo japonés e izquierda-derecha.)";
    // char textoB[] = "Levantate, camina, estirate, dobla el tronco (como saludo japonés e izquierda-derecha.) ADICIONALMENTE: Intenta mirar hacia arriba. Siéntate derecho y lleva la mirada hacia algo lejano, despues al extremo inferior derecho y de ahí hacia el cielo, luego a la izquierda y de vuelta hacia abajo. Ahora mueve los ojos en la dirección contraria. Repite cinco veces.";
    ProgramaActivo = true; // indica que el programa ya está activo
    int Horas = 0, Minutos = 0, Segundos = 0;
    int LitrosAgua = FLitros, VasoAgua = FMililitro;
    int jj;              /*La variable JJ la hice para no hacer if (LitrosAgua - VasoAgua >= 0) ya que eso me estaba retando la variable
                  causando fallos logicos en el programa*/
    char numero[6] = {}; // estos dos chat son para mostrar mensajes por Labels
    char Texto3[30] = "";
    strcpy(Texto3, "MiliLitros Sugeridos: ");
    itoa(LitrosAgua, numero, 10);
    strcat(Texto3, numero);
    SetWindowText(LblDatos2, Texto3);
    /*DESPUES DESCUBRÍ QUE LA MEJOR MANERA ES ESTA:
    wsprintf(cadena, "Este numero en decimal %d, ahora en hexadecimal 0x%X", 50, 50);
    MessageBox(0, cadena, "Demostracion simple", 0);  */
    // printf("\nhasta ahora la original es %i Y la local es %i",FMililitro, VasoAgua);
    while (true)
    {
        Sleep(1000); // detiene todo por 1 segundo
        Segundos++;
        if (Segundos == 60)
        {
            Segundos = 0;
            Minutos++;
            if (Minutos == 60)
            {
                Minutos = 0;
                Horas++;
                jj = LitrosAgua - VasoAgua;
                if (jj >= 0)
                {
                    LitrosAgua -= VasoAgua;
                }
                else
                {
                    LitrosAgua = 0;
                }
                if (Horas == 24)
                {
                    Horas = 0;
                    MessageBox(ventana1, "Trabajar 24 Horas Seguidas es inhumano, si no vas a descansar, yo me la saco, Bye!.", "Ya Descansa", MB_OK | MB_ICONSTOP);
                    SendMessage(0, WM_DESTROY, 0, 0); // cierra el programa al trabajar 24 horas seguidas
                }
                ShowWindow(ventana1, SW_NORMAL); // Maximiza la ventana
                MessageBox(ventana1, "Intenta mirar hacia arriba. Siéntate derecho y lleva la mirada hacia algo lejano, despues al extremo inferior derecho y de ahí hacia el cielo, luego a la izquierda y de vuelta hacia abajo. Ahora mueve los ojos en la dirección contraria. Repite cinco veces.", "Notificacion", MB_OK | MB_ICONINFORMATION);
                strcpy(Texto3, "MiliLitros por tomar : ");
                itoa(LitrosAgua, numero, 10);
                // printf("\nhola %i quitando %i ML",LitrosAgua, VasoAgua);
                strcat(Texto3, numero);
                SetWindowText(LblDatos, Texto3);
                ShowWindow(ventana1, SW_MINIMIZE); // minimiza la ventana
            }
            else if (Minutos == 30)
            {
                ShowWindow(ventana1, SW_NORMAL); // Maximiza la ventana
                MessageBox(ventana1, "Levantate, camina, estirate, dobla el tronco (como saludo japonés e izquierda-derecha.)", "Notificacion", MB_OK | MB_ICONINFORMATION);
                ShowWindow(ventana1, SW_MINIMIZE); // minimiza la ventana
            }
        }
        char CharTiempo[7] = {};
        char numero[3] = {};
        char cero[2] = {"0"};
        char DosPuntos[2] = {":"};

        itoa(Horas, numero, 10); // el 10 es de la Base decimal, si le pones 2 se hace binario
        if (Horas < 10)
        {
            strcpy(CharTiempo, cero);
        }                           // 0
        strcat(CharTiempo, numero); // 0#

        strcat(CharTiempo, DosPuntos); // 0#:
        // printf("\nProcesando...%s y su nuemro es %i en total %s", numero,ho,CharTiempo);

        itoa(Minutos, numero, 10);
        if (Minutos < 10)
            strcat(CharTiempo, cero);
        strcat(CharTiempo, numero); // 0#:0#

        strcat(CharTiempo, DosPuntos); // 0#:0#:

        itoa(Segundos, numero, 10);
        if (Segundos < 10)
            strcat(CharTiempo, cero);
        strcat(CharTiempo, numero); // 0#:0#:0#

        SetWindowText(LblTiempo, CharTiempo);
    }
}