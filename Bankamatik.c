#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



typedef struct Musteri {
	int musteriNo; 
	char tc[20] ; 
	char adSoyad[30] ; 
	char dogumTarih[20] ; 
	char cinsiyet ; 
	char adres[30] ; 
	char telefon[20] ; 
	char eposta[30] ; 
	int  sifre ; 
	float bakiye ; 
	int sifreDurum ; 
	int hesapDurum ; 	
} musteri ;

typedef struct Hareket {
	int musteriNo; 
	char adSoyad[30]; 
	char sube[20]; 
	char islem[20] ; 
	time_t tarih; 	
} hareket  ;

void musteriEkle() 
{
	srand(time(0)); 

	
	system("cls"); 
	printf("Musteri ekleme ekrani \n\n"); 
	musteri m1; 
	
	printf("TC           : ") ; scanf(" %[^\n]s", m1.tc ); 
	printf("Ad-Soyad     : ") ; scanf(" %[^\n]s", m1.adSoyad ); 
	printf("Dogum Tarih  : ") ; scanf(" %[^\n]s", m1.dogumTarih ); 
	printf("Cinsiyet     : ") ; scanf(" %[^\n]s", &m1.cinsiyet ); 
	printf("Adres        : ") ; scanf(" %[^\n]s", m1.adres ); 
	printf("Telefon      : ") ; scanf(" %[^\n]s", m1.telefon ); 
	printf("E-Posta      : ") ; scanf(" %[^\n]s", m1.eposta ); 
	
	m1.musteriNo= rand() % 1000 + 1000; 
	m1.sifre= rand() % 10000 + 10000; 
	m1.bakiye= 0.0; 
	m1.sifreDurum = 0; 
	m1.hesapDurum= 1; 
	
	FILE * ptr= fopen("musteriler.dat", "a+b") ; 
	fwrite( &m1, sizeof(musteri), 1, ptr); 
	fclose(ptr); 
	printf("\nMusteri kaydi tamam \n"); 
	printf("Tek kullanimlik sifre SMS olarak gonderildi \n") ; 
	printf("gizli sifre ( %d ) \n \n", m1.sifre ) ; 
	
}
void musteriSil() 
{
	srand(time(0)); 
	
	system("cls"); 
	printf("Musteri silme ekrani \n\n"); 
	musteri m1; 
	char tc[20]; 
	printf("TC           : ") ; scanf(" %[^\n]s", tc ); 
	FILE * ptr= fopen("musteriler.dat", "r+b") ; 
	int sonuc=0; 

	while(fread ( &m1, sizeof(musteri), 1, ptr) !=NULL   )
	{
		if( strcmp( tc, m1.tc ) ==0  ) 
		{
			sonuc= 1; 
			break; 
		}
	}
	fclose(ptr); 
	if( sonuc==0 )
	{
		printf("%s numarali musteri kaydi bulunamadi ! \n", tc ); 
	}
	else
	{
		char tercih; 
		printf("%s kisisini silmek istediginize emin misiniz ? (E)  : ", m1.adSoyad ) ; scanf(" %c", &tercih ) ; 
		if( tercih =='e' || tercih =='E' ) 
		{
			ptr= fopen("musteriler.dat", "r+b") ;
			FILE *yptr= fopen("yedek.dat", "w+b") ;			
			int silSonuc=0; 
		
			while(fread ( &m1, sizeof(musteri), 1, ptr) !=NULL   )
			{				
				if( strcmp( tc, m1.tc ) ==0  ) 
				{
					silSonuc=1; 				
				}
				else
				fwrite ( &m1, sizeof(musteri), 1, yptr) ; 				
			}
			fclose(ptr); 
			fclose(yptr); 
			
			if( silSonuc==0 )
			printf("Silme islemi basarisiz ! \n"); 
			else
			{
				remove("musteriler.dat"); 
				rename("yedek.dat", "musteriler.dat") ; 
				printf("%s numarali kisi silindi \n", tc ) ; 				
			}			
		}
		else
		{
			printf("Silme islemi iptal edilmistir \n"); 
		}
		
	}
	
	
	
}
void hesapDondur() 
{
	srand(time(0)); 
	
	system("cls"); 
	printf("Musteri hesap dondurma  ekrani \n\n"); 
	musteri m1; 
	char tc[20]; 
	printf("TC           : ") ; scanf(" %[^\n]s", tc ); 
	FILE * ptr= fopen("musteriler.dat", "r+b") ; 
	int sonuc=0, sayac=0 ; 

	while(fread ( &m1, sizeof(musteri), 1, ptr) !=NULL   )
	{
		if( strcmp( tc, m1.tc ) ==0  ) 
		{
			sonuc= 1; 
			break; 
		}
		sayac++; 
	}	
	if( sonuc==0 )
	{
		printf("%s numarali musteri kaydi bulunamadi ! \n", tc ); 
	}
	else
	{
		rewind(ptr); 
		fseek ( ptr, (sayac) * sizeof(musteri), 0 ) ; 
		m1.hesapDurum= 0; 
		fwrite ( &m1, sizeof(musteri), 1, ptr) ; 
		printf("Hesap donduruldu \n")		; 
	}
	fclose(ptr); 	
	
}
void hesapAktiflestir() 
{
	srand(time(0)); 
	
	system("cls"); 
	printf("Musteri hesap Aktiflestirme  ekrani \n\n"); 
	musteri m1; 
	char tc[20]; 
	printf("TC           : ") ; scanf(" %[^\n]s", tc ); 
	FILE * ptr= fopen("musteriler.dat", "r+b") ; 
	int sonuc=0, sayac=0 ; 

	while(fread ( &m1, sizeof(musteri), 1, ptr) !=NULL   )
	{
		if( strcmp( tc, m1.tc ) ==0  ) 
		{
			sonuc= 1; 
			break; 
		}
		sayac++; 
	}	
	if( sonuc==0 )
	{
		printf("%s numarali musteri kaydi bulunamadi ! \n", tc ); 
	}
	else
	{
		rewind(ptr); 
		fseek ( ptr, (sayac) * sizeof(musteri), 0 ) ; 
		m1.hesapDurum= 1; 
		fwrite ( &m1, sizeof(musteri), 1, ptr) ; 
		printf("Hesap Aktiflestirildi  \n")		; 
	}
	fclose(ptr); 
	
	
}
void musteriListele() 
{
 		
	system("cls"); 
	printf("Musteri listeleme  ekrani \n\n"); 
	int sayac=0;  
	FILE * ptr= fopen("musteriler.dat", "r+b") ; 
 	musteri m1; 
 	printf("%-10s%-15s%-30s%-15s%-10s%-30s%-20s%-30s%-10s%-10s%-10s\n", "Mst.NO", "TC", "AD-SOYAD", "DOG-TARIH","CINSIYET", "ADRES", "TELEFON", "E-POSTA","BAKIYE", "SIF-DURUM", "HSP-DURUM"  ) ;  	
 
	while(fread ( &m1, sizeof(musteri), 1, ptr) !=NULL   )
	{
	 printf("%-10d%-15s%-30s%-15s%-10c%-30s%-20s%-30s%-10.2f%-10d%-10d\n", m1.musteriNo, m1.tc, m1.adSoyad, m1.dogumTarih, m1.cinsiyet, m1.adres, m1.telefon, m1.eposta, m1.bakiye, m1.sifreDurum, m1.hesapDurum    ); 
	sayac++; 	 
	}	
	printf("\nMusteri sayisi : %d \n\n", sayac  ) ; 
	
	fclose(ptr); 	
	
}



int yetkiliMenu() 
{
	int secim; 
	
	printf("\t1- MUSTERI EKLE \n\n"); 
	printf("\t2- MUSTERI SIL  \n\n"); 
	printf("\t3- HESAP DONDUR  \n\n"); 
	printf("\t4- HESAP AKTIFLESTIR  \n\n"); 
	printf("\t5- MUSTERI LISTELE  \n\n"); 	
	printf("\t0- CIKIS   \n\n"); 
	printf("Seciminiz    :  ") ; scanf("%d", &secim); 
	return secim; 	
	
}


void yetkili() 
{
	system("cls"); 
	printf("Sayin Yetkili ADMIN hosgeldiniz... \n\n") ; 
	
	int secim= yetkiliMenu(); 
	
	while( secim != 0 )
	{
		switch(secim )
		{
			case 1: musteriEkle(); break; 
			case 2: musteriSil(); break; 
			case 3: hesapDondur(); break; 
			case 4: hesapAktiflestir(); break; 
			case 5: musteriListele(); break; 			
			case 0: break; 
			default: printf("Hatali secim ! \n"); break; 
		}
		secim= yetkiliMenu(); 
	}
	system("cls") ; 
	printf("ADMIN cikis yaptiniz ... ") ; 
	
}

void yetkiliGiris()
{
	system("cls"); 
	printf("Yetkili Giris Ekrani \n\n"); 
	char tc[20];
	int parola; 
		
		printf("TC        : "); scanf(" %[^\n]s", tc ); 
		printf("PAROLA    : "); scanf(" %d", &parola ); 
		
		if( strcmp( tc, "admin" ) ==0 && parola == 123 ) 
		yetkili(); 
		else
		printf("Hatali giris denemesi ! \n") ; 	
}

void hareketKaydet(musteri m1, char * islemPtr ) 
{
	hareket h1; 
	h1.musteriNo = m1.musteriNo; 
	strcpy( h1.adSoyad, m1.adSoyad ) ; 
	strcpy( h1.islem, islemPtr ) ;  
	strcpy( h1.sube, "Eregli Sb." ) ; 
	h1.tarih = time(0); 
	
	char dosyaAdi[20]; 
	
	strcpy( dosyaAdi, m1.tc ) ; 
	strcat( dosyaAdi, ".dat" ) ; 
	FILE *ptr= fopen( dosyaAdi, "a+b") ; 
	fwrite( &h1, sizeof(hareket), 1, ptr ); 
	fclose(ptr); 
//	printf("Hareket kaydi tamam \n\n"); 		
	
}

void bakiyeGuncelle(musteri m1, float para ) 
{ 
	
 	FILE *ptr = fopen("musteriler.dat", "r+b" ) ; 
 	int sayac=0; 
 	musteri m2; 
	while( fread( &m2, sizeof(musteri), 1, ptr ) !=NULL  )
	{
		if( strcmp( m1.tc, m2.tc) ==0   ) 
		break; 
		
		sayac++; 
	}
	rewind(ptr) ; 
	m2.bakiye += para; 
	fseek( ptr, (sayac) * sizeof(musteri), 0 ) ; 	 
	fwrite ( &m2, sizeof(musteri), 1, ptr ) ; 
//	printf("Bakiye guncellendi \n\n") ; 	
	fclose(ptr) ; 
	
	
}
void paraCek(musteri m1 ) 
{
	system("cls"); 
	printf("Para Cekme Ekrani... \n\n ") ; 
	float ucret; 
	printf("Ucret   :  "); scanf("%f", &ucret ) ; 
	musteri m2; 
	FILE *ptr = fopen("musteriler.dat", "r+b" ) ; 
	while( fread( &m2, sizeof(musteri), 1, ptr ) !=NULL  )
	{
		if( strcmp( m1.tc, m2.tc) ==0   ) 
		break; 
	}
	fclose(ptr); 
	if( ucret >m2.bakiye  ) 
	printf("Yetersiz Bakiye \n") ; 
	else
	{
		bakiyeGuncelle(m2, -ucret); 
		hareketKaydet(m2, "Para cekme"); 
		printf("Para cekme islemi tamam \n") ; 
	}
	
}
void paraYatir(musteri m1) 
{
	system("cls"); 
	printf("Para Yatirma Ekrani... \n\n ") ; 
	float ucret; 
	printf("Ucret   :  "); scanf("%f", &ucret ) ; 
	musteri m2; 
	FILE *ptr = fopen("musteriler.dat", "r+b" ) ; 
	while( fread( &m2, sizeof(musteri), 1, ptr ) !=NULL  )
	{
		if( strcmp( m1.tc, m2.tc) ==0   ) 
		break; 
	}
	fclose(ptr); 
		bakiyeGuncelle(m2, ucret); 
		hareketKaydet(m2, "Para yatirma"); 
		printf("Para yatirma islemi tamam \n") ; 
	
}
void havaleEFT(musteri m1)
{
	system("cls"); 
	printf("Havale /EFT Ekrani... \n\n ") ; 
	
	float ucret; 
	int musteriNo; 
	char adSoyad[20]; 
	printf("Hesap No   :  "); scanf("%d", &musteriNo ) ; 
	printf("Ad Soyad   :  "); scanf(" %[^\n]s", adSoyad ) ; 	
	printf("Ucret (TL) :  "); scanf("%f", &ucret ) ; 
	
	musteri m2; 
	int sonuc=0; 
	FILE *ptr = fopen("musteriler.dat", "r+b" ) ; 
	while( fread( &m2, sizeof(musteri), 1, ptr ) !=NULL  )
	{
		if( musteriNo == m2.musteriNo && strcmp( adSoyad, m2.adSoyad ) ==0   ) 
		{
			sonuc=1; 
			break;
		}		 
	}
	fclose(ptr); 
	ptr = fopen("musteriler.dat", "r+b" ) ; 
	
	if( sonuc==0 )
	{
		printf("Alici hasep numarasi veya ad/soyad bilgilerinde hatali islem yaptaniz ! \n") ; 	
		return; 	
	}
		
	musteri m3; 
	int sonuc2=0; 
	while( fread( &m3, sizeof(musteri), 1, ptr ) !=NULL  )
	{
		if(  strcmp( m1.tc, m3.tc )   ==0  ) 
		{
			sonuc2=1; 
			break; 					
		}
	}
	fclose(ptr); 
	if(  ucret > m3.bakiye  ) 
	{
		printf("Yetersiz bakiye ! \n") ; 
	}
	else
	{
		bakiyeGuncelle(m3, -ucret ) ; 
		bakiyeGuncelle(m2, ucret ) ; 
		
		hareketKaydet(m3, "Havale gonderdi" ) ; 
		hareketKaydet(m2, "Havale aldi " ) ; 
				
		printf("Havale islemi tamam \n") ; 
		
	}
		
	
}
void bakiyeSorgula(musteri m1) 
{
	system("cls"); 
	printf("Bakiye Sorgulama Ekrani... \n\n ") ; 
	
	musteri m2; 
	FILE *ptr = fopen("musteriler.dat", "r+b" ) ; 
	while( fread( &m2, sizeof(musteri), 1, ptr ) !=NULL  )
	{
		if( strcmp( m1.tc, m2.tc) ==0   ) 
		break; 
	}
	fclose(ptr); 
		printf("\nBakiyeniz : %.2f TL \n\n", m2.bakiye ) ; 
		hareketKaydet(m2, "Bakiye sorgulama"); 
		
}
void sifreDegistir(musteri m1) 
{
	system("cls"); 
	printf("%s Sifre degitirme ekrani... \n\n", m1.adSoyad  ); 
	int eskiSifre, yeni, sifreTekrar; 
	
	printf("Eski Sifre        : ") ; scanf("%d", &eskiSifre) ; 
	printf("Yeni Sifre        : ") ; scanf("%d", &yeni ) ; 
	printf("Yeni Sifre Tekrar : ") ; scanf("%d", &sifreTekrar) ; 
	int sonuc=0, sayac =0 ; 
	if( m1.sifre== eskiSifre  && yeni == sifreTekrar  ) 
	{
		musteri m2; 
		FILE *ptr= fopen("musteriler.dat", "r+b") ; 
		while( fread ( &m2, sizeof(musteri), 1, ptr ) !=NULL   ) 
		{
			if(  strcmp(  m1.tc, m2.tc) ==0  ) 
			{
				sonuc=1; 
				break; 
			}
			sayac++; 
		}
		if( sonuc==0)		
		{
			printf("Sifre degistirme isleminde hata olustu ! \n"); 
			fclose(ptr); 			
		}
		else
		{
			rewind(ptr); 
			fseek ( ptr, (sayac) * sizeof(musteri), 0 ) ; 
			//m2.sifreDurum= 1; 
			m2.sifre= yeni; 
			fwrite ( &m2, sizeof(musteri), 1, ptr ) ; 
			fclose(ptr); 
			printf("Sifre degistirme islemi basarili \n\n") ; 
			hareketKaydet(m2, "Sifre Degisimi") ; 
			fclose(ptr); 
				
		}
		
	}
	else 
	{
		printf("Hatali sifre degistirme islemi ! \n") ; 
	}
	  	
}

void hareketRaporu(musteri m1) 
{
	system("cls") ; 
	printf("Hareket rapor ekrani... \n\n"); 
	
	hareket h1; 
	int sayac=0; 
	
	char dosyaAdi[20]; 
	
	strcpy( dosyaAdi, m1.tc ) ; 
	strcat( dosyaAdi, ".dat" ) ; 
	FILE *ptr= fopen( dosyaAdi, "r+b") ; 
	
	printf("%-10s%-30s%-20s%-20s%-30s\n", "Mst.No", "AD-SOYAD", "SUBESI", "ISLEM", "TARIH"  ) ; 	
	while  ( fread( &h1, sizeof(hareket), 1, ptr ) != NULL  )
	{
		printf("%-10d%-30s%-20s%-20s%-30s\n", h1.musteriNo, h1.adSoyad, h1.sube, h1.islem, ctime(&h1.tarih) ) ; 
		sayac++; 
	}	
	fclose(ptr); 
	
	printf("\nToplam islem sayisi : %d \n", sayac )	; 
}

int musteriMenu() 
{
	int secim; 
	
	printf("\t1- PARA CEK \n\n"); 
	printf("\t2- PARA YATIR  \n\n"); 
	printf("\t3- HAVALE/ EFT  \n\n"); 
	printf("\t4- BAKIYE SORGULA  \n\n"); 
	printf("\t5- SIFRE DEGISTIRME  \n\n"); 	
	printf("\t6- HAREKET RAPORU \n\n"); 	
	printf("\t0- CIKIS   \n\n"); 
	printf("Seciminiz    :  ") ; scanf("%d", &secim); 
	return secim; 
	
	
}


void musterimiz ( musteri m1 ) 
{
	system("cls"); 
	printf("Sayin %s Hosgeldiniz... \n\n", m1.adSoyad ) ; 	
	printf("Musteri No : %d \n" , m1.musteriNo ) ; 
	
	
	int secim= musteriMenu(); 
	
	
	while( secim != 0 )
	{
		switch(secim )
		{
			case 1: paraCek(m1); break; 
			case 2: paraYatir(m1); break; 
			case 3: havaleEFT(m1); break; 
			case 4: bakiyeSorgula(m1); break; 
			case 5: sifreDegistir(m1); break; 			
			case 6: hareketRaporu(m1); break; 			
			
			case 0: break; 
			default: printf("Hatali secim ! \n"); break; 
		}
		secim= musteriMenu(); 
	}
	
	system("cls"); 
	printf("\n%s cikis yaptiniz ... ", m1.adSoyad ) ; 	
	
}


void sifreDegistirTek(musteri m1)
{
	system("cls"); 
	printf("%s Tek kullanimlik sifrenizi degistiriniz... \n\n", m1.adSoyad  ); 
	int eskiSifre, yeni, sifreTekrar; 
	
	printf("Eski Sifre        : ") ; scanf("%d", &eskiSifre) ; 
	printf("Yeni Sifre        : ") ; scanf("%d", &yeni ) ; 
	printf("Yeni Sifre Tekrar : ") ; scanf("%d", &sifreTekrar) ; 
	int sonuc=0, sayac =0 ; 
	if( m1.sifre== eskiSifre  && yeni == sifreTekrar  ) 
	{
		musteri m2; 
		FILE *ptr= fopen("musteriler.dat", "r+b") ; 
		while( fread ( &m2, sizeof(musteri), 1, ptr ) !=NULL   ) 
		{
			if(  strcmp(  m1.tc, m2.tc) ==0  ) 
			{
				sonuc=1; 
				break; 
			}
			sayac++; 
		}
		if( sonuc==0)		
		{
			printf("Sifre degistirme isleminde hata olustu ! \n"); 
			fclose(ptr); 			
		}
		else
		{
			rewind(ptr); 
			fseek ( ptr, (sayac) * sizeof(musteri), 0 ) ; 
			m2.sifreDurum= 1; 
			m2.sifre= yeni; 
			fwrite ( &m2, sizeof(musteri), 1, ptr ) ; 
			fclose(ptr); 
			printf("Sifre degistirme islemi basarili, yeni sifreniz ile giris yapabilirsiniz \n\n") ; 
			fclose(ptr); 
			
		}
		
	}
	else 
	{
		printf("Hatali sifre degistirme islemi ! \n") ; 
	}
	

		
}


void musteriGiris() 
{
	system("cls"); 
	printf("Musteri Giris Ekrani \n\n"); 
	char tc[20];
	int parola; 
		
		printf("TC        : "); scanf(" %[^\n]s", tc ); 
		printf("PAROLA    : "); scanf(" %d", &parola ); 
		FILE *ptr= fopen("musteriler.dat","r+b") ; 
		musteri m1; 
		int sonuc=0; 
		
		while(  fread( &m1, sizeof(musteri), 1, ptr ) != NULL  ) 
		{
			if( strcmp( tc, m1.tc ) ==0 && parola == m1.sifre   ) 
			{
				sonuc=1; 
				break; 				
			}			 
		}
		fclose(ptr) ; 
		if( sonuc==0)
		{
			printf("Hatali giris denemesi \n"); 			
		}
		else
		{	
			if( m1.sifreDurum==0  ) 
			sifreDegistirTek(m1) ; 
			else if( m1.hesapDurum==0 ) 
			{
				printf("\nHesabiniz dondurulmustur, Lutfen banka subeniz ile gorusunuz... \n") ; 
			}
			else 				
			musterimiz ( m1 ); 
			
		}
	
	
}

int menu() 
{
	int secim; 
	printf("\n\n\tBANKAMATIK OTOMASYONU \n\n"); 
	printf("\t1- MUSTERI GIRIS \n\n"); 
	printf("\t2- YETKILI GIRIS \n\n"); 
	printf("\t0- PROGRAMI KAPAT  \n\n"); 
	printf("Seciminiz    :  ") ; scanf("%d", &secim); 
	return secim; 	
}


int main() 
{
	int secim = menu(); 
	
	while( secim != 0 )
	{
		switch(secim )
		{
			case 1: musteriGiris(); break; 
			case 2: yetkiliGiris(); break; 
			case 0: break; 
			default: printf("Hatali secim ! \n"); break; 
		}
		secim= menu(); 
	}
	
	printf("Program kapatiliyor... ") ; 
	
	
	
	return 0; 
}
