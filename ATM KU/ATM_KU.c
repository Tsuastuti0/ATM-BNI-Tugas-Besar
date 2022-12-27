#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

//pendeklarasian fungsi dan prosedur
void login();
void pin_atm();
void menu();
int cek_saldo();
int transfer();
void input_rek();
void konfirmasi();
void struk_transfer();
void setor_tunai();
int tarik_tunai();
void struk_tarik_tunai();
void ganti_pin();
void keluar();

//pendeklarasian variabel global
int validasi_pin= 0, validasi_login = 0;
int counter_login = 0;
int counter_pin = 0;
struct data u1;
struct data u2;
struct data user;
struct data other;

struct data{ //digunakan untuk menyimpan data dengan berbagai tipe data
	char akun[50]; 
	int rek; 
	int pin;
	double saldo;
};

time_t t;
struct tm *tm;

void validasi_angka(int pilihan) { 
	int angka;  //Variabel untuk menyimpan input angka
	char huruf;  // Variabel untuk menyimpan input karakter
	
	scanf("%c",&huruf);  // Membaca input dari user
	if(huruf != '\n') {      // Mengecek apakah input terdiri dari angka saja atau tidak
		printf("\n\t\t\t\t\tINPUT HANYA BERUPA ANGKA!!\n\n\t\t\t\t\t MOHON INPUTKAN ULANG: \n");  // Jika input terdiri dari karakter lain selain angka, menampilkan pesan error dan meminta user untuk memasukkan input ulang
		fflush(stdin);   //Menghapus buffer input
	}  

}

void validasi_menu(int angka){
    validasi_angka(angka);
    
    if(angka >=1 && angka <=6){
        return angka;
        
    }else{
        printf("\n\t\t\tMASUKKAN PILIHAN YANG TERSEDIA: ");
	}
}

void header(){
	printf("\n");
	printf("\t\t+-------------------------------------------------------------------+\n");
    printf("\t\t|                  SELAMAT DATANG DI BANK BNI SENTAUSA              |\n");
    printf("\t\t|                        Cabang Denpasar Selatan                    |\n");
    printf("\t\t|                      Call center : (0361) 231314                  |\n");
    printf("\t\t+-------------------------------------------------------------------+\n");
}

void login(struct data user){
	system("cls");;
	int rek;
	header();
	if (counter_login<3){ //selama nilai counter login belum 3, maka masih bisa looping. Jika sudah sama dengan 3, maka otomatis akan langsung menjalankan fungsi keluar().
		printf("\n\t\t\t\t\tMASUKKAN USER AKUN ANDA: ");
		scanf("%d", &rek);
		validasi_angka(rek);
		system("pause");
		if(rek == u1.rek){
			validasi_login = 1; 
			pin_atm(u1);
		}else if(rek == u2.rek){
			validasi_login = 1;
			pin_atm(u2);
		}else{
			printf("\n\t\t\t\t\tMASUKKAN NO REKENING YANG BENAR!!\n\t\t");
			counter_login++;
			login(user);
		}
	}else{
		system("cls");
		printf("\n\t\tREKENING ANDA TERBLOKIR!!");
		system("pause");
		keluar();
	}
}

void pin_atm(struct data u){
	int pin;
	if(validasi_login != 1){
		login(user);
	}
	system("cls");
	header();
	if(counter_pin<3){ //untuk membatasi inputan agar tidak lebih dari 3 kali
		printf("\n\t\t\t\t\tMASUKKAN 4 DIGIT PIN ANDA: ");
		scanf("%d", &pin);
		validasi_angka(pin);
		system("pause");
		if(pin == u.pin){
			validasi_pin=1;
			user = u;
			if(u.rek!=u1.rek){
				other = u1;
			}else{
				other = u2;
			}
			menu();
		}else{
			printf("\n\t\t\t\t\tMASUKKAN PIN YANG BENAR!!");
			counter_pin++;
			pin_atm(u);
		}
	}else{
        printf("\nATM ANDA TERBLOKIR.\nSILAHKAN COBA LAGI NANTI!!\n");
        keluar();
    }
}

void menu(){
	if(validasi_pin != 1){
		login(user);
	}else{
		system("cls");
		int pilih;
		printf("+-------------------------------------------------------------------+\n");
	    printf("|                      -----  MENU UTAMA  -----                     |\n");
	    printf("+---+---------------------------------------------------------------+\n");
	    printf("| 1 <--  CEK SALDO                                SETOR TUNAI --> 4 |\n");
	    printf("| 2 <--  TRANSFER                                  GANTI PIN  --> 5 |\n");
	    printf("| 3 <--  TARIK TUNAI                                  KELUAR  --> 6 |\n");
	    printf("+---+---------------------------------------------------------------+\n");
	    printf("\nPILIHAN: ");scanf("%d", &pilih);
	    validasi_menu(pilih);
	    switch(pilih){
	    	case 1:
	    		cek_saldo();
	    		break;
			case 2:
				input_rek();
				break;
			case 3:
				tarik_tunai();
				break;
			case 4:
				setor_tunai();
				break;
			case 5:
				ganti_pin();
				break;
			case 6:
				keluar();
				exit(0);	
		}
	}
}
int cek_saldo(){
	system("cls");
	int pilih;
	printf("\n");
	printf("+-------------------------------------------------------------------+\n");
	printf("                           SISA SALDO ANDA                           \n");
	printf("                             Rp %.2lf                                \n", user.saldo);
	printf("                                                                     \n");
    printf("           APAKAH ANDA INGIN MELAKUKAN TRANSAKSI YANG LAIN?          \n");
    printf("+-------------------------------------------------------------------+\n");
    printf("                 1. YA                           2. TIDAK            \n");
    printf("\n\t\t\tPILIHAN: ");scanf("%d", &pilih);
    validasi_menu(pilih);
    switch(pilih){
    	case 1:
    		menu();
    		break;
    	default:
    		keluar();
    		break;
	}
	return 0;
}

int transfer(){
	system("cls");
	double nominal;
	printf("\n+======================================================================+\n");
	printf("\n                        MASUKKAN NOMINAL TRANSFER                       \n");
	printf("                              Rp ");scanf("%lf", &nominal);
	validasi_angka(nominal);              
	system("pause");
	if(user.saldo>=nominal){
		return nominal;
	}else{
		printf("+---------------------------------------------------------------------+\n");
	    printf("|            -----  MAAF SALDO ANDA TIDAK MENCUKUPI  -----            |\n");
	    printf("+---------------------------------------------------------------------+\n");
	    cek_saldo();
	}
}

void input_rek(){
	int pilih;
	int rekening;
	double nominal;
	system("cls");
	printf("\t\t\t+====================================================================+\n");
	printf("\t\t\t                    MASUKKAN NOMOR REKENING TUJUAN                    \n");
	printf("\t\t\t                           ");scanf("%d", &rekening);    
	validasi_angka(rekening);
    printf("\n\t\t\t+====================================================================+\n");
	printf("\t\t                       1. BENAR             2. KELUAR                   \n");
    printf("\n\t\t\t\tPILIHAN: ");scanf("%d", &pilih);
    validasi_menu(pilih);
    switch(pilih){
    	case 1:
    		if(rekening != user.rek){
    			if(rekening == other.rek){
    				nominal = transfer();
    				konfirmasi(nominal);
				}else{
					input_rek();
				}
				break;
			}else if(rekening == user.rek){
				printf("\n\t\t\tMAAF, TIDAK BISA MELAKUKAN TRANSFER KE REKENING SENDIRI!\n");
				getch();
				input_rek();
			}
		default:
			keluar();
			break;
	}	
}

void konfirmasi(double nominal){
	int pilih;
	system("cls");
	printf("\t+-------------------------------------------------------------+\n");
	printf("\t            ----      DETAIL TRANSFER      ----                \n");
	printf("\t                      NAMA: %s                                 \n", other.akun);    
    printf("\t                      REKENING: %d                             \n", other.rek);
    printf("\t                      NOMINAL: %.2lf                           \n ", nominal);
    printf("\t+-------------------------------------------------------------+\n");
	printf("\t    1. BENAR          2. KELUAR           3. KEMBALI KE MENU\n\n");
	printf("\n\t\t\t\t PILIHAN: ");scanf("%d", &pilih);
	validasi_menu(pilih);
	switch(pilih){
		case 1:
			user.saldo = user.saldo - nominal;
			other.saldo = other.saldo + nominal;
			struk_transfer(nominal);
			break;
		case 2:
			keluar();
			break;
		default:
			menu();
			break;
	}
}

void struk_transfer(double nominal){
	system("cls");
	char lokasi[100]="BNI Sentausa, Denpasar Selatan";
	time_t t = time(NULL); //Untuk mendapatkan waktu sekarang menyimpannya dalam variabel time_t bernama t
	struct tm tm = *localtime(&t); //Konversi t ke struktur tm bernama tm
	FILE *fPointer = fopen("transfer_receipt.txt", "w"); //Membuka file bernama "struk_transfer.txt" dalam mode tulis dan simpan handle ke file ke dalam pointer FILE bernama fPointer

		printf("\t\t\t+---------------------------------------------------------------------+\n");
	    printf("\t\t\t|               ---  TRANSAKSI TRANSFER SUKSES  ---                   |\n");
	    printf("\t\t\t+---------------------------------------------------------------------+\n");
	    printf("\t\t\t                      TRANSFER KEPADA: %d                             \n", other.rek);
	    printf("\t\t\t                      JUMLAH         : Rp %.2lf                       \n", nominal);
	    printf("\t\t\t                      NAMA PENERIMA  : %s                             \n", other.akun);
	    printf("\t\t\t                      Tanggal        : %d/%d/%d                       \n", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);
		printf("\t\t\t                      Waktu          : %d:%d:%d                       \n", tm.tm_hour, tm.tm_min, tm.tm_sec);
		printf("\t\t\t                      Lokasi         : %s                             \n", lokasi);
	    printf("\t\t\t+--------------------------------------------------------------------+\n");
	    getch();
	    
	    fprintf(fPointer, "\t\t\t+--------------------------------------------------------------------+\n");
	    fprintf(fPointer, "\t\t\t|               ---  TRANSAKSI TRANSFER SUKSES  ---                  |\n");
	    fprintf(fPointer, "\t\t\t+--------------------------------------------------------------------+\n");
	    fprintf(fPointer, "\t\t\t                     TRANSFER KEPADA: %d                              \n", other.rek);
	    fprintf(fPointer, "\t\t\t                     JUMLAH         : Rp %.2lf                        \n", nominal);
	    fprintf(fPointer, "\t\t\t                     NAMA PENERIMA  : %s                              \n", other.akun);
	    fprintf(fPointer, "\t\t\t                     Tanggal        : %d/%d/%d                        \n", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);
		fprintf(fPointer, "\t\t\t                     Waktu          : %d:%d:%d                        \n", tm.tm_hour, tm.tm_min, tm.tm_sec);
		fprintf(fPointer, "\t\t\t                     Lokasi         : %s                              \n", lokasi);
	    fprintf(fPointer, "\t\t\t+--------------------------------------------------------------------+\n");
	    fclose(fPointer);
	    
	    cek_saldo();  
	}

void setor_tunai(){
	int pilih;
	int nominal;
	system("cls");
	printf("+----------------------------------------------------------------------+\n");
	printf("|                 MASUKKAN NOMINAL YANG INGIN DISETOR                  |\n");
	printf("|                HANYA BISA MENERIMA KELIPATAN Rp 50000                |\n");
	printf("|                       Rp ");scanf("%d", &nominal);   
    printf("+----------------------------------------------------------------------+\n");
    printf("            1. BENAR          2. KELUAR       3. KEMBALI KE MENU        \n");
    printf("\nPILIHAN: ");
    scanf("%d", &pilih);
    validasi_menu(pilih);
    switch(pilih){
    	case 1:
    		if(nominal%50000 == 0){
    			printf("SELAMAT ANDA BERHASIL MENYETOR SEBESAR Rp %d\n\n", nominal);
    			user.saldo = user.saldo + nominal;
				system("pause");
				cek_saldo();
			}else if(nominal%50000 != 0){
				printf("\nMASUKKAN PECAHAN YANG BENAR!!\nHANYA MENERIMA PECAHAN 50000/100000\n");
				system("pause");
				setor_tunai();
			    break;
			}
		case 2:
			keluar();
			break;
		default:
			menu();
			break;
	}
}

int tarik_tunai(){
	system("cls");
	int nominal;
	int pilih;
	printf("------------------------------------------------------------------------\n");
	printf("                           MENU PENARIKAN CEPAT                         \n");
	printf("                     SILAHKAN PILIH JUMLAH PENARIKAN                    \n");
	printf("     1 <-- 100000                                      1000000 --> 4    \n");
	printf("     2 <-- 200000                                      1500000 --> 5    \n");
	printf("     3 <-- 300000                                  JUMLAH LAIN --> 6    \n");
	printf("\n\t\t\tPILIHAN: ");
	scanf("%d", &pilih);
	validasi_menu(pilih);
	switch(pilih){
		case 1:
			nominal = 100000;
			if(user.saldo > nominal){
				system("cls");
				printf("\n\t\tSELAMAT ANDA BERHASIL MENARIK SENILAI Rp %d", nominal);
				user.saldo = user.saldo - nominal;
				getch();
				struk_tarik_tunai((double)nominal);
			}else{
			printf("+---------------------------------------------------------------------+\n");
		    printf("|            -----  MAAF SALDO ANDA TIDAK MENCUKUPI  -----            |\n");
		    printf("+---------------------------------------------------------------------+\n");
		    cek_saldo();
			}
		    break;
		case 2:
			nominal = 200000;
			if(user.saldo > nominal){
				system("cls");
				printf("\n\t\tSELAMAT ANDA BERHASIL MENARIK SENILAI Rp %d", nominal);
				user.saldo = user.saldo - nominal;	
				getch();
				struk_tarik_tunai((double)nominal);	
			}else{
			printf("+---------------------------------------------------------------------+\n");
		    printf("|            -----  MAAF SALDO ANDA TIDAK MENCUKUPI  -----            |\n");
		    printf("+---------------------------------------------------------------------+\n");
		    cek_saldo();
			}
			break;
		case 3:
			nominal = 300000;
			if(user.saldo > nominal){
				system("cls");
				printf("\n\t\tSELAMAT ANDA BERHASIL MENARIK SENILAI Rp %d", nominal);
				user.saldo = user.saldo - nominal;
				getch();
				struk_tarik_tunai((double)nominal);
			}else{
			printf("+---------------------------------------------------------------------+\n");
		    printf("|            -----  MAAF SALDO ANDA TIDAK MENCUKUPI  -----            |\n");
		    printf("+---------------------------------------------------------------------+\n");
		    cek_saldo();
		    }
		    break;
		case 4:
			nominal = 1000000;
			if(user.saldo > nominal){
				system("cls");
				printf("\n\t\tSELAMAT ANDA BERHASIL MENARIK SENILAI Rp %d", nominal);
				user.saldo = user.saldo - nominal;
			    getch();
				struk_tarik_tunai((double)nominal);
			}else{
			printf("+---------------------------------------------------------------------+\n");
		    printf("|            -----  MAAF SALDO ANDA TIDAK MENCUKUPI  -----            |\n");
		    printf("+---------------------------------------------------------------------+\n");
		    cek_saldo();
		    }
		    break;
		case 5:
		   	nominal = 1500000;
			if(user.saldo > nominal){
				system("cls");
				printf("\n\t\tSELAMAT ANDA BERHASIL MENARIK SENILAI Rp %d", nominal);
				user.saldo = user.saldo - nominal;
				getch();
				struk_tarik_tunai((double)nominal);
			}else{
			printf("+---------------------------------------------------------------------+\n");
		    printf("|            -----  MAAF SALDO ANDA TIDAK MENCUKUPI  -----            |\n");
		    printf("+---------------------------------------------------------------------+\n");
		    cek_saldo();
		    break;
		    }
		case 6:
			system("cls");
			printf("+----------------------------------------------------------------------+\n");
			printf("                  MASUKKAN NOMINAL KELIPATAN RP 50000                   \n");
			printf("                            Rp ");scanf("%d", &nominal);              
		    printf("------------------------------------------------------------------------\n");
		    printf("           1. BENAR             2. KELUAR           3. KEMBALI          \n");
		    printf("\n\t\tPilihan: ");scanf("%d", &pilih);
		    switch(pilih){
		   	case 1:
	    		if(nominal%50000 == 0){
	    			printf("\n\t\tSELAMAT ANDA BERHASIL MENARIK SENILAI Rp %2.lf", nominal);
	    			user.saldo = user.saldo - nominal;
	    			getch();
					struk_tarik_tunai((double)nominal);
				}else if(nominal%50000 != 0){
					printf("\nMASUKKAN PECAHAN YANG BENAR!!\nHANYA MENERIMA PECAHAN 50000/100000\n");
					system("pause");
					tarik_tunai();
				}else{
					printf("+---------------------------------------------------------------------+\n");
				    printf("|            -----  MAAF SALDO ANDA TIDAK MENCUKUPI  -----            |\n");
				    printf("+---------------------------------------------------------------------+\n");
				    cek_saldo();
				    break;
				}
			case 2:
				keluar();
				break;
			default:
				menu();
				break;
		}
	}
}

void struk_tarik_tunai(double nominal){
	system("cls");
	char lokasi[100]="BNI Sentausa, Denpasar Selatan";
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	FILE *fPointer = fopen("tarik_receipt.txt", "a+");
		printf("\t\t\t+---------------------------------------------------------------------+\n");
	    printf("\t\t\t|               ---  TRANSAKSI TARIK TUNAI SUKSES  ---                |\n");
	    printf("\t\t\t+---------------------------------------------------------------------+\n");
	    printf("\t\t\t                 JUMLAH      : Rp %.2lf                                \n", nominal);
	    printf("\t\t\t                 NO REKENING : %d                                      \n", user.rek);
	    printf("\t\t\t                 Tanggal     : %d/%d/%d                                \n", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);
		printf("\t\t\t                 Waktu       : %d:%d:%d                                \n", tm.tm_hour, tm.tm_min, tm.tm_sec);
		printf("\t\t\t                 Lokasi      : %s                                      \n", lokasi);
	    printf("\t\t\t+---------------------------------------------------------------------+\n");
	    getch();
	    
	    fprintf(fPointer, "\t\t\t+---------------------------------------------------------------------+\n");
	    fprintf(fPointer, "\t\t\t|               ---  TRANSAKSI TARIK TUNAI SUKSES  ---                |\n");
	    fprintf(fPointer, "\t\t\t+---------------------------------------------------------------------+\n");
	    fprintf(fPointer, "\t\t\t                 JUMLAH      : Rp %.2lf                                \n", nominal);
	    fprintf(fPointer, "\t\t\t                 NO REKENING : %d                                      \n", user.rek);
	    fprintf(fPointer, "\t\t\t                 Tanggal     : %d/%d/%d                                \n", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);
		fprintf(fPointer, "\t\t\t                 Waktu       : %d:%d:%d                                \n", tm.tm_hour, tm.tm_min, tm.tm_sec);
		fprintf(fPointer, "\t\t\t                 Lokasi      : %s                                      \n", lokasi);
	    fprintf(fPointer, "\t\t\t+---------------------------------------------------------------------+\n");
	    fclose(fPointer);
	    
	    system("cls");
	    cek_saldo();
	}

void ganti_pin(){
	system("cls");
	int pilih;
	int pin;
	printf("\n\t\t\tMASUKKAN 4 DIGIT PIN LAMA ANDA: ");
	scanf("%d", &pin);
	if(pin == user.pin){
		printf("\n\t\t\tMASUKKAN PIN BARU: ");
		scanf("%d", &pin);
		printf("\n\t\t\t\tPIN BERHASIL DIGANTI!!");
	}else{
		printf("\n\t\t\tANDA MEMASUKKAN PIN YANG SALAH!!");
		printf("\n\t\t\tULANGI KEMBALI");
		ganti_pin();
	}
	printf("\n\t\t\tAPA ANDA INGIN MELAKUKAN TRANSAKSI KEMBALI?\n");
	printf("\n\t\t\t        1. YA               2. TIDAK       \n");
	printf("\n\t\tPILIHAN: ");
	scanf("%d", &pilih);
	validasi_menu(pilih);
	switch(pilih){
    	case 1:
    		menu();
    		break;
    	default:
    		keluar();
    		break;
	}
}

void keluar(){
	system("cls");
	printf("+-------------------------------------------------------------------+\n");
	printf("+         --------         BANK BNI SENTAUSA        --------        +\n");
    printf("|      ------  TERIMAKASIH TELAH MENGGUNAKAN LAYANAN INI  -----     |\n");
    printf("+-------------------------------------------------------------------+\n");
    exit(0);
}

//menyimpan assign data struct ke dalam fungsi main
int main(){
	strcpy(u1.akun , "Tami Suastuti");
	u1.rek = 112233;
	u1.pin = 1234;
	u1.saldo = 10000000;
	
	strcpy(u2.akun, "Zaskia Alia");
	u2.rek = 223344;
	u2.pin = 4321;
	u2.saldo = 5000000;

	menu();
	
	return 0;
}
