# Moji: Solusi Monitorisasi Haji Berbasis IoT

Moji merupakan sebuah solusi monitorisasi haji yang inovatif, dirancang sebagai perangkat Internet of Things (IoT) dengan tujuan utama untuk mengatasi dan mencegah masalah kehilangan atau penyimpangan jamaah haji. Perangkat ini disediakan kepada setiap jemaah sebagai sarana untuk memungkinkan petugas melaksanakan pemantauan yang efisien terhadap pergerakan jamaah. Dilengkapi dengan teknologi GPS canggih, sensor suhu udara, dan pengukuran kelembaban, Moji tidak hanya menjamin keamanan jamaah, tetapi juga memberikan informasi yang berharga untuk pengelolaan optimal selama perjalanan haji. Dengan Moji, kita memasuki era baru dalam penyelenggaraan haji yang lebih terencana, aman, dan berfokus pada kebutuhan jamaah. Perangkat ini menggunakan konsep Internet of Things (IoT) dan dilengkapi dengan berbagai komponen canggih, termasuk:

- Papan Arduino yang handal
- Sensor DHT untuk pemantauan suhu dan kelembaban udara
- Modul GPS untuk pelacakan akurat lokasi
- Layar LCD yang informatif

Selain itu, Moji juga dibekali dengan baterai daya tahan seharian, sehingga memungkinkan operasional yang lancar tanpa khawatir kehabisan daya. Moji berperan sebagai alat yang memberikan informasi real-time kepada petugas dan jamaah, dengan tujuan meningkatkan pengawasan dan pengelolaan proses perjalanan haji secara efisien.

Dalam era di mana teknologi semakin berperan dalam berbagai aspek kehidupan, Moji menjadi contoh nyata bagaimana konsep IoT dan komponen teknologi modern dapat digunakan untuk meningkatkan kualitas, keamanan, dan pengalaman dalam menjalankan ibadah haji.

## Komponen Alat Moji terdiri dari beberapa komponen utama yang bekerja secara sinergis:

- **Papan Arduino**: Digunakan sebagai otak perangkat, mengendalikan berbagai sensor dan modul.

- **Sensor DHT**: Memonitor suhu dan kelembaban udara di sekitar perangkat.

- **Modul GPS**: Menggunakan GPS untuk pelacakan akurat lokasi perangkat.

- **Layar LCD**: Menampilkan informasi penting kepada petugas dan jamaah.

## Jalur Kabel Jalur kabel pada Moji dirancang untuk koneksi yang efisien:

1. Hubungkan sensor DHT ke pin analog Arduino.

   | Fungsi | Pin Arduino | Keterangan                               |
   | ------ | ----------- | ---------------------------------------- |
   | data   | A0          | Mengukur suhu udara di sekitar perangkat |
   | VCC    | VCC         | Potensial Positif                        |
   | GND    | GND         | Potensial Negatif                        |

2. Sambungkan modul GPS ke pin komunikasi serial Arduino.

   | Fungsi | Pin Arduino | Keterangan        |
   | ------ | ----------- | ----------------- |
   | TX     | A1          | TX                |
   | RX     | A2          | RX                |
   | VCC    | VCC         | Potensial Positif |
   | GND    | GND         | Potensial Negatif |

3. Koneksikan layar LCD dengan pin yang ditentukan di papan Arduino.

   | Fungsi | Pin Arduino | Keterangan        |
   | ------ | ----------- | ----------------- |
   | SDA    | A4          | SDA               |
   | SCL    | A5          | SCL               |
   | VCC    | VCC         | Potensial Positif |
   | GND    | GND         | Potensial Negatif |

## Panduan Pengunduhan Kode Moji dari GitHub

### Prasyarat

- Komputer dengan akses internet.
- Git telah terinstal di komputer Anda (jika ingin melakukan cloning).

### Langkah-langkah:

1. **Buka Repositori GitHub**

   - Buka repositori GitHub tempat Anda telah memposting kode Moji.

2. **Unduh Kode (Download ZIP)**

   1. Di repositori GitHub, klik tombol "Code" di bagian kanan atas.
   2. Pilih "Download ZIP" untuk mengunduh kode dalam bentuk file ZIP.
   3. Ekstrak file ZIP di komputer Anda.

3. **Clone Repositori (Opsional)**

   1. Buka terminal atau command prompt di komputer Anda.
   2. Pindahkan ke direktori tempat Anda ingin menyimpan repositori Moji dengan perintah `cd nama_direktori`.
   3. Jalankan perintah `git clone URL_repositori` untuk mengklon repositori Moji ke direktori tersebut.
   4.

## Panduan Penggunaan Kode Moji di Arduino IDE

### Prasyarat

- Perangkat keras Moji yang lengkap dengan komponen yang dijelaskan sebelumnya.
- Komputer dengan akses internet.
- Arduino IDE terinstal di komputer Anda.

### Langkah-langkah:

1. **Buka Arduino IDE**

   1. Buka Arduino IDE di komputer Anda.

2. **Salin dan Tempelkan Kode**

   1. Salin kode Moji yang telah diunduh atau diklon ke dalam area kode (sketch) di Arduino IDE file ada di src/main.cpp

3. **Konfigurasi Pin**

   1. Pastikan bahwa Anda telah mengkonfigurasi nomor pin dengan benar sesuai dengan koneksi perangkat Moji di kode Anda.

4. **Pengaturan Library**

   1. Pastikan Anda telah menginstal pustaka yang diperlukan melalui "Library Manager" di Arduino IDE.
   2. (cara lebih mudah) copy library dari folder "Lib" ke library arduino anda, contoh: C:\Users\<namuser>\Documents\Arduino\libraries

5. **Unggah Kode**

   1. Hubungkan perangkat Moji ke komputer melalui kabel USB.
   2. Pilih papan Arduino yang sesuai dan port serial yang digunakan pada menu "Tools".
   3. Klik tombol unggah (upload) di Arduino IDE untuk mengunggah kode ke perangkat Moji.

6. **Monitor Serial**

   1. Buka Serial Monitor di Arduino IDE untuk melihat output dan pesan dari perangkat Moji.

## Panduan Penggunaan Kode Moji di PlatformIO

### Prasyarat

- Perangkat keras Moji yang lengkap dengan komponen yang dijelaskan sebelumnya.
- Komputer dengan akses internet.
- PlatformIO terinstal di komputer Anda.

### Langkah-langkah:

1. **Buka atau Buat Proyek**

   1. Buka PlatformIO IDE.
   2. Buka proyek yang ada atau buat proyek baru dengan pilihan papan Arduino yang sesuai.

2. **Salin dan Tempelkan Kode**

   1. Salin kode Moji dan tempelkan ke dalam file `.cpp` dalam direktori proyek.

3. **Konfigurasi Pin**

   1. Pastikan bahwa Anda telah mengkonfigurasi nomor pin dengan benar sesuai dengan koneksi perangkat Moji di kode Anda.

4. **Pengaturan Library**

   1. Pastikan Anda telah menambahkan pustaka yang diperlukan ke dalam `platformio.ini`.

5. **Unggah Kode**

   1. Hubungkan perangkat Moji ke komputer melalui kabel USB.
   2. Klik tombol unggah (upload) di PlatformIO IDE untuk mengunggah kode ke perangkat Moji.

6. **Monitor Serial**

   1. Buka Serial Monitor di PlatformIO IDE untuk melihat output dan pesan dari perangkat Moji.

## Folering

ada banyak filder yanf tersedia, anda dapat memahami dari list berikut ini:

1. **src**
   ini adalah folder utama dimana anda meletakan file **.cpp** yang akan dieksekusi ke mikrokontroller.
2. **lib**
   merupakan folder yang berisikan library yang anda gunakan, di dalamnya mungkin terdapat ebberapa folder yang menandakan seberapa banyak anda menggunakan external library, library ini dapat ada salin dan tempel ke folder arduino ide, platform i0, atau ke platform c++ lainnya.
3. **components**
   ialah folder yang berisikan komponen dimana saya meletakan satu komponen dari setiap input output unutk mengetahui apakah alat berjalan lancar, anda dapat mengesampingakn folder ini jika anda ingin lagnsung mendapatkan hasil, tetapi jika anda penasaran denga kerja alat ini maka saya sarankan untuk menilik folder ini.
4. **mytestcode**
   adalah folder coba-coba, anda boleh skip folder ini.
