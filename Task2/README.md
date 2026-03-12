## Refleksi Design Pattern

**1. Struktur Invarian**
Struktur invarian dari game ini terletak pada kelas `RunSession`. Kelas ini bertugas mengatur *core loop* (siklus utama) permainan dengan urutan yang sudah pasti: membagikan kartu, menerima input pemain, menghitung skor, memberikan hadiah atau hukuman, lalu membuka toko. Urutan langkah-langkah ini sangat ketat dan tidak boleh berubah.

**2. Bagian Mutable**
Bagian yang Mutable (dapat diubah) adalah antarmuka (*interface*) beserta kelas-kelas pendukungnya. Contoh dari kelas pendukung ini adalah `HandGenerator` (mengatur cara kartu dibagikan), `ScoringSystem` (mengatur logika perhitungan kombinasi kartu), dan `RewardRule` (mengatur jumlah uang yang didapat). Aturan di dalam kelas-kelas pendukung ini bisa kita ganti secara bebas tanpa merusak alur utama permainan.

**3. Penambahan Fitur Baru**
Jika kita ingin menambah fitur baru, kelas `RunSession` sama sekali tidak perlu diubah. Kita hanya perlu mengubah atau menambah kelas pendukung dan *modifier* sesuai dengan fitur apa yang ingin kita buat. Misalnya, jika ingin menambah aturan skor baru, kita cukup memperbarui kelas `ScoringSystem`. Jika ingin menambah barang baru, kita cukup memperbarui kelas `ShopSystem`.

**4. Dampak Perubahan Urutan Loop**
Jika urutan *loop* diubah, logika dan aliran data game akan rusak. Sebagai contoh, jika sistem mencoba menghitung skor sebelum pemain memasukkan kartu, maka hasil *damage* yang keluar adalah nol. Contoh lain, jika fase toko diletakkan sebelum fase pembagian hadiah, pemain tidak akan bisa menggunakan uang yang baru saja mereka menangkan untuk membeli barang.