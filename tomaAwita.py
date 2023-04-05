''' Toma Awita por Armando Ramírez
fuente de los ejercicio: https://www.nytimes.com/es/2020/05/27/espanol/estilos-de-vida/estiramientos-oficina-silla.html
							https://www.ofiprix.com/blog/hacer-ejercicio-en-la-oficina/
ejecutalo con este comando: 
 			exec(open("D:\tomaAwita.py").read())

Para ejecutarlo al inicio de windows, presiona la tecla del logotipo de Windows  + R, escribe shell:startup y luego selecciona Aceptar. Esto hará que se abra la carpeta Inicio donde lo pegaras o su acceso directo.

Para generar EXE en cmd ingresas: pyinstaller --onefile --windowed D:\tomaAwita.py
'''

import time
import threading
from tkinter import *
from tkinter import messagebox

root = Tk()
root.attributes('-topmost', True) #mantiene siempre la ventana en primer plano
root.title("Toma Awuita! uwu V2.0")
root.geometry("296x170")
root.resizable(0, 0)

texto1="Levantate, camina, estirate, dobla el tronco (como saludo japonés e izquierda-derecha.)"
texto2="Intenta mirar hacia arriba. Siéntate derecho y lleva la mirada hacia algo lejano, despues al extremo inferior derecho y de ahí hacia el cielo, luego a la izquierda y de vuelta hacia abajo. Ahora mueve los ojos en la dirección contraria. Repite cinco veces."
Horas=0
Minutos=0
Segundos=0
LitrosAgua=0
VasoAgua=0

def Reloj():
	global Horas,Minutos,Segundos,LitrosAgua,VasoAgua #'global' indica que voy a usar las mismas variables declaradas antes, si no, bota error
	while(True): #crea un bucle infinito
		time.sleep(1) #despues activo esto, suspende la ejecución un minuto/60 segundos
		Segundos+=1
		if(Segundos>59):
			Segundos=0
			Minutos+=1 #incrementa en uno
			if(Minutos==60):
				#root.state(newstate='normal') #la restaura si estava invisible
				root.deiconify() #maximiza la ventana
				Minutos=0
				Horas+=1
				if(LitrosAgua-VasoAgua>=0):
					LitrosAgua-=VasoAgua
				else:
					LitrosAgua=0
				messagebox.showinfo("Pausa",texto1+" ADICIONALMENTE: \n\n"+ texto2+"\n\nSi toma agua ahora te quedan: "+str(LitrosAgua)+" litros.")
				root.iconify() #minimiza la ventana
				#print('\n '+ str(time.strftime("%H:%M:%S"))+' Se advirtio...') #obtiene hora del sistema
			elif(Minutos==30): #cada 30 min
				#root.state(newstate='normal') #la restaura si estava invisible
				root.deiconify() #maximiza la ventana
				messagebox.showinfo(message=texto2, title="Pausa")
				root.iconify() #minimiza la ventana
		#print("\nHora: "+str(Horas)+" Minutos: "+str(Minutos)) #para controlar tiempo por consola
		LblMensaje.config(text = "Tiempo: "+str(Horas).zfill(2)+":"+str(Minutos).zfill(2)+":"+str(Segundos).zfill(2)+"\nLitros De agua por Tomar: "+str(LitrosAgua))
		#.zfill(2) pone ceros a la izquierda de los numeros

def pulsar_boton():
	global LitrosAgua,VasoAgua 
	try: #mientras no ingrese un numero adecuado no procede
		#print("pulsate este!\n")
		DoubleKG=float(cajadetexto.get(1.0, 'end'))
		VasoAgua=float(cajadetexto2.get(1.0, 'end'))
		'''In this syntax, 1.0 is the starting position and the end keyword refers to the end of the document.
		that means all the data will be fetched from the Text box. '''
		if(DoubleKG>1):
			LitrosAgua=round(DoubleKG*0.035,2) #litros de Agua a tomar en un día (35ml x cada kilo convertido a (litros(peso*35)/1000) )
			
			Opcion=messagebox.askyesno(message="Todo calculo se hace en base a que tengas <"+str(DoubleKG)+" KG> de peso.\n\nTomaras "+str(LitrosAgua)+" Litros de agua Durante la jornada.\n\nProcede?", title="Confirma para confirmar")
			if(Opcion):
				Boton.config(state="disabled") #desactiva botón y cajas, para habilitar pones: state="normal"
				cajadetexto.config(state="disabled")
				cajadetexto2.config(state="disabled")
				t.start() #da inicio a la funcion reloj en un hilo para q no se congele app
				#root.state(newstate='withdraw') #solo invisiviliza la ventana
				root.iconify() #minimiza la ventana
	except ValueError:
		cajadetexto.delete(1.0, 'end')
		#print("nada ok")

t = threading.Thread(target=Reloj) # configura el hilo con la funcion Reloj
t.daemon=True #incica que este hilo se cerrará con el proceso principal

Label(root,text="Su peso en KG:").pack()
#caja de texto
cajadetexto=Text(root, height=1, width=7)#alto y ancho
cajadetexto.insert(1.0,"85") #pone valor por default
cajadetexto.focus_set()
cajadetexto.pack()
''' se crea una variable contenedora del txtbox para
asi manejar el setfocus
text.insert(INSERT, "asi se inserta texto desde codigo")
'''
Label(root,text="Litros a tomar por cada vaso:").pack()
cajadetexto2=Text(root, height=1, width=7)#alto y ancho
cajadetexto2.insert(1.0,"0.5") #pone valor por default que son 2 vasos normales de agua
cajadetexto2.pack()
#botones
Boton=Button(root, text="Go!",command=pulsar_boton,width=19)
Boton.pack()
'''se llama a la funcionsin los parentesis, ya que si los pones, no se
ejecuta cuando quiere, y solo una vez al cargar la ventana'''
LblMensaje=Label(root,text="--")
LblMensaje.pack()
Label(root,text="Creado por: Armando Ramirez",fg= "gray51").pack()
mainloop()