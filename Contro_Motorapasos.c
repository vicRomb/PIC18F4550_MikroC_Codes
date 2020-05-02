/////////////////////////////////////////////////////////////////////////////||
/////////////////////////////////////////////////////////////////////////////||
// Benemérita Universidad Autónoma de Puebla                                 ||
// Facultad de Ciencias de la Electrónica                                    ||
// Maestría en Ingenieria Electronica, Opcion Instrumentación Electrónica    ||
// Asignatura: Sistemas programables                                         ||
// Profesor:   Nicolás Quiroz Hernández                                      ||
// Equipo 3:   Victor Romero Bautista, 219470611 Y                           ||
//             Narciso Ariel Ramirez Tecuatl, 219470609                      ||
// Nombre:     Control de motor a pasos con smartphone                       ||
// Fecha:      29-Abril-2020                                                 ||
/////////////////////////////////////////////////////////////////////////////||
/////////////////////////////////////////////////////////////////////////////||

// Pines de Coneccion al Modulo LCD
sbit LCD_RS at RB0_bit;
sbit LCD_EN at RB2_bit;
sbit LCD_D4 at RB4_bit;
sbit LCD_D5 at RB5_bit;
sbit LCD_D6 at RB6_bit;
sbit LCD_D7 at RB7_bit;

sbit LCD_RS_Direction at TRISB0_bit;
sbit LCD_EN_Direction at TRISB2_bit;
sbit LCD_D4_Direction at TRISB4_bit;
sbit LCD_D5_Direction at TRISB5_bit;
sbit LCD_D6_Direction at TRISB6_bit;
sbit LCD_D7_Direction at TRISB7_bit;
// Fin de pines al modulo LCD

char dato;  // Variable

// Función de Ratardo 10ms
void Move_Delay() {
  Delay_ms(10);
}
// Función para mover eje del motor en sentido Horario
void Giro_Horario()
{
  PORTD = 0x80;
  Move_Delay();
  PORTD = 0x40;
  Move_Delay();
  PORTD = 0x20;
  Move_Delay();
  PORTD = 0x10;
  Move_Delay();
}
// Función para mover eje del motor en sentido Antihorario
void Giro_Anti()
{
  PORTD = 0x10;
  Move_Delay();
  PORTD = 0x20;
  Move_Delay();
  PORTD = 0x40;
  Move_Delay();
  PORTD = 0x80;
  Move_Delay();
}

// Función para escribir en el LCD
void LCD_1()
{
  Lcd_Out(1,1,"Motor a pasos");
  Lcd_Out(2,1,"Giro:");
}

void main(){
 // Configuración de  puertos de en/sal
  PORTD = 0x00; // Comienza la salidas de puerto D en bajo
  TRISD = 0x00; // Puerto D como salida
 // Inicializar componentes
  Lcd_Init();       // Ininicializa LCD
  UART1_Init(9600); // inicializa comunicacion serial
  Delay_ms(1);
 // Mensajes de bienvenida //////////////////////////////////////
  Lcd_Cmd(_LCD_CLEAR);
  Lcd_Out(1,1,"Hola!");
  Lcd_Out(2,1,"Bienvenido");
  Delay_ms(1000);
  Lcd_Cmd(_LCD_CLEAR);

  Lcd_Out(1,1,"Control de Motor");
  Lcd_Out(2,1,"Paso a Paso");
  
  Delay_ms(1000);
  Lcd_Out(1,1,"Motor a pasos");
  Lcd_Out(2,1,"Giro:");
 // Fin mensajes de bienvenida ////////////////////////////////
 
  Lcd_Cmd(_LCD_CURSOR_OFF); // Quitar el cursos
  Lcd_Cmd(_LCD_CLEAR);      // limpia LCD
  LCD_1();                  // Escribe en el LCD
  
  while(1) {
       if(UART1_Data_Ready())
        {
          dato = UART1_Read(); // Lee el bit recibido
          if(dato == '1') // Giro Horario
          {
            Lcd_Out(2,6,"Horario");
            Giro_Horario();
            PORTD.RD1 = 0;
            PORTD.RD0 = 1;
          }
          else if (dato == '0') // Parar motor
          {
            Lcd_Cmd(_LCD_CLEAR);  // limpia LCD
            PORTD = 0x00;
            Lcd_Out(2,6,"Apagado");
            LCD_1();
          }
          else if (dato == '2') // Giro Antihorario
          {
            PORTD.RD1 = 1;
            PORTD.RD0 = 0;
            Lcd_Out(2,6,"Antihorario");
            Giro_Anti();
          }

        }
  }
}