# Task 2 - Core Loop Architecture

**Konsep Game:** Cyber Survival (Permainan bertahan hidup berbasis kartu)

### Step 1 - Core Loop
Game ini adalah permainan bertahan hidup dengan sistem *wave* (gelombang). Siklus utama (*core loop*) permainannya adalah:
1. Sistem membagikan kartu secara acak kepada pemain.
2. Pemain memilih maksimal 5 kartu dari tangan untuk dimainkan.
3. Sistem mengevaluasi kombinasi kartu tersebut dan menghitung total *damage*.
4. Sistem mengurangi HP Virus (musuh) berdasarkan *damage* yang dihasilkan.
5. Sistem mengevaluasi apakah HP Virus sudah habis atau jatah serangan pemain habis.
6. Hadiah (uang) diberikan jika pemain menang, atau penalti (pengurangan nyawa) diberikan jika kalah.
7. Jika pemain menang, sistem membuka Toko untuk membeli peningkatan.
8. Siklus berulang untuk gelombang musuh berikutnya.

### Step 2 - Identifikasi Invarian (Invariant Identification)
Urutan langkah berikut mutlak dan tidak boleh berubah:
1. Pembagian kartu
2. Pemilihan kartu oleh pemain
3. Perhitungan *damage*
4. Pengurangan HP musuh
5. Evaluasi menang/kalah
6. Akses ke Toko

Jika urutan ini diubah, logika permainan akan hancur. Sebagai contoh:
1. Jika sistem menghitung *damage* sebelum pemain memilih kartu, maka serangan yang terjadi selalu bernilai 0.
2. Jika evaluasi menang/kalah dilakukan sebelum pengurangan HP musuh, game tidak akan pernah mendeteksi kemenangan pemain.
3. Jika fase Toko dijalankan sebelum pemberian hadiah kemenangan, pemain tidak akan memiliki uang untuk membeli barang.

**Komponen yang Wajib Ada:**
Game ini tidak bisa berjalan tanpa komponen struktural berikut:
1. Pengendali siklus utama (`RunSession`)
2. Penghasil input kartu (`HandGenerator`)
3. Penghitung nilai kombinasi kartu (`ScoringSystem`)
4. Penentu hasil akhir dan mutasi uang/nyawa (`RewardRule`)
5. Pelacak status HP musuh dan Uang pemain

### Step 3 - Elemen Mutabel (Mutable Elements)
Berikut adalah bagian-bagian game yang bersifat mutable (bebas diubah tanpa merusak siklus utama):
1. **Formula perhitungan skor:** Aturan seberapa besar nilai dasar (base) dan pengali (multiplier) untuk setiap kombinasi kartu (misalnya *High Card*, *Pair*, *Flush*).
2. **Skala HP Musuh (Virus):** Seberapa besar penambahan "darah" musuh setiap kali pemain naik ke gelombang berikutnya.
3. **Sistem Toko:** Daftar barang (seperti *RAM Upgrade* atau *Overclock* (ini kedepannya bisa ditambahkan), harga barang, dan seberapa besar efek peningkatan yang diberikan.
4. **Kapasitas kartu:** Jumlah maksimal kartu yang ditarik dari tumpukan (saat ini disetel 7) dan batas maksimal kartu yang bisa dipilih pemain (saat ini disetel 5).

---

## Refleksi Design Pattern

**1. Struktur Invarian**
Struktur invarian dari game ini terletak pada kelas `RunSession`. Kelas ini bertugas mengatur *core loop* (siklus utama) permainan dengan urutan yang sudah pasti: membagikan kartu, menerima input pemain, menghitung skor, memberikan hadiah atau hukuman, lalu membuka toko. Urutan langkah-langkah ini sangat ketat dan tidak boleh berubah.

**2. Bagian Mutable**
Bagian yang Mutable (dapat diubah) adalah antarmuka (*interface*) beserta kelas-kelas pendukungnya. Contoh dari kelas pendukung ini adalah `HandGenerator` (mengatur cara kartu dibagikan), `ScoringSystem` (mengatur logika perhitungan kombinasi kartu), dan `RewardRule` (mengatur jumlah uang yang didapat). Aturan di dalam kelas-kelas pendukung ini bisa kita ganti secara bebas tanpa merusak alur utama permainan.

**3. Penambahan Fitur Baru**
Jika kita ingin menambah fitur baru, kelas `RunSession` sama sekali tidak perlu diubah. Kita hanya perlu mengubah atau menambah kelas pendukung dan *modifier* sesuai dengan fitur apa yang ingin kita buat. Misalnya, jika ingin menambah aturan skor baru, kita cukup memperbarui kelas `ScoringSystem`. Jika ingin menambah barang baru, kita cukup memperbarui kelas `ShopSystem`.

**4. Dampak Perubahan Urutan Loop**
Jika urutan *loop* diubah, logika dan aliran data game akan rusak. Sebagai contoh, jika sistem mencoba menghitung skor sebelum pemain memasukkan kartu, maka hasil *damage* yang keluar adalah nol. Contoh lain, jika fase toko diletakkan sebelum fase pembagian hadiah, pemain tidak akan bisa menggunakan uang yang baru saja mereka menangkan untuk membeli barang.