using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Net.Mime.MediaTypeNames;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        bool ProgramaActivo = false;
        float FLitros = 0;
        float FPeso = 0;
        float FMililitro = 0;
        int Horas = 0, Minutos = 0, Segundos = 0;

        private void timer1_Tick(object sender, EventArgs e)
        {
            float jj; /*La variable JJ la hice para no hacer if (FLitros - FMililitro >= 0) ya que eso me estaba retando la variable
                  causando fallos logicos en el programa*/
            Segundos++;
            if (Segundos == 60)
            {
                Segundos = 0;
                Minutos++;
                if (Minutos == 60)
                {
                    Minutos = 0;
                    Horas++;
                    jj = FLitros - FMililitro;
                    if (jj >= 0)
                    {
                        FLitros -= FMililitro;
                    }
                    else
                    {
                        FLitros = 0;
                    }
                    if (Horas == 24)
                    {
                        Horas = 0;
                        MessageBox.Show("Trabajar 24 Horas Seguidas es inhumano, si no vas a descansar, yo me la saco, Bye!.", "Ya Descansa", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                        this.Close(); // cierra el programa al trabajar 24 horas seguidas
                    }
                    this.WindowState = FormWindowState.Maximized;// maximiza la ventana
                    MessageBox.Show("Intenta mirar hacia arriba. Siéntate derecho y lleva la mirada hacia algo lejano, despues al extremo inferior derecho y de ahí hacia el cielo, luego a la izquierda y de vuelta hacia abajo. Ahora mueve los ojos en la dirección contraria. Repite cinco veces.", "Notificacion", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    label4.Text = "MiliLitros por tomar : " + FLitros;
                    this.WindowState = FormWindowState.Minimized;// minimiza la ventana
                }
                else if (Minutos == 30)
                {
                    this.WindowState = FormWindowState.Maximized;// maximiza la ventana
                    MessageBox.Show("Levantate, camina, estirate, dobla el tronco (como saludo japonés e izquierda-derecha.)", "Notificacion", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    this.WindowState = FormWindowState.Minimized;// minimiza la ventana
                }
            }
            label5.Text = Horas.ToString("00") +":" + Minutos.ToString("00") + ":"+Segundos.ToString("00");
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (ProgramaActivo == true)
            {
                DialogResult rpta = MessageBox.Show("Desea Dejar de recibir el recordatorio? No te olvides de seguir tomando Aguita uwu", "Salir", MessageBoxButtons.YesNo, MessageBoxIcon.Information);
                if(rpta == DialogResult.No)
                {
                    e.Cancel = true; //cancela el cierre
                }
            }
        }

        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            FPeso = float.Parse(txtKG.Text);
            FMililitro = float.Parse(txtVaso.Text);
            if(FPeso > 1 && FMililitro > 1)
            {
                FLitros = FPeso * 35; // Mililitros de Agua a tomar en un día (35ml x cada kilo)
                DialogResult rpta = MessageBox.Show("Todo calculo del agua a tomar se hace en base al peso introducido", "Aclaración", MessageBoxButtons.YesNo, MessageBoxIcon.Information);
                if (rpta == DialogResult.Yes)
                {
                    ProgramaActivo = true;
                    button1.Enabled = false;
                    txtKG.Enabled = false;
                    txtVaso.Enabled = false;
                    label3.Text = "MiliLitros Sugeridos: " + FLitros;
                    this.WindowState= FormWindowState.Minimized;// minimiza la ventana
                    timer1.Enabled = true;
                }
            }

        }
    }
}
