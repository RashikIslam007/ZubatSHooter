# include "iGraphics.h"
# include "windows.h"
int Archer_y=200;
int Arrow_x=1025, Arrow_y=Archer_y+50;
int Arrow_x1=1025, Arrow_y2=Archer_y+50;
int Zubat_x=800, Zubat_y=0;
int Pelipper_x = 500, Pelipper_y = Zubat_y - 250;
int Woobat_x = 650 , Woobat_y =Zubat_y-128 ;
bool shoot=false;
bool GameOver=false;
int score=0;
char sc[20];
int T=60;
char tm[50];

bool HitWoobat(void);
bool HitZubat(void);
bool HitPelipper(void);

void ResetWoobat(void);
void ResetZubat(void);
void ResetPelipper(void);

void ShowScore(void);
void ShowTime(void);


void iDraw()
{
	iClear();
	iShowBMP(0,0,"BackGround.bmp");
	if(shoot==true)iShowBMP(Arrow_x,Arrow_y,"Arrow.bmp");
	//if(shoot==true)iShowBMP(Arrow_x1,Arrow_y2,"Arrow.bmp");
	iShowBMP(0,Archer_y,"Archer.bmp");
	
	//zubat hit
	if(HitZubat()==false){
		iShowBMP(Zubat_x,Zubat_y,"Zubat.bmp");
	}
	else{ 
		iShowBMP(Zubat_x,Zubat_y,"POOF.bmp");
		ResetZubat();
	}
	
	//Woobat hit

	if(HitWoobat()==false){
		iShowBMP(Woobat_x,Woobat_y,"Woobat.bmp");
	}
	else{ 
		iShowBMP(Woobat_x,Woobat_y,"POOF.bmp");
		ResetWoobat();
	}

	// Pe;pper hit
	if(HitPelipper()==false){
		iShowBMP(Pelipper_x,Pelipper_y,"Pelipper.bmp");
	}
	else{ 
		iShowBMP(Pelipper_x,Pelipper_y,"POOF.bmp");
		ResetPelipper();
	}



	ShowScore();
	ShowTime();
	if(GameOver==true){
		iClear();
		iShowBMP(0,0,"GameOver.bmp");
		iSetColor(255,0,0);
		iText(480,120,sc,GLUT_BITMAP_TIMES_ROMAN_24);
	}
	

}
void iMouseMove(int mx, int my)
{
	
}
void iPassiveMouseMove(int mx, int my){
	if(my>382)
	Archer_y=382;
	else
    Archer_y=my;
	//if(shoot==false)Arrow_y=my+50;
}

void iMouse(int button, int state, int mx, int my)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{   
		
		shoot=true;
		if( my<=382){
			
			Arrow_x=0;
		   Arrow_y=my+50;
		}
		else if(my>=382)
		{
          Arrow_x=0;
		  Arrow_y=432;
	    }
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		
	}
}

void iKeyboard(unsigned char key)
{
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use 
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6, 
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12, 
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP, 
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT 
*/
void iSpecialKeyboard(unsigned char key)
{

	if(key == GLUT_KEY_END)
	{
		exit(0);	
	}
	
	//place your codes for other keys here
}
void Shoot(void){
	//if(shoot==true /*&& Arrow_x<1025*/)
		Arrow_x+=5;
	//if(Arrow_x>1024)shoot=false;
}

//Move
void MoveZubat(void){
	if(Zubat_y<470)Zubat_y+=1;
	else Zubat_y=0;
}


void MoveWoobat(){
	if(Woobat_y<470)Woobat_y+=1;
	else Woobat_y=0;

}

void MovePelipper(void){
	if(Pelipper_y<470)Pelipper_y+=1;
	else Pelipper_y=0;
}

//Hit

bool HitZubat(void){
	if(Arrow_x+128>=Zubat_x && Arrow_x<Zubat_x && Arrow_y>=Zubat_y && Arrow_y+16 <=Zubat_y+128){
		score++;
		
		return true;
	}
	return false;
}

bool HitWoobat(void){
	if(Arrow_x+128>=Woobat_x && Arrow_x<Woobat_x && Arrow_y>Woobat_y && Arrow_y+16 <=Woobat_y+128){
		score++;
		
		return true;
	}
	return false;
}

bool HitPelipper(void){
	if(Arrow_x+128>=Pelipper_x && Arrow_x<Pelipper_x && Arrow_y>Pelipper_y && Pelipper_y+16 <=Pelipper_y+128){
		score++;
		
		return true;
	}
	return false;
}

//Reset

void ResetZubat(void){
	Zubat_y=0;
}

void ResetWoobat(void){
	Woobat_y=0;
}

void ResetPelipper(void){
	Pelipper_y=0;
}


void Timer(void){
	if(T>0)T--;
	if(T==0)GameOver=true;
}
void ShowScore(void){
	sprintf(sc, "Score: %d", score);
	iSetColor(255,0,0);
	iText(500,500, sc);
}
void ShowTime(void){
	sprintf(tm, "Time Remaining %d s", T);
	iSetColor(255,0,0);
	iText(475,475,tm);
}

void Poof(){
		iShowBMP(Zubat_x,Zubat_y,"POOF.bmp");

}

int main()
{
	iSetTimer(1000,Poof);
	iSetTimer(10,Shoot);
	iSetTimer(15,MoveZubat);
	iSetTimer(15,MoveWoobat);
	iSetTimer(15,MovePelipper);
	iSetTimer(1000,Timer);
	iInitialize(1024, 512, "Poke Shooter");
	return 0;
}	