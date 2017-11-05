float kp=4.5,ki=10,kd=2;
float error=0,P=0,I=0,D=0,PID=0;
float prev_error=0,prev_I=0;
int s1=1,s2=1,s3=1,s4=1,s5=1,s6=1,a=0;
int initial_speed=50;

void read_sensor_values(void);
void calculate_pid(void);
void motor_control(void);
void setup()
{
    pinMode(2,INPUT);
    pinMode(4,INPUT);
    pinMode(7,INPUT);
    pinMode(8,INPUT);
    pinMode(12,INPUT);
    pinMode(13,INPUT);
    pinMode(3,OUTPUT);
    pinMode(5,OUTPUT);
    pinMode(6,OUTPUT);
    pinMode(9,OUTPUT); 
    pinMode(10,OUTPUT);
    pinMode(11,OUTPUT);
    pinMode(1,INPUT);
    pinMode(0,INPUT);
}
void loop()
{
    read_sensor_values();
    calculate_pid();
    motor_control();
}
void read_sensor_values()
{
  a=0;

    s1=digitalRead(2);
    s2=digitalRead(4);
    s3=digitalRead(7);
    s4=digitalRead(8);
    s5=digitalRead(12);
    s6=digitalRead(13);
    sx=digitalRead(0);
    sy=digitalRead(1);
  
    if(s1==1 && s2==1 && s3==1 && s4==1 && s5==1 && s6==0)
    error=5;
    else if(s1==1 && s2==1 && s3==1 && s4==1 && s5==0 && s6==0)
    error=4;
    else if(s1==1 && s2==1 && s3==1 && s4==1 && s5==0 && s6==1)
    error=3;
    else if(s1==1 && s2==1 && s3==1 && s4==0 && s5==0 && s6==1)
    error=2;
    else if(s1==1 && s2==1 && s3==1 && s4==0 && s5==1 && s6==1)
    error=1;
    else if(s1==1 && s2==1 && s3==0 && s4==0 && s5==1 && s6==1)
    error=0;
    else if(s1==1 && s2==1 && s3==0 && s4==1 && s5==1 && s6==1)
    error=-1;
    else if(s1==1 && s2==0 && s3==0 && s4==1 && s5==1 && s6==1)
    error=-2;
    else if(s1==1 && s2==0 && s3==1 && s4==1 && s5==1 && s6==1)
    error=-3;
    else if(s1==0 && s2==0 && s3==1 && s4==1 && s5==1 && s6==1)
    error=-4;
    else if(s1==0 && s2==1 && s3==1 && s4==1 && s5==1 && s6==1)
    error=-5;
    else if(s1==1 && s2==1 && s3==1 && s4==1 && s5==1 && s6==1 && error==-5)
    {
        error=-6;
    }
    else if(s1==1 && s2==1 && s3==1 && s4==1 && s5==1 && s6==1 && error==5)
    {
        error=6;
    }
    else if(s1==1 && s2==1 && s3==0 && s4==0 && s5==0 && s6==0 )
    {
        a=2;
    }
    else if(s1==0 && s2==0 && s3==0 && s4==0 && s5==1 && s6==1)
    {
        a=3;
    }
    else if(s1==0 && s2==0 && s3==0 && s4==0 && s5==1 && s6==1)


      
    if(s1==1 && s2==1 && s3==1 && s4==1 && s5==1 && s6==1)
    {
        a=1;
    }
   
}
void calculate_pid()
{
    P=error;
    I=I+prev_I;
    D=error-prev_error;
    PID=(kp*P)+(ki*I)+(kd*D);
    prev_I=I;
    prev_error=error;
}
void motor_control()
{
    int left_speed=initial_speed+PID;
    int right_speed=initial_speed-PID;
    constrain(left_speed,0,255);
    constrain(right_speed,0,255);
    if(a==1)
    {
        analogWrite(3,0);
        analogWrite(6,0);
        analogWrite(5,70);
        analogWrite(9,70);
      
        
    }
    else if(a==2)
    {
        analogWrite(3,left_speed);
        digitalWrite(6,LOW);
        digitalWrite(5,LOW);
        analogWrite(9,right_speed);
      analogWrite(10,255);
      analogWrite(11,255);
        
    }
    else if(a==3)
    {
        digitalWrite(3,LOW);
        analogWrite(6,left_speed);
        digitalWrite(9,LOW);
        analogWrite(5,right_speed);
      analogWrite(10,255);
      analogWrite(11,255);
       
    }
    else
    {
        analogWrite(3,left_speed);
        analogWrite(6,right_speed);
        digitalWrite(5,LOW);
        digitalWrite(9,LOW);
        analogWrite(10,255);
       analogWrite(11,255);
    }
}

