
#include <map>
#include <string>
#include "iso639.h"

info_t infoTable[] = {
    {"aar", "aa", "Afar"},
    {"abk", "ab", "Abkhazian"},
    {"ace", NULL, "Achinese"},
    {"ach", NULL, "Acoli"},
    {"ada", NULL, "Adangme"},
    {"ady", NULL, "Adyghe; Adygei"},
    {"afa", NULL, "Afro-Asiatic languages"},
    {"afh", NULL, "Afrihili"},
    {"afr", "af", "Afrikaans"},
    {"ain", NULL, "Ainu"},
    {"aka", "ak", "Akan"},
    {"akk", NULL, "Akkadian"},
    {"alb", "sq", "Albanian"},
    {"ale", NULL, "Aleut"},
    {"alg", NULL, "Algonquian languages"},
    {"alt", NULL, "Southern Altai"},
    {"amh", "am", "Amharic"},
    {"ang", NULL, "English, Old (ca.450-1100)"},
    {"anp", NULL, "Angika"},
    {"apa", NULL, "Apache languages"},
    {"ara", "ar", "Arabic"},
    {"arc", NULL, "Official Aramaic (700-300 BCE); Imperial Aramaic (700-300 BCE)"},
    {"arg", "an", "Aragonese"},
    {"arm", "hy", "Armenian"},
    {"arn", NULL, "Mapudungun; Mapuche"},
    {"arp", NULL, "Arapaho"},
    {"art", NULL, "Artificial languages"},
    {"arw", NULL, "Arawak"},
    {"asm", "as", "Assamese"},
    {"ast", NULL, "Asturian; Bable; Leonese; Asturleonese"},
    {"ath", NULL, "Athapascan languages"},
    {"aus", NULL, "Australian languages"},
    {"ava", "av", "Avaric"},
    {"ave", "ae", "Avestan"},
    {"awa", NULL, "Awadhi"},
    {"aym", "ay", "Aymara"},
    {"aze", "az", "Azerbaijani"},
    {"bad", NULL, "Banda languages"},
    {"bai", NULL, "Bamileke languages"},
    {"bak", "ba", "Bashkir"},
    {"bal", NULL, "Baluchi"},
    {"bam", "bm", "Bambara"},
    {"ban", NULL, "Balinese"},
    {"baq", "eu", "Basque"},
    {"bas", NULL, "Basa"},
    {"bat", NULL, "Baltic languages"},
    {"bej", NULL, "Beja; Bedawiyet"},
    {"bel", "be", "Belarusian"},
    {"bem", NULL, "Bemba"},
    {"ben", "bn", "Bengali"},
    {"ber", NULL, "Berber languages"},
    {"bho", NULL, "Bhojpuri"},
    {"bih", "bh", "Bihari languages"},
    {"bik", NULL, "Bikol"},
    {"bin", NULL, "Bini; Edo"},
    {"bis", "bi", "Bislama"},
    {"bla", NULL, "Siksika"},
    {"bnt", NULL, "Bantu languages"},
    {"bod", "bo", "Tibetan"},
    {"bos", "bs", "Bosnian"},
    {"bra", NULL, "Braj"},
    {"bre", "br", "Breton"},
    {"btk", NULL, "Batak languages"},
    {"bua", NULL, "Buriat"},
    {"bug", NULL, "Buginese"},
    {"bul", "bg", "Bulgarian"},
    {"bur", "my", "Burmese"},
    {"byn", NULL, "Blin; Bilin"},
    {"cad", NULL, "Caddo"},
    {"cai", NULL, "Central American Indian languages"},
    {"car", NULL, "Galibi Carib"},
    {"cat", "ca", "Catalan; Valencian"},
    {"cau", NULL, "Caucasian languages"},
    {"ceb", NULL, "Cebuano"},
    {"cel", NULL, "Celtic languages"},
    {"ces", "cs", "Czech"},
    {"cha", "ch", "Chamorro"},
    {"chb", NULL, "Chibcha"},
    {"che", "ce", "Chechen"},
    {"chg", NULL, "Chagatai"},
    {"chi", "zh", "Chinese"},
    {"chk", NULL, "Chuukese"},
    {"chm", NULL, "Mari"},
    {"chn", NULL, "Chinook jargon"},
    {"cho", NULL, "Choctaw"},
    {"chp", NULL, "Chipewyan; Dene Suline"},
    {"chr", NULL, "Cherokee"},
    {"chu", "cu", "Church Slavic; Old Slavonic; Church Slavonic; Old Bulgarian; Old Church Slavonic"},
    {"chv", "cv", "Chuvash"},
    {"chy", NULL, "Cheyenne"},
    {"cmc", NULL, "Chamic languages"},
    {"cop", NULL, "Coptic"},
    {"cor", "kw", "Cornish"},
    {"cos", "co", "Corsican"},
    {"cpe", NULL, "Creoles and pidgins, English based"},
    {"cpf", NULL, "Creoles and pidgins, French-based"},
    {"cpp", NULL, "Creoles and pidgins, Portuguese-based"},
    {"cre", "cr", "Cree"},
    {"crh", NULL, "Crimean Tatar; Crimean Turkish"},
    {"crp", NULL, "Creoles and pidgins"},
    {"csb", NULL, "Kashubian"},
    {"cus", NULL, "Cushitic languages"},
    {"cym", "cy", "Welsh"},
    {"cze", "cs", "Czech"},
    {"dak", NULL, "Dakota"},
    {"dan", "da", "Danish"},
    {"dar", NULL, "Dargwa"},
    {"day", NULL, "Land Dayak languages"},
    {"del", NULL, "Delaware"},
    {"den", NULL, "Slave (Athapascan)"},
    {"deu", "de", "German"},
    {"dgr", NULL, "Dogrib"},
    {"din", NULL, "Dinka"},
    {"div", "dv", "Divehi; Dhivehi; Maldivian"},
    {"doi", NULL, "Dogri"},
    {"dra", NULL, "Dravidian languages"},
    {"dsb", NULL, "Lower Sorbian"},
    {"dua", NULL, "Duala"},
    {"dum", NULL, "Dutch, Middle (ca.1050-1350)"},
    {"dut", "nl", "Dutch; Flemish"},
    {"dyu", NULL, "Dyula"},
    {"dzo", "dz", "Dzongkha"},
    {"efi", NULL, "Efik"},
    {"egy", NULL, "Egyptian (Ancient)"},
    {"eka", NULL, "Ekajuk"},
    {"ell", "el", "Greek, Modern (1453-)"},
    {"elx", NULL, "Elamite"},
    {"eng", "en", "English"},
    {"enm", NULL, "English, Middle (1100-1500)"},
    {"epo", "eo", "Esperanto"},
    {"est", "et", "Estonian"},
    {"eus", "eu", "Basque"},
    {"ewe", "ee", "Ewe"},
    {"ewo", NULL, "Ewondo"},
    {"fan", NULL, "Fang"},
    {"fao", "fo", "Faroese"},
    {"fas", "fa", "Persian"},
    {"fat", NULL, "Fanti"},
    {"fij", "fj", "Fijian"},
    {"fil", NULL, "Filipino; Pilipino"},
    {"fin", "fi", "Finnish"},
    {"fiu", NULL, "Finno-Ugrian languages"},
    {"fon", NULL, "Fon"},
    {"fra", "fr", "French"},
    {"fre", "fr", "French"},
    {"frm", NULL, "French, Middle (ca.1400-1600)"},
    {"fro", NULL, "French, Old (842-ca.1400)"},
    {"frr", NULL, "Northern Frisian"},
    {"frs", NULL, "Eastern Frisian"},
    {"fry", "fy", "Western Frisian"},
    {"ful", "ff", "Fulah"},
    {"fur", NULL, "Friulian"},
    {"gaa", NULL, "Ga"},
    {"gay", NULL, "Gayo"},
    {"gba", NULL, "Gbaya"},
    {"gem", NULL, "Germanic languages"},
    {"geo", "ka", "Georgian"},
    {"ger", "de", "German"},
    {"gez", NULL, "Geez"},
    {"gil", NULL, "Gilbertese"},
    {"gla", "gd", "Gaelic; Scottish Gaelic"},
    {"gle", "ga", "Irish"},
    {"glg", "gl", "Galician"},
    {"glv", "gv", "Manx"},
    {"gmh", NULL, "German, Middle High (ca.1050-1500)"},
    {"goh", NULL, "German, Old High (ca.750-1050)"},
    {"gon", NULL, "Gondi"},
    {"gor", NULL, "Gorontalo"},
    {"got", NULL, "Gothic"},
    {"grb", NULL, "Grebo"},
    {"grc", NULL, "Greek, Ancient (to 1453)"},
    {"gre", "el", "Greek, Modern (1453-)"},
    {"grn", "gn", "Guarani"},
    {"gsw", NULL, "Swiss German; Alemannic; Alsatian"},
    {"guj", "gu", "Gujarati"},
    {"gwi", NULL, "Gwich'in"},
    {"hai", NULL, "Haida"},
    {"hat", "ht", "Haitian; Haitian Creole"},
    {"hau", "ha", "Hausa"},
    {"haw", NULL, "Hawaiian"},
    {"heb", "he", "Hebrew"},
    {"her", "hz", "Herero"},
    {"hil", NULL, "Hiligaynon"},
    {"him", NULL, "Himachali languages; Western Pahari languages"},
    {"hin", "hi", "Hindi"},
    {"hit", NULL, "Hittite"},
    {"hmn", NULL, "Hmong; Mong"},
    {"hmo", "ho", "Hiri Motu"},
    {"hrv", "hr", "Croatian"},
    {"hsb", NULL, "Upper Sorbian"},
    {"hun", "hu", "Hungarian"},
    {"hup", NULL, "Hupa"},
    {"hye", "hy", "Armenian"},
    {"iba", NULL, "Iban"},
    {"ibo", "ig", "Igbo"},
    {"ice", "is", "Icelandic"},
    {"ido", "io", "Ido"},
    {"iii", "ii", "Sichuan Yi; Nuosu"},
    {"ijo", NULL, "Ijo languages"},
    {"iku", "iu", "Inuktitut"},
    {"ile", "ie", "Interlingue; Occidental"},
    {"ilo", NULL, "Iloko"},
    {"ina", "ia", "Interlingua (International Auxiliary Language Association)"},
    {"inc", NULL, "Indic languages"},
    {"ind", "id", "Indonesian"},
    {"ine", NULL, "Indo-European languages"},
    {"inh", NULL, "Ingush"},
    {"ipk", "ik", "Inupiaq"},
    {"ira", NULL, "Iranian languages"},
    {"iro", NULL, "Iroquoian languages"},
    {"isl", "is", "Icelandic"},
    {"ita", "it", "Italian"},
    {"jav", "jv", "Javanese"},
    {"jbo", NULL, "Lojban"},
    {"jpn", "ja", "Japanese"},
    {"jpr", NULL, "Judeo-Persian"},
    {"jrb", NULL, "Judeo-Arabic"},
    {"kaa", NULL, "Kara-Kalpak"},
    {"kab", NULL, "Kabyle"},
    {"kac", NULL, "Kachin; Jingpho"},
    {"kal", "kl", "Kalaallisut; Greenlandic"},
    {"kam", NULL, "Kamba"},
    {"kan", "kn", "Kannada"},
    {"kar", NULL, "Karen languages"},
    {"kas", "ks", "Kashmiri"},
    {"kat", "ka", "Georgian"},
    {"kau", "kr", "Kanuri"},
    {"kaw", NULL, "Kawi"},
    {"kaz", "kk", "Kazakh"},
    {"kbd", NULL, "Kabardian"},
    {"kha", NULL, "Khasi"},
    {"khi", NULL, "Khoisan languages"},
    {"khm", "km", "Central Khmer"},
    {"kho", NULL, "Khotanese; Sakan"},
    {"kik", "ki", "Kikuyu; Gikuyu"},
    {"kin", "rw", "Kinyarwanda"},
    {"kir", "ky", "Kirghiz; Kyrgyz"},
    {"kmb", NULL, "Kimbundu"},
    {"kok", NULL, "Konkani"},
    {"kom", "kv", "Komi"},
    {"kon", "kg", "Kongo"},
    {"kor", "ko", "Korean"},
    {"kos", NULL, "Kosraean"},
    {"kpe", NULL, "Kpelle"},
    {"krc", NULL, "Karachay-Balkar"},
    {"krl", NULL, "Karelian"},
    {"kro", NULL, "Kru languages"},
    {"kru", NULL, "Kurukh"},
    {"kua", "kj", "Kuanyama; Kwanyama"},
    {"kum", NULL, "Kumyk"},
    {"kur", "ku", "Kurdish"},
    {"kut", NULL, "Kutenai"},
    {"lad", NULL, "Ladino"},
    {"lah", NULL, "Lahnda"},
    {"lam", NULL, "Lamba"},
    {"lao", "lo", "Lao"},
    {"lat", "la", "Latin"},
    {"lav", "lv", "Latvian"},
    {"lez", NULL, "Lezghian"},
    {"lim", "li", "Limburgan; Limburger; Limburgish"},
    {"lin", "ln", "Lingala"},
    {"lit", "lt", "Lithuanian"},
    {"lol", NULL, "Mongo"},
    {"loz", NULL, "Lozi"},
    {"ltz", "lb", "Luxembourgish; Letzeburgesch"},
    {"lua", NULL, "Luba-Lulua"},
    {"lub", "lu", "Luba-Katanga"},
    {"lug", "lg", "Ganda"},
    {"lui", NULL, "Luiseno"},
    {"lun", NULL, "Lunda"},
    {"luo", NULL, "Luo (Kenya and Tanzania)"},
    {"lus", NULL, "Lushai"},
    {"mac", "mk", "Macedonian"},
    {"mad", NULL, "Madurese"},
    {"mag", NULL, "Magahi"},
    {"mah", "mh", "Marshallese"},
    {"mai", NULL, "Maithili"},
    {"mak", NULL, "Makasar"},
    {"mal", "ml", "Malayalam"},
    {"man", NULL, "Mandingo"},
    {"mao", "mi", "Maori"},
    {"map", NULL, "Austronesian languages"},
    {"mar", "mr", "Marathi"},
    {"mas", NULL, "Masai"},
    {"may", "ms", "Malay"},
    {"mdf", NULL, "Moksha"},
    {"mdr", NULL, "Mandar"},
    {"men", NULL, "Mende"},
    {"mga", NULL, "Irish, Middle (900-1200)"},
    {"mic", NULL, "Mi'kmaq; Micmac"},
    {"min", NULL, "Minangkabau"},
    {"mis", NULL, "Uncoded languages"},
    {"mkd", "mk", "Macedonian"},
    {"mkh", NULL, "Mon-Khmer languages"},
    {"mlg", "mg", "Malagasy"},
    {"mlt", "mt", "Maltese"},
    {"mnc", NULL, "Manchu"},
    {"mni", NULL, "Manipuri"},
    {"mno", NULL, "Manobo languages"},
    {"moh", NULL, "Mohawk"},
    {"mon", "mn", "Mongolian"},
    {"mos", NULL, "Mossi"},
    {"mri", "mi", "Maori"},
    {"msa", "ms", "Malay"},
    {"mul", NULL, "Multiple languages"},
    {"mun", NULL, "Munda languages"},
    {"mus", NULL, "Creek"},
    {"mwl", NULL, "Mirandese"},
    {"mwr", NULL, "Marwari"},
    {"mya", "my", "Burmese"},
    {"myn", NULL, "Mayan languages"},
    {"myv", NULL, "Erzya"},
    {"nah", NULL, "Nahuatl languages"},
    {"nai", NULL, "North American Indian languages"},
    {"nap", NULL, "Neapolitan"},
    {"nau", "na", "Nauru"},
    {"nav", "nv", "Navajo; Navaho"},
    {"nbl", "nr", "Ndebele, South; South Ndebele"},
    {"nde", "nd", "Ndebele, North; North Ndebele"},
    {"ndo", "ng", "Ndonga"},
    {"nds", NULL, "Low German; Low Saxon; German, Low; Saxon, Low"},
    {"nep", "ne", "Nepali"},
    {"new", NULL, "Nepal Bhasa; Newari"},
    {"nia", NULL, "Nias"},
    {"nic", NULL, "Niger-Kordofanian languages"},
    {"niu", NULL, "Niuean"},
    {"nld", "nl", "Dutch; Flemish"},
    {"nno", "nn", "Norwegian Nynorsk; Nynorsk, Norwegian"},
    {"nob", "nb", "Bokmål, Norwegian; Norwegian Bokmål"},
    {"nog", NULL, "Nogai"},
    {"non", NULL, "Norse, Old"},
    {"nor", "no", "Norwegian"},
    {"nqo", NULL, "N'Ko"},
    {"nso", NULL, "Pedi; Sepedi; Northern Sotho"},
    {"nub", NULL, "Nubian languages"},
    {"nwc", NULL, "Classical Newari; Old Newari; Classical Nepal Bhasa"},
    {"nya", "ny", "Chichewa; Chewa; Nyanja"},
    {"nym", NULL, "Nyamwezi"},
    {"nyn", NULL, "Nyankole"},
    {"nyo", NULL, "Nyoro"},
    {"nzi", NULL, "Nzima"},
    {"oci", "oc", "Occitan (post 1500)"},
    {"oji", "oj", "Ojibwa"},
    {"ori", "or", "Oriya"},
    {"orm", "om", "Oromo"},
    {"osa", NULL, "Osage"},
    {"oss", "os", "Ossetian; Ossetic"},
    {"ota", NULL, "Turkish, Ottoman (1500-1928)"},
    {"oto", NULL, "Otomian languages"},
    {"paa", NULL, "Papuan languages"},
    {"pag", NULL, "Pangasinan"},
    {"pal", NULL, "Pahlavi"},
    {"pam", NULL, "Pampanga; Kapampangan"},
    {"pan", "pa", "Panjabi; Punjabi"},
    {"pap", NULL, "Papiamento"},
    {"pau", NULL, "Palauan"},
    {"peo", NULL, "Persian, Old (ca.600-400 B.C.)"},
    {"per", "fa", "Persian"},
    {"phi", NULL, "Philippine languages"},
    {"phn", NULL, "Phoenician"},
    {"pli", "pi", "Pali"},
    {"pol", "pl", "Polish"},
    {"pon", NULL, "Pohnpeian"},
    {"por", "pt", "Portuguese"},
    {"pra", NULL, "Prakrit languages"},
    {"pro", NULL, "Provençal, Old (to 1500);Occitan, Old (to 1500)"},
    {"pus", "ps", "Pushto; Pashto"},
    {"que", "qu", "Quechua"},
    {"raj", NULL, "Rajasthani"},
    {"rap", NULL, "Rapanui"},
    {"rar", NULL, "Rarotongan; Cook Islands Maori"},
    {"roa", NULL, "Romance languages"},
    {"roh", "rm", "Romansh"},
    {"rom", NULL, "Romany"},
    {"ron", "ro", "Romanian; Moldavian; Moldovan"},
    {"rum", "ro", "Romanian; Moldavian; Moldovan"},
    {"run", "rn", "Rundi"},
    {"rup", NULL, "Aromanian; Arumanian; Macedo-Romanian"},
    {"rus", "ru", "Russian"},
    {"sad", NULL, "Sandawe"},
    {"sag", "sg", "Sango"},
    {"sah", NULL, "Yakut"},
    {"sai", NULL, "South American Indian languages"},
    {"sal", NULL, "Salishan languages"},
    {"sam", NULL, "Samaritan Aramaic"},
    {"san", "sa", "Sanskrit"},
    {"sas", NULL, "Sasak"},
    {"sat", NULL, "Santali"},
    {"scn", NULL, "Sicilian"},
    {"sco", NULL, "Scots"},
    {"sel", NULL, "Selkup"},
    {"sem", NULL, "Semitic languages"},
    {"sga", NULL, "Irish, Old (to 900)"},
    {"sgn", NULL, "Sign Languages"},
    {"shn", NULL, "Shan"},
    {"sid", NULL, "Sidamo"},
    {"sin", "si", "Sinhala; Sinhalese"},
    {"sio", NULL, "Siouan languages"},
    {"sit", NULL, "Sino-Tibetan languages"},
    {"sla", NULL, "Slavic languages"},
    {"slk", "sk", "Slovak"},
    {"slo", "sk", "Slovak"},
    {"slv", "sl", "Slovenian"},
    {"sma", NULL, "Southern Sami"},
    {"sme", "se", "Northern Sami"},
    {"smi", NULL, "Sami languages"},
    {"smj", NULL, "Lule Sami"},
    {"smn", NULL, "Inari Sami"},
    {"smo", "sm", "Samoan"},
    {"sms", NULL, "Skolt Sami"},
    {"sna", "sn", "Shona"},
    {"snd", "sd", "Sindhi"},
    {"snk", NULL, "Soninke"},
    {"sog", NULL, "Sogdian"},
    {"som", "so", "Somali"},
    {"son", NULL, "Songhai languages"},
    {"sot", "st", "Sotho, Southern"},
    {"spa", "es", "Spanish; Castilian"},
    {"sqi", "sq", "Albanian"},
    {"srd", "sc", "Sardinian"},
    {"srn", NULL, "Sranan Tongo"},
    {"srp", "sr", "Serbian"},
    {"srr", NULL, "Serer"},
    {"ssa", NULL, "Nilo-Saharan languages"},
    {"ssw", "ss", "Swati"},
    {"suk", NULL, "Sukuma"},
    {"sun", "su", "Sundanese"},
    {"sus", NULL, "Susu"},
    {"sux", NULL, "Sumerian"},
    {"swa", "sw", "Swahili"},
    {"swe", "sv", "Swedish"},
    {"syc", NULL, "Classical Syriac"},
    {"syr", NULL, "Syriac"},
    {"tah", "ty", "Tahitian"},
    {"tai", NULL, "Tai languages"},
    {"tam", "ta", "Tamil"},
    {"tat", "tt", "Tatar"},
    {"tel", "te", "Telugu"},
    {"tem", NULL, "Timne"},
    {"ter", NULL, "Tereno"},
    {"tet", NULL, "Tetum"},
    {"tgk", "tg", "Tajik"},
    {"tgl", "tl", "Tagalog"},
    {"tha", "th", "Thai"},
    {"tib", "bo", "Tibetan"},
    {"tig", NULL, "Tigre"},
    {"tir", "ti", "Tigrinya"},
    {"tiv", NULL, "Tiv"},
    {"tkl", NULL, "Tokelau"},
    {"tlh", NULL, "Klingon; tlhIngan-Hol"},
    {"tli", NULL, "Tlingit"},
    {"tmh", NULL, "Tamashek"},
    {"tog", NULL, "Tonga (Nyasa)"},
    {"ton", "to", "Tonga (Tonga Islands)"},
    {"tpi", NULL, "Tok Pisin"},
    {"tsi", NULL, "Tsimshian"},
    {"tsn", "tn", "Tswana"},
    {"tso", "ts", "Tsonga"},
    {"tuk", "tk", "Turkmen"},
    {"tum", NULL, "Tumbuka"},
    {"tup", NULL, "Tupi languages"},
    {"tur", "tr", "Turkish"},
    {"tut", NULL, "Altaic languages"},
    {"tvl", NULL, "Tuvalu"},
    {"twi", "tw", "Twi"},
    {"tyv", NULL, "Tuvinian"},
    {"udm", NULL, "Udmurt"},
    {"uga", NULL, "Ugaritic"},
    {"uig", "ug", "Uighur; Uyghur"},
    {"ukr", "uk", "Ukrainian"},
    {"umb", NULL, "Umbundu"},
    {"und", NULL, "Undetermined"},
    {"urd", "ur", "Urdu"},
    {"uzb", "uz", "Uzbek"},
    {"vai", NULL, "Vai"},
    {"ven", "ve", "Venda"},
    {"vie", "vi", "Vietnamese"},
    {"vol", "vo", "Volapük"},
    {"vot", NULL, "Votic"},
    {"wak", NULL, "Wakashan languages"},
    {"wal", NULL, "Wolaitta; Wolaytta"},
    {"war", NULL, "Waray"},
    {"was", NULL, "Washo"},
    {"wel", "cy", "Welsh"},
    {"wen", NULL, "Sorbian languages"},
    {"wln", "wa", "Walloon"},
    {"wol", "wo", "Wolof"},
    {"xal", NULL, "Kalmyk; Oirat"},
    {"xho", "xh", "Xhosa"},
    {"yao", NULL, "Yao"},
    {"yap", NULL, "Yapese"},
    {"yid", "yi", "Yiddish"},
    {"yor", "yo", "Yoruba"},
    {"ypk", NULL, "Yupik languages"},
    {"zap", NULL, "Zapotec"},
    {"zbl", NULL, "Blissymbols; Blissymbolics; Bliss"},
    {"zen", NULL, "Zenaga"},
    {"zha", "za", "Zhuang; Chuang"},
    {"zho", "zh", "Chinese"},
    {"znd", NULL, "Zande languages"},
    {"zul", "zu", "Zulu"},
    {"zun", NULL, "Zuni"},
    {"zxx", NULL, "No linguistic content; Not applicable"},
    {"zza", NULL, "Zaza; Dimili; Dimli; Kirdki; Kirmanjki; Zazaki"},
    {NULL, NULL, NULL}
};

static std::map<std::string, info_t*> infoCache;

extern "C" void generateLanguageInfoCache() {
    info_t* info;
    
    infoCache.clear();
    
    for (info = infoTable; info->iso639_2 != NULL; info++) {
        infoCache.insert(std::make_pair(std::string(info->iso639_2), info));
    }
}

extern "C" info_t* getLanguageInfo(const char* iso639_2) {
    std::map<std::string, info_t*>::const_iterator info = infoCache.find(iso639_2);
    if (info == infoCache.end()) {
        return NULL;
    }
    
    return info->second;
}
