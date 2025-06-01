#include "menuHelp.h"

static void normalizeCommand(char *command)
{
    int i = 0, j = 0;

    while (command[i])
    {

        if (command[i] != '_')
        {

            command[j] = (command[i] >= 'a' && command[i] <= 'z') ? command[i] - 32 : command[i];
            j++;
        }
        i++;
    }
    command[j] = '\0';
}

static void printFootnote()
{
    printf("\nFootnote:\n");
    printf("Untuk menggunakan aplikasi, silahkan masukkan nama fungsi yang terdaftar\n");
    printf("Jangan lupa untuk memasukkan input yang valid\n");
}

void displayMenu(Session *session)
{

    if (session == NULL)
    {
        printError("Sesi tidak valid!");
        return;
    }

    printHeader("Daftar Perintah");

    const char *menu[20];
    int count = 0;

    int widths[] = {20};

    if (!session->isLoggedIn)
    {

        printf(COLOR_YELLOW "Anda belum login. Perintah yang tersedia:\n" COLOR_RESET);

        menu[count++] = "LOGIN";
        menu[count++] = "REGISTER_PASIEN";
        menu[count++] = "LUPA_PASSWORD";
        menu[count++] = "MENU";
        menu[count++] = "HELP";
        menu[count++] = "EXIT";
    }

    else
    {

        switch (session->role)
        {
        case DOCTOR:

            printf(COLOR_YELLOW "Halo Dokter %s. Kamu memanggil command HELP. Kamu pasti sedang kebingungan. Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n" COLOR_RESET, session->username);

            menu[count++] = "LOGOUT";
            menu[count++] = "MENU";
            menu[count++] = "HELP";
            menu[count++] = "LIHAT_DENAH";
            menu[count++] = "DIAGNOSIS";
            menu[count++] = "NGOBATIN";
            menu[count++] = "LIHAT_DOMPET";
            menu[count++] = "EXIT";
            break;
        case MANAGER:

            printf(COLOR_YELLOW "Halo Manager %s. Kenapa kamu memanggil command HELP? Kan kamu manager, tapi yasudahlah kamu pasti sedang kebingungan. Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n" COLOR_RESET, session->username);

            menu[count++] = "LOGOUT";
            menu[count++] = "MENU";
            menu[count++] = "HELP";
            menu[count++] = "LIHAT_DENAH";
            menu[count++] = "LIHAT_USER";
            menu[count++] = "CARI_USER";
            menu[count++] = "LIHAT_ANTRIAN";
            menu[count++] = "TAMBAH_DOKTER";
            menu[count++] = "UBAH_DENAH";
            menu[count++] = "PINDAH_DOKTER";
            menu[count++] = "LIHAT_FINANSIAL";
            menu[count++] = "EXIT";
            break;
        case PATIENT:

            printf(COLOR_YELLOW "Selamat datang, %s. Kamu memanggil command HELP. Kamu pasti sedang kebingungan. Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n" COLOR_RESET, session->username);

            menu[count++] = "LOGOUT";
            menu[count++] = "MENU";
            menu[count++] = "HELP";
            menu[count++] = "LIHAT_DENAH";
            menu[count++] = "PULANG_DOK";
            menu[count++] = "DAFTAR_CHECKUP";
            menu[count++] = "ANTRIAN_SAYA";
            menu[count++] = "MINUM_OBAT";
            menu[count++] = "MINUM_PENAWAR";
            menu[count++] = "LIHAT_DOMPET";
            menu[count++] = "GACHA";
            menu[count++] = "LEWATI_ANTRIAN";
            menu[count++] = "BATALKAN_ANTRIAN";
            menu[count++] = "EXIT";
            break;
        }
    }

    printTableBorder(widths, 1, 1);

    for (int i = 0; i < count; i++)
    {
        printTableRow(&menu[i], widths, 1);
    }
    printTableBorder(widths, 1, 3);

    printFootnote();
}

void displayHelp(Session *session, const char *command)
{

    if (session == NULL)
    {
        printError("Sesi tidak valid!");
        return;
    }

    if (command == NULL || command[0] == '\0')
    {
        printError("Perintah tidak valid!");
        return;
    }

    char normalCommand[50];
    strcpy(normalCommand, command);
    normalizeCommand(normalCommand);

    printHeader("Bantuan Perintah");
    printf("\n");

    if (!session->isLoggedIn)
    {
        printf("Anda belum login! Silakan login terlebih dahulu.\n");

        printf("Bantuan untuk perintah '%s%s%s':\n", FORMAT_BOLD, command, FORMAT_RESET);
        printf("────────────────────────────────────────────────────────\n");

        if (strcmp(normalCommand, "LOGIN") == 0)
        {
            printf("  🔑 %sLOGIN%s\n", FORMAT_BOLD, FORMAT_RESET);
            printf("     Deskripsi: Masuk ke sistem dengan username dan password Anda.\n");
        }
        else if (strcmp(normalCommand, "REGISTERPATIENT") == 0)
        {
            printf("  📝 %sREGISTER_PATIENT%s\n", FORMAT_BOLD, FORMAT_RESET);
            printf("     Deskripsi: Daftar sebagai pasien baru dengan username dan password.\n");
        }
        else if (strcmp(normalCommand, "LUPAPASSWORD") == 0)
        {
            printf("  ❓ %sLUPA_PASSWORD%s\n", FORMAT_BOLD, FORMAT_RESET);
            printf("     Deskripsi: Atur ulang kata sandi menggunakan username dan kode verifikasi (RLE).\n");
        }
        else if (strcmp(normalCommand, "MENU") == 0)
        {
            printf("  📜 %sMENU%s\n", FORMAT_BOLD, FORMAT_RESET);
            printf("     Deskripsi: Tampilkan daftar semua perintah yang tersedia untuk Anda saat ini.\n");
        }
        else if (strcmp(normalCommand, "HELP") == 0)
        {
            printf("  ℹ️  %sHELP%s\n", FORMAT_BOLD, FORMAT_RESET);
            printf("     Deskripsi: Tampilkan bantuan detail untuk perintah tertentu.\n");
        }
        else if (strcmp(normalCommand, "EXIT") == 0)
        {
            printf("  🚪 %sEXIT%s\n", FORMAT_BOLD, FORMAT_RESET);
            printf("     Deskripsi: Keluar dari sistem aplikasi.\n");
        }
        else
        {
            char errorMessage[100] = "";
            strcat(errorMessage, "Perintah '");
            strcat(errorMessage, command);
            strcat(errorMessage, "' tidak dikenal atau tidak tersedia saat ini.");
            printError(errorMessage);
        }
    }

    else
    {

        printf("Anda login sebagai %s%s%s.\n", FORMAT_BOLD, (session->role == MANAGER) ? "Manajer" : (session->role == DOCTOR) ? "Dokter"
                                                                                                                               : "Pasien",
               FORMAT_RESET);

        printf("Bantuan untuk perintah '%s%s%s':\n", FORMAT_BOLD, command, FORMAT_RESET);
        printf("────────────────────────────────────────────────────────\n");

        switch (session->role)
        {
        case MANAGER:
            if (strcmp(normalCommand, "LOGOUT") == 0)
            {
                printf("  🚪 %sLOGOUT%s\n     Deskripsi: Keluar dari sesi Anda saat ini.\n", FORMAT_BOLD, FORMAT_RESET);
            }
            else if (strcmp(normalCommand, "MENU") == 0)
            {
                printf("  📜 %sMENU%s\n     Deskripsi: Tampilkan daftar semua perintah yang tersedia.\n", FORMAT_BOLD, FORMAT_RESET);
            }
            else if (strcmp(normalCommand, "HELP") == 0)
            {
                printf("  ℹ️  %sHELP%s\n     Deskripsi: Tampilkan bantuan untuk perintah tertentu.\n", FORMAT_BOLD, FORMAT_RESET);
            }
            else if (strcmp(normalCommand, "LIHATDENAH") == 0)
            {
                printf("  🗺️ %sLIHAT_DENAH%s\n     Deskripsi: Tampilkan denah rumah sakit atau detail ruangan tertentu.\n", FORMAT_BOLD, FORMAT_RESET);
            }
            else if (strcmp(normalCommand, "LIHATUSER") == 0)
            {
                printf("  👥 %sLIHAT_USER%s\n     Deskripsi: Tampilkan daftar semua pengguna (pasien atau dokter).\n", FORMAT_BOLD, FORMAT_RESET);
            }
            else if (strcmp(normalCommand, "CARIUSER") == 0)
            {
                printf("  🔍 %sCARI_USER%s\n     Deskripsi: Cari pengguna berdasarkan ID atau username.\n", FORMAT_BOLD, FORMAT_RESET);
            }
            else if (strcmp(normalCommand, "LIHATANTRIAN") == 0)
            {
                printf("  🚶 %sLIHAT_ANTRIAN%s\n     Deskripsi: Tampilkan antrian pasien di setiap ruangan atau ruangan tertentu.\n", FORMAT_BOLD, FORMAT_RESET);
            }
            else if (strcmp(normalCommand, "TAMBAHDOKTER") == 0)
            {
                printf("  👨‍⚕️ %sTAMBAH_DOKTER%s\n     Deskripsi: Tambah dokter baru ke sistem atau tetapkan dokter ke ruangan.\n", FORMAT_BOLD, FORMAT_RESET);
            }
            else if (strcmp(normalCommand, "UBAHDENAH") == 0)
            {
                printf("  ✏️ %sUBAH_DENAH%s\n     Deskripsi: Ubah ukuran denah rumah sakit (jumlah baris dan kolom).\n", FORMAT_BOLD, FORMAT_RESET);
            }
            else if (strcmp(normalCommand, "PINDAHDOKTER") == 0)
            {
                printf("  🔄 %sPINDAH_DOKTER%s\n     Deskripsi: Pindahkan dokter dari satu ruangan ke ruangan lain.\n", FORMAT_BOLD, FORMAT_RESET);
            }
            else if (strcmp(normalCommand, "LIHATFINANSIAL") == 0)
            {
                printf("  💰 %sLIHAT_FINANSIAL%s\n     Deskripsi: Tampilkan laporan keuangan rumah sakit.\n", FORMAT_BOLD, FORMAT_RESET);
            }
            else if (strcmp(normalCommand, "EXIT") == 0)
            {
                printf("  🚪 %sEXIT%s\n     Deskripsi: Keluar dari sistem aplikasi.\n", FORMAT_BOLD, FORMAT_RESET);
            }
            else
            {
                char errorMessage[100] = "";
                strcat(errorMessage, "Perintah '");
                strcat(errorMessage, command);
                strcat(errorMessage, "' tidak dikenal atau tidak tersedia untuk Manajer.");
                printError(errorMessage);
            }
            break;

        case DOCTOR:
            if (strcmp(normalCommand, "LOGOUT") == 0)
            {
                printf("  🚪 %sLOGOUT%s\n     Deskripsi: Keluar dari sesi Anda saat ini.\n", FORMAT_BOLD, FORMAT_RESET);
            }
            else if (strcmp(normalCommand, "MENU") == 0)
            {
                printf("  📜 %sMENU%s\n     Deskripsi: Tampilkan daftar semua perintah yang tersedia.\n", FORMAT_BOLD, FORMAT_RESET);
            }
            else if (strcmp(normalCommand, "HELP") == 0)
            {
                printf("  ℹ️  %sHELP%s\n     Deskripsi: Tampilkan bantuan untuk perintah tertentu.\n", FORMAT_BOLD, FORMAT_RESET);
            }
            else if (strcmp(normalCommand, "LIHATDENAH") == 0)
            {
                printf("  🗺️ %sLIHAT_DENAH%s\n     Deskripsi: Tampilkan denah rumah sakit atau detail ruangan tertentu.\n", FORMAT_BOLD, FORMAT_RESET);
            }
            else if (strcmp(normalCommand, "DIAGNOSIS") == 0)
            {
                printf("  🩺 %sDIAGNOSIS%s\n     Deskripsi: Lakukan diagnosis otomatis untuk pasien di ruangan Anda.\n", FORMAT_BOLD, FORMAT_RESET);
            }
            else if (strcmp(normalCommand, "NGOBATIN") == 0)
            {
                printf("  💊 %sNGOBATIN%s\n     Deskripsi: Berikan resep obat otomatis berdasarkan penyakit pasien.\n", FORMAT_BOLD, FORMAT_RESET);
            }
            else if (strcmp(normalCommand, "LIHATDOMPET") == 0)
            {
                printf("  💵 %sLIHAT_DOMPET%s\n     Deskripsi: Tampilkan saldo BananaRich Anda.\n", FORMAT_BOLD, FORMAT_RESET);
            }
            else if (strcmp(normalCommand, "EXIT") == 0)
            {
                printf("  🚪 %sEXIT%s\n     Deskripsi: Keluar dari sistem aplikasi.\n", FORMAT_BOLD, FORMAT_RESET);
            }
            else
            {
                char errorMessage[100] = "";
                strcat(errorMessage, "Perintah '");
                strcat(errorMessage, command);
                strcat(errorMessage, "' tidak dikenal atau tidak tersedia untuk Dokter.");
                printError(errorMessage);
            }
            break;

        case PATIENT:
            if (strcmp(normalCommand, "LOGOUT") == 0)
            {
                printf("  🚪 %sLOGOUT%s\n     Deskripsi: Keluar dari sesi Anda saat ini.\n", FORMAT_BOLD, FORMAT_RESET);
            }
            else if (strcmp(normalCommand, "MENU") == 0)
            {
                printf("  📜 %sMENU%s\n     Deskripsi: Tampilkan daftar semua perintah yang tersedia.\n", FORMAT_BOLD, FORMAT_RESET);
            }
            else if (strcmp(normalCommand, "HELP") == 0)
            {
                printf("  ℹ️  %sHELP%s\n     Deskripsi: Tampilkan bantuan untuk perintah tertentu.\n", FORMAT_BOLD, FORMAT_RESET);
            }
            else if (strcmp(normalCommand, "LIHATDENAH") == 0)
            {
                printf("  🗺️ %sLIHAT_DENAH%s\n     Deskripsi: Tampilkan denah rumah sakit atau detail ruangan tertentu.\n", FORMAT_BOLD, FORMAT_RESET);
            }
            else if (strcmp(normalCommand, "PULANGDOK") == 0)
            {
                printf("  🚶‍♀️ %sPULANG_DOK%s\n     Deskripsi: Periksa apakah Anda sudah boleh pulang berdasarkan status pengobatan.\n", FORMAT_BOLD, FORMAT_RESET);
            }
            else if (strcmp(normalCommand, "DAFTARCHECKUP") == 0)
            {
                printf("  ➕ %sDAFTAR_CHECKUP%s\n     Deskripsi: Daftar untuk pemeriksaan dengan dokter di ruangan tertentu.\n", FORMAT_BOLD, FORMAT_RESET);
            }
            else if (strcmp(normalCommand, "ANTRIANSAYA") == 0)
            {
                printf("  🔢 %sANTRIAN_SAYA%s\n     Deskripsi: Tampilkan status antrian Anda saat ini.\n", FORMAT_BOLD, FORMAT_RESET);
            }
            else if (strcmp(normalCommand, "MINUMOBAT") == 0)
            {
                printf("  💧 %sMINUM_OBAT%s\n     Deskripsi: Minum obat sesuai urutan yang telah diresepkan oleh dokter.\n", FORMAT_BOLD, FORMAT_RESET);
            }
            else if (strcmp(normalCommand, "MINUMPENAWAR") == 0)
            {
                printf("  🧪 %sMINUM_PENAWAR%s\n     Deskripsi: Minum penawar untuk membatalkan efek obat terakhir yang diminum.\n", FORMAT_BOLD, FORMAT_RESET);
            }
            else if (strcmp(normalCommand, "LIHATDOMPET") == 0)
            {
                printf("  💵 %sLIHAT_DOMPET%s\n     Deskripsi: Tampilkan saldo BananaRich Anda.\n", FORMAT_BOLD, FORMAT_RESET);
            }
            else if (strcmp(normalCommand, "GACHA") == 0)
            {
                printf("  🎰 %sGACHA%s\n     Deskripsi: Gunakan sejumlah BananaRich untuk mencoba peruntungan di mesin gacha.\n", FORMAT_BOLD, FORMAT_RESET);
            }
            else if (strcmp(normalCommand, "LEWATIANTRIAN") == 0)
            {
                printf("  💨 %sLEWATI_ANTRIAN%s\n     Deskripsi: Gunakan item khusus (jika punya) untuk melewati antrian pemeriksaan.\n", FORMAT_BOLD, FORMAT_RESET);
            }
            else if (strcmp(normalCommand, "BATALKANANTRIAN") == 0)
            {
                printf("  ❌ %sBATALKAN_ANTRIAN%s\n     Deskripsi: Batalkan antrian pemeriksaan Anda saat ini.\n", FORMAT_BOLD, FORMAT_RESET);
            }
            else if (strcmp(normalCommand, "EXIT") == 0)
            {
                printf("  🚪 %sEXIT%s\n     Deskripsi: Keluar dari sistem aplikasi.\n", FORMAT_BOLD, FORMAT_RESET);
            }
            else
            {
                char errorMessage[100] = "";
                strcat(errorMessage, "Perintah '");
                strcat(errorMessage, command);
                strcat(errorMessage, "' tidak dikenal atau tidak tersedia untuk Pasien.");
                printError(errorMessage);
            }
            break;
        default:
            printError("Peran pengguna tidak dikenal!");
            break;
        }
    }
}