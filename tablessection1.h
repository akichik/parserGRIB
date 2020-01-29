#ifndef TABLESSECTION1_H

enum class OrigCenters{
    USWS_NationalMetCenter=7,
    USWS_NWSTelecommsGateway=8,
    USWS_FieldStations=9,
    JapaneseMA_Tokyo=34,
    NHC_Miami=52,
    CanadianMS_Montreal=54,
    USAF_GWC=57,
    USNavy_FNOC=58,
    NOAAFSL_BoulderCO=59,
    UKMO_Bracknell=74,
    FWS_Toulouse=85,
    ESA=97,
    ECforMediumRangeForecaste=98,
    DeBilt=99
    //IG=99-101,

};

enum class TimeUnit{
    minute=0,
    hour=1,
    day=2,
    month=3,
    year=4,
    decade=5,
    normal=6,//30 years
    century=7,
    //8-253 reserved
    second=254
};

#endif // TABLESSECTION1_H
