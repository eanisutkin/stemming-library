#pragma once

#include <QString>
#include <QVector>
#include <QRegularExpression>

typedef QVector<QString> noChange;
typedef QVector<QPair<QString, QString>> simpleChange;
typedef QVector<QPair<QString, QString>> regexChange;

/** Евгений Анисюткин. 02.12.2021
*
* Русские слова, которые не стеммируются, но участвуют в поиске ошибок.
*
*/
noChange rusNoChange {
  {
    "останов", "режим", "она", "оно", "они", "себя", "себе", "его", "ее", "каждый", "другой", "любой", "иной", "самый", "всякий", "этот", "таков", "такой",
    "столько", "какой", "сколько", "каков", "который", "ничей", "нечего", "некого", "никто", "ничто", "нечто", "некто", "несколько", "кто-либо","какой-либо",
    "кто-нибудь", "чей-либо", "что-либо", "что-нибудь", "какой-нибудь", "один", "четыре", "восемь", "девять", "десять", "вашей", "второго",  "еще", "одно",
    "первом", "потом", "почти", "с помощью", "такие", "тремя", "третью", "эта", "этой", "этим", "эти", "точно", "сегодня", "вчера", "завтра", "мере", "это",
    "салями", "казах", "размах", "взмах", "много", "итого", "ничего", "вигвам", "атом", "зачем", "затем", "тотем", "аудит", "ледостав", "состав", "габарит",
    "конъюнктивит", "весь", "пять", "шесть", "семь", "помощью", "также", "тоже", "или", "потому", "калым", "зажим", "электрообогрев", "обогрев", "отит"
  }
};

/** Евгений Анисюткин. 02.12.2021
*
* Регулярные выражения отвечающие за за обработку спецефических окончаний в русском языке.
* Внимание уделяется множественному числу, окончаниям: аму, ему, ому, иму, яму.
* Также учитываются их вариации с 'ост' перед окончанием.
*
* Окончания типа -ция и его производные тоже должны стеммироватся одинакого, добавлены правило под их обработку
*
*/
regexChange rusRegexChange {
  {"(вагон)(.{1,3})$", "\\1"}, // Отдельная обработка слова вагон и его производных. Необходимо, так как пересекается с другими правилами
  {"(.*[жзлр][нк])([аеиоыя]{1,3})$", "\\1"}, // Частичный учет беглых гласных, в словах где они есть
  {"(.*нн)([а-яё]{1,3})$", "\\1"}, // Спецефическая обработка слов с двумя нн и окончаниями после двух н. Нужна вследствии пересечения с правилами о беглых гласных
  {"(.*ц(?>(?=ия)|(?=и[ао]н)))([^н][а-яё]{1,3})$", "\\1"}, // Обработка окончаний типа -ция / -циан*
  {"(.*ц)(ией)$", "\\1"}, // Обработка окончаний типа -цией
  {"(.*)([ое]([н])ь)$", "\\1\\3"}, // Обработка оль, ель
  {"(.*[бвгджзклмнпрстфхчцшщ])(ого$)", "\\1"}, // Обработка окончания -ого .
  {"(.*[бвгджзклмнпрстфхчцшщ])(его$)", "\\1"}, // Обработка окончания -его .
  {"(.*[бвгджзклмнпрстфхчцшщ])(ами$)", "\\1"}, // Обработка окончания -ами .
  {"(.*[бвгджзклмнпрстфхчцшщ])(ему$)", "\\1"}, // Обработка окончания -ему .
  {"(.*[бвгджзклмнпрстфхчцшщ])(ом[уы]$)", "\\1"}, // Обработка окончания -оми .
  {"(.*[бвгджзклмнпрстфхчцшщ])(ыми$)", "\\1"}, // Обработка окончания -ыми .
  {"(.*[бвгджзклмнпрстфхчцшщ])(ими$)", "\\1"}, // Обработка окончания -ими .
  {"(.*[бвгджзклмнпрстфхчцшщ])([ь]?ями$)", "\\1"} // Обработка окончания -ями .
};

/** Евгений Анисюткин. 02.12.2021
*
* Регулярные выражения отвечающие за за обработку спецефических окончаний в русском языке.
* Внимание уделяется множественному числу, окончаниям: аму, ему, ому, иму, яму.
* Также учитываются их вариации с 'ост' перед окончанием.
* Используются исключительно в модуле стеммер ввиду того, что стеммер оставляет окончания, но ставит знак | перед окончанием.
*
*/
regexChange rusRegexStemmerChange {
  {"(вагон)(.{1,3})$", "\\1|\\2"},
  {"(.*[жзлр][нк])([аеиоыя]{1,3})$", "\\1|\\2"},
  {"(.*нн)([а-яё]{1,3})$", "\\1|\\2"},
  {"(.*ц(?>(?=ия)|(?=и[ао]н)))([^н][а-яё]{1,3})$", "\\1|\\2"}, // Обработка окончаний типа -ция / -циан*
  {"(.*ц)(ией)$", "\\1|\\2"}, // Обработка окончаний типа -цией
  {"(.*)([ое]([н])ь)$", "\\1\\3|\\2"}, // Обработка оль, ель
  {"(.*[бвгджзклмнпрстфхчцшщ])(ого$)", "\\1|\\2"}, // Обработка окончания -ого .
  {"(.*[бвгджзклмнпрстфхчцшщ])(его$)", "\\1|\\2"}, // Обработка окончания -его .
  {"(.*[бвгджзклмнпрстфхчцшщ])(ами$)", "\\1|\\2"}, // Обработка окончания -ами .
  {"(.*[бвгджзклмнпрстфхчцшщ])(ему$)", "\\1|\\2"}, // Обработка окончания -ему* .
  {"(.*[бвгджзклмнпрстфхчцшщ])(ом[уы]$)", "\\1|\\2"}, // Обработка окончания -ому .
  {"(.*[бвгджзклмнпрстфхчцшщ])(ыми$)", "\\1|\\2"}, // Обработка окончания -ыми .
  {"(.*[бвгджзклмнпрстфхчцшщ])(ими$)", "\\1|\\2"}, // Обработка окончания -ими .
  {"(.*[бвгджзклмнпрстфхчцшщ])([ь]?ями$)", "\\1|\\2"} // Обработка окончания -ями .
};

/** Евгений Анисюткин. 02.12.2021
*
* Регулярное выражение, отвечающее за стеммирование большинства русских окончаний.
* Не используется для спецефических окончаний, под которые реализована отдельная обработка.
* Охватывает все окончания, кроме спецефических.
* Получена экспериментальным путем.
*
*/
QRegularExpression RU_ENDINGS("([а-я\\-]+[бвгджзклмнпрстфхчцшщ])([еиоы][й]|[аеия][я]|[еиоую][ю]|[еиоы][е]|[аео][вк]|[аеиоыя]м|н[аеио]|с[ая]|[аиыя]х|[ие]ну|[иуя]т|[ь]?[аеёоуыэюя]|и{1,2}|[йь]|[ь]?ев)$", QRegularExpression::UseUnicodePropertiesOption | QRegularExpression::CaseInsensitiveOption);

/** Евгений Анисюткин. 02.12.2021
*
* Английские слова, которые не стеммируются, но участвуют в поиске ошибок.
*
*/
noChange engNoChange {
  {
    "is", "his", "has", "was", "gas", "bias", "atlas", "canvas", "physics", "aquatics", "politics", "statistics", "acoustics", "goods", "braces",
    "clothes", "series", "flakes", "scales", "spectacles", "lodgings", "savings", "earnings", "means", "lens", "scissors", "pants",
    "shorts", "bus", "circus", "exodus", "nucleus", "genious", "surplus", "plus", "terminus", "minus", "bonus", "chorus", "census", "apparatus",
    "eucalyptus", "news", "as", "towards", "upwards", "afterwards", "themselves", "ourselves", "yes", "perhaps", "downstairs", "upstairs", "outdoors",
    "consensus", "its", "thus", "analysis", "abacus", "alumnus", "axis", "bacillus", "basis", "caucus", "crisis", "diagnosis", "ellipsis", "foetus",
    "fungus", "genus", "hiatus", "hypothesis", "oasis", "parenthesis", "phallus", "platypus", "synopsis", "synthesis", "thesis", "abdominocentesis",
    "alzheimers", "mitosis", "nephritis", "syphilis", "trichomoniasis", "christmas", "columbus", "davis", "jesus", "louis", "nicholas", "paris",
    "thomas", "uranus", "venus", "zeus", "cactus", "chaos", "discurs", "economics", "ers", "focus", "genesis", "gymnastics", "hippopotamus", "iris",
    "locus", "lyrics", "narcissus", "octopus", "photosynthesis", "prospectus", "radius", "rhinoceros", "sinus", "sis", "stimulus", "syllabus", "tennis",
    "virus", "this", "enzymes", "dais", "mantis", "neurosis", "paralysis", "corus", "rhombus", "walrus", "crocus"
  }
};

/** Евгений Анисюткин. 02.12.2021
*
* Регулярные выражения, отвечающие за 'простые' изменения в английсом языке при стеммировании.
* По сути эти слова не стеммируются, а заменяются на заранее заданный желаемый результат.
*
* Формат задачи изменений - массив вида {"изменяемое слово", "подставляемое слово"}
*
*/
simpleChange engSimpleChange {
  {"indices", "index"}, {"appendices", "appendix"}, {"vortices", "vortex"}, {"men", "man"}, {"women", "woman"}, {"teeth", "tooth"}, {"mice", "mouse"},
  {"feet", "foot"}, {"dice", "die"}, {"oxen", "ox"}, {"children", "child"}, {"axes", "axis"}, {"analyses", "analysis"}, {"crises", "crisis"},
  {"theses", "thesis"}, {"phenomena", "phenomenon"}, {"criteria", "criterion"}, {"data", "datum"}, {"memoranda", "memorandum"}, {"bacteria", "bacterium"},
  {"strata", "stratum"}, {"gases", "gas"}, {"quizzes", "quiz"}, {"lives", "life"}, {"knives", "knife"}, {"wives", "wife"}, {"bases", "basis"},
  {"ellipses", "ellipsis"}, {"hypotheses", "hypothesis"}, {"neuroses", "neurosis"}, {"oases", "oasis"}, {"paralyses", "paralysis"},
  {"parentheses", "parenthesis"}, {"synopses", "synopsis"}, {"syntheses", "synthesis"}, {"vertices", "vertex"}
};

simpleChange engSimpleStemmerChange {
  {"indices", "index"}, {"appendices", "appendix"}, {"vortices", "vortex"}, {"men", "man"}, {"women", "woman"}, {"teeth", "tooth"}, {"mice", "mouse"},
  {"feet", "foot"}, {"dice", "die"}, {"oxen", "ox"}, {"children", "child"}, {"axes", "axis"}, {"analyses", "analysis"}, {"crises", "crisis"},
  {"theses", "thesis"}, {"phenomena", "phenomenon"}, {"criteria", "criterion"}, {"data", "datum"}, {"memoranda", "memorandum"}, {"bacteria", "bacterium"},
  {"strata", "stratum"}, {"gases", "gas"}, {"quizzes", "quiz|es"}, {"lives", "life|s"}, {"knives", "knife|s"}, {"wives", "wife|s"}, {"bases", "basis|es"},
  {"ellipses", "ellipsis|es"}, {"hypotheses", "hypothesis|es"}, {"neuroses", "neurosis|es"}, {"oases", "oasis|es"}, {"paralyses", "paralysis|es"},
  {"parentheses", "parenthesis|es"}, {"synopses", "synopsis|es"}, {"syntheses", "synthesis|es"}, {"vertices", "vertex|es"}
};

/** Евгений Анисюткин. 02.12.2021
*
* Регулярные выражения отвечающие за стеммирования всех остальных английских окончаний.
* Используются для случаев когда модуль - не стеммер.
* На самом деле это тоже не совсем стеммирование, а замена окончаний.
*
*/
regexChange engRegexChange {
  {"(.*[bcdfghjklmnpqrstvwxz])(ies$)", "\\1y"}, //  Обработка окончания -ies, замена на -ly . Работает в случае если перед окончанием согласная
  {"(.*ous$)", "\\1"},
  {"(.*)(ves$)", "\\1f"}, // Обработка окончания -ves , замена на -f
  {"(.*)(ch)(es$)", "\\1\\2"}, // Обработка окончания -ches, Обрезка -es.
  {"(.*)(sh)(es$)", "\\1\\2"},// Обработка окончания -shes, Обрезка -es.
  {"(.*[sxoz])(es$)", "\\1"}, // Обработка окончания -oes, -xes, -ses, обрезка -es
  {"(.*[ouiae])(s$)", "\\1"}, // Обработка окончания -os, -us, -is, -as, -es. Обрезка -s. Работает в случае если вышестоящие регулярки не отработали
  {"(.*[bcdfghjklmnpqrtvwxyz])(s$)", "\\1"} //  Обработка окончания -s . Простое удаление. Работает в случае если перед окончанием согласная
};

/** Евгений Анисюткин. 02.12.2021
*
* Регулярные выражения отвечающие за стеммирования всех остальных английских окончаний.
* Используются для случаев когда модуль стеммер.
* Необходимы вследствие того, что стеммер должен подставлять символ | перед окончанием.
*
*/
regexChange engRegexStemmerChange {
  {"(.*[bcdfghjklmnpqrstvwxz])(ies$)", "\\1y|es"},
  {"(.*ous$)", "\\1"},
  {"(.*)(ves$)", "\\1f|es"},
  {"(.*)(ch)(es$)", "\\1\\2|\\3"},
  {"(.*)(sh)(es$)", "\\1\\2|\\3"},
  {"(.*[sxoz])(es$)", "\\1|\\2"},
  {"(.*[ouiae])(s$)", "\\1|\\2"},
  {"(.*[bcdfghjklmnpqrtvwxyz])(s$)", "\\1|\\2"}
};

/** Евгений Анисюткин. 02.12.2021
*
* Регулярные выражения отвечающие за стеммирования немецких окончаний.
* Используются для случаев когда модуль - не стеммер.
* На самом деле это тоже не совсем стеммирование, а замена окончаний.
*
*/
regexChange deuRegexChange {
  {"(.*)(?<!ss)(?<=s|ß|x|tz|z|sch|tsch|st)(es)$", "\\1"},
  {"(.*)(?<=is|as|os|us)(se)$", "\\1"},
  {"(.*)(s)(ses)$", "\\1"},
  {"(.*)(?<=and|ant|ast|at|ent|et|ist|loge|om|oph|ot)(en)$", "\\1"},
  {"(.*)(?<!ch)(s)$", "\\1"},
  {"(.*)[bcdfghjklmnpqrstvwxyz](e)$", "\\1"},
  {"(.*)(?<=el|er)(n)$", "\\1"},
};

/** Евгений Анисюткин. 02.12.2021
*
* Регулярные выражения отвечающие за стеммирования немецких окончаний.
* Используются для случаев когда модуль - стеммер.
* Необходимы вследствие того, что стеммер должен подставлять символ | перед окончанием..
*
*/
regexChange deuRegexStemmerChange {
  {"(.*)(?<!ss)(?<=s|ß|x|tz|z|sch|tsch|st)(es)$", "\\1|\\2"},
  {"(.*)(?<=is|as|os|us)(se)$", "\\1|\\2"},
  {"(.*)(s)(ses)$", "\\1|\\2"},
  {"(.*)(?<=and|ant|ast|at|ent|et|ist|loge|om|oph|ot)(en)$", "\\1|\\2"},
  {"(.*)(?<!ch)(s)$", "\\1|\\2"},
  {"(.*[bcdfghjklmnpqrstvwxyz])(e)$", "\\1|\\2"},
  {"(.*)(?<=el|er)(n)$", "\\1|\\2"},
};

/** Евгений Анисюткин. 02.12.2021
*
* Регулярные выражения отвечающие за стеммирования французских окончаний.
* Используются для случаев когда модуль - не стеммер.
* На самом деле это тоже не совсем стеммирование, а замена окончаний.
*
*/
regexChange freRegexChange {
  {"(.*)(s)$", "\\1"},
  {"l['’](.*)$", "\\1"}
};

/** Евгений Анисюткин. 02.12.2021
*
* Регулярные выражения отвечающие за стеммирования французских окончаний.
* Используются для случаев когда модуль - стеммер.
* Необходимы вследствие того, что стеммер должен подставлять символ | перед окончанием..
*
*/
regexChange freRegexStemmerChange {
  {"(.*)(s)$", "\\1|\\2"},
  {"l['’](.*)$", "\\1"}
};

/** Евгений Анисюткин. 02.12.2021
*
* Регулярные выражения отвечающие за стеммирования испанских окончаний.
* Используются для случаев когда модуль - не стеммер.
* На самом деле это тоже не совсем стеммирование, а замена окончаний.
*
*/
regexChange spaRegexChange {
  {"(.*)(a|e|o|as|es|os)$", "\\1"}
};

/** Евгений Анисюткин. 02.12.2021
*
* Регулярные выражения отвечающие за стеммирования испанских окончаний.
* Используются для случаев когда модуль - стеммер.
* Необходимы вследствие того, что стеммер должен подставлять символ | перед окончанием..
*
*/
regexChange spaRegexStemmerChange {
  {"(.*)(a|e|o|as|es|os)$", "\\1|\\2"}
};

/** Евгений Анисюткин. 02.12.2021
*
* Вспомогательные регулярнгые выражения
*
*/
QRegularExpression vowels("[аеёиоуыэюя]", QRegularExpression::UseUnicodePropertiesOption | QRegularExpression::CaseInsensitiveOption);

/** Евгений Анисюткин. 02.12.2021
*
* Регулярное выражение под вырезку аббревитур, использование под вопросом.
*
*/
QRegularExpression ABBR("[А-ЯЁA-Z0-9]{2,6}", QRegularExpression::UseUnicodePropertiesOption);

/** Евгений Анисюткин. 02.12.2021
*
* Функция стеммирования русских слов.
*
*/
QString stemRusWord(QString word, std::string module="stemmer") {

  if(module != "stemmer" && word.contains(ABBR) ) {
    return word; // Не стеммируем аббревиатуры. Под вопросом
  }

  word = word.toLower();

  if(rusNoChange.contains(word)) {
    return word; //Не стеммируем слова, заданные в исключениях
  }

  QString temp = word;

  /**
  *
  * Определяем какой набор регулярных выражений мы используем при стеммировании в русском стеммере
  * при стеммировании спецефических русских окончаний
  *
  */
  regexChange toChange;
  if(module != "stemmer") {
    toChange = rusRegexChange;
  } else {
    toChange = rusRegexStemmerChange;
  }

  QStringList parts;
  for(int i = 0; i < toChange.size(); i++) {
    if(word.length() < 5) {
      break;
    }
    QRegularExpression source(toChange[i].first);
    QString replacement = toChange[i].second;

    if(word.contains(source)) {
      word.replace(source, replacement);
      QStringList parts = word.split("|");
      if(!parts[0].contains(vowels)) {
        word = temp;
      }
      return word;
    }
  }

  // Стеммируем все слова русского языка, которые не были обработаны ранее
  if(word.contains(RU_ENDINGS)) {
    if(module == "stemmer") {
      word.replace(RU_ENDINGS, "\\1|\\2"); // Если модуль - стеммер добавляем символ | и обрезанное окончание.
    } else {
      word.replace(RU_ENDINGS, "\\1"); // Если модуль не стеммер, оставляем обрезанное слово
    }
  }

  parts = word.split("|");
  if(!parts[0].contains(vowels)) {
    word = temp;
  }

  return word;
}

/** Евгений Анисюткин. 02.12.2021
*
* Функция стеммирования алглийских слов.
*
*/
QString stemEngWord(QString word, std::string module="stemmer") {

  if(module != "stemmer" && word.contains(ABBR)) {
    return word; // Не стеммируем аббревиатуры. Под вопросом
  }

  word = word.toLower();

  // Определяем какой набор регулярных выражений мы используем при стеммировании в английском стеммере.
  simpleChange toSimpleChange;
  regexChange toChange;
  if(module != "stemmer") {
    toSimpleChange = engSimpleChange;
    toChange = engRegexChange;
  } else {
    toSimpleChange = engSimpleStemmerChange;
    toChange = engRegexStemmerChange;
  }

  if(engNoChange.contains(word)) {
    return word; //Не стеммируем слова, заданные в исключениях
  }

  QString temp = word;

  for(int i = 0; i < toSimpleChange.size(); i++) {
    if(toSimpleChange[i].first == word) {
      word = toSimpleChange[i].second;
      return word;
    }
  }

  for(int i = 0; i < toChange.size(); i++) {
    QRegularExpression source(toChange[i].first);
    QString replacement = toChange[i].second;

    if(word.contains(source)) {
      word.replace(source, replacement);
      break;
    }
  }

  return word;
}

/** Евгений Анисюткин. 02.12.2021
*
* Функция стеммирования немецких слов.
*
*/
QString stemDeuWord(QString word, std::string module="stemmer"){

  if(module != "stemmer" && word.contains( ABBR )) {
    return word; // Не стеммируем аббревиатуры. Под вопросом
  }

  word = word.toLower();

  // Определяем какой набор регулярных выражений мы используем при стеммировании в английском стеммере.
  regexChange toChange;
  if(module != "stemmer") {
    toChange = deuRegexChange;
  } else {
    toChange = deuRegexStemmerChange;
  }

  QString temp = word;

  for(int i = 0; i < toChange.size(); i++) {
    QRegularExpression source(toChange[i].first);
    QString replacement = toChange[i].second;

    if(word.contains(source)) {
      word.replace(source, replacement);
      break;
    }
  }

  return word;
}

/** Евгений Анисюткин. 02.12.2021
*
* Функция стеммирования французских слов.
*
*/
QString stemFreWord(QString word, std::string module="stemmer"){

  if(module != "stemmer" && word.contains( ABBR )) {
    return word; // Не стеммируем аббревиатуры. Под вопросом
  }

  word = word.toLower();

  // Определяем какой набор регулярных выражений мы используем при стеммировании в английском стеммере.
  regexChange toChange;
  if(module != "stemmer") {
    toChange = freRegexChange;
  } else {
    toChange = freRegexStemmerChange;
  }

  QString temp = word;

  for(int i = 0; i < toChange.size(); i++) {
    QRegularExpression source(toChange[i].first);
    QString replacement = toChange[i].second;

    if(word.contains(source)) {
      word.replace(source, replacement);
      break;
    }
  }

  return word;
}

/** Евгений Анисюткин. 02.12.2021
*
* Функция стеммирования испанских слов.
*
*/
QString stemSpaWord(QString word, std::string module="stemmer"){

  if(module != "stemmer" && word.contains( ABBR )) {
    return word; // Не стеммируем аббревиатуры. Под вопросом
  }

  word = word.toLower();

  // Определяем какой набор регулярных выражений мы используем при стеммировании в английском стеммере.
  regexChange toChange;
  if(module != "stemmer") {
    toChange = spaRegexChange;
  } else {
    toChange = spaRegexStemmerChange;
  }

  QString temp = word;

  for(int i = 0; i < toChange.size(); i++) {
    QRegularExpression source(toChange[i].first);
    QString replacement = toChange[i].second;

    if(word.contains(source)) {
      word.replace(source, replacement);
      break;
    }
  }

  return word;
}

/** Евгений Анисюткин. 02.12.2021
*
* Функция обертка под стеммирование любого иностранного языка.
* Рассмотреть обертку под стеммирование любого языка, где язык стеммирования передается вторым параметром
*
*/
QString stemWord(QString source, QString sourceLang, std::string module="stemmer") {
  QString res;
  if(sourceLang == "ru") {
    res = stemRusWord(source, module);
  } else if(sourceLang == "en") {
    res = stemEngWord(source, module);
  } else if(sourceLang == "de") {
    res = stemDeuWord(source, module);
  } else if(sourceLang == "fr") {
    res = stemFreWord(source, module);
  } else if(sourceLang == "es" || sourceLang == "spa") {
    res = stemSpaWord(source, module);
  }

  return res;
}
