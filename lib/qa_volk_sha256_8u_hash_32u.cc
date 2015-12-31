#include <volk_sha256/volk_sha256.h>
#include <inttypes.h>
#include <iostream>
#include <string.h>
#include <stdio.h>

int main(){
    // Init
    char msg_char[] = "Es ist ein paradiesmatisches Land, in dem einem gebratene Satzteile in den Mund fliegen. Nicht einmal von der allmächtigen Interpunktion werden die Blindtexte beherrscht – ein geradezu unorthographisches Leben. Eines Tages aber beschloß eine kleine Zeile Blindtext, ihr Name war Lorem Ipsum, hinaus zu gehen in die weite Grammatik. Der große Oxmox riet ihr davon ab, da es dort wimmele von bösen Kommata, wilden Fragezeichen und hinterhältigen Semikoli, doch das Blindtextchen ließ sich nicht beirren. Es packte seine sieben Versalien, schob sich sein Initial in den Gürtel und machte sich auf den Weg. Als es die ersten Hügel des Kursivgebirges erklommen hatte, warf es einen letzten Blick zurück auf die Skyline seiner Heimatstadt Buchstabhausen, die Headline von Alphabetdorf und die Subline seiner eigenen Straße, der Zeilengasse. Wehmütig lief ihm eine rethorische Frage über die Wange, dann setzte es seinen Weg fort. Unterwegs traf es eine Copy. Die Copy warnte das Blindtextchen, da, wo sie herkäme wäre sie zigmal umgeschrieben worden und alles, was von ihrem Ursprung noch übrig wäre, sei das Wort “und” und das Blindtextchen solle umkehren und wieder in sein eigenes, sicheres Land zurückkehren. Doch alles Gutzureden konnte es nicht überzeugen und so dauerte es nicht lange, bis ihm ein paar heimtückische Werbetexter auflauerten, es mit Longe und Parole betrunken machten und es dann in ihre Agentur schleppten, wo sie es für ihre Projekte wieder und wieder mißbrauchten. Und wenn es nicht umgeschrieben wurde, dann benutzen Sie es immernoch. Weit hinten, hinter den Wortbergen, fern der Länder Vokalien und Konsonantien leben die Blindtexte. Abgeschieden wohnen Sie in Buchstabhausen an der Küste des Semantik, eines großen Sprachozeans. Ein kleines Bächlein namens Duden fließt durch ihren Ort und versorgt sie mit den nötigen Regelialien.\n";

    size_t msg_len = strlen(msg_char);
    std::cout << "Message length: " << msg_len << std::endl;

    size_t alignment = volk_sha256_get_alignment();
    uint8_t* msg = (uint8_t*) volk_sha256_malloc(msg_len*sizeof(uint8_t), alignment);
    for(size_t k=0; k<msg_len; k++) msg[k] = (uint8_t) msg_char[k];

    uint32_t* hash = (uint32_t*) volk_sha256_malloc(8*sizeof(uint32_t), alignment);

    // Run generic kernel
    volk_sha256_8u_hash_32u_manual(hash, msg, msg_len, "generic");

    // Print hash from function
    std::cout << "Hash (hex): ";
    for(size_t k=0; k<8; k++) printf("%#08x ", hash[k]);
    std::cout << std::endl;

    // Check against hash generated by sha256sum
    uint32_t test_hash[8] = {0x048aaad6, 0x7b9200d2, 0x00293f13, 0x65474e76, 0x1fbfaca0, 0xd1e11fb5, 0xb059ed04, 0xd57d0d4a};
    for(size_t k=0; k<8; k++){
        if(hash[k]!=test_hash[k]) return 1;
    }
    return 0;
}