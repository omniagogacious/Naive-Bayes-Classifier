#! /bin/bash

CITIES=dat/cities/
./textClassifier $CITIES/usCities100.txt $CITIES/russiaCities100.txt $CITIES/usCitiesNext50.txt $CITIES/russiaCitiesNext50.txt
./textClassifier $CITIES/russiaCities100.txt $CITIES/otherCities100.txt $CITIES/otherCitiesNext50.txt $CITIES/russiaCitiesNext50.txt
./textClassifier $CITIES/usCities100.txt $CITIES/otherCities100.txt $CITIES/otherCitiesNext50.txt $CITIES/usCitiesNext50.txt