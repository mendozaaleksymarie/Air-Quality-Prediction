/*
 * ════════════════════════════════════════════════════════════════════════
 * RANDOM FOREST MODEL - C++ EMBEDDED VERSION FOR ESP32
 * ════════════════════════════════════════════════════════════════════════
 * 
 * GENERATED: Automated conversion from Python sklearn model
 * Model Type: Random Forest Classifier
 * Features: 7 (PM2.5, PM10, Temperature, Humidity, Gas, CO, TimeOfDay)
 * Classes: 3 (0=Safe, 1=Caution, 2=Hazardous)
 * 
 * USAGE:
 *   float features[7] = {pm2_5, pm10, temp, humidity, gas, co, time_of_day};
 *   int prediction = predict(features);  // Returns 0, 1, or 2
 * 
 * ════════════════════════════════════════════════════════════════════════
 */

#ifndef MODEL_H
#define MODEL_H

#include <cmath>
#include <algorithm>

// ════════════════════════════════════════════════════════════════════════
// SCALER PARAMETERS (StandardScaler)
// ════════════════════════════════════════════════════════════════════════

const float SCALER_MEAN[] = {
    133.217755813861f,  // feature_0
    161.27621028991143f,  // feature_1
    31.449337391861768f,  // feature_2
    58.05692278116027f,  // feature_3
    16.01097656308724f,  // feature_4
    5.374461746573425e-69f,  // feature_5
    12.510349247036206f,  // feature_6
    28.827866216540663f,  // feature_7
    1.4076558225860476f,  // feature_8
    160.10976563087183f,  // feature_9
    294.4939661037749f,  // feature_10
    -0.0068302736144241795f,  // feature_11
    -0.02627590476303486f,  // feature_12
    0.01086554938469387f,  // feature_13
    1.2316588446877352e-70f,  // feature_14
    0.20205062479974367f,  // feature_15
    0.009291893623838513f,  // feature_16
    133.22458608747618f,  // feature_17
    133.26594806784823f,  // feature_18
    133.3590931701217f,  // feature_19
    16.00011101370255f,  // feature_20
    15.95203123553706f,  // feature_21
    15.892221210062443f,  // feature_22
    5.251295862104641e-69f,  // feature_23
    4.2051648778364183e-69f,  // feature_24
    4.2052207040892455e-69f,  // feature_25
    6.919913545479911f,  // feature_26
    0.5195082398065101f,  // feature_27
    -0.03479653957065043f,  // feature_28
    0.008779237423902596f,  // feature_29
    0.38615828260173024f,  // feature_30
    0.38276193527715474f,  // feature_31
    0.0f,  // feature_32
    0.9987824415251522f,  // feature_33
    0.899391220762576f,  // feature_34
};

const float SCALER_SCALE[] = {
    240.48863205757942f,  // feature_0
    316.21516438817525f,  // feature_1
    5.3170883142500305f,  // feature_2
    12.577877564454162f,  // feature_3
    148.25909238140423f,  // feature_4
    3.024698621937001e-67f,  // feature_5
    4.187174529593373f,  // feature_6
    3.439590398916908f,  // feature_7
    1.2344354871033696f,  // feature_8
    1482.5909238140457f,  // feature_9
    555.7485017892001f,  // feature_10
    16.62503349804496f,  // feature_11
    24.230928203938255f,  // feature_12
    4.494508213268482f,  // feature_13
    1.4515824829259196e-67f,  // feature_14
    0.4015297869620494f,  // feature_15
    0.09594558007914966f,  // feature_16
    240.52789922403286f,  // feature_17
    240.69637095049487f,  // feature_18
    240.9824955632812f,  // feature_19
    148.21371841648076f,  // feature_20
    148.05768813557864f,  // feature_21
    147.77402102695763f,  // feature_22
    3.019797205287314e-67f,  // feature_23
    2.6379059587438376e-67f,  // feature_24
    2.6379445207058726e-67f,  // feature_25
    22.28837979762967f,  // feature_26
    6.661751100371604f,  // feature_27
    0.9855120141770674f,  // feature_28
    0.9968806601548997f,  // feature_29
    0.4868676035430413f,  // feature_30
    0.4860609387515998f,  // feature_31
    1.0f,  // feature_32
    0.03487228163180798f,  // feature_33
    0.43714463512110413f,  // feature_34
};

const int NUM_FEATURES = 35;
const int NUM_CLASSES = 3;
const int NUM_TREES = 200;

const int CLASS_LABELS[NUM_CLASSES] = {0, 1, 2};

// ════════════════════════════════════════════════════════════════════════
// FEATURE PREPROCESSING (StandardScaler normalization)
// ════════════════════════════════════════════════════════════════════════

void normalize_features(float* features) {
    for (int i = 0; i < NUM_FEATURES; i++) {
        features[i] = (features[i] - SCALER_MEAN[i]) / SCALER_SCALE[i];
    }
}


// Tree 0
int predict_tree_0(const float* features) {
    // Max depth: 10
    if (features[21] <= -0.07738054171204567f) {
        if (features[22] <= -0.08196991309523582f) {
            if (features[1] <= -0.2824445366859436f) {
                return 0;            } else {
                return 1;            }
        } else {
            if (features[1] <= -0.3082122802734375f) {
                if (features[15] <= 0.7420355677604675f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[10] <= 0.04044125974178314f) {
                    if (features[22] <= -0.07890717685222626f) {
                        if (features[19] <= -0.33420728147029877f) {
                            if (features[18] <= -0.33926980197429657f) {
                                if (features[11] <= -0.00961419939994812f) {
                                    return 0;                                } else {
                                    if (features[17] <= -0.34572573006153107f) {
                                        if (features[0] <= -0.33322784304618835f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                return 1;                            }
                        } else {
                            if (features[26] <= -0.14540664106607437f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    } else {
                        return 0;                    }
                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[2] <= -0.47664007544517517f) {
            return 0;        } else {
            if (features[20] <= -0.04661053791642189f) {
                if (features[10] <= -0.14639385044574738f) {
                    if (features[10] <= -0.32388776540756226f) {
                        return 0;                    } else {
                        if (features[27] <= -0.06938143074512482f) {
                            if (features[0] <= -0.3414672315120697f) {
                                return 0;                            } else {
                                if (features[18] <= -0.11235618218779564f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        } else {
                            if (features[9] <= -0.061708297580480576f) {
                                return 0;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[18] <= -0.29690301418304443f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[19] <= -0.06499045714735985f) {
                    if (features[20] <= 13.23633861541748f) {
                        if (features[17] <= -0.3428000658750534f) {
                            if (features[9] <= 7.349121570587158f) {
                                if (features[1] <= -0.29415714740753174f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            } else {
                                return 1;                            }
                        } else {
                            if (features[0] <= -0.13075940683484077f) {
                                return 1;                            } else {
                                if (features[10] <= -0.05583641305565834f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[8] <= -0.3369559943675995f) {
                        return 1;                    } else {
                        if (features[8] <= -0.2970873564481735f) {
                            if (features[15] <= 0.7420355677604675f) {
                                return 2;                            } else {
                                return 1;                            }
                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    }
}

// Tree 1
int predict_tree_1(const float* features) {
    // Max depth: 9
    if (features[17] <= -0.09930915758013725f) {
        if (features[4] <= -0.05137520097196102f) {
            if (features[0] <= -0.3415699154138565f) {
                return 0;            } else {
                if (features[1] <= -0.10966407880187035f) {
                    if (features[11] <= -0.11357760429382324f) {
                        return 1;                    } else {
                        return 1;                    }
                } else {
                    return 1;                }
            }
        } else {
            if (features[19] <= -0.3605910390615463f) {
                if (features[0] <= -0.5267125070095062f) {
                    return 0;                } else {
                    if (features[20] <= 7.509936571121216f) {
                        if (features[22] <= -0.0028463478665798903f) {
                            if (features[18] <= -0.3956648111343384f) {
                                return 0;                            } else {
                                return 1;                            }
                        } else {
                            if (features[20] <= 0.04070831649005413f) {
                                if (features[18] <= -0.4183613061904907f) {
                                    return 1;                                } else {
                                    if (features[30] <= 0.23382475972175598f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                }
                            } else {
                                return 0;                            }
                        }
                    } else {
                        if (features[4] <= 13.491242408752441f) {
                            return 1;                        } else {
                            if (features[1] <= -0.48040710389614105f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                if (features[34] <= -2.0574225783348083f) {
                    if (features[18] <= -0.18044565618038177f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[20] <= -0.04794536158442497f) {
                        if (features[8] <= -0.31556612253189087f) {
                            return 2;                        } else {
                            if (features[0] <= -0.13042572140693665f) {
                                return 1;                            } else {
                                if (features[3] <= -0.787646621465683f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        }
                    } else {
                        if (features[0] <= -0.1299893744289875f) {
                            if (features[22] <= 0.02430471871048212f) {
                                return 1;                            } else {
                                if (features[3] <= 0.7229420840740204f) {
                                    if (features[19] <= -0.33172260224819183f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 0;                                }
                            }
                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    } else {
        if (features[3] <= 1.8876855373382568f) {
            if (features[10] <= -0.13565313816070557f) {
                return 2;            } else {
                return 2;            }
        } else {
            if (features[9] <= -0.05491879768669605f) {
                return 0;            } else {
                return 0;            }
        }
    }
}

// Tree 2
int predict_tree_2(const float* features) {
    // Max depth: 9
    if (features[17] <= -0.12116822972893715f) {
        if (features[4] <= -0.05116993933916092f) {
            if (features[17] <= -0.3523726314306259f) {
                if (features[10] <= -0.31527964770793915f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                if (features[20] <= -0.07251865044236183f) {
                    if (features[10] <= -0.3222438842058182f) {
                        return 0;                    } else {
                        if (features[26] <= -0.29373420774936676f) {
                            return 1;                        } else {
                            if (features[13] <= -0.0002749844134086743f) {
                                if (features[19] <= -0.4283435195684433f) {
                                    if (features[2] <= -0.04689359664916992f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[15] <= 0.7420355677604675f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    if (features[31] <= 0.24120032787322998f) {
                        return 1;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[9] <= 13.232214450836182f) {
                if (features[17] <= -0.3428000658750534f) {
                    if (features[6] <= -0.36070844903588295f) {
                        if (features[8] <= 0.18876448273658752f) {
                            if (features[8] <= -0.17630131542682648f) {
                                return 0;                            } else {
                                if (features[20] <= 6.680717468261719f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            }
                        } else {
                            return 0;                        }
                    } else {
                        if (features[15] <= 0.7420355677604675f) {
                            return 0;                        } else {
                            if (features[19] <= -0.42188847064971924f) {
                                if (features[7] <= -0.7765958607196808f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    if (features[0] <= -0.129886694252491f) {
                        return 1;                    } else {
                        if (features[2] <= 0.32925213500857353f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[17] <= 0.9494706392288208f) {
            if (features[0] <= -0.12706322595477104f) {
                return 2;            } else {
                if (features[1] <= 0.675236701965332f) {
                    return 2;                } else {
                    if (features[27] <= -0.07701577246189117f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[22] <= -0.04790680855512619f) {
                if (features[3] <= 1.42258320748806f) {
                    return 2;                } else {
                    return 0;                }
            } else {
                if (features[17] <= 1.1928396821022034f) {
                    if (features[10] <= 1.0918316841125488f) {
                        return 2;                    } else {
                        if (features[11] <= 1.0593523681163788f) {
                            return 2;                        } else {
                            if (features[21] <= -0.04354905150830746f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 3
int predict_tree_3(const float* features) {
    // Max depth: 7
    if (features[18] <= -0.11551060900092125f) {
        if (features[0] <= -0.34198060631752014f) {
            if (features[0] <= -0.5160860121250153f) {
                if (features[20] <= 7.332235813140869f) {
                    if (features[30] <= 0.23382475972175598f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[4] <= 13.232214450836182f) {
                        return 1;                    } else {
                        if (features[9] <= 14.60155439376831f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                return 0;            }
        } else {
            if (features[1] <= 0.10100666433572769f) {
                if (features[6] <= -0.36070844158530235f) {
                    if (features[0] <= -0.1276792585849762f) {
                        return 1;                    } else {
                        if (features[11] <= 0.091750118881464f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[27] <= -0.010618324624374509f) {
                        if (features[0] <= -0.1576593741774559f) {
                            if (features[20] <= -0.082460917532444f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[7] <= -0.7951010167598724f) {
                            return 2;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[7] <= 1.9298940896987915f) {
            if (features[22] <= 0.014494944829493761f) {
                if (features[17] <= -0.11534256488084793f) {
                    return 1;                } else {
                    if (features[12] <= -3.83341908454895f) {
                        if (features[19] <= 1.0966891050338745f) {
                            return 2;                        } else {
                            return 2;                        }
                    } else {
                        if (features[7] <= 1.918724775314331f) {
                            if (features[6] <= -2.8683661222457886f) {
                                return 2;                            } else {
                                return 2;                            }
                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[1] <= -0.10150429606437683f) {
                    return 1;                } else {
                    return 2;                }
            }
        } else {
            if (features[4] <= -0.04266172647476196f) {
                return 0;            } else {
                return 2;            }
        }
    }
}

// Tree 4
int predict_tree_4(const float* features) {
    // Max depth: 8
    if (features[0] <= -0.13170911371707916f) {
        if (features[1] <= -0.3082122802734375f) {
            if (features[21] <= 7.811189413070679f) {
                if (features[20] <= -0.08395067974925041f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[0] <= -0.5231703519821167f) {
                    if (features[26] <= -0.30242639780044556f) {
                        return 1;                    } else {
                        return 1;                    }
                } else {
                    if (features[0] <= -0.5167533755302429f) {
                        if (features[9] <= 13.145212650299072f) {
                            return 1;                        } else {
                            return 2;                        }
                    } else {
                        return 1;                    }
                }
            }
        } else {
            if (features[3] <= -0.9267798066139221f) {
                return 1;            } else {
                if (features[18] <= -0.33455097675323486f) {
                    if (features[3] <= -0.660439133644104f) {
                        return 0;                    } else {
                        if (features[10] <= -0.32011130452156067f) {
                            return 0;                        } else {
                            if (features[0] <= -0.34213460981845856f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[10] <= 0.880149632692337f) {
            return 2;        } else {
            if (features[8] <= -0.16992498934268951f) {
                if (features[27] <= -0.06029519438743591f) {
                    if (features[2] <= -0.6017085164785385f) {
                        return 0;                    } else {
                        if (features[4] <= -0.04729991964995861f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[26] <= -0.11276192963123322f) {
                        return 0;                    } else {
                        if (features[11] <= 1.4540420174598694f) {
                            if (features[20] <= -0.049426790326833725f) {
                                if (features[6] <= 0.4751773923635483f) {
                                    return 2;                                } else {
                                    return 0;                                }
                            } else {
                                return 2;                            }
                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[2] <= -0.8179923221468925f) {
                    return 0;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 5
int predict_tree_5(const float* features) {
    // Max depth: 9
    if (features[0] <= -0.1289113163948059f) {
        if (features[10] <= -0.3220328539609909f) {
            if (features[22] <= 6.220737934112549f) {
                return 0;            } else {
                if (features[4] <= 13.695127487182617f) {
                    if (features[2] <= -0.28198467195034027f) {
                        return 1;                    } else {
                        return 1;                    }
                } else {
                    if (features[3] <= -0.2708662748336792f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[11] <= 0.2291303351521492f) {
                if (features[6] <= -1.1965942978858948f) {
                    return 0;                } else {
                    if (features[19] <= -0.3300832211971283f) {
                        if (features[26] <= -0.283571794629097f) {
                            return 0;                        } else {
                            if (features[21] <= -0.08273506537079811f) {
                                return 1;                            } else {
                                if (features[9] <= -0.08229538053274155f) {
                                    if (features[26] <= -0.2537175342440605f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 1;                                }
                            }
                        }
                    } else {
                        return 1;                    }
                }
            } else {
                if (features[4] <= -0.08203015848994255f) {
                    return 1;                } else {
                    if (features[7] <= -0.760534942150116f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            }
        }
    } else {
        if (features[7] <= 1.918283224105835f) {
            return 2;        } else {
            if (features[4] <= -0.04289446957409382f) {
                return 0;            } else {
                if (features[2] <= 2.0689260959625244f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 6
int predict_tree_6(const float* features) {
    // Max depth: 7
    if (features[21] <= -0.07733801752328873f) {
        if (features[18] <= -0.353246733546257f) {
            if (features[0] <= -0.3416982591152191f) {
                return 0;            } else {
                return 1;            }
        } else {
            if (features[2] <= -0.3948283940553665f) {
                if (features[9] <= -0.08073737844824791f) {
                    return 0;                } else {
                    return 2;                }
            } else {
                if (features[6] <= 0.23635287210345268f) {
                    if (features[26] <= 0.06223623640835285f) {
                        if (features[19] <= -0.3797256797552109f) {
                            return 1;                        } else {
                            return 0;                        }
                    } else {
                        return 0;                    }
                } else {
                    if (features[4] <= -0.081146240234375f) {
                        if (features[10] <= -0.3214108347892761f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        return 0;                    }
                }
            }
        }
    } else {
        if (features[0] <= -0.13478926569223404f) {
            if (features[0] <= -0.34192925691604614f) {
                if (features[17] <= -0.515260249376297f) {
                    if (features[20] <= 7.2288596630096436f) {
                        return 0;                    } else {
                        if (features[22] <= 15.93189811706543f) {
                            if (features[8] <= 0.15700668096542358f) {
                                return 1;                            } else {
                                return 2;                            }
                        } else {
                            if (features[10] <= -0.4966944009065628f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    return 0;                }
            } else {
                return 1;            }
        } else {
            if (features[1] <= 0.894574761390686f) {
                if (features[10] <= 0.8786945641040802f) {
                    return 2;                } else {
                    if (features[21] <= -0.047989679500460625f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[20] <= -0.0484618004411459f) {
                    if (features[3] <= 1.42258320748806f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 7
int predict_tree_7(const float* features) {
    // Max depth: 9
    if (features[0] <= -0.1342502385377884f) {
        if (features[9] <= -0.05088348686695099f) {
            if (features[8] <= -0.17109087109565735f) {
                if (features[26] <= 0.4199005216360092f) {
                    if (features[18] <= -0.34439894556999207f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    return 1;                }
            } else {
                if (features[17] <= -0.35250094532966614f) {
                    if (features[4] <= -0.08399952203035355f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[1] <= -0.3081732392311096f) {
                        return 0;                    } else {
                        if (features[27] <= -0.0679597295820713f) {
                            if (features[6] <= -0.8383575081825256f) {
                                if (features[7] <= 0.02339221630245447f) {
                                    return 1;                                } else {
                                    return 0;                                }
                            } else {
                                if (features[11] <= 0.05536292865872383f) {
                                    if (features[10] <= -0.32079994678497314f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 1;                                }
                            }
                        } else {
                            return 0;                        }
                    }
                }
            }
        } else {
            if (features[18] <= -0.376507431268692f) {
                if (features[10] <= -0.48734210431575775f) {
                    if (features[34] <= -2.0574225783348083f) {
                        if (features[20] <= 14.232638835906982f) {
                            if (features[4] <= 5.766835570335388f) {
                                return 0;                            } else {
                                if (features[1] <= -0.46875306963920593f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[26] <= -0.30489830672740936f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        return 0;                    }
                } else {
                    if (features[1] <= -0.3243756592273712f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[17] <= -0.34231245517730713f) {
                    return 0;                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[18] <= 0.9483521282672882f) {
            if (features[3] <= 1.9234626293182373f) {
                return 2;            } else {
                return 0;            }
        } else {
            if (features[2] <= -0.7615704536437988f) {
                return 0;            } else {
                return 2;            }
        }
    }
}

// Tree 8
int predict_tree_8(const float* features) {
    // Max depth: 8
    if (features[1] <= -0.06462910771369934f) {
        if (features[0] <= -0.34192925691604614f) {
            if (features[21] <= 6.281148672103882f) {
                return 0;            } else {
                if (features[9] <= 13.232214450836182f) {
                    if (features[20] <= 7.802642107009888f) {
                        return 1;                    } else {
                        return 1;                    }
                } else {
                    if (features[31] <= 0.24120032787322998f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[19] <= -0.10676901414990425f) {
                if (features[8] <= -0.32313086092472076f) {
                    return 2;                } else {
                    if (features[6] <= -0.36070844158530235f) {
                        if (features[18] <= -0.10822721943259239f) {
                            if (features[8] <= -0.3141946792602539f) {
                                return 2;                            } else {
                                if (features[13] <= -0.001813212875276804f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        } else {
                            return 2;                        }
                    } else {
                        return 1;                    }
                }
            } else {
                if (features[26] <= -0.15462499856948853f) {
                    if (features[11] <= -0.10540904849767685f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    if (features[10] <= -0.1179148517549038f) {
                        if (features[21] <= -0.043440235778689384f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        if (features[18] <= 0.04613456502556801f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    } else {
        if (features[10] <= 0.8777837753295898f) {
            if (features[21] <= 0.08507823944091797f) {
                if (features[9] <= -0.07795154675841331f) {
                    return 1;                } else {
                    if (features[16] <= 5.114441957324743f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                return 1;            }
        } else {
            if (features[9] <= -0.048392850905656815f) {
                if (features[22] <= -0.06526397354900837f) {
                    return 2;                } else {
                    if (features[0] <= 2.2774804830551147f) {
                        return 0;                    } else {
                        if (features[19] <= 2.4326295852661133f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                return 2;            }
        }
    }
}

// Tree 9
int predict_tree_9(const float* features) {
    // Max depth: 10
    if (features[1] <= -0.07146146520972252f) {
        if (features[1] <= -0.30885645747184753f) {
            if (features[22] <= 5.339713096618652f) {
                return 0;            } else {
                if (features[22] <= 16.578267097473145f) {
                    if (features[28] <= 0.03530806303024292f) {
                        if (features[4] <= 14.203718185424805f) {
                            return 1;                        } else {
                            return 2;                        }
                    } else {
                        if (features[17] <= -0.5210602283477783f) {
                            return 1;                        } else {
                            if (features[22] <= 8.51295804977417f) {
                                return 1;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[17] <= -0.5205726325511932f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[10] <= -0.10146501287817955f) {
                if (features[1] <= -0.1732635349035263f) {
                    if (features[7] <= 1.2658986449241638f) {
                        if (features[2] <= -0.4023513048887253f) {
                            if (features[13] <= -0.0018269470310769975f) {
                                return 1;                            } else {
                                return 0;                            }
                        } else {
                            if (features[6] <= -0.9577697813510895f) {
                                if (features[1] <= -0.28791041672229767f) {
                                    if (features[26] <= -0.282365158200264f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                if (features[10] <= -0.16434317082166672f) {
                                    if (features[27] <= -0.07701197266578674f) {
                                        if (features[0] <= -0.3404148519039154f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[1] <= -0.3026878237724304f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    return 2;                                }
                            }
                        }
                    } else {
                        return 0;                    }
                } else {
                    if (features[26] <= -0.1544383242726326f) {
                        return 2;                    } else {
                        if (features[19] <= -0.07075390219688416f) {
                            if (features[20] <= -0.04735645465552807f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            return 1;                        }
                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[18] <= -0.18470285087823868f) {
            if (features[17] <= -0.16728591918945312f) {
                return 1;            } else {
                if (features[22] <= -0.05850106105208397f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[8] <= -0.2101227045059204f) {
                if (features[7] <= 1.6395642161369324f) {
                    return 2;                } else {
                    return 0;                }
            } else {
                if (features[10] <= 2.074623703956604f) {
                    if (features[4] <= -0.04916852153837681f) {
                        if (features[3] <= 1.630090393126011f) {
                            return 2;                        } else {
                            return 0;                        }
                    } else {
                        if (features[19] <= 1.1217408776283264f) {
                            if (features[0] <= -0.10537384822964668f) {
                                return 2;                            } else {
                                return 2;                            }
                        } else {
                            if (features[9] <= -0.048392850905656815f) {
                                return 0;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[21] <= -0.04899987950921059f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 10
int predict_tree_10(const float* features) {
    // Max depth: 9
    if (features[1] <= -0.06462910771369934f) {
        if (features[1] <= -0.3082122802734375f) {
            if (features[6] <= -0.7189452350139618f) {
                if (features[17] <= -0.515260249376297f) {
                    if (features[27] <= 2.7554391622543335f) {
                        if (features[34] <= -2.0574225783348083f) {
                            if (features[26] <= -0.2964233160018921f) {
                                return 2;                            } else {
                                return 0;                            }
                        } else {
                            return 0;                        }
                    } else {
                        if (features[12] <= 0.018916926346719265f) {
                            if (features[21] <= 14.85464859008789f) {
                                if (features[20] <= 6.277178049087524f) {
                                    return 0;                                } else {
                                    if (features[9] <= 13.145212650299072f) {
                                        return 1;                                    } else {
                                        return 2;                                    }
                                }
                            } else {
                                if (features[10] <= -0.4963834136724472f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[20] <= 9.529451370239258f) {
                                return 0;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    return 0;                }
            } else {
                return 0;            }
        } else {
            if (features[18] <= -0.12004990875720978f) {
                if (features[0] <= -0.3415699154138565f) {
                    return 0;                } else {
                    if (features[4] <= -0.04824754409492016f) {
                        if (features[0] <= -0.13042572140693665f) {
                            return 1;                        } else {
                            return 2;                        }
                    } else {
                        return 1;                    }
                }
            } else {
                if (features[12] <= -0.11762930825352669f) {
                    if (features[6] <= -0.4801207147538662f) {
                        return 2;                    } else {
                        return 1;                    }
                } else {
                    if (features[13] <= -0.0050407457165420055f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[18] <= 0.9486342072486877f) {
            if (features[9] <= 0.0653602946549654f) {
                if (features[17] <= -0.17680716514587402f) {
                    return 1;                } else {
                    if (features[1] <= 1.0932986736297607f) {
                        return 2;                    } else {
                        if (features[4] <= -0.04943915084004402f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                return 1;            }
        } else {
            if (features[2] <= -0.7615704536437988f) {
                return 0;            } else {
                return 2;            }
        }
    }
}

// Tree 11
int predict_tree_11(const float* features) {
    // Max depth: 9
    if (features[18] <= -0.089890506118536f) {
        if (features[0] <= -0.34185226261615753f) {
            if (features[27] <= 5.6861772537231445f) {
                if (features[8] <= 0.05667075887322426f) {
                    if (features[16] <= 5.114441957324743f) {
                        return 0;                    } else {
                        if (features[18] <= -0.5137634873390198f) {
                            return 2;                        } else {
                            if (features[14] <= 0.849807287188014f) {
                                return 0;                            } else {
                                return 0;                            }
                        }
                    }
                } else {
                    if (features[20] <= 10.197363376617432f) {
                        return 0;                    } else {
                        if (features[4] <= 20.165966987609863f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[4] <= 13.145212650299072f) {
                    if (features[28] <= 0.03530806303024292f) {
                        if (features[0] <= -0.5162656605243683f) {
                            if (features[0] <= -0.5186784565448761f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            return 0;                        }
                    } else {
                        if (features[12] <= 0.0005748944822698832f) {
                            return 1;                        } else {
                            if (features[27] <= 13.96885347366333f) {
                                return 0;                            } else {
                                return 0;                            }
                        }
                    }
                } else {
                    if (features[12] <= -0.01649338472634554f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[7] <= -0.806524008512497f) {
                return 2;            } else {
                if (features[8] <= -0.3214367479085922f) {
                    return 2;                } else {
                    if (features[27] <= 0.14518307894468307f) {
                        if (features[22] <= -0.04748491011559963f) {
                            if (features[10] <= -0.14639385044574738f) {
                                if (features[10] <= -0.16145528852939606f) {
                                    if (features[22] <= -0.08196114003658295f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                return 2;                            }
                        } else {
                            if (features[10] <= 0.00019968044944107533f) {
                                return 1;                            } else {
                                return 2;                            }
                        }
                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[3] <= 1.8876855373382568f) {
            if (features[0] <= -0.12957868725061417f) {
                if (features[8] <= -0.14807479828596115f) {
                    return 1;                } else {
                    return 0;                }
            } else {
                return 2;            }
        } else {
            if (features[29] <= -0.008806705474853516f) {
                return 0;            } else {
                return 0;            }
        }
    }
}

// Tree 12
int predict_tree_12(const float* features) {
    // Max depth: 10
    if (features[8] <= -0.3167666047811508f) {
        if (features[18] <= 0.014103020075708628f) {
            if (features[17] <= -0.32224343717098236f) {
                if (features[21] <= -0.04445794224739075f) {
                    if (features[28] <= -0.4720424022525549f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    return 2;                }
            } else {
                if (features[21] <= -0.04652586951851845f) {
                    return 2;                } else {
                    return 1;                }
            }
        } else {
            return 2;        }
    } else {
        if (features[1] <= -0.30885645747184753f) {
            if (features[9] <= 7.0539209842681885f) {
                if (features[3] <= -1.4395849108695984f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[9] <= 13.232214450836182f) {
                    return 1;                } else {
                    if (features[21] <= 12.51248025894165f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[6] <= 1.1916509866714478f) {
                if (features[2] <= -0.9656295031309128f) {
                    if (features[18] <= -0.3682495057582855f) {
                        return 1;                    } else {
                        return 0;                    }
                } else {
                    if (features[18] <= -0.08578718453645706f) {
                        if (features[26] <= 0.6430623233318329f) {
                            if (features[17] <= -0.12091159075498581f) {
                                if (features[10] <= -0.3222438842058182f) {
                                    return 0;                                } else {
                                    if (features[3] <= 0.7229420840740204f) {
                                        if (features[3] <= -0.8234237134456635f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 0;                                    }
                                }
                            } else {
                                return 2;                            }
                        } else {
                            if (features[27] <= -0.0571341123431921f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[1] <= -0.17242413014173508f) {
                            return 1;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                return 2;            }
        }
    }
}

// Tree 13
int predict_tree_13(const float* features) {
    // Max depth: 10
    if (features[21] <= -0.07733259722590446f) {
        if (features[6] <= 0.23635287210345268f) {
            if (features[17] <= -0.36915670335292816f) {
                if (features[13] <= -0.006702581886202097f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[20] <= -0.08186451718211174f) {
                    if (features[10] <= -0.32837508618831635f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[18] <= 0.008435308933258057f) {
                        if (features[30] <= 0.23382475972175598f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[26] <= -0.269607737660408f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[27] <= -0.07676960900425911f) {
                if (features[26] <= -0.2800694555044174f) {
                    if (features[3] <= 0.3333692103624344f) {
                        return 0;                    } else {
                        if (features[1] <= -0.27461661398410797f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[2] <= 0.00012461841106414795f) {
                        if (features[21] <= -0.08223184198141098f) {
                            return 0;                        } else {
                            if (features[17] <= -0.3408752977848053f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[17] <= -0.33615317940711975f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[1] <= -0.28775425255298615f) {
                    return 0;                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[22] <= -0.07025199010968208f) {
            if (features[20] <= -0.07318752259016037f) {
                if (features[19] <= -0.32895614206790924f) {
                    if (features[12] <= 0.1269311085343361f) {
                        if (features[28] <= 0.03530806303024292f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[1] <= -0.341749370098114f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[20] <= -0.07761681079864502f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[8] <= -0.19030234962701797f) {
                    if (features[26] <= -0.30267180502414703f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    if (features[0] <= -0.3426222950220108f) {
                        if (features[17] <= -0.4569009393453598f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                }
            }
        } else {
            if (features[0] <= -0.1342502385377884f) {
                if (features[4] <= -0.05116993933916092f) {
                    if (features[2] <= -0.03748995345085859f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[6] <= 1.072238713502884f) {
                        if (features[20] <= 0.046071359887719154f) {
                            if (features[10] <= -0.32007797062397003f) {
                                if (features[26] <= -0.3079490214586258f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                if (features[0] <= -0.34085120260715485f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            }
                        } else {
                            if (features[2] <= -0.22556281834840775f) {
                                if (features[3] <= -0.19931206852197647f) {
                                    if (features[4] <= 11.277470350265503f) {
                                        return 0;                                    } else {
                                        return 2;                                    }
                                } else {
                                    if (features[19] <= -0.5256560444831848f) {
                                        return 0;                                    } else {
                                        if (features[4] <= 13.695127487182617f) {
                                            return 1;                                        } else {
                                            return 2;                                        }
                                    }
                                }
                            } else {
                                if (features[6] <= 0.23635287210345268f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            }
                        }
                    } else {
                        if (features[11] <= -0.0404319241642952f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                }
            } else {
                if (features[7] <= 1.9298940896987915f) {
                    if (features[4] <= -0.049794718623161316f) {
                        if (features[27] <= -0.06131746806204319f) {
                            if (features[0] <= 0.751523494720459f) {
                                return 2;                            } else {
                                return 0;                            }
                        } else {
                            return 2;                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[20] <= -0.04340528883039951f) {
                        return 0;                    } else {
                        if (features[17] <= 2.0259865522384644f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    }
}

// Tree 14
int predict_tree_14(const float* features) {
    // Max depth: 10
    if (features[18] <= -0.089890506118536f) {
        if (features[10] <= -0.3220328539609909f) {
            if (features[13] <= -3.6484583616256714f) {
                if (features[20] <= 14.415037631988525f) {
                    if (features[9] <= 6.768197298049927f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[2] <= -0.28198467195034027f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[20] <= 7.051059246063232f) {
                    return 0;                } else {
                    if (features[18] <= -0.5177385807037354f) {
                        if (features[28] <= 0.03530806303024292f) {
                            return 2;                        } else {
                            return 2;                        }
                    } else {
                        if (features[19] <= -0.5159734487533569f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            }
        } else {
            if (features[11] <= 1.483745813369751f) {
                if (features[18] <= -0.11235618218779564f) {
                    if (features[7] <= 1.2658986449241638f) {
                        if (features[18] <= -0.15685156732797623f) {
                            if (features[17] <= -0.15394078940153122f) {
                                if (features[17] <= -0.3438779413700104f) {
                                    if (features[18] <= -0.3627869635820389f) {
                                        if (features[21] <= -0.07693443819880486f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 0;                                    }
                                } else {
                                    if (features[22] <= -0.08184835687279701f) {
                                        if (features[26] <= -0.28316234052181244f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[18] <= -0.3391672223806381f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            } else {
                                return 2;                            }
                        } else {
                            if (features[11] <= -0.027436494827270508f) {
                                return 1;                            } else {
                                if (features[22] <= -0.048549264669418335f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        }
                    } else {
                        return 0;                    }
                } else {
                    if (features[11] <= -0.11914706975221634f) {
                        return 1;                    } else {
                        if (features[27] <= -0.07628919184207916f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[17] <= 0.9494706392288208f) {
            if (features[2] <= -0.4465484172105789f) {
                if (features[22] <= -0.07303610071539879f) {
                    if (features[1] <= 0.26180123537778854f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    return 1;                }
            } else {
                if (features[1] <= -0.1508924588561058f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[3] <= 1.4504098445177078f) {
                return 2;            } else {
                return 0;            }
        }
    }
}

// Tree 15
int predict_tree_15(const float* features) {
    // Max depth: 9
    if (features[0] <= -0.1342502385377884f) {
        if (features[18] <= -0.3770972937345505f) {
            if (features[13] <= 2.6731386184692383f) {
                if (features[9] <= 4.818542003631592f) {
                    if (features[17] <= -0.3769328147172928f) {
                        return 0;                    } else {
                        if (features[27] <= -0.07735327258706093f) {
                            return 0;                        } else {
                            if (features[21] <= -0.07634449377655983f) {
                                if (features[10] <= -0.3058495819568634f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            } else {
                                if (features[7] <= 0.8715281784534454f) {
                                    if (features[11] <= 0.005609012208878994f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    return 1;                                }
                            }
                        }
                    }
                } else {
                    if (features[26] <= -0.284723237156868f) {
                        if (features[0] <= -0.5207318961620331f) {
                            return 1;                        } else {
                            if (features[17] <= -0.5185451805591583f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[7] <= -0.6849594712257385f) {
                    if (features[22] <= 6.977897763252258f) {
                        return 0;                    } else {
                        if (features[26] <= -0.30435535311698914f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[21] <= 12.398977279663086f) {
                        if (features[27] <= 10.090704441070557f) {
                            return 0;                        } else {
                            if (features[4] <= 7.255112886428833f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[17] <= -0.3438779413700104f) {
                if (features[18] <= -0.37455835938453674f) {
                    if (features[12] <= 0.05203448235988617f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    return 0;                }
            } else {
                if (features[4] <= 0.06442433036863804f) {
                    if (features[4] <= -0.08251646161079407f) {
                        return 1;                    } else {
                        if (features[1] <= -0.3081732392311096f) {
                            return 1;                        } else {
                            if (features[0] <= -0.3412362188100815f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[7] <= 1.9464809894561768f) {
            if (features[18] <= 1.2116570472717285f) {
                if (features[3] <= -1.6303961277008057f) {
                    return 2;                } else {
                    return 2;                }
            } else {
                if (features[26] <= -0.07288593798875809f) {
                    if (features[3] <= 1.3748804032802582f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[6] <= 1.3110632300376892f) {
                return 0;            } else {
                if (features[2] <= 2.0689260959625244f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 16
int predict_tree_16(const float* features) {
    // Max depth: 10
    if (features[19] <= -0.07141989842057228f) {
        if (features[1] <= -0.3092859238386154f) {
            if (features[22] <= 6.220737934112549f) {
                return 0;            } else {
                if (features[19] <= -0.5161271691322327f) {
                    if (features[9] <= 13.232214450836182f) {
                        return 1;                    } else {
                        if (features[12] <= -0.025409650057554245f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[7] <= -0.6616357862949371f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            }
        } else {
            if (features[6] <= -0.36070844158530235f) {
                if (features[2] <= 0.36686669290065765f) {
                    if (features[1] <= -0.11717966571450233f) {
                        if (features[21] <= -0.08264250680804253f) {
                            return 0;                        } else {
                            if (features[0] <= -0.33969615399837494f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[3] <= 0.32541875541210175f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[17] <= -0.14590805023908615f) {
                        if (features[9] <= -0.06348530016839504f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        if (features[7] <= 0.043661003932356834f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[17] <= -0.12876468896865845f) {
                    if (features[10] <= -0.3220328539609909f) {
                        return 0;                    } else {
                        if (features[7] <= 1.2658986449241638f) {
                            if (features[12] <= 1.2626085877418518f) {
                                if (features[1] <= -0.07062206044793129f) {
                                    if (features[8] <= -0.09369833394885063f) {
                                        return 1;                                    } else {
                                        if (features[1] <= -0.30022817850112915f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                if (features[2] <= 0.818241536617279f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        } else {
                            return 0;                        }
                    }
                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[19] <= 0.9442524611949921f) {
            if (features[26] <= 2.562739849090576f) {
                if (features[3] <= 1.9234626293182373f) {
                    if (features[10] <= -0.16516511142253876f) {
                        if (features[17] <= -0.23955494910478592f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        return 2;                    }
                } else {
                    return 0;                }
            } else {
                if (features[2] <= -0.028086304664611816f) {
                    return 1;                } else {
                    return 2;                }
            }
        } else {
            if (features[22] <= -0.0478758979588747f) {
                if (features[2] <= -0.786019928753376f) {
                    return 0;                } else {
                    if (features[18] <= 0.7946058511734009f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[9] <= -0.049643997102975845f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 17
int predict_tree_17(const float* features) {
    // Max depth: 10
    if (features[19] <= -0.0748523473739624f) {
        if (features[26] <= -0.2802617996931076f) {
            if (features[21] <= -0.045907992869615555f) {
                if (features[0] <= -0.3414929062128067f) {
                    if (features[4] <= -0.08400743082165718f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[21] <= -0.052053412422537804f) {
                        return 1;                    } else {
                        if (features[29] <= -0.008806705474853516f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[10] <= -0.31892281770706177f) {
                    if (features[21] <= 6.56263542175293f) {
                        return 0;                    } else {
                        if (features[20] <= 13.23633861541748f) {
                            if (features[9] <= 12.265872478485107f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            if (features[31] <= 0.24120032787322998f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    return 1;                }
            }
        } else {
            if (features[8] <= 0.05426382087171078f) {
                if (features[12] <= 1.5211802124977112f) {
                    if (features[1] <= -0.3088759779930115f) {
                        if (features[29] <= -0.5103712691925466f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[10] <= -0.11163925379514694f) {
                            if (features[17] <= -0.13138239085674286f) {
                                if (features[26] <= 0.1886681765317917f) {
                                    if (features[10] <= -0.3226437568664551f) {
                                        return 0;                                    } else {
                                        if (features[10] <= -0.3180009126663208f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    if (features[19] <= -0.3127928823232651f) {
                                        return 1;                                    } else {
                                        return 2;                                    }
                                }
                            } else {
                                if (features[1] <= -0.17775336652994156f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[31] <= 0.24120032787322998f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    return 2;                }
            } else {
                if (features[0] <= -0.3361539840698242f) {
                    return 0;                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[7] <= 1.9298940896987915f) {
            if (features[6] <= 0.4751773923635483f) {
                if (features[7] <= 1.542201817035675f) {
                    return 2;                } else {
                    return 0;                }
            } else {
                if (features[17] <= -0.018770004040561616f) {
                    return 1;                } else {
                    return 2;                }
            }
        } else {
            if (features[20] <= -0.04340528883039951f) {
                return 0;            } else {
                if (features[10] <= 2.2895379066467285f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 18
int predict_tree_18(const float* features) {
    // Max depth: 8
    if (features[20] <= -0.077583909034729f) {
        if (features[18] <= -0.36135078966617584f) {
            if (features[17] <= -0.34821511805057526f) {
                return 0;            } else {
                return 1;            }
        } else {
            if (features[10] <= -0.32188844680786133f) {
                return 0;            } else {
                if (features[18] <= -0.2639738768339157f) {
                    if (features[9] <= -0.08246483653783798f) {
                        return 1;                    } else {
                        if (features[8] <= -0.08677325397729874f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[0] <= -0.1287573091685772f) {
            if (features[9] <= -0.04636145569384098f) {
                if (features[17] <= -0.3524239510297775f) {
                    return 0;                } else {
                    if (features[0] <= -0.3426736295223236f) {
                        return 0;                    } else {
                        if (features[3] <= -0.8353494107723236f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[10] <= -0.320211261510849f) {
                    if (features[4] <= 6.761305093765259f) {
                        return 0;                    } else {
                        if (features[3] <= -0.19136159867048264f) {
                            if (features[19] <= -0.521147757768631f) {
                                return 2;                            } else {
                                return 2;                            }
                        } else {
                            if (features[21] <= 15.815736293792725f) {
                                if (features[4] <= 12.655932903289795f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            } else {
                                if (features[12] <= -0.025409650057554245f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                } else {
                    return 1;                }
            }
        } else {
            if (features[20] <= -0.06035112030804157f) {
                return 2;            } else {
                if (features[4] <= -0.04967314377427101f) {
                    if (features[0] <= 0.58383509516716f) {
                        return 2;                    } else {
                        if (features[27] <= -0.03477079980075359f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[2] <= -0.817992314696312f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 19
int predict_tree_19(const float* features) {
    // Max depth: 10
    if (features[10] <= -0.1192588321864605f) {
        if (features[6] <= -0.2412961833178997f) {
            if (features[20] <= -0.07596712559461594f) {
                if (features[0] <= -0.34310999512672424f) {
                    if (features[10] <= -0.529871791601181f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    return 1;                }
            } else {
                if (features[4] <= 12.916000366210938f) {
                    if (features[0] <= -0.13478926569223404f) {
                        if (features[6] <= -1.077182024717331f) {
                            if (features[10] <= -0.31755663454532623f) {
                                if (features[9] <= -0.07483513280749321f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        } else {
                            if (features[13] <= -23.010056495666504f) {
                                return 0;                            } else {
                                if (features[8] <= 0.15393587946891785f) {
                                    if (features[17] <= -0.5154398679733276f) {
                                        if (features[2] <= -0.3195992410182953f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[19] <= -0.516869992017746f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    return 0;                                }
                            }
                        }
                    } else {
                        if (features[3] <= -0.8194484710693359f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[19] <= -0.3803916871547699f) {
                if (features[26] <= -0.0065974153112620115f) {
                    if (features[30] <= 0.23382475972175598f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[8] <= 0.028010285459458828f) {
                        if (features[10] <= -0.34685756266117096f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        return 1;                    }
                }
            } else {
                if (features[10] <= -0.3220328539609909f) {
                    if (features[15] <= 0.7420355677604675f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[3] <= 0.7149916291236877f) {
                        if (features[12] <= -0.3820602595806122f) {
                            if (features[20] <= -0.057878049090504646f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            if (features[18] <= -0.3346792012453079f) {
                                if (features[0] <= -0.3414929062128067f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            } else {
                                return 1;                            }
                        }
                    } else {
                        return 0;                    }
                }
            }
        }
    } else {
        if (features[4] <= -0.0612211637198925f) {
            return 2;        } else {
            if (features[2] <= -0.8085886687040329f) {
                return 0;            } else {
                if (features[17] <= -0.1392098218202591f) {
                    return 1;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 20
int predict_tree_20(const float* features) {
    // Max depth: 8
    if (features[4] <= -0.0776713415980339f) {
        if (features[0] <= -0.3415699154138565f) {
            return 0;        } else {
            if (features[1] <= 0.06190607696771622f) {
                return 1;            } else {
                return 2;            }
        }
    } else {
        if (features[0] <= -0.13170911371707916f) {
            if (features[17] <= -0.34251776337623596f) {
                if (features[20] <= 7.632521390914917f) {
                    if (features[18] <= -0.3898688703775406f) {
                        return 0;                    } else {
                        if (features[0] <= -0.34308432042598724f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[8] <= 0.10057849436998367f) {
                        if (features[19] <= -0.5172286033630371f) {
                            if (features[9] <= 14.705083847045898f) {
                                return 1;                            } else {
                                if (features[31] <= 0.24120032787322998f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[13] <= -8.141568183898926f) {
                            return 1;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[1] <= -0.31933926045894623f) {
                    return 0;                } else {
                    return 1;                }
            }
        } else {
            if (features[2] <= -0.9750331491231918f) {
                return 0;            } else {
                if (features[11] <= -10.307188987731934f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 21
int predict_tree_21(const float* features) {
    // Max depth: 9
    if (features[0] <= -0.1342502385377884f) {
        if (features[19] <= -0.3801611512899399f) {
            if (features[21] <= 7.811189413070679f) {
                if (features[26] <= -0.05453410744667053f) {
                    if (features[14] <= -42.493581771850586f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[10] <= -0.3148575723171234f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[3] <= -0.21521300077438354f) {
                    if (features[1] <= -0.46992433071136475f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    if (features[20] <= 14.415037631988525f) {
                        if (features[21] <= 8.318356990814209f) {
                            return 1;                        } else {
                            if (features[31] <= 0.24120032787322998f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[27] <= 0.6895518228411674f) {
                if (features[17] <= -0.3438779413700104f) {
                    if (features[18] <= -0.4624463617801666f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[12] <= -0.4803302437067032f) {
                        if (features[17] <= -0.2907283902168274f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        if (features[19] <= -0.31724996864795685f) {
                            if (features[21] <= -0.08218514174222946f) {
                                return 1;                            } else {
                                if (features[18] <= -0.33455097675323486f) {
                                    if (features[26] <= -0.26666635274887085f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 1;                                }
                            }
                        } else {
                            if (features[4] <= -0.06880256719887257f) {
                                if (features[1] <= -0.29415714740753174f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            } else {
                                return 1;                            }
                        }
                    }
                }
            } else {
                return 0;            }
        }
    } else {
        if (features[7] <= 2.0095704793930054f) {
            if (features[10] <= 1.1466570496559143f) {
                return 2;            } else {
                if (features[4] <= -0.04917309992015362f) {
                    if (features[10] <= 1.2098129391670227f) {
                        if (features[1] <= 1.0991939902305603f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[4] <= -0.05048669874668121f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[1] <= 1.1891078352928162f) {
                        if (features[22] <= -0.0482180118560791f) {
                            return 0;                        } else {
                            if (features[19] <= 0.5600229203701019f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[8] <= -0.11660250648856163f) {
                if (features[9] <= -0.048904551193118095f) {
                    return 0;                } else {
                    return 2;                }
            } else {
                if (features[28] <= 0.03530806303024292f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 22
int predict_tree_22(const float* features) {
    // Max depth: 7
    if (features[4] <= -0.07767258957028389f) {
        if (features[18] <= -0.35242606699466705f) {
            if (features[1] <= -0.2936691343784332f) {
                if (features[31] <= 0.24120032787322998f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                return 1;            }
        } else {
            if (features[8] <= -0.26111800968647003f) {
                return 2;            } else {
                if (features[9] <= -0.08301275968551636f) {
                    return 0;                } else {
                    if (features[9] <= -0.08188360556960106f) {
                        if (features[0] <= -0.3414929062128067f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        return 1;                    }
                }
            }
        }
    } else {
        if (features[17] <= -0.09930915758013725f) {
            if (features[0] <= -0.34192925691604614f) {
                if (features[22] <= 6.220737934112549f) {
                    return 0;                } else {
                    if (features[7] <= -0.6849594712257385f) {
                        return 2;                    } else {
                        if (features[4] <= 13.232214450836182f) {
                            if (features[12] <= 0.008217407623305917f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            if (features[2] <= -0.3007919490337372f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                if (features[11] <= 0.6093393564224243f) {
                    if (features[8] <= -0.320157453417778f) {
                        return 1;                    } else {
                        if (features[0] <= -0.1322481408715248f) {
                            if (features[1] <= -0.3066701143980026f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[7] <= -0.13110225647687912f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            }
        } else {
            if (features[7] <= 1.9151568412780762f) {
                if (features[1] <= -0.15946217626333237f) {
                    return 2;                } else {
                    return 2;                }
            } else {
                if (features[2] <= 0.26342660188674927f) {
                    return 0;                } else {
                    if (features[3] <= -1.5349904894828796f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 23
int predict_tree_23(const float* features) {
    // Max depth: 10
    if (features[22] <= -0.07715734466910362f) {
        if (features[1] <= -0.30264878273010254f) {
            return 0;        } else {
            if (features[7] <= -0.03485427750274539f) {
                if (features[6] <= -1.1965942978858948f) {
                    return 2;                } else {
                    if (features[4] <= -0.0835336223244667f) {
                        return 1;                    } else {
                        return 0;                    }
                }
            } else {
                if (features[0] <= -0.3414929062128067f) {
                    return 0;                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[20] <= -0.07042333111166954f) {
            if (features[18] <= -0.340193048119545f) {
                if (features[15] <= 0.7420355677604675f) {
                    if (features[1] <= -0.30885645747184753f) {
                        if (features[9] <= -0.07793822512030602f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[11] <= -0.014812369598075747f) {
                            return 1;                        } else {
                            if (features[3] <= 0.4247995913028717f) {
                                return 0;                            } else {
                                return 0;                            }
                        }
                    }
                } else {
                    if (features[1] <= -0.32093997299671173f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[10] <= -0.23116440325975418f) {
                    return 0;                } else {
                    return 2;                }
            }
        } else {
            if (features[18] <= -0.089890506118536f) {
                if (features[4] <= -0.05574234761297703f) {
                    return 0;                } else {
                    if (features[0] <= -0.34085121750831604f) {
                        if (features[2] <= -0.26317739486694336f) {
                            if (features[7] <= -0.6849594712257385f) {
                                if (features[22] <= 7.908597648143768f) {
                                    return 0;                                } else {
                                    if (features[18] <= -0.5203031599521637f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                }
                            } else {
                                if (features[18] <= -0.5264581441879272f) {
                                    return 0;                                } else {
                                    if (features[22] <= 6.220737934112549f) {
                                        return 0;                                    } else {
                                        if (features[21] <= 15.814280033111572f) {
                                            return 1;                                        } else {
                                            return 2;                                        }
                                    }
                                }
                            }
                        } else {
                            if (features[27] <= 2.5553556084632874f) {
                                return 0;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[10] <= -0.15654587745666504f) {
                            return 1;                        } else {
                            if (features[9] <= -0.04222746938467026f) {
                                if (features[28] <= 0.03530806303024292f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            } else {
                                if (features[6] <= 0.4751773923635483f) {
                                    if (features[0] <= -0.11286887526512146f) {
                                        return 1;                                    } else {
                                        return 2;                                    }
                                } else {
                                    if (features[13] <= 0.0592352282255888f) {
                                        return 1;                                    } else {
                                        return 2;                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                if (features[7] <= 1.9464809894561768f) {
                    if (features[3] <= 1.8876855373382568f) {
                        if (features[1] <= -0.23233410716056824f) {
                            return 0;                        } else {
                            return 2;                        }
                    } else {
                        return 0;                    }
                } else {
                    if (features[20] <= -0.04340528883039951f) {
                        return 0;                    } else {
                        if (features[28] <= 0.03530806303024292f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    }
}

// Tree 24
int predict_tree_24(const float* features) {
    // Max depth: 6
    if (features[0] <= -0.1322738081216812f) {
        if (features[19] <= -0.3542640805244446f) {
            if (features[4] <= 6.761305093765259f) {
                if (features[27] <= -0.0718812420964241f) {
                    if (features[17] <= -0.344134584069252f) {
                        if (features[26] <= 0.32327835261821747f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        if (features[9] <= -0.0824027992784977f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[1] <= -0.3103986233472824f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[27] <= 11.219933032989502f) {
                    if (features[2] <= -0.3007919490337372f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    if (features[21] <= 15.755089282989502f) {
                        if (features[20] <= 13.58247423171997f) {
                            return 1;                        } else {
                            return 2;                        }
                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[0] <= -0.34185226261615753f) {
                return 0;            } else {
                if (features[21] <= -0.08222600072622299f) {
                    return 1;                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[8] <= -0.21027258038520813f) {
            if (features[2] <= -0.9637487679719925f) {
                return 0;            } else {
                if (features[12] <= -4.7013537883758545f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[3] <= 1.8876855373382568f) {
                return 2;            } else {
                return 0;            }
        }
    }
}

// Tree 25
int predict_tree_25(const float* features) {
    // Max depth: 10
    if (features[1] <= -0.06425821036100388f) {
        if (features[13] <= 0.0006726741266902536f) {
            if (features[24] <= -0.01594117283821106f) {
                if (features[7] <= 0.36774855852127075f) {
                    if (features[10] <= -0.32268817722797394f) {
                        if (features[10] <= -0.4948617219924927f) {
                            if (features[21] <= 5.203335285186768f) {
                                if (features[3] <= -1.4276592135429382f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                if (features[17] <= -0.5201619863510132f) {
                                    if (features[11] <= -0.010356795508414507f) {
                                        return 2;                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[17] <= -0.5182628929615021f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                }
                            }
                        } else {
                            return 0;                        }
                    } else {
                        if (features[0] <= -0.13045138865709305f) {
                            if (features[9] <= -0.07387210428714752f) {
                                if (features[3] <= 0.3969729542732239f) {
                                    if (features[26] <= 0.23364635556936264f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                return 1;                            }
                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[26] <= -0.28434115648269653f) {
                        if (features[17] <= -0.34059299528598785f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        if (features[6] <= 0.23635287210345268f) {
                            return 0;                        } else {
                            if (features[21] <= 0.05418270826339722f) {
                                if (features[18] <= -0.36135078966617584f) {
                                    if (features[9] <= -0.08162962645292282f) {
                                        if (features[17] <= -0.5268089175224304f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        if (features[17] <= -0.3838106840848923f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    if (features[0] <= -0.3412875682115555f) {
                                        return 0;                                    } else {
                                        if (features[17] <= -0.1334611475467682f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            } else {
                                return 0;                            }
                        }
                    }
                }
            } else {
                return 0;            }
        } else {
            if (features[21] <= -0.04604349285364151f) {
                if (features[18] <= -0.3149063289165497f) {
                    return 0;                } else {
                    if (features[21] <= -0.053537651896476746f) {
                        return 1;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[18] <= -0.376507431268692f) {
                    if (features[8] <= -0.05804338492453098f) {
                        return 0;                    } else {
                        if (features[8] <= 0.09749685600399971f) {
                            if (features[20] <= 14.39190673828125f) {
                                if (features[19] <= -0.5170493125915527f) {
                                    return 0;                                } else {
                                    if (features[2] <= 0.037739187479019165f) {
                                        if (features[34] <= -2.0574225783348083f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 0;                                    }
                                }
                            } else {
                                if (features[19] <= -0.5184325277805328f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[6] <= -0.12188392877578735f) {
                                if (features[26] <= -0.29804255068302155f) {
                                    if (features[21] <= 11.959622859954834f) {
                                        return 2;                                    } else {
                                        if (features[20] <= 14.489178657531738f) {
                                            return 2;                                        } else {
                                            return 2;                                        }
                                    }
                                } else {
                                    if (features[3] <= -0.1595597341656685f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                }
                            } else {
                                if (features[11] <= -0.0047873277217149734f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            }
                        }
                    }
                } else {
                    if (features[27] <= 0.021429708693176508f) {
                        if (features[18] <= 0.02713106293231249f) {
                            if (features[10] <= -0.3191782832145691f) {
                                return 0;                            } else {
                                return 1;                            }
                        } else {
                            return 2;                        }
                    } else {
                        return 0;                    }
                }
            }
        }
    } else {
        if (features[0] <= -0.13137543573975563f) {
            return 1;        } else {
            if (features[7] <= 1.918283224105835f) {
                if (features[8] <= -0.33922989666461945f) {
                    return 2;                } else {
                    return 2;                }
            } else {
                if (features[20] <= -0.043262017890810966f) {
                    return 0;                } else {
                    if (features[21] <= -0.028248876333236694f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 26
int predict_tree_26(const float* features) {
    // Max depth: 10
    if (features[18] <= -0.089890506118536f) {
        if (features[18] <= -0.35237477719783783f) {
            if (features[11] <= 0.11922616139054298f) {
                if (features[21] <= 6.56263542175293f) {
                    if (features[4] <= -0.08354319632053375f) {
                        if (features[18] <= -0.4342360198497772f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        if (features[10] <= -0.5288166105747223f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[4] <= 13.695127487182617f) {
                        if (features[21] <= 8.531316757202148f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[1] <= -0.30499130487442017f) {
                    return 0;                } else {
                    if (features[20] <= -0.0822381004691124f) {
                        return 1;                    } else {
                        if (features[0] <= -0.33333051204681396f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            }
        } else {
            if (features[1] <= -0.30911023914813995f) {
                return 0;            } else {
                if (features[17] <= -0.12091159075498581f) {
                    if (features[19] <= -0.33016008138656616f) {
                        if (features[11] <= 0.06835835240781307f) {
                            if (features[19] <= -0.33997073769569397f) {
                                if (features[7] <= 0.9109122455120087f) {
                                    if (features[26] <= -0.2940869927406311f) {
                                        return 0;                                    } else {
                                        if (features[0] <= -0.3414929062128067f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    return 0;                                }
                            } else {
                                if (features[7] <= 0.8871990740299225f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            }
                        } else {
                            if (features[0] <= -0.11343356966972351f) {
                                return 1;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[1] <= -0.09777578338980675f) {
                            if (features[26] <= 0.18634029477834702f) {
                                if (features[20] <= -0.04766631871461868f) {
                                    if (features[0] <= -0.13042572140693665f) {
                                        if (features[11] <= -0.1804112233221531f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 2;                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    }
                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[6] <= 0.23635287210345268f) {
            if (features[1] <= -0.1314300075173378f) {
                return 1;            } else {
                if (features[17] <= -0.04312486946582794f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[7] <= 1.918724775314331f) {
                if (features[7] <= -0.8123047649860382f) {
                    if (features[8] <= -0.11818868666887283f) {
                        return 1;                    } else {
                        return 2;                    }
                } else {
                    if (features[26] <= -0.2862652391195297f) {
                        return 2;                    } else {
                        if (features[19] <= 0.4793347269296646f) {
                            if (features[10] <= -0.0706035066395998f) {
                                return 2;                            } else {
                                return 2;                            }
                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[20] <= -0.04345110058784485f) {
                    return 0;                } else {
                    if (features[28] <= 0.03530806303024292f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 27
int predict_tree_27(const float* features) {
    // Max depth: 10
    if (features[27] <= -0.07595403864979744f) {
        if (features[10] <= -0.32228831946849823f) {
            return 0;        } else {
            if (features[8] <= -0.24331920593976974f) {
                if (features[20] <= -0.061381081119179726f) {
                    return 2;                } else {
                    if (features[17] <= -0.1513230949640274f) {
                        return 1;                    } else {
                        if (features[18] <= -0.039496603421866894f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[10] <= -0.05615852400660515f) {
                    if (features[3] <= 0.567907989025116f) {
                        if (features[22] <= -0.08256683498620987f) {
                            return 1;                        } else {
                            if (features[12] <= -0.5937578678131104f) {
                                return 1;                            } else {
                                if (features[0] <= -0.3406202048063278f) {
                                    return 0;                                } else {
                                    if (features[19] <= -0.4569302052259445f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[2] <= -0.8367995992302895f) {
                        return 0;                    } else {
                        if (features[2] <= 0.05654647573828697f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    } else {
        if (features[10] <= -0.1076573058962822f) {
            if (features[19] <= -0.34271156787872314f) {
                if (features[9] <= 6.756311655044556f) {
                    if (features[9] <= -0.07320510223507881f) {
                        if (features[10] <= -0.3247874528169632f) {
                            return 0;                        } else {
                            if (features[0] <= -0.342545285820961f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[27] <= -0.05042671971023083f) {
                            return 0;                        } else {
                            if (features[7] <= -0.737484484910965f) {
                                if (features[18] <= -0.3956648111343384f) {
                                    if (features[27] <= -0.04828728549182415f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                return 0;                            }
                        }
                    }
                } else {
                    if (features[9] <= 13.232214450836182f) {
                        return 1;                    } else {
                        if (features[12] <= -0.02311689592897892f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[4] <= -0.04888206906616688f) {
                    if (features[10] <= -0.24771422147750854f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    if (features[17] <= -0.09825694561004639f) {
                        if (features[3] <= -0.8234237134456635f) {
                            return 1;                        } else {
                            if (features[4] <= -0.04818800464272499f) {
                                if (features[22] <= -0.04817582108080387f) {
                                    return 2;                                } else {
                                    return 1;                                }
                            } else {
                                if (features[4] <= 0.350473852828145f) {
                                    if (features[1] <= -0.29581643640995026f) {
                                        return 0;                                    } else {
                                        if (features[4] <= -0.028130630031228065f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    return 0;                                }
                            }
                        }
                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[3] <= 1.8876855373382568f) {
                if (features[30] <= 0.23382475972175598f) {
                    return 2;                } else {
                    return 2;                }
            } else {
                if (features[22] <= -0.05346292443573475f) {
                    return 0;                } else {
                    return 0;                }
            }
        }
    }
}

// Tree 28
int predict_tree_28(const float* features) {
    // Max depth: 9
    if (features[2] <= -0.3675578236579895f) {
        if (features[8] <= -0.29840369522571564f) {
            if (features[18] <= -0.08860822021961212f) {
                return 0;            } else {
                return 2;            }
        } else {
            if (features[4] <= -0.07219419255852699f) {
                return 0;            } else {
                if (features[2] <= -0.45125024020671844f) {
                    if (features[11] <= 3.477244019508362f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    if (features[0] <= -0.35222209990024567f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            }
        }
    } else {
        if (features[0] <= -0.13478926569223404f) {
            if (features[10] <= -0.3220328539609909f) {
                if (features[16] <= 5.114441957324743f) {
                    if (features[2] <= -0.3637963682413101f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[0] <= -0.5147512853145599f) {
                        if (features[7] <= -0.6849594712257385f) {
                            if (features[3] <= -0.23906440287828445f) {
                                return 2;                            } else {
                                if (features[27] <= 5.743350028991699f) {
                                    return 0;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[20] <= 13.23633861541748f) {
                                if (features[9] <= 6.475581407546997f) {
                                    return 0;                                } else {
                                    if (features[13] <= 16.799142837524414f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                if (features[26] <= -0.30405640602111816f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        }
                    } else {
                        return 0;                    }
                }
            } else {
                if (features[26] <= -0.2707788646221161f) {
                    if (features[6] <= -1.077182024717331f) {
                        return 0;                    } else {
                        if (features[1] <= -0.29667535424232483f) {
                            if (features[22] <= -0.007798018865287304f) {
                                if (features[9] <= -0.06410192139446735f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            } else {
                                return 0;                            }
                        } else {
                            if (features[3] <= -1.4833124876022339f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    if (features[0] <= -0.3402095139026642f) {
                        return 1;                    } else {
                        if (features[10] <= -0.3198113888502121f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            }
        } else {
            return 2;        }
    }
}

// Tree 29
int predict_tree_29(const float* features) {
    // Max depth: 9
    if (features[17] <= -0.12956026196479797f) {
        if (features[1] <= -0.3081732392311096f) {
            if (features[7] <= -0.5189975202083588f) {
                if (features[27] <= 3.0325530767440796f) {
                    if (features[21] <= -0.08372775465250015f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[4] <= 13.491242408752441f) {
                        if (features[10] <= -0.48955243825912476f) {
                            if (features[21] <= 5.450888395309448f) {
                                return 0;                            } else {
                                if (features[8] <= -0.17630131542682648f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        } else {
                            return 0;                        }
                    } else {
                        if (features[31] <= 0.24120032787322998f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[21] <= 0.6685586869716644f) {
                    return 0;                } else {
                    return 2;                }
            }
        } else {
            if (features[10] <= -0.3214108347892761f) {
                return 0;            } else {
                if (features[26] <= 0.6430623233318329f) {
                    if (features[26] <= 0.1886681765317917f) {
                        if (features[3] <= 0.7229420840740204f) {
                            if (features[22] <= -0.08184835687279701f) {
                                if (features[18] <= -0.33296094834804535f) {
                                    if (features[12] <= 0.006943655665963888f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                if (features[6] <= -1.1965942978858948f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        } else {
                            return 0;                        }
                    } else {
                        if (features[21] <= -0.06343161128461361f) {
                            return 1;                        } else {
                            return 2;                        }
                    }
                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[7] <= 1.9113677144050598f) {
            if (features[12] <= -0.33467668294906616f) {
                if (features[0] <= -0.1232387125492096f) {
                    return 1;                } else {
                    return 2;                }
            } else {
                return 2;            }
        } else {
            if (features[21] <= -0.03897834476083517f) {
                return 0;            } else {
                if (features[0] <= 2.113693594932556f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 30
int predict_tree_30(const float* features) {
    // Max depth: 9
    if (features[1] <= -0.06447293981909752f) {
        if (features[10] <= -0.3220328539609909f) {
            if (features[21] <= 6.56263542175293f) {
                return 0;            } else {
                if (features[20] <= 14.232638835906982f) {
                    if (features[0] <= -0.5171383619308472f) {
                        return 1;                    } else {
                        return 1;                    }
                } else {
                    if (features[28] <= 0.03530806303024292f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[3] <= 0.7269173264503479f) {
                if (features[19] <= -0.15779469907283783f) {
                    if (features[4] <= -0.04739026911556721f) {
                        if (features[0] <= -0.13042572140693665f) {
                            if (features[10] <= -0.3186229169368744f) {
                                if (features[4] <= -0.0822545774281025f) {
                                    return 0;                                } else {
                                    if (features[10] <= -0.32094433903694153f) {
                                        return 1;                                    } else {
                                        return 0;                                    }
                                }
                            } else {
                                if (features[7] <= -1.3622127622365952f) {
                                    return 1;                                } else {
                                    if (features[10] <= -0.3175455182790756f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        } else {
                            return 2;                        }
                    } else {
                        if (features[13] <= -0.04230158217251301f) {
                            if (features[10] <= -0.30439452826976776f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            if (features[6] <= -0.0024716556072235107f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    if (features[22] <= -0.04785918816924095f) {
                        if (features[13] <= 0.003446978982537985f) {
                            return 2;                        } else {
                            return 1;                        }
                    } else {
                        if (features[17] <= -0.08156911469995975f) {
                            if (features[29] <= -0.008806705474853516f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            return 2;                        }
                    }
                }
            } else {
                return 0;            }
        }
    } else {
        if (features[10] <= 0.8786945641040802f) {
            if (features[0] <= -0.12506112828850746f) {
                return 1;            } else {
                if (features[20] <= -0.06035112030804157f) {
                    return 2;                } else {
                    if (features[20] <= -0.05152919329702854f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[20] <= -0.0484618004411459f) {
                if (features[27] <= -0.04238719865679741f) {
                    if (features[4] <= -0.06204179860651493f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    return 2;                }
            } else {
                return 2;            }
        }
    }
}

// Tree 31
int predict_tree_31(const float* features) {
    // Max depth: 7
    if (features[1] <= -0.07091487571597099f) {
        if (features[17] <= -0.34364697337150574f) {
            if (features[17] <= -0.5247044861316681f) {
                return 0;            } else {
                if (features[27] <= 2.857832908630371f) {
                    if (features[10] <= -0.3196558952331543f) {
                        if (features[30] <= 0.23382475972175598f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[18] <= -0.3720450699329376f) {
                            if (features[26] <= 0.20249386876821518f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[21] <= 15.220935821533203f) {
                        if (features[9] <= 6.761305093765259f) {
                            return 0;                        } else {
                            if (features[9] <= 13.232214450836182f) {
                                return 1;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[31] <= 0.24120032787322998f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[18] <= -0.12004990875720978f) {
                if (features[0] <= -0.1244450993835926f) {
                    if (features[0] <= -0.3417752683162689f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            } else {
                if (features[9] <= -0.042602187022566795f) {
                    if (features[7] <= 0.18408645689487457f) {
                        if (features[10] <= -0.24663682281970978f) {
                            return 0;                        } else {
                            return 2;                        }
                    } else {
                        return 1;                    }
                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[3] <= 1.8876855373382568f) {
            if (features[4] <= -0.0779365599155426f) {
                return 1;            } else {
                if (features[8] <= 0.28126396238803864f) {
                    return 2;                } else {
                    return 1;                }
            }
        } else {
            if (features[10] <= 0.8834929168224335f) {
                return 0;            } else {
                return 0;            }
        }
    }
}

// Tree 32
int predict_tree_32(const float* features) {
    // Max depth: 10
    if (features[19] <= -0.09142544493079185f) {
        if (features[10] <= -0.3206000179052353f) {
            if (features[22] <= 5.547876358032227f) {
                if (features[11] <= -0.572873055934906f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[4] <= 13.232214450836182f) {
                    if (features[7] <= -0.5597891807556152f) {
                        return 1;                    } else {
                        return 1;                    }
                } else {
                    if (features[17] <= -0.5215735137462616f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[12] <= 1.9015225768089294f) {
                if (features[11] <= 1.483745813369751f) {
                    if (features[19] <= -0.12874694168567657f) {
                        if (features[10] <= -0.07023141533136368f) {
                            if (features[7] <= 1.2606700658798218f) {
                                if (features[1] <= -0.18177469074726105f) {
                                    if (features[18] <= -0.3346792012453079f) {
                                        if (features[12] <= -0.0070676186587661505f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[17] <= -0.1474222093820572f) {
                                        return 1;                                    } else {
                                        if (features[6] <= -0.0024716556072235107f) {
                                            return 2;                                        } else {
                                            return 2;                                        }
                                    }
                                }
                            } else {
                                return 0;                            }
                        } else {
                            return 2;                        }
                    } else {
                        if (features[17] <= -0.12707088515162468f) {
                            return 1;                        } else {
                            if (features[15] <= 0.7420355677604675f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    return 2;                }
            } else {
                return 2;            }
        }
    } else {
        if (features[0] <= -0.12957868725061417f) {
            if (features[0] <= -0.3472425192594528f) {
                return 0;            } else {
                return 1;            }
        } else {
            if (features[6] <= 0.23635287210345268f) {
                return 2;            } else {
                if (features[22] <= -0.04767288453876972f) {
                    if (features[4] <= -0.061673739925026894f) {
                        return 2;                    } else {
                        if (features[3] <= 1.3550042361021042f) {
                            return 2;                        } else {
                            return 0;                        }
                    }
                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 33
int predict_tree_33(const float* features) {
    // Max depth: 9
    if (features[4] <= -0.07766551524400711f) {
        if (features[4] <= -0.08251771330833435f) {
            if (features[2] <= -1.8617966771125793f) {
                if (features[1] <= -0.2915803790092468f) {
                    if (features[10] <= -0.5298051536083221f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    return 1;                }
            } else {
                return 0;            }
        } else {
            if (features[26] <= -0.2621251791715622f) {
                if (features[1] <= -0.2993692606687546f) {
                    if (features[1] <= -0.5068385601043701f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[4] <= -0.08015698194503784f) {
                        if (features[20] <= -0.08244134485721588f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[18] <= -0.4196435809135437f) {
                    return 0;                } else {
                    if (features[17] <= -0.3439292758703232f) {
                        return 0;                    } else {
                        if (features[0] <= -0.3393881320953369f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            }
        }
    } else {
        if (features[21] <= -0.07017280906438828f) {
            if (features[19] <= -0.31778787076473236f) {
                if (features[3] <= 0.42002931237220764f) {
                    if (features[17] <= -0.3459053784608841f) {
                        if (features[11] <= -0.04785788059234619f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[13] <= 0.0021559659217018634f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[10] <= -0.31755663454532623f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[26] <= 2.445977568626404f) {
                    if (features[1] <= -0.2414894625544548f) {
                        return 0;                    } else {
                        if (features[15] <= 0.7420355677604675f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    return 1;                }
            }
        } else {
            if (features[18] <= 0.004280696855857968f) {
                if (features[18] <= -0.33785928785800934f) {
                    if (features[9] <= 6.756311655044556f) {
                        if (features[27] <= 0.06641668453812599f) {
                            return 0;                        } else {
                            if (features[10] <= -0.3606305569410324f) {
                                if (features[4] <= -0.027573026716709137f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[9] <= 13.145212650299072f) {
                            return 1;                        } else {
                            if (features[20] <= 13.842621326446533f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[11] <= 1.1737120747566223f) {
                        if (features[26] <= -0.16018392145633698f) {
                            if (features[18] <= -0.14751651138067245f) {
                                if (features[12] <= -0.27404607832431793f) {
                                    return 1;                                } else {
                                    if (features[27] <= -0.0772504098713398f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                if (features[8] <= -0.32480064034461975f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[0] <= -0.13170911371707916f) {
                                return 1;                            } else {
                                if (features[18] <= -0.21309269964694977f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        }
                    } else {
                        if (features[26] <= 0.6532096564769745f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[27] <= -0.06029519438743591f) {
                    if (features[21] <= -0.049470582976937294f) {
                        if (features[6] <= -0.0024716556072235107f) {
                            return 2;                        } else {
                            return 0;                        }
                    } else {
                        if (features[6] <= 0.11694060638546944f) {
                            if (features[27] <= -0.07711689919233322f) {
                                return 2;                            } else {
                                return 2;                            }
                        } else {
                            if (features[21] <= -0.04887605458498001f) {
                                return 0;                            } else {
                                if (features[7] <= 1.5369973182678223f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                } else {
                    if (features[3] <= 1.9075616896152496f) {
                        return 2;                    } else {
                        return 0;                    }
                }
            }
        }
    }
}

// Tree 34
int predict_tree_34(const float* features) {
    // Max depth: 10
    if (features[17] <= -0.12116822972893715f) {
        if (features[34] <= -2.0574225783348083f) {
            if (features[6] <= -0.36070844903588295f) {
                if (features[9] <= 13.695127487182617f) {
                    if (features[19] <= -0.5256560444831848f) {
                        return 0;                    } else {
                        if (features[9] <= 6.38598370552063f) {
                            if (features[27] <= 0.12961514294147491f) {
                                return 1;                            } else {
                                if (features[16] <= 5.114441957324743f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            }
                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[11] <= -0.013698476366698742f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[1] <= -0.33245736360549927f) {
                    if (features[15] <= 0.7420355677604675f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    return 1;                }
            }
        } else {
            if (features[3] <= -1.0420615673065186f) {
                if (features[6] <= -0.2412961833178997f) {
                    return 0;                } else {
                    if (features[7] <= 0.13179679214954376f) {
                        if (features[10] <= -0.3993837684392929f) {
                            return 0;                        } else {
                            if (features[26] <= 0.19166061282157898f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[31] <= 0.24120032787322998f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                }
            } else {
                if (features[1] <= -0.3088759779930115f) {
                    return 0;                } else {
                    if (features[10] <= -0.3220328539609909f) {
                        return 0;                    } else {
                        if (features[17] <= -0.15299123525619507f) {
                            if (features[6] <= -1.1965942978858948f) {
                                if (features[19] <= -0.3493715524673462f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            } else {
                                if (features[26] <= -0.28540782630443573f) {
                                    if (features[12] <= 0.008726908185053617f) {
                                        if (features[12] <= -0.021843143738806248f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 0;                                    }
                                } else {
                                    if (features[0] <= -0.34205760061740875f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        } else {
                            if (features[26] <= -0.007164847105741501f) {
                                return 1;                            } else {
                                return 2;                            }
                        }
                    }
                }
            }
        }
    } else {
        if (features[10] <= 0.9648979604244232f) {
            if (features[4] <= -0.042304910719394684f) {
                if (features[27] <= -0.07790148258209229f) {
                    return 2;                } else {
                    if (features[18] <= 0.9342469573020935f) {
                        return 2;                    } else {
                        if (features[18] <= 1.0633989572525024f) {
                            if (features[7] <= 2.1267447471618652f) {
                                return 2;                            } else {
                                return 0;                            }
                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[20] <= -0.04285386577248573f) {
                    return 1;                } else {
                    return 2;                }
            }
        } else {
            if (features[2] <= -0.7803777381777763f) {
                return 0;            } else {
                return 2;            }
        }
    }
}

// Tree 35
int predict_tree_35(const float* features) {
    // Max depth: 9
    if (features[34] <= -2.0574225783348083f) {
        if (features[17] <= 0.1587715744972229f) {
            if (features[20] <= 7.332235813140869f) {
                if (features[19] <= -0.2466285601258278f) {
                    if (features[28] <= -0.4720424022525549f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[31] <= 0.24120032787322998f) {
                        return 1;                    } else {
                        return 0;                    }
                }
            } else {
                if (features[9] <= 13.57824420928955f) {
                    return 1;                } else {
                    if (features[22] <= 12.982412338256836f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            return 2;        }
    } else {
        if (features[1] <= -0.30885645747184753f) {
            return 0;        } else {
            if (features[19] <= -0.06099447049200535f) {
                if (features[0] <= -0.129886694252491f) {
                    if (features[7] <= 1.2658986449241638f) {
                        if (features[17] <= -0.3441859185695648f) {
                            if (features[2] <= -0.3468698114156723f) {
                                return 0;                            } else {
                                if (features[27] <= -0.07538244128227234f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            }
                        } else {
                            if (features[18] <= -0.33434581756591797f) {
                                if (features[28] <= 0.03530806303024292f) {
                                    if (features[0] <= -0.3414929062128067f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                if (features[27] <= -0.07713204994797707f) {
                                    if (features[18] <= -0.26497405767440796f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 1;                                }
                            }
                        }
                    } else {
                        return 0;                    }
                } else {
                    return 2;                }
            } else {
                if (features[20] <= -0.06035112030804157f) {
                    return 2;                } else {
                    if (features[8] <= -0.21304427087306976f) {
                        if (features[11] <= -0.48598936200141907f) {
                            if (features[8] <= -0.2970873564481735f) {
                                return 1;                            } else {
                                return 2;                            }
                        } else {
                            return 2;                        }
                    } else {
                        if (features[4] <= -0.0491601936519146f) {
                            if (features[12] <= -4.5645530223846436f) {
                                return 2;                            } else {
                                return 0;                            }
                        } else {
                            if (features[3] <= 1.8876855373382568f) {
                                return 2;                            } else {
                                return 0;                            }
                        }
                    }
                }
            }
        }
    }
}

// Tree 36
int predict_tree_36(const float* features) {
    // Max depth: 10
    if (features[17] <= -0.09823128208518028f) {
        if (features[20] <= -0.046298591420054436f) {
            if (features[1] <= -0.3081732392311096f) {
                return 0;            } else {
                if (features[17] <= -0.14593371003866196f) {
                    if (features[17] <= -0.3852991908788681f) {
                        return 0;                    } else {
                        if (features[17] <= -0.3440575897693634f) {
                            if (features[7] <= -0.036383877508342266f) {
                                return 1;                            } else {
                                if (features[18] <= -0.34842532873153687f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            }
                        } else {
                            if (features[20] <= -0.08245550468564034f) {
                                return 1;                            } else {
                                if (features[17] <= -0.3395407795906067f) {
                                    if (features[8] <= -0.10481414571404457f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[26] <= 0.07442639581859112f) {
                                        return 1;                                    } else {
                                        if (features[27] <= -0.07712071761488914f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        }
                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[17] <= -0.36027707159519196f) {
                if (features[22] <= 6.220737934112549f) {
                    if (features[17] <= -0.382245197892189f) {
                        return 0;                    } else {
                        if (features[15] <= 0.7420355677604675f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[20] <= 14.232638835906982f) {
                        if (features[9] <= 13.232214450836182f) {
                            if (features[8] <= -0.10066728293895721f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            return 2;                        }
                    } else {
                        if (features[13] <= -20.31034278869629f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[18] <= -0.33873124420642853f) {
                    if (features[28] <= 0.03530806303024292f) {
                        if (features[13] <= -0.046943734399974346f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[2] <= 0.02833554893732071f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[7] <= -0.7893293499946594f) {
                        return 1;                    } else {
                        if (features[21] <= 0.07248304784297943f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            }
        }
    } else {
        if (features[19] <= 1.013644278049469f) {
            if (features[19] <= 0.9631821513175964f) {
                if (features[21] <= -0.06467987224459648f) {
                    return 2;                } else {
                    if (features[7] <= 1.65190851688385f) {
                        return 2;                    } else {
                        return 0;                    }
                }
            } else {
                if (features[7] <= 1.1678272113204002f) {
                    return 2;                } else {
                    return 0;                }
            }
        } else {
            if (features[2] <= -0.7615704564377666f) {
                return 0;            } else {
                return 2;            }
        }
    }
}

// Tree 37
int predict_tree_37(const float* features) {
    // Max depth: 7
    if (features[17] <= -0.13138239085674286f) {
        if (features[18] <= -0.36450521647930145f) {
            if (features[27] <= 2.857832908630371f) {
                if (features[17] <= -0.360431045293808f) {
                    if (features[1] <= -0.2959335595369339f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[17] <= -0.35255227982997894f) {
                        if (features[13] <= -0.0010715670250647236f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        return 1;                    }
                }
            } else {
                if (features[9] <= 13.232214450836182f) {
                    if (features[22] <= 4.732909083366394f) {
                        return 0;                    } else {
                        if (features[29] <= -0.008806705474853516f) {
                            if (features[22] <= 9.717023849487305f) {
                                return 0;                            } else {
                                return 1;                            }
                        } else {
                            return 1;                        }
                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[0] <= -0.3414929062128067f) {
                return 0;            } else {
                if (features[11] <= 0.7140453457832336f) {
                    if (features[13] <= 0.005465903785079718f) {
                        return 1;                    } else {
                        if (features[26] <= 0.1919950160663575f) {
                            if (features[31] <= 0.24120032787322998f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            return 1;                        }
                    }
                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[2] <= -0.9656295031309128f) {
            return 0;        } else {
            if (features[1] <= -0.20397496223449707f) {
                return 1;            } else {
                if (features[10] <= -0.15275830775499344f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 38
int predict_tree_38(const float* features) {
    // Max depth: 6
    if (features[0] <= -0.13170911371707916f) {
        if (features[0] <= -0.34192925691604614f) {
            if (features[21] <= 6.56263542175293f) {
                return 0;            } else {
                if (features[22] <= 16.578267097473145f) {
                    if (features[2] <= -0.28198467195034027f) {
                        if (features[9] <= 12.582086563110352f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        if (features[1] <= -0.4720911532640457f) {
                            return 1;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[8] <= -0.2348814681172371f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            return 1;        }
    } else {
        if (features[18] <= 0.9525067210197449f) {
            if (features[7] <= 1.664268970489502f) {
                return 2;            } else {
                return 0;            }
        } else {
            if (features[9] <= -0.0491601936519146f) {
                if (features[18] <= 1.0290336608886719f) {
                    if (features[26] <= 0.2929369881749153f) {
                        if (features[18] <= 0.9728438258171082f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[7] <= 1.2237303256988525f) {
                        return 2;                    } else {
                        return 0;                    }
                }
            } else {
                if (features[20] <= -0.048605071380734444f) {
                    return 0;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 39
int predict_tree_39(const float* features) {
    // Max depth: 9
    if (features[22] <= -0.0771949365735054f) {
        if (features[17] <= -0.3439292758703232f) {
            if (features[0] <= -0.34308432042598724f) {
                return 0;            } else {
                return 1;            }
        } else {
            if (features[13] <= -0.0007556807831861079f) {
                if (features[27] <= -0.07645418867468834f) {
                    return 1;                } else {
                    return 1;                }
            } else {
                return 2;            }
        }
    } else {
        if (features[18] <= 0.004819257650524378f) {
            if (features[20] <= -0.0502685010433197f) {
                if (features[11] <= 0.2443535327911377f) {
                    if (features[10] <= -0.32388776540756226f) {
                        return 0;                    } else {
                        if (features[19] <= -0.174598328769207f) {
                            return 1;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[17] <= -0.22023016959428787f) {
                        if (features[9] <= -0.07235199213027954f) {
                            if (features[20] <= -0.07544069364666939f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            return 0;                        }
                    } else {
                        if (features[20] <= -0.07573306187987328f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[0] <= -0.34321266412734985f) {
                    if (features[9] <= 6.761305093765259f) {
                        return 0;                    } else {
                        if (features[12] <= -0.019040889106690884f) {
                            return 2;                        } else {
                            if (features[8] <= 0.10223649069666862f) {
                                if (features[9] <= 14.315023422241211f) {
                                    return 1;                                } else {
                                    if (features[26] <= -0.3015701174736023f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                }
                            } else {
                                if (features[20] <= 14.489178657531738f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                } else {
                    if (features[0] <= -0.1322481408715248f) {
                        return 1;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[20] <= -0.07243035733699799f) {
                return 2;            } else {
                if (features[2] <= -0.20675552636384964f) {
                    if (features[26] <= 2.3145679235458374f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 40
int predict_tree_40(const float* features) {
    // Max depth: 9
    if (features[21] <= -0.07734093442559242f) {
        if (features[20] <= -0.08245300501585007f) {
            if (features[10] <= -0.31521299481391907f) {
                return 0;            } else {
                return 1;            }
        } else {
            if (features[7] <= 0.3678558021783829f) {
                if (features[21] <= -0.0816381424665451f) {
                    if (features[0] <= -0.33987583220005035f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[1] <= -0.3045228123664856f) {
                        return 0;                    } else {
                        if (features[21] <= -0.07930838689208031f) {
                            if (features[19] <= -0.3481932431459427f) {
                                return 1;                            } else {
                                return 0;                            }
                        } else {
                            if (features[4] <= -0.07805979996919632f) {
                                return 0;                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                if (features[26] <= -0.2931167632341385f) {
                    return 0;                } else {
                    if (features[10] <= -0.32197731733322144f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            }
        }
    } else {
        if (features[26] <= -0.0021955875563435256f) {
            if (features[20] <= -0.045917509123682976f) {
                if (features[3] <= 0.4414955675601959f) {
                    if (features[19] <= -0.10802416503429413f) {
                        if (features[0] <= -0.3414672315120697f) {
                            return 0;                        } else {
                            if (features[10] <= -0.16332130879163742f) {
                                return 1;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[15] <= 0.7420355677604675f) {
                            return 2;                        } else {
                            if (features[6] <= 0.8334142118692398f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[22] <= -0.07305322960019112f) {
                        return 2;                    } else {
                        return 0;                    }
                }
            } else {
                if (features[10] <= -0.09598913416266441f) {
                    if (features[10] <= -0.3188894987106323f) {
                        if (features[9] <= 6.761305093765259f) {
                            return 0;                        } else {
                            if (features[27] <= 11.219933032989502f) {
                                return 2;                            } else {
                                if (features[4] <= 13.491242408752441f) {
                                    return 1;                                } else {
                                    if (features[0] <= -0.5223746299743652f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                }
                            }
                        }
                    } else {
                        if (features[10] <= -0.1128721609711647f) {
                            if (features[6] <= -0.0024716556072235107f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            return 1;                        }
                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[1] <= -0.07091487571597099f) {
                if (features[27] <= -0.06162642873823643f) {
                    if (features[21] <= -0.07253633439540863f) {
                        return 1;                    } else {
                        if (features[10] <= -0.23866181075572968f) {
                            if (features[17] <= -0.4511009454727173f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[1] <= -0.32736237347126007f) {
                        if (features[28] <= 0.03530806303024292f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                }
            } else {
                if (features[3] <= 1.895635962486267f) {
                    if (features[13] <= 0.2278497815132141f) {
                        if (features[17] <= -0.04102044552564621f) {
                            return 2;                        } else {
                            return 2;                        }
                    } else {
                        if (features[10] <= 0.23703964985907078f) {
                            return 1;                        } else {
                            if (features[0] <= 1.4575449228286743f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[15] <= 0.7420355677604675f) {
                        return 0;                    } else {
                        return 0;                    }
                }
            }
        }
    }
}

// Tree 41
int predict_tree_41(const float* features) {
    // Max depth: 9
    if (features[13] <= 0.0005078639660496265f) {
        if (features[15] <= 0.7420355677604675f) {
            if (features[1] <= -0.30885645747184753f) {
                if (features[8] <= -0.08474614471197128f) {
                    if (features[27] <= 5.1986998319625854f) {
                        if (features[18] <= -0.5536426305770874f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[27] <= 21.983678817749023f) {
                            if (features[9] <= 12.075742721557617f) {
                                return 0;                            } else {
                                return 2;                            }
                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[27] <= 10.764761179685593f) {
                        if (features[19] <= -0.5533718168735504f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[17] <= -0.523985892534256f) {
                            return 1;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[7] <= 1.2502129673957825f) {
                    if (features[19] <= -0.10315725579857826f) {
                        if (features[19] <= -0.42839474976062775f) {
                            return 0;                        } else {
                            if (features[17] <= -0.1474222093820572f) {
                                if (features[0] <= -0.3414929062128067f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            } else {
                                if (features[1] <= -0.17014016956090927f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        }
                    } else {
                        if (features[18] <= -0.0629368219524622f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[20] <= -0.035528773441910744f) {
                        if (features[12] <= -0.17341965436935425f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[3] <= 0.7229420840740204f) {
                            return 2;                        } else {
                            return 0;                        }
                    }
                }
            }
        } else {
            if (features[1] <= -0.044541988521814346f) {
                if (features[9] <= -0.07556042075157166f) {
                    if (features[18] <= -0.33452533185482025f) {
                        if (features[0] <= -0.3325861394405365f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        if (features[8] <= -0.24176105856895447f) {
                            return 2;                        } else {
                            if (features[30] <= 0.23382475972175598f) {
                                if (features[3] <= -0.398073747754097f) {
                                    return 0;                                } else {
                                    if (features[10] <= -0.32773086428642273f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    if (features[1] <= -0.30483514070510864f) {
                        return 0;                    } else {
                        if (features[12] <= -0.687697097659111f) {
                            return 2;                        } else {
                            if (features[8] <= -0.2994510382413864f) {
                                return 1;                            } else {
                                if (features[1] <= -0.11200660094618797f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        }
                    }
                }
            } else {
                if (features[2] <= -0.9938404411077499f) {
                    return 0;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[4] <= -0.04635770991444588f) {
            if (features[18] <= -0.34232163429260254f) {
                return 0;            } else {
                if (features[7] <= 1.4860554337501526f) {
                    if (features[21] <= -0.06312642432749271f) {
                        if (features[0] <= -0.16949227079749107f) {
                            return 0;                        } else {
                            if (features[18] <= -0.09150618314743042f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[26] <= -0.30488575994968414f) {
                            return 1;                        } else {
                            return 2;                        }
                    }
                } else {
                    return 0;                }
            }
        } else {
            if (features[17] <= -0.0986098200082779f) {
                if (features[2] <= 0.7148014903068542f) {
                    if (features[8] <= -0.1298019289970398f) {
                        return 0;                    } else {
                        if (features[0] <= -0.3440083712339401f) {
                            if (features[20] <= 7.051059246063232f) {
                                return 0;                            } else {
                                if (features[21] <= 11.302950382232666f) {
                                    return 1;                                } else {
                                    if (features[0] <= -0.5216302871704102f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                }
                            }
                        } else {
                            if (features[3] <= -0.5292564332485199f) {
                                return 2;                            } else {
                                if (features[10] <= -0.1360641084611416f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        }
                    }
                } else {
                    if (features[17] <= -0.16115229576826096f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[6] <= -2.8683661222457886f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 42
int predict_tree_42(const float* features) {
    // Max depth: 8
    if (features[0] <= -0.13170911371707916f) {
        if (features[0] <= -0.34185226261615753f) {
            if (features[19] <= -0.5136680901050568f) {
                if (features[16] <= 5.114441957324743f) {
                    if (features[4] <= -0.083995770663023f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[26] <= -0.2962592542171478f) {
                        if (features[21] <= 15.220935821533203f) {
                            if (features[4] <= 6.677205801010132f) {
                                return 0;                            } else {
                                if (features[12] <= 0.003631899686297402f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        } else {
                            if (features[4] <= 16.52177143096924f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[19] <= -0.5217881202697754f) {
                            return 0;                        } else {
                            if (features[21] <= 10.715972185134888f) {
                                if (features[4] <= 2.3359702825546265f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                return 0;            }
        } else {
            return 1;        }
    } else {
        if (features[3] <= 1.8916608095169067f) {
            if (features[8] <= -0.33922989666461945f) {
                return 2;            } else {
                return 2;            }
        } else {
            if (features[17] <= 0.8787157833576202f) {
                return 0;            } else {
                return 0;            }
        }
    }
}

// Tree 43
int predict_tree_43(const float* features) {
    // Max depth: 7
    if (features[0] <= -0.13478926569223404f) {
        if (features[0] <= -0.34192925691604614f) {
            if (features[22] <= 6.220737934112549f) {
                return 0;            } else {
                if (features[27] <= 11.219933032989502f) {
                    if (features[0] <= -0.5214249193668365f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    if (features[21] <= 15.220935821533203f) {
                        if (features[8] <= 0.17305199801921844f) {
                            if (features[20] <= 7.802642107009888f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            return 2;                        }
                    } else {
                        if (features[1] <= -0.4773618280887604f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            return 1;        }
    } else {
        if (features[0] <= 0.9496540725231171f) {
            if (features[0] <= 0.8040400743484497f) {
                return 2;            } else {
                if (features[4] <= -0.05341617204248905f) {
                    if (features[19] <= 0.7834652066230774f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[3] <= 1.7644532918930054f) {
                return 2;            } else {
                return 0;            }
        }
    }
}

// Tree 44
int predict_tree_44(const float* features) {
    // Max depth: 10
    if (features[18] <= -0.08578718453645706f) {
        if (features[18] <= -0.3770972937345505f) {
            if (features[20] <= 7.632521390914917f) {
                if (features[18] <= -0.41956664621829987f) {
                    if (features[0] <= -0.3413902372121811f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[1] <= -0.30065764486789703f) {
                        return 0;                    } else {
                        if (features[26] <= -0.06476951763033867f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[8] <= 0.09915485233068466f) {
                    if (features[9] <= 14.705083847045898f) {
                        return 1;                    } else {
                        if (features[30] <= 0.23382475972175598f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[1] <= -0.47384804487228394f) {
                        return 1;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[21] <= -0.0481285136193037f) {
                if (features[1] <= -0.3088759779930115f) {
                    return 0;                } else {
                    if (features[19] <= -0.2371509000658989f) {
                        if (features[10] <= -0.3222438842058182f) {
                            return 0;                        } else {
                            if (features[10] <= -0.06598844472318888f) {
                                if (features[4] <= -0.048823779448866844f) {
                                    if (features[17] <= -0.34508414566516876f) {
                                        return 1;                                    } else {
                                        if (features[3] <= 0.567907989025116f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    return 2;                                }
                            } else {
                                return 2;                            }
                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[0] <= -0.12244300171732903f) {
                    if (features[17] <= -0.3432620167732239f) {
                        return 0;                    } else {
                        if (features[12] <= -1.0696316808462143f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[17] <= -0.09494632482528687f) {
            if (features[18] <= -0.026186455972492695f) {
                return 2;            } else {
                return 1;            }
        } else {
            if (features[19] <= 0.9445854425430298f) {
                if (features[0] <= -0.0956200435757637f) {
                    return 2;                } else {
                    if (features[2] <= -0.9750331491231918f) {
                        return 0;                    } else {
                        if (features[10] <= -0.11133936047554016f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[9] <= -0.048392850905656815f) {
                    if (features[3] <= 1.5120259635150433f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 45
int predict_tree_45(const float* features) {
    // Max depth: 5
    if (features[10] <= -0.07267500832676888f) {
        if (features[0] <= -0.34205760061740875f) {
            if (features[9] <= 6.761305093765259f) {
                return 0;            } else {
                if (features[9] <= 13.57824420928955f) {
                    return 1;                } else {
                    if (features[7] <= -0.7407416999340057f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[0] <= -0.1342502385377884f) {
                if (features[15] <= 0.7420355677604675f) {
                    return 1;                } else {
                    return 1;                }
            } else {
                return 2;            }
        }
    } else {
        if (features[2] <= -0.9750331491231918f) {
            return 0;        } else {
            return 2;        }
    }
}

// Tree 46
int predict_tree_46(const float* features) {
    // Max depth: 10
    if (features[9] <= -0.07763345539569855f) {
        if (features[7] <= 0.3678558021783829f) {
            if (features[10] <= -0.3203667551279068f) {
                if (features[13] <= -0.008488025283440948f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[10] <= 0.049227096140384674f) {
                    if (features[4] <= -0.0820767916738987f) {
                        return 1;                    } else {
                        if (features[10] <= -0.29008840024471283f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[28] <= 0.03530806303024292f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[17] <= -0.3445708602666855f) {
                return 0;            } else {
                if (features[10] <= -0.3186229169368744f) {
                    return 0;                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[22] <= -0.06824274733662605f) {
            if (features[8] <= -0.18345124274492264f) {
                if (features[0] <= -0.21838963776826859f) {
                    return 0;                } else {
                    if (features[11] <= -1.6002542972564697f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[11] <= 0.07615560665726662f) {
                    return 0;                } else {
                    if (features[12] <= 0.3365907222032547f) {
                        if (features[1] <= -0.30508890748023987f) {
                            if (features[20] <= -0.07291805744171143f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[1] <= -0.07146146520972252f) {
                if (features[4] <= -0.05137520097196102f) {
                    if (features[7] <= -0.345880389213562f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[1] <= -0.30901263654232025f) {
                        if (features[9] <= 6.57856559753418f) {
                            return 0;                        } else {
                            if (features[4] <= 13.232214450836182f) {
                                return 1;                            } else {
                                if (features[28] <= 0.03530806303024292f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        }
                    } else {
                        if (features[9] <= -0.048110147938132286f) {
                            if (features[1] <= -0.18167708814144135f) {
                                return 1;                            } else {
                                if (features[0] <= -0.11679606884717941f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[10] <= -0.09983779862523079f) {
                                if (features[3] <= 0.7229420840740204f) {
                                    if (features[19] <= -0.10676901414990425f) {
                                        if (features[20] <= 0.029688610695302486f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 0;                                }
                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                if (features[3] <= 1.8876855373382568f) {
                    return 2;                } else {
                    if (features[6] <= 0.4751773923635483f) {
                        return 0;                    } else {
                        return 0;                    }
                }
            }
        }
    }
}

// Tree 47
int predict_tree_47(const float* features) {
    // Max depth: 9
    if (features[1] <= -0.07091487571597099f) {
        if (features[1] <= -0.3081732392311096f) {
            if (features[16] <= 5.114441957324743f) {
                return 0;            } else {
                if (features[9] <= 13.491242408752441f) {
                    if (features[21] <= 6.281148672103882f) {
                        if (features[10] <= -0.49640561640262604f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[11] <= 0.01971833175048232f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[9] <= 15.842573642730713f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[1] <= -0.1804472655057907f) {
                if (features[8] <= 0.11857757344841957f) {
                    if (features[2] <= -0.45971351861953735f) {
                        return 0;                    } else {
                        if (features[3] <= 0.7229420840740204f) {
                            if (features[0] <= -0.34192925691604614f) {
                                return 0;                            } else {
                                if (features[21] <= -0.04813059791922569f) {
                                    if (features[22] <= -0.06354379653930664f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 1;                                }
                            }
                        } else {
                            return 0;                        }
                    }
                } else {
                    return 0;                }
            } else {
                if (features[26] <= -0.1782234013080597f) {
                    return 2;                } else {
                    if (features[22] <= -0.023863172624260187f) {
                        if (features[3] <= -0.398073747754097f) {
                            if (features[27] <= -0.05951378494501114f) {
                                return 2;                            } else {
                                return 1;                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[12] <= -0.1897236779332161f) {
                            return 2;                        } else {
                            return 1;                        }
                    }
                }
            }
        }
    } else {
        if (features[10] <= 0.9333533942699432f) {
            if (features[8] <= 0.0964956171810627f) {
                if (features[0] <= 0.9496540725231171f) {
                    if (features[7] <= 1.1601127982139587f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    if (features[3] <= 1.4702859818935394f) {
                        return 2;                    } else {
                        return 0;                    }
                }
            } else {
                return 1;            }
        } else {
            if (features[22] <= -0.0478758979588747f) {
                if (features[22] <= -0.06526397354900837f) {
                    return 2;                } else {
                    return 0;                }
            } else {
                if (features[4] <= -0.049643997102975845f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 48
int predict_tree_48(const float* features) {
    // Max depth: 10
    if (features[20] <= -0.07750394567847252f) {
        if (features[0] <= -0.3416982591152191f) {
            return 0;        } else {
            if (features[21] <= -0.07906615734100342f) {
                return 1;            } else {
                return 2;            }
        }
    } else {
        if (features[17] <= -0.09825694561004639f) {
            if (features[19] <= -0.35359805822372437f) {
                if (features[3] <= 0.41287387907505035f) {
                    if (features[19] <= -0.5249388217926025f) {
                        return 0;                    } else {
                        if (features[22] <= 7.139202833175659f) {
                            if (features[22] <= 0.04996785894036293f) {
                                if (features[26] <= -0.19272704422473907f) {
                                    if (features[27] <= -0.07790279760956764f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    if (features[10] <= -0.32457640767097473f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                return 0;                            }
                        } else {
                            if (features[29] <= -0.008806705474853516f) {
                                if (features[21] <= 16.121376514434814f) {
                                    return 1;                                } else {
                                    if (features[27] <= 11.68908405303955f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                }
                            } else {
                                if (features[20] <= 13.819615364074707f) {
                                    return 1;                                } else {
                                    if (features[8] <= 0.029010399244725704f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                }
                            }
                        }
                    }
                } else {
                    if (features[0] <= -0.34547144174575806f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[6] <= 0.9528264701366425f) {
                    if (features[1] <= -0.3047765791416168f) {
                        return 0;                    } else {
                        if (features[10] <= -0.3179231733083725f) {
                            return 0;                        } else {
                            if (features[18] <= -0.14502887427806854f) {
                                if (features[26] <= 0.6430623233318329f) {
                                    if (features[22] <= -0.04748491011559963f) {
                                        if (features[0] <= -0.1322481408715248f) {
                                            return 1;                                        } else {
                                            return 2;                                        }
                                    } else {
                                        if (features[19] <= -0.19204235076904297f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    return 2;                                }
                            } else {
                                if (features[19] <= -0.10945862159132957f) {
                                    return 2;                                } else {
                                    if (features[6] <= -0.36070844158530235f) {
                                        if (features[26] <= -0.2662103921175003f) {
                                            return 2;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[1] <= -0.11530565097928047f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        }
                    }
                } else {
                    return 0;                }
            }
        } else {
            if (features[19] <= 0.9637456834316254f) {
                if (features[1] <= -0.15913031995296478f) {
                    return 2;                } else {
                    if (features[3] <= 1.9234626293182373f) {
                        return 2;                    } else {
                        return 0;                    }
                }
            } else {
                if (features[2] <= -0.7521668104454875f) {
                    return 0;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 49
int predict_tree_49(const float* features) {
    // Max depth: 9
    if (features[18] <= -0.11235618218779564f) {
        if (features[8] <= -0.28515027463436127f) {
            if (features[21] <= -0.05598748102784157f) {
                if (features[26] <= 0.6268563717603683f) {
                    return 0;                } else {
                    return 2;                }
            } else {
                if (features[1] <= -0.18318020552396774f) {
                    if (features[18] <= -0.36514636874198914f) {
                        if (features[20] <= 9.247836969792843f) {
                            if (features[2] <= -0.34781017899513245f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 2;                        }
                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[19] <= -0.3526502996683121f) {
                if (features[20] <= 7.509936571121216f) {
                    if (features[0] <= -0.34205760061740875f) {
                        return 0;                    } else {
                        if (features[12] <= 1.84547758102417f) {
                            return 1;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[27] <= 10.740880489349365f) {
                        if (features[20] <= 16.684825897216797f) {
                            return 2;                        } else {
                            return 2;                        }
                    } else {
                        if (features[9] <= 13.57824420928955f) {
                            return 1;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[18] <= -0.3474251478910446f) {
                    return 0;                } else {
                    if (features[3] <= 0.7229420840740204f) {
                        if (features[17] <= -0.1416992023587227f) {
                            if (features[10] <= -0.31868956983089447f) {
                                return 0;                            } else {
                                if (features[15] <= 0.7420355677604675f) {
                                    if (features[31] <= 0.24120032787322998f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[0] <= -0.32871030271053314f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        } else {
                            return 2;                        }
                    } else {
                        return 0;                    }
                }
            }
        }
    } else {
        if (features[10] <= 0.9258226454257965f) {
            if (features[8] <= -0.3423120379447937f) {
                return 1;            } else {
                if (features[2] <= -0.4465484172105789f) {
                    if (features[4] <= -0.07296361774206161f) {
                        return 2;                    } else {
                        if (features[11] <= 0.026772992219775915f) {
                            return 1;                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[21] <= -0.04266059212386608f) {
                        if (features[27] <= -0.07790148258209229f) {
                            return 2;                        } else {
                            return 2;                        }
                    } else {
                        if (features[1] <= -0.07782531157135963f) {
                            return 1;                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[2] <= -0.7803777381777763f) {
                return 0;            } else {
                return 2;            }
        }
    }
}

// Tree 50
int predict_tree_50(const float* features) {
    // Max depth: 9
    if (features[19] <= -0.06099447049200535f) {
        if (features[0] <= -0.34185226261615753f) {
            if (features[2] <= -0.26317739486694336f) {
                if (features[12] <= -0.03840192221105099f) {
                    if (features[21] <= 7.8702627420425415f) {
                        if (features[6] <= -1.1965942978858948f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[4] <= 6.761305093765259f) {
                        if (features[34] <= -2.0574225783348083f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[26] <= -0.3017694056034088f) {
                            if (features[9] <= 14.484671115875244f) {
                                return 1;                            } else {
                                if (features[1] <= -0.4705294817686081f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[21] <= 13.706112384796143f) {
                                return 1;                            } else {
                                if (features[3] <= -0.2708662748336792f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                }
            } else {
                if (features[2] <= -0.24437010288238525f) {
                    if (features[27] <= -0.06791233271360397f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    return 0;                }
            }
        } else {
            if (features[18] <= -0.11235618218779564f) {
                if (features[0] <= -0.1322738081216812f) {
                    return 1;                } else {
                    return 2;                }
            } else {
                if (features[8] <= -0.16510577872395515f) {
                    return 2;                } else {
                    if (features[30] <= 0.23382475972175598f) {
                        return 1;                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[13] <= 0.021328884176909924f) {
            if (features[31] <= 0.24120032787322998f) {
                if (features[19] <= 1.0672827363014221f) {
                    if (features[4] <= -0.042022205889225006f) {
                        if (features[10] <= -0.22035705298185349f) {
                            return 0;                        } else {
                            if (features[1] <= 0.8241039216518402f) {
                                return 2;                            } else {
                                if (features[3] <= 1.4822116494178772f) {
                                    return 2;                                } else {
                                    if (features[11] <= 0.07986858487129211f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                }
                            }
                        }
                    } else {
                        if (features[1] <= -0.17201418429613113f) {
                            return 1;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[22] <= -0.04734622687101364f) {
                        if (features[18] <= 1.0577569007873535f) {
                            return 2;                        } else {
                            if (features[26] <= 3.1029378175735474f) {
                                return 0;                            } else {
                                return 2;                            }
                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[34] <= -2.0574225783348083f) {
                    return 2;                } else {
                    if (features[7] <= 1.8217158913612366f) {
                        if (features[18] <= -0.00284882215783f) {
                            if (features[27] <= -0.06441465765237808f) {
                                if (features[27] <= -0.07168177515268326f) {
                                    return 2;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        } else {
                            return 2;                        }
                    } else {
                        if (features[20] <= -0.03415230102837086f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[7] <= 2.1049013137817383f) {
                return 2;            } else {
                if (features[1] <= 2.250055193901062f) {
                    return 0;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 51
int predict_tree_51(const float* features) {
    // Max depth: 6
    if (features[0] <= -0.13478926569223404f) {
        if (features[18] <= -0.37684081494808197f) {
            if (features[0] <= -0.3325861394405365f) {
                if (features[9] <= 7.048927545547485f) {
                    return 0;                } else {
                    if (features[4] <= 13.232214450836182f) {
                        return 1;                    } else {
                        if (features[27] <= 3.829816699028015f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                return 1;            }
        } else {
            if (features[28] <= -0.4720424022525549f) {
                if (features[10] <= -0.32167741656303406f) {
                    if (features[16] <= 5.114441957324743f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[10] <= -0.3188006281852722f) {
                        if (features[20] <= -0.07842312380671501f) {
                            return 1;                        } else {
                            return 0;                        }
                    } else {
                        if (features[21] <= -0.08224017545580864f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[0] <= -0.3414672315120697f) {
                    return 0;                } else {
                    if (features[21] <= -0.0821826420724392f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            }
        }
    } else {
        if (features[17] <= 1.0339812636375427f) {
            if (features[26] <= -0.3096549063920975f) {
                return 2;            } else {
                if (features[18] <= 0.9484290480613708f) {
                    return 2;                } else {
                    if (features[3] <= 1.4583602845668793f) {
                        return 2;                    } else {
                        if (features[27] <= -0.0753341019153595f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                }
            }
        } else {
            if (features[4] <= -0.0491601936519146f) {
                if (features[4] <= -0.06295986101031303f) {
                    return 2;                } else {
                    return 0;                }
            } else {
                if (features[21] <= -0.04824775457382202f) {
                    return 0;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 52
int predict_tree_52(const float* features) {
    // Max depth: 9
    if (features[21] <= -0.07745100557804108f) {
        if (features[0] <= -0.3415699154138565f) {
            return 0;        } else {
            if (features[21] <= -0.07906615734100342f) {
                if (features[21] <= -0.08222891762852669f) {
                    return 1;                } else {
                    return 1;                }
            } else {
                return 2;            }
        }
    } else {
        if (features[21] <= -0.07017280906438828f) {
            if (features[18] <= 0.16395115107297897f) {
                if (features[10] <= -0.32388776540756226f) {
                    return 0;                } else {
                    if (features[1] <= -0.14663687348365784f) {
                        if (features[26] <= -0.22911246120929718f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        if (features[13] <= -0.006537771550938487f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[0] <= 0.16716796904802322f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[0] <= -0.1342502385377884f) {
                if (features[17] <= -0.36027707159519196f) {
                    if (features[22] <= 6.220737934112549f) {
                        if (features[27] <= 0.06268145702779293f) {
                            return 0;                        } else {
                            if (features[10] <= -0.3602973371744156f) {
                                if (features[10] <= -0.5002153962850571f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[22] <= 15.93189811706543f) {
                            if (features[21] <= 14.85464859008789f) {
                                if (features[4] <= 12.916000366210938f) {
                                    if (features[20] <= 7.332235813140869f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 2;                                }
                            } else {
                                return 2;                            }
                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[2] <= 0.6489759981632233f) {
                        if (features[9] <= 0.24772290140390396f) {
                            if (features[1] <= -0.29581643640995026f) {
                                return 0;                            } else {
                                return 1;                            }
                        } else {
                            return 1;                        }
                    } else {
                        return 1;                    }
                }
            } else {
                if (features[2] <= -0.8273959532380104f) {
                    return 0;                } else {
                    if (features[10] <= -0.151780866086483f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 53
int predict_tree_53(const float* features) {
    // Max depth: 6
    if (features[20] <= -0.07761431112885475f) {
        if (features[1] <= -0.3081732392311096f) {
            return 0;        } else {
            if (features[20] <= -0.07954137772321701f) {
                if (features[0] <= -0.3415699154138565f) {
                    return 0;                } else {
                    if (features[19] <= -0.46067003905773163f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[18] <= -0.026596784591674805f) {
                    return 0;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[19] <= -0.06099447049200535f) {
            if (features[0] <= -0.34192925691604614f) {
                if (features[20] <= 7.509936571121216f) {
                    return 0;                } else {
                    if (features[4] <= 13.232214450836182f) {
                        return 1;                    } else {
                        if (features[29] <= -0.008806705474853516f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[0] <= -0.1342502385377884f) {
                    return 1;                } else {
                    return 2;                }
            }
        } else {
            if (features[2] <= -0.9562258571386337f) {
                return 0;            } else {
                if (features[17] <= -0.08958261087536812f) {
                    if (features[3] <= -0.3384452387690544f) {
                        return 1;                    } else {
                        if (features[17] <= -0.34123459458351135f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 54
int predict_tree_54(const float* features) {
    // Max depth: 9
    if (features[17] <= -0.09825694561004639f) {
        if (features[1] <= -0.30885645747184753f) {
            if (features[4] <= 7.171375513076782f) {
                return 0;            } else {
                if (features[7] <= -0.6476379632949829f) {
                    return 2;                } else {
                    if (features[17] <= -0.519135445356369f) {
                        if (features[11] <= -0.009242902044206858f) {
                            return 2;                        } else {
                            return 1;                        }
                    } else {
                        if (features[4] <= 13.468619346618652f) {
                            return 1;                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[0] <= -0.1342502385377884f) {
                if (features[19] <= -0.4898458570241928f) {
                    return 0;                } else {
                    if (features[22] <= -0.08199121803045273f) {
                        return 1;                    } else {
                        if (features[4] <= -0.07225706055760384f) {
                            if (features[27] <= -0.06847511604428291f) {
                                if (features[10] <= -0.3226437568664551f) {
                                    return 0;                                } else {
                                    if (features[0] <= -0.3414672315120697f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                return 0;                            }
                        } else {
                            if (features[18] <= -0.336653932929039f) {
                                if (features[15] <= 0.7420355677604675f) {
                                    if (features[12] <= -0.0246453988365829f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                return 1;                            }
                        }
                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[10] <= 0.9558455646038055f) {
            if (features[27] <= -0.07788299396634102f) {
                return 0;            } else {
                if (features[2] <= -1.0154688209295273f) {
                    return 0;                } else {
                    if (features[3] <= -1.6582227945327759f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[17] <= 2.1914405822753906f) {
                if (features[4] <= -0.048392850905656815f) {
                    if (features[6] <= -0.12188391387462616f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    return 2;                }
            } else {
                if (features[2] <= -0.68634133040905f) {
                    return 0;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 55
int predict_tree_55(const float* features) {
    // Max depth: 8
    if (features[1] <= -0.06449246034026146f) {
        if (features[1] <= -0.3082122802734375f) {
            if (features[16] <= 5.114441957324743f) {
                return 0;            } else {
                if (features[3] <= -0.19931206852197647f) {
                    if (features[22] <= 7.948672294616699f) {
                        return 0;                    } else {
                        if (features[19] <= -0.521147757768631f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[4] <= 6.756311655044556f) {
                        return 0;                    } else {
                        if (features[9] <= 13.232214450836182f) {
                            return 1;                        } else {
                            if (features[28] <= 0.03530806303024292f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                }
            }
        } else {
            if (features[0] <= -0.1342502385377884f) {
                if (features[19] <= -0.4898458570241928f) {
                    return 0;                } else {
                    if (features[9] <= -0.08301983773708344f) {
                        return 1;                    } else {
                        if (features[10] <= -0.32167741656303406f) {
                            return 0;                        } else {
                            if (features[0] <= -0.34192925691604614f) {
                                return 0;                            } else {
                                if (features[30] <= 0.23382475972175598f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        }
                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[20] <= -0.0636529941111803f) {
            return 2;        } else {
            if (features[3] <= 1.8876855373382568f) {
                if (features[1] <= 0.09366676583886147f) {
                    if (features[18] <= -0.16546853631734848f) {
                        return 1;                    } else {
                        return 2;                    }
                } else {
                    return 2;                }
            } else {
                if (features[20] <= -0.05486230179667473f) {
                    return 0;                } else {
                    return 0;                }
            }
        }
    }
}

// Tree 56
int predict_tree_56(const float* features) {
    // Max depth: 10
    if (features[2] <= -0.3844843804836273f) {
        if (features[17] <= -0.34441687166690826f) {
            return 0;        } else {
            if (features[7] <= 0.04743613488972187f) {
                if (features[17] <= -0.00847885012626648f) {
                    return 1;                } else {
                    return 2;                }
            } else {
                return 0;            }
        }
    } else {
        if (features[18] <= -0.089890506118536f) {
            if (features[4] <= -0.04916976951062679f) {
                if (features[3] <= 0.2936168760061264f) {
                    if (features[8] <= 0.38190461695194244f) {
                        if (features[2] <= -0.31019559502601624f) {
                            return 1;                        } else {
                            if (features[21] <= -0.08159144967794418f) {
                                if (features[17] <= -0.37023457884788513f) {
                                    return 0;                                } else {
                                    if (features[11] <= -0.26321064680814743f) {
                                        return 0;                                    } else {
                                        if (features[3] <= -0.2867671996355057f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            } else {
                                if (features[9] <= -0.05404403619468212f) {
                                    return 0;                                } else {
                                    return 2;                                }
                            }
                        }
                    } else {
                        if (features[17] <= -0.3895336985588074f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[18] <= -0.364402636885643f) {
                        return 0;                    } else {
                        if (features[0] <= -0.34187793731689453f) {
                            return 0;                        } else {
                            if (features[8] <= -0.2607467621564865f) {
                                return 2;                            } else {
                                return 1;                            }
                        }
                    }
                }
            } else {
                if (features[0] <= -0.34321266412734985f) {
                    if (features[9] <= 6.761305093765259f) {
                        return 0;                    } else {
                        if (features[4] <= 13.57824420928955f) {
                            return 1;                        } else {
                            if (features[0] <= -0.5220666229724884f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[8] <= -0.3238828331232071f) {
                        return 2;                    } else {
                        if (features[1] <= 0.10100666433572769f) {
                            if (features[6] <= -0.36070844158530235f) {
                                if (features[8] <= -0.3128150552511215f) {
                                    return 2;                                } else {
                                    if (features[20] <= -0.04882372356951237f) {
                                        return 2;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                if (features[7] <= -0.7813142538070679f) {
                                    if (features[19] <= -0.2066686898469925f) {
                                        return 1;                                    } else {
                                        return 2;                                    }
                                } else {
                                    return 1;                                }
                            }
                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[1] <= -0.17242413014173508f) {
                return 1;            } else {
                return 2;            }
        }
    }
}

// Tree 57
int predict_tree_57(const float* features) {
    // Max depth: 7
    if (features[17] <= -0.12116822972893715f) {
        if (features[0] <= -0.34203194081783295f) {
            if (features[2] <= -0.26317739486694336f) {
                if (features[16] <= 5.114441957324743f) {
                    if (features[29] <= -0.5103712691925466f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[9] <= 13.232214450836182f) {
                        if (features[22] <= 7.139202833175659f) {
                            return 0;                        } else {
                            if (features[9] <= 9.447161674499512f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[8] <= -0.10351208969950676f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[13] <= 2.6433216333389282f) {
                    if (features[9] <= -0.08359024301171303f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[27] <= 0.09685203433036804f) {
                if (features[0] <= -0.13512294739484787f) {
                    return 1;                } else {
                    return 1;                }
            } else {
                return 1;            }
        }
    } else {
        if (features[18] <= 0.9486342072486877f) {
            if (features[12] <= -0.33467668294906616f) {
                if (features[13] <= 0.019200085662305355f) {
                    if (features[11] <= -2.1055907011032104f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    if (features[8] <= -0.2712436765432358f) {
                        return 1;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[2] <= -0.9656295031309128f) {
                    return 0;                } else {
                    if (features[28] <= -0.4720424022525549f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[7] <= 1.918724775314331f) {
                return 2;            } else {
                if (features[8] <= -0.11726700887084007f) {
                    return 0;                } else {
                    if (features[0] <= 2.330407738685608f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 58
int predict_tree_58(const float* features) {
    // Max depth: 9
    if (features[19] <= -0.10802416503429413f) {
        if (features[19] <= -0.36007873713970184f) {
            if (features[16] <= 5.114441957324743f) {
                if (features[10] <= -0.3226437568664551f) {
                    return 0;                } else {
                    if (features[3] <= 0.6434374153614044f) {
                        if (features[27] <= -0.047004638239741325f) {
                            if (features[12] <= -0.09954202547669411f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            return 1;                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[9] <= 12.916000366210938f) {
                    if (features[22] <= 6.220737934112549f) {
                        return 0;                    } else {
                        if (features[26] <= -0.28017736971378326f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[30] <= 0.23382475972175598f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[19] <= -0.3515232354402542f) {
                if (features[17] <= -0.34382662177085876f) {
                    if (features[26] <= -0.3060027211904526f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    return 1;                }
            } else {
                if (features[18] <= -0.3463223725557327f) {
                    return 0;                } else {
                    if (features[17] <= -0.13138239085674286f) {
                        if (features[0] <= -0.34185226261615753f) {
                            return 0;                        } else {
                            if (features[27] <= -0.018145435489714146f) {
                                if (features[6] <= -1.077182024717331f) {
                                    return 1;                                } else {
                                    if (features[1] <= -0.15489426255226135f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                if (features[6] <= 0.11694060638546944f) {
                                    return 2;                                } else {
                                    if (features[10] <= -0.1108950711786747f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        }
                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[10] <= -0.12043619900941849f) {
            if (features[19] <= -0.08842846006155014f) {
                return 2;            } else {
                if (features[17] <= -0.29429564625024796f) {
                    return 0;                } else {
                    if (features[11] <= -1.079184114933014f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            }
        } else {
            if (features[3] <= 1.8876855373382568f) {
                if (features[16] <= 5.114441957324743f) {
                    return 2;                } else {
                    return 2;                }
            } else {
                if (features[10] <= 0.8793610036373138f) {
                    return 0;                } else {
                    return 0;                }
            }
        }
    }
}

// Tree 59
int predict_tree_59(const float* features) {
    // Max depth: 8
    if (features[0] <= -0.13188879191875458f) {
        if (features[0] <= -0.34192925691604614f) {
            if (features[27] <= 3.091771364212036f) {
                return 0;            } else {
                if (features[0] <= -0.5183961093425751f) {
                    if (features[0] <= -0.5213222801685333f) {
                        if (features[21] <= 15.041060447692871f) {
                            return 1;                        } else {
                            return 2;                        }
                    } else {
                        if (features[0] <= -0.5200901925563812f) {
                            if (features[19] <= -0.5175359845161438f) {
                                if (features[17] <= -0.5207779407501221f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            } else {
                                return 2;                            }
                        } else {
                            if (features[20] <= 14.475947856903076f) {
                                if (features[18] <= -0.5172000229358673f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            } else {
                                if (features[21] <= 18.064950942993164f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                } else {
                    if (features[20] <= 13.264090061187744f) {
                        if (features[10] <= -0.4898190349340439f) {
                            if (features[3] <= -0.2072625383734703f) {
                                return 1;                            } else {
                                return 0;                            }
                        } else {
                            return 0;                        }
                    } else {
                        return 2;                    }
                }
            }
        } else {
            return 1;        }
    } else {
        if (features[10] <= 0.880149632692337f) {
            if (features[27] <= -0.07781131193041801f) {
                return 2;            } else {
                return 2;            }
        } else {
            if (features[20] <= -0.04852135851979256f) {
                if (features[2] <= -0.5829012393951416f) {
                    return 0;                } else {
                    if (features[18] <= 0.7180276215076447f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                return 2;            }
        }
    }
}

// Tree 60
int predict_tree_60(const float* features) {
    // Max depth: 10
    if (features[19] <= -0.07141989842057228f) {
        if (features[1] <= -0.3088759779930115f) {
            if (features[17] <= -0.515260249376297f) {
                if (features[0] <= -0.5213735997676849f) {
                    if (features[21] <= 5.7933796644210815f) {
                        if (features[34] <= -2.0574225783348083f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[19] <= -0.5209684669971466f) {
                            return 1;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[4] <= 6.38598370552063f) {
                        return 0;                    } else {
                        if (features[22] <= 10.761457443237305f) {
                            return 1;                        } else {
                            if (features[1] <= -0.4771861433982849f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                return 0;            }
        } else {
            if (features[18] <= -0.1209988035261631f) {
                if (features[0] <= -0.14028219878673553f) {
                    if (features[12] <= -0.12145056575536728f) {
                        if (features[0] <= -0.342596635222435f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        if (features[3] <= 0.7229420840740204f) {
                            if (features[19] <= -0.4994259774684906f) {
                                return 0;                            } else {
                                if (features[10] <= -0.3222438842058182f) {
                                    return 0;                                } else {
                                    if (features[2] <= -0.3468698114156723f) {
                                        if (features[2] <= -0.35627345740795135f) {
                                            return 1;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        if (features[0] <= -0.34192925691604614f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        } else {
                            return 0;                        }
                    }
                } else {
                    return 2;                }
            } else {
                if (features[17] <= -0.11226291581988335f) {
                    return 1;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[0] <= -0.13242461532354355f) {
            if (features[8] <= -0.1492765098810196f) {
                return 1;            } else {
                if (features[19] <= 0.40745818614959717f) {
                    return 0;                } else {
                    return 0;                }
            }
        } else {
            if (features[18] <= 0.948762446641922f) {
                return 2;            } else {
                if (features[20] <= -0.04837808758020401f) {
                    if (features[2] <= -0.6017085313796997f) {
                        return 0;                    } else {
                        if (features[9] <= -0.07229245081543922f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 61
int predict_tree_61(const float* features) {
    // Max depth: 10
    if (features[18] <= -0.10202094539999962f) {
        if (features[1] <= -0.30885645747184753f) {
            if (features[27] <= 2.857832908630371f) {
                return 0;            } else {
                if (features[8] <= 0.12991198897361755f) {
                    if (features[4] <= 14.060916900634766f) {
                        if (features[9] <= 6.761305093765259f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        if (features[11] <= -0.014441072009503841f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[0] <= -0.5232986807823181f) {
                        return 1;                    } else {
                        if (features[9] <= 14.371158599853516f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[1] <= 0.10100666433572769f) {
                if (features[11] <= 0.016376651357859373f) {
                    if (features[17] <= -0.3403106927871704f) {
                        return 0;                    } else {
                        if (features[1] <= -0.1804472655057907f) {
                            if (features[26] <= 0.07442639581859112f) {
                                if (features[21] <= -0.08218347653746605f) {
                                    if (features[0] <= -0.3357176333665848f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                return 1;                            }
                        } else {
                            if (features[12] <= -0.06922672316431999f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    if (features[8] <= -0.31448063254356384f) {
                        if (features[0] <= -0.14308000355958939f) {
                            return 1;                        } else {
                            if (features[8] <= -0.31935296952724457f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[10] <= -0.32063333690166473f) {
                            return 0;                        } else {
                            if (features[22] <= 0.005414513638243079f) {
                                if (features[10] <= -0.0776732750236988f) {
                                    if (features[17] <= -0.34508414566516876f) {
                                        return 1;                                    } else {
                                        if (features[27] <= -0.07776334881782532f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                return 1;                            }
                        }
                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[10] <= 0.9558455646038055f) {
            if (features[3] <= 0.658940851688385f) {
                if (features[4] <= -0.04226494021713734f) {
                    if (features[8] <= -0.12708564847707748f) {
                        if (features[3] <= 0.4403029978275299f) {
                            return 2;                        } else {
                            return 2;                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[8] <= -0.2918621152639389f) {
                        return 1;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[8] <= -0.14270787686109543f) {
                    if (features[17] <= 0.8787157833576202f) {
                        return 1;                    } else {
                        if (features[30] <= 0.23382475972175598f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[9] <= -0.04917309992015362f) {
                if (features[3] <= 1.42258320748806f) {
                    return 2;                } else {
                    return 0;                }
            } else {
                if (features[17] <= 1.3110210299491882f) {
                    if (features[18] <= 1.2851064801216125f) {
                        if (features[2] <= -0.06570088118314743f) {
                            return 2;                        } else {
                            return 2;                        }
                    } else {
                        if (features[30] <= 0.23382475972175598f) {
                            return 2;                        } else {
                            return 0;                        }
                    }
                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 62
int predict_tree_62(const float* features) {
    // Max depth: 8
    if (features[19] <= -0.10753747075796127f) {
        if (features[17] <= -0.3523726314306259f) {
            if (features[12] <= 0.6259872019290924f) {
                if (features[4] <= 6.57856559753418f) {
                    return 0;                } else {
                    if (features[3] <= -0.19931206852197647f) {
                        if (features[27] <= 3.4643077850341797f) {
                            return 2;                        } else {
                            return 2;                        }
                    } else {
                        if (features[9] <= 12.842154026031494f) {
                            return 1;                        } else {
                            if (features[7] <= -0.6160452365875244f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                return 1;            }
        } else {
            if (features[10] <= 0.00019968044944107533f) {
                if (features[7] <= 1.2658986449241638f) {
                    if (features[10] <= -0.3222438842058182f) {
                        return 0;                    } else {
                        if (features[1] <= -0.18177469074726105f) {
                            if (features[0] <= -0.3415699154138565f) {
                                return 0;                            } else {
                                if (features[27] <= -0.07792000845074654f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        } else {
                            if (features[0] <= -0.13371121138334274f) {
                                return 1;                            } else {
                                if (features[29] <= -0.008806705474853516f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                } else {
                    if (features[12] <= -0.03458066610619426f) {
                        return 0;                    } else {
                        return 0;                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[17] <= -0.09825694561004639f) {
            if (features[17] <= -0.22715938091278076f) {
                return 0;            } else {
                if (features[1] <= -0.17952977865934372f) {
                    return 1;                } else {
                    if (features[17] <= -0.11054344847798347f) {
                        return 1;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[10] <= 0.955612301826477f) {
                if (features[19] <= 0.7919182479381561f) {
                    return 2;                } else {
                    if (features[3] <= 1.9075616896152496f) {
                        return 2;                    } else {
                        if (features[8] <= -0.19992052018642426f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                }
            } else {
                if (features[9] <= -0.0491601936519146f) {
                    if (features[10] <= 1.4939919710159302f) {
                        if (features[20] <= -0.06332147307693958f) {
                            return 2;                        } else {
                            if (features[2] <= -1.4856509566307068f) {
                                return 0;                            } else {
                                if (features[19] <= 0.9996583759784698f) {
                                    return 0;                                } else {
                                    return 2;                                }
                            }
                        }
                    } else {
                        return 0;                    }
                } else {
                    if (features[7] <= 1.918724775314331f) {
                        return 2;                    } else {
                        if (features[17] <= 1.6207307577133179f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    }
}

// Tree 63
int predict_tree_63(const float* features) {
    // Max depth: 8
    if (features[0] <= -0.1342502385377884f) {
        if (features[9] <= -0.04684359394013882f) {
            if (features[18] <= -0.36450521647930145f) {
                if (features[1] <= -0.17162376269698143f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                if (features[6] <= -0.8383575081825256f) {
                    if (features[3] <= 0.3333692103624344f) {
                        if (features[2] <= -1.1189088970422745f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        return 0;                    }
                } else {
                    if (features[10] <= -0.3222438842058182f) {
                        return 0;                    } else {
                        if (features[1] <= -0.29800279438495636f) {
                            if (features[1] <= -0.3008918911218643f) {
                                if (features[21] <= -0.08220181986689568f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            } else {
                                return 1;                            }
                        } else {
                            return 1;                        }
                    }
                }
            }
        } else {
            if (features[17] <= -0.34231245517730713f) {
                if (features[27] <= 12.027545928955078f) {
                    if (features[9] <= 10.082738399505615f) {
                        if (features[1] <= -0.29677295684814453f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        if (features[1] <= -0.47337953746318817f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[1] <= -0.468284547328949f) {
                        if (features[19] <= -0.5256560444831848f) {
                            return 0;                        } else {
                            if (features[9] <= 13.695127487182617f) {
                                return 1;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[18] <= -0.5173282623291016f) {
                            return 2;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                return 1;            }
        }
    } else {
        if (features[1] <= 0.8183257281780243f) {
            return 2;        } else {
            if (features[2] <= -0.7803777381777763f) {
                return 0;            } else {
                return 2;            }
        }
    }
}

// Tree 64
int predict_tree_64(const float* features) {
    // Max depth: 9
    if (features[18] <= -0.089890506118536f) {
        if (features[21] <= -0.055408794432878494f) {
            if (features[9] <= -0.08251771330833435f) {
                return 0;            } else {
                if (features[15] <= 0.7420355677604675f) {
                    if (features[1] <= -0.30885645747184753f) {
                        if (features[30] <= 0.23382475972175598f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[4] <= -0.07289241999387741f) {
                            if (features[9] <= -0.08005539327859879f) {
                                if (features[1] <= -0.3056940734386444f) {
                                    return 0;                                } else {
                                    if (features[10] <= -0.3186229169368744f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                return 1;                            }
                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[3] <= -0.398073747754097f) {
                        return 0;                    } else {
                        if (features[10] <= -0.3224104940891266f) {
                            return 0;                        } else {
                            if (features[0] <= -0.05760587379336357f) {
                                if (features[0] <= -0.33179043233394623f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            } else {
                                return 2;                            }
                        }
                    }
                }
            }
        } else {
            if (features[18] <= -0.3601967394351959f) {
                if (features[4] <= 7.0539209842681885f) {
                    if (features[28] <= 0.5426585469394922f) {
                        return 0;                    } else {
                        if (features[0] <= -0.351503387093544f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[21] <= 15.041060447692871f) {
                        if (features[19] <= -0.5171773731708527f) {
                            if (features[13] <= 0.3172321319580078f) {
                                return 1;                            } else {
                                return 2;                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[28] <= 0.03530806303024292f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[8] <= -0.3214367479085922f) {
                    return 2;                } else {
                    if (features[7] <= 1.2658986449241638f) {
                        if (features[19] <= -0.15705185383558273f) {
                            if (features[0] <= -0.1322481408715248f) {
                                if (features[13] <= 2.2553172968328f) {
                                    if (features[17] <= -0.3413628935813904f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                return 2;                            }
                        } else {
                            if (features[26] <= -0.18058372288942337f) {
                                return 2;                            } else {
                                if (features[2] <= 0.05654647573828697f) {
                                    return 2;                                } else {
                                    return 1;                                }
                            }
                        }
                    } else {
                        return 0;                    }
                }
            }
        }
    } else {
        if (features[2] <= -0.9731524139642715f) {
            return 0;        } else {
            if (features[11] <= -1.5219104290008545f) {
                if (features[3] <= -0.19931206852197647f) {
                    return 2;                } else {
                    return 1;                }
            } else {
                if (features[20] <= -0.06662126258015633f) {
                    return 2;                } else {
                    if (features[0] <= -0.11274053901433945f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 65
int predict_tree_65(const float* features) {
    // Max depth: 7
    if (features[17] <= -0.10328061878681183f) {
        if (features[9] <= -0.05116993933916092f) {
            if (features[2] <= -0.3779018223285675f) {
                if (features[9] <= -0.07219419255852699f) {
                    if (features[10] <= -0.31930047273635864f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[0] <= -0.35109271109104156f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[18] <= -0.37684081494808197f) {
                    if (features[27] <= -0.07501078397035599f) {
                        if (features[12] <= 0.259146586060524f) {
                            if (features[7] <= -0.8650018274784088f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            if (features[10] <= -0.31883396208286285f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[11] <= 0.41663576662540436f) {
                            if (features[4] <= -0.08298777788877487f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[0] <= -0.3414929062128067f) {
                        return 0;                    } else {
                        if (features[12] <= 0.5426838397979736f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            }
        } else {
            if (features[17] <= -0.36027707159519196f) {
                if (features[6] <= -0.36070844903588295f) {
                    if (features[9] <= 13.232214450836182f) {
                        if (features[9] <= 7.437852382659912f) {
                            if (features[28] <= 0.03530806303024292f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[30] <= 0.23382475972175598f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[26] <= 0.06050146312918514f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[18] <= -0.15685156732797623f) {
                    if (features[9] <= 0.013974609784781933f) {
                        if (features[22] <= -0.051262784749269485f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        if (features[0] <= -0.34321266412734985f) {
                            return 0;                        } else {
                            if (features[28] <= -0.4720424022525549f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    if (features[28] <= 0.03530806303024292f) {
                        if (features[20] <= -0.04805156588554382f) {
                            return 2;                        } else {
                            return 1;                        }
                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[7] <= 1.918283224105835f) {
            if (features[28] <= -0.4720424022525549f) {
                return 2;            } else {
                return 2;            }
        } else {
            if (features[22] <= -0.039651794359087944f) {
                return 0;            } else {
                if (features[3] <= -1.5508914589881897f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 66
int predict_tree_66(const float* features) {
    // Max depth: 10
    if (features[10] <= -0.1153935082256794f) {
        if (features[20] <= -0.055738579481840134f) {
            if (features[11] <= 0.052021248266100883f) {
                if (features[17] <= -0.34318502247333527f) {
                    if (features[6] <= -1.1965942978858948f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[8] <= -0.08632495626807213f) {
                        if (features[0] <= -0.2662859559059143f) {
                            if (features[22] <= -0.07240742817521095f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[10] <= -0.31723451614379883f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[1] <= -0.3049132227897644f) {
                    return 0;                } else {
                    if (features[10] <= -0.31813420355319977f) {
                        return 0;                    } else {
                        if (features[19] <= -0.48241741955280304f) {
                            return 1;                        } else {
                            if (features[9] <= -0.07547382265329361f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    }
                }
            }
        } else {
            if (features[9] <= 13.232214450836182f) {
                if (features[7] <= -0.861983060836792f) {
                    return 0;                } else {
                    if (features[19] <= -0.3601555824279785f) {
                        if (features[9] <= 7.0539209842681885f) {
                            if (features[26] <= -0.024127117358148098f) {
                                return 0;                            } else {
                                return 1;                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[18] <= -0.33785928785800934f) {
                            return 0;                        } else {
                            if (features[20] <= -0.04791870713233948f) {
                                if (features[19] <= -0.11568313837051392f) {
                                    if (features[2] <= 0.7900306284427643f) {
                                        if (features[26] <= 0.007815873250365257f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 2;                                    }
                                } else {
                                    if (features[1] <= -0.17584031075239182f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                }
                            } else {
                                if (features[0] <= -0.360512837767601f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            }
                        }
                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[2] <= -0.9731524139642715f) {
            return 0;        } else {
            if (features[21] <= 0.09047236666083336f) {
                return 2;            } else {
                if (features[17] <= 0.9778803884983063f) {
                    return 1;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 67
int predict_tree_67(const float* features) {
    // Max depth: 8
    if (features[18] <= -0.10296984016895294f) {
        if (features[17] <= -0.34377528727054596f) {
            if (features[27] <= 2.857832908630371f) {
                if (features[26] <= -0.13577885180711746f) {
                    return 0;                } else {
                    if (features[4] <= -0.08103632181882858f) {
                        if (features[21] <= -0.08342590183019638f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[19] <= -0.4624374955892563f) {
                            if (features[18] <= -0.5267145931720734f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            if (features[12] <= 0.05177973210811615f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    }
                }
            } else {
                if (features[27] <= 12.022491455078125f) {
                    if (features[13] <= 7.490100860595703f) {
                        if (features[4] <= 9.430949449539185f) {
                            return 0;                        } else {
                            return 2;                        }
                    } else {
                        return 0;                    }
                } else {
                    if (features[8] <= 0.17305199801921844f) {
                        if (features[20] <= 14.415037631988525f) {
                            if (features[4] <= 6.57856559753418f) {
                                return 0;                            } else {
                                return 1;                            }
                        } else {
                            if (features[7] <= -0.545683354139328f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[17] <= -0.15299123525619507f) {
                if (features[26] <= 0.049645169172436f) {
                    if (features[9] <= 0.029635381884872913f) {
                        if (features[6] <= -0.36070844158530235f) {
                            if (features[10] <= -0.3187673091888428f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            if (features[1] <= -0.29950590431690216f) {
                                if (features[8] <= -0.11306718736886978f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[4] <= 0.0301849702373147f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[13] <= -0.002486187731847167f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[3] <= 1.8876855373382568f) {
            if (features[1] <= -0.17377107590436935f) {
                return 1;            } else {
                return 2;            }
        } else {
            if (features[21] <= -0.056391892954707146f) {
                return 0;            } else {
                return 0;            }
        }
    }
}

// Tree 68
int predict_tree_68(const float* features) {
    // Max depth: 10
    if (features[22] <= -0.07715734466910362f) {
        if (features[18] <= -0.35242606699466705f) {
            if (features[6] <= 0.23635287210345268f) {
                if (features[11] <= 0.5922596454620361f) {
                    if (features[10] <= -0.529871791601181f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    return 1;                }
            } else {
                if (features[0] <= -0.33964481949806213f) {
                    return 0;                } else {
                    return 1;                }
            }
        } else {
            if (features[19] <= -0.2635602802038193f) {
                if (features[18] <= -0.33434581756591797f) {
                    if (features[3] <= 0.32144351303577423f) {
                        return 0;                    } else {
                        if (features[12] <= -0.0029916117200627923f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[17] <= -0.33807794749736786f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[8] <= -0.31573793292045593f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[4] <= -0.04684942401945591f) {
            if (features[17] <= -0.18283813446760178f) {
                if (features[10] <= -0.3183230310678482f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                if (features[22] <= -0.06408767215907574f) {
                    return 2;                } else {
                    if (features[2] <= 0.018931910395622253f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[6] <= 1.072238713502884f) {
                if (features[18] <= 0.004280696855857968f) {
                    if (features[4] <= 13.57824420928955f) {
                        if (features[3] <= -0.4696279466152191f) {
                            if (features[20] <= 0.012239666655659676f) {
                                if (features[17] <= -0.09525429084897041f) {
                                    if (features[11] <= 0.4901527315378189f) {
                                        if (features[10] <= -0.3163570463657379f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 2;                                }
                            } else {
                                return 2;                            }
                        } else {
                            if (features[17] <= -0.3413628935813904f) {
                                if (features[16] <= 5.114441957324743f) {
                                    if (features[1] <= -0.2984127253293991f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[21] <= 6.56263542175293f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                if (features[18] <= -0.0921473316848278f) {
                                    if (features[1] <= -0.0037235580384731293f) {
                                        return 1;                                    } else {
                                        return 2;                                    }
                                } else {
                                    return 2;                                }
                            }
                        }
                    } else {
                        return 2;                    }
                } else {
                    return 2;                }
            } else {
                if (features[10] <= -0.17078537493944168f) {
                    return 0;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 69
int predict_tree_69(const float* features) {
    // Max depth: 7
    if (features[0] <= -0.12929633632302284f) {
        if (features[9] <= -0.05075233615934849f) {
            if (features[0] <= -0.3415699154138565f) {
                return 0;            } else {
                return 1;            }
        } else {
            if (features[10] <= -0.31994467973709106f) {
                if (features[20] <= 7.509936571121216f) {
                    return 0;                } else {
                    if (features[7] <= -0.6301346123218536f) {
                        if (features[8] <= 0.031131218187510967f) {
                            return 2;                        } else {
                            return 2;                        }
                    } else {
                        if (features[9] <= 14.618082046508789f) {
                            return 1;                        } else {
                            if (features[2] <= -0.2913883179426193f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                if (features[17] <= -0.3432620167732239f) {
                    if (features[30] <= 0.23382475972175598f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[3] <= 1.8876855373382568f) {
            return 2;        } else {
            if (features[10] <= 0.8900128602981567f) {
                return 0;            } else {
                return 0;            }
        }
    }
}

// Tree 70
int predict_tree_70(const float* features) {
    // Max depth: 9
    if (features[10] <= -0.07267500832676888f) {
        if (features[10] <= -0.3220328539609909f) {
            if (features[3] <= -0.0959559977054596f) {
                if (features[6] <= -0.7189452350139618f) {
                    if (features[7] <= -0.5189160108566284f) {
                        if (features[20] <= 7.509936571121216f) {
                            return 0;                        } else {
                            if (features[27] <= 12.022491455078125f) {
                                if (features[22] <= 15.971939086914062f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            } else {
                                if (features[13] <= 14.472229480743408f) {
                                    if (features[9] <= 13.744702816009521f) {
                                        return 1;                                    } else {
                                        return 2;                                    }
                                } else {
                                    return 2;                                }
                            }
                        }
                    } else {
                        return 0;                    }
                } else {
                    if (features[31] <= 0.24120032787322998f) {
                        return 0;                    } else {
                        return 0;                    }
                }
            } else {
                return 0;            }
        } else {
            if (features[18] <= -0.15759529173374176f) {
                if (features[10] <= -0.31868956983089447f) {
                    if (features[26] <= -0.2570791244506836f) {
                        if (features[9] <= -0.08233493193984032f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[13] <= -0.001099035347579047f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[7] <= -0.7801311016082764f) {
                        if (features[18] <= -0.3681469112634659f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        if (features[8] <= -0.07853119820356369f) {
                            if (features[7] <= -0.6067076325416565f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            if (features[20] <= -0.08105487748980522f) {
                                if (features[6] <= 0.4751773923635483f) {
                                    return 0;                                } else {
                                    if (features[19] <= -0.36883917450904846f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                return 1;                            }
                        }
                    }
                }
            } else {
                if (features[26] <= -0.1507079228758812f) {
                    if (features[29] <= -0.008806705474853516f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    if (features[7] <= 0.06151151657104492f) {
                        return 1;                    } else {
                        if (features[11] <= -0.1573907509446144f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            }
        }
    } else {
        if (features[10] <= 0.8777837753295898f) {
            return 2;        } else {
            if (features[3] <= 1.7644532918930054f) {
                return 2;            } else {
                return 0;            }
        }
    }
}

// Tree 71
int predict_tree_71(const float* features) {
    // Max depth: 10
    if (features[21] <= -0.07737887650728226f) {
        if (features[0] <= -0.3404148519039154f) {
            return 0;        } else {
            if (features[1] <= 0.061008110642433167f) {
                return 1;            } else {
                return 2;            }
        }
    } else {
        if (features[20] <= -0.0688127912580967f) {
            if (features[17] <= -0.265475295484066f) {
                if (features[0] <= -0.3414672315120697f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                if (features[3] <= -1.5671899318695068f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[1] <= -0.07292553782463074f) {
                if (features[15] <= 0.7420355677604675f) {
                    if (features[17] <= -0.3413628935813904f) {
                        if (features[22] <= 4.915213584899902f) {
                            if (features[27] <= -0.07786957174539566f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            if (features[18] <= -0.5226625800132751f) {
                                if (features[19] <= -0.524528980255127f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            } else {
                                if (features[9] <= 12.842154026031494f) {
                                    return 1;                                } else {
                                    if (features[2] <= -0.3007919490337372f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                }
                            }
                        }
                    } else {
                        if (features[18] <= -0.16116005182266235f) {
                            return 1;                        } else {
                            if (features[18] <= -0.13233422487974167f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[0] <= -0.11897783726453781f) {
                        if (features[17] <= -0.36212486028671265f) {
                            return 0;                        } else {
                            if (features[1] <= -0.2752998620271683f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[10] <= -0.11503807455301285f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[4] <= -0.04967314377427101f) {
                    if (features[2] <= -0.9637487679719925f) {
                        return 0;                    } else {
                        if (features[0] <= 0.09696625173091888f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[13] <= 0.22390807420015335f) {
                        if (features[0] <= -0.116616390645504f) {
                            return 1;                        } else {
                            if (features[26] <= -0.11734667047858238f) {
                                if (features[17] <= 0.7347936481237411f) {
                                    return 2;                                } else {
                                    if (features[17] <= 1.8477777242660522f) {
                                        if (features[11] <= -0.07050704769790173f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        return 2;                                    }
                                }
                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[19] <= -0.3265739381313324f) {
                            return 1;                        } else {
                            if (features[13] <= 0.2457866296172142f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                }
            }
        }
    }
}

// Tree 72
int predict_tree_72(const float* features) {
    // Max depth: 9
    if (features[10] <= -0.1192588321864605f) {
        if (features[10] <= -0.3220328539609909f) {
            if (features[21] <= 6.56263542175293f) {
                if (features[20] <= -0.08395151048898697f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[9] <= 13.491242408752441f) {
                    if (features[4] <= 7.630112409591675f) {
                        return 1;                    } else {
                        return 1;                    }
                } else {
                    if (features[0] <= -0.5220666229724884f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[7] <= 1.2711345553398132f) {
                if (features[22] <= -0.04748491011559963f) {
                    if (features[6] <= -0.12188391387462616f) {
                        if (features[1] <= -0.18167708814144135f) {
                            if (features[13] <= -0.011289798654615879f) {
                                return 0;                            } else {
                                if (features[3] <= 0.4247995913028717f) {
                                    return 1;                                } else {
                                    return 0;                                }
                            }
                        } else {
                            if (features[27] <= -0.07662075012922287f) {
                                return 1;                            } else {
                                if (features[20] <= -0.04915982484817505f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        }
                    } else {
                        if (features[3] <= 0.567907989025116f) {
                            if (features[1] <= -0.24476899206638336f) {
                                if (features[27] <= -0.07702451199293137f) {
                                    return 1;                                } else {
                                    if (features[9] <= -0.08242278546094894f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                return 1;                            }
                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[12] <= -0.3820602595806122f) {
                        return 1;                    } else {
                        if (features[10] <= -0.32007797062397003f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                return 0;            }
        }
    } else {
        if (features[2] <= -0.9637487679719925f) {
            return 0;        } else {
            if (features[4] <= 0.08995188027620316f) {
                return 2;            } else {
                if (features[1] <= 1.212728202342987f) {
                    return 1;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 73
int predict_tree_73(const float* features) {
    // Max depth: 6
    if (features[17] <= -0.09930915758013725f) {
        if (features[18] <= -0.3523234874010086f) {
            if (features[10] <= -0.3224104940891266f) {
                if (features[21] <= 6.75391149520874f) {
                    return 0;                } else {
                    if (features[9] <= 13.232214450836182f) {
                        if (features[0] <= -0.516933023929596f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        if (features[11] <= -0.012584582902491093f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[9] <= -0.08220420032739639f) {
                    return 1;                } else {
                    return 1;                }
            }
        } else {
            if (features[27] <= 0.12008187919855118f) {
                if (features[8] <= -0.3214367479085922f) {
                    if (features[18] <= -0.10584216564893723f) {
                        if (features[22] <= -0.0479987058788538f) {
                            return 2;                        } else {
                            return 2;                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[0] <= -0.3414929062128067f) {
                        return 0;                    } else {
                        if (features[0] <= -0.13170911371707916f) {
                            return 1;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[2] <= -0.9637487679719925f) {
            return 0;        } else {
            if (features[1] <= -0.15946217626333237f) {
                return 2;            } else {
                return 2;            }
        }
    }
}

// Tree 74
int predict_tree_74(const float* features) {
    // Max depth: 9
    if (features[18] <= -0.089890506118536f) {
        if (features[1] <= -0.3088759779930115f) {
            if (features[6] <= -0.7189452350139618f) {
                if (features[4] <= 6.756311655044556f) {
                    return 0;                } else {
                    if (features[22] <= 15.250558376312256f) {
                        if (features[26] <= -0.30330905318260193f) {
                            if (features[3] <= -0.23508917540311813f) {
                                return 2;                            } else {
                                return 1;                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[20] <= 16.526902198791504f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                return 0;            }
        } else {
            if (features[1] <= 0.13263070210814476f) {
                if (features[0] <= -0.1342502385377884f) {
                    if (features[21] <= -0.08275965973734856f) {
                        return 0;                    } else {
                        if (features[3] <= 0.7229420840740204f) {
                            if (features[21] <= -0.08221390843391418f) {
                                return 1;                            } else {
                                if (features[0] <= -0.34192925691604614f) {
                                    return 0;                                } else {
                                    if (features[28] <= -0.4720424022525549f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        } else {
                            return 0;                        }
                    }
                } else {
                    return 2;                }
            } else {
                return 2;            }
        }
    } else {
        if (features[3] <= 1.8876855373382568f) {
            if (features[3] <= 0.658940851688385f) {
                if (features[8] <= -0.3421710729598999f) {
                    return 1;                } else {
                    if (features[0] <= -0.2330716773867607f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[10] <= -0.01877150870859623f) {
                    return 1;                } else {
                    return 2;                }
            }
        } else {
            if (features[1] <= 0.8346452713012695f) {
                return 0;            } else {
                return 0;            }
        }
    }
}

// Tree 75
int predict_tree_75(const float* features) {
    // Max depth: 6
    if (features[17] <= -0.1284310594201088f) {
        if (features[10] <= -0.3206000179052353f) {
            if (features[20] <= 7.332235813140869f) {
                return 0;            } else {
                if (features[9] <= 13.491242408752441f) {
                    return 1;                } else {
                    if (features[2] <= -0.3007919490337372f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[2] <= -0.3468698114156723f) {
                if (features[9] <= -0.07555126026272774f) {
                    return 1;                } else {
                    if (features[27] <= -0.0679597295820713f) {
                        if (features[19] <= -0.3461696356534958f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[17] <= -0.15394078940153122f) {
                    if (features[1] <= -0.29770997166633606f) {
                        if (features[6] <= 0.4751773923635483f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        return 1;                    }
                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[18] <= 0.9489676058292389f) {
            if (features[1] <= -0.20397496223449707f) {
                return 1;            } else {
                if (features[27] <= -0.07790148258209229f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[4] <= -0.0491601936519146f) {
                if (features[3] <= 1.402707040309906f) {
                    return 2;                } else {
                    return 0;                }
            } else {
                if (features[21] <= -0.04824775457382202f) {
                    return 0;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 76
int predict_tree_76(const float* features) {
    // Max depth: 10
    if (features[21] <= -0.07734385505318642f) {
        if (features[19] <= -0.3624609708786011f) {
            if (features[10] <= -0.3058495819568634f) {
                return 0;            } else {
                return 1;            }
        } else {
            if (features[26] <= -0.129316046833992f) {
                if (features[4] <= -0.08173121884465218f) {
                    if (features[10] <= -0.32157744467258453f) {
                        return 0;                    } else {
                        if (features[8] <= -0.08632495626807213f) {
                            return 1;                        } else {
                            if (features[30] <= 0.23382475972175598f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    if (features[8] <= -0.23272117972373962f) {
                        return 2;                    } else {
                        return 0;                    }
                }
            } else {
                return 0;            }
        }
    } else {
        if (features[20] <= -0.06883528083562851f) {
            if (features[2] <= -0.3280625194311142f) {
                if (features[20] <= -0.0734715610742569f) {
                    if (features[11] <= 0.2387840673327446f) {
                        if (features[4] <= -0.07552419975399971f) {
                            return 2;                        } else {
                            if (features[6] <= -0.8383574932813644f) {
                                return 0;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[0] <= -0.15116539876908064f) {
                            return 1;                        } else {
                            if (features[9] <= -0.07583896443247795f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[11] <= -0.1700148805975914f) {
                        return 1;                    } else {
                        if (features[7] <= -0.12526960670948029f) {
                            if (features[9] <= -0.07233534008264542f) {
                                return 1;                            } else {
                                return 0;                            }
                        } else {
                            return 0;                        }
                    }
                }
            } else {
                if (features[0] <= -0.2240365743637085f) {
                    return 0;                } else {
                    if (features[11] <= -2.1159870624542236f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[20] <= -0.05007899925112724f) {
                if (features[8] <= -0.29835084080696106f) {
                    if (features[3] <= -0.47360317409038544f) {
                        return 1;                    } else {
                        return 0;                    }
                } else {
                    if (features[21] <= -0.07037751749157906f) {
                        return 2;                    } else {
                        if (features[8] <= -0.22151988744735718f) {
                            if (features[19] <= -0.5140267014503479f) {
                                if (features[26] <= -0.2995859682559967f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 2;                            }
                        } else {
                            if (features[11] <= -6.066967487335205f) {
                                return 2;                            } else {
                                return 0;                            }
                        }
                    }
                }
            } else {
                if (features[0] <= -0.13170911371707916f) {
                    if (features[1] <= -0.30901263654232025f) {
                        if (features[34] <= -2.0574225783348083f) {
                            if (features[4] <= 6.761305093765259f) {
                                return 0;                            } else {
                                if (features[20] <= 13.932217121124268f) {
                                    if (features[28] <= 0.03530806303024292f) {
                                        if (features[7] <= -0.6347659528255463f) {
                                            return 2;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[26] <= -0.3053042143583298f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                }
                            }
                        } else {
                            return 0;                        }
                    } else {
                        if (features[15] <= 0.7420355677604675f) {
                            if (features[18] <= -0.33785928785800934f) {
                                return 0;                            } else {
                                if (features[29] <= -0.008806705474853516f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        } else {
                            if (features[0] <= -0.3235253840684891f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    if (features[6] <= 0.4751773923635483f) {
                        if (features[19] <= 1.122483730316162f) {
                            return 2;                        } else {
                            if (features[26] <= 0.06920654699206352f) {
                                if (features[3] <= 3.0921813249588013f) {
                                    return 2;                                } else {
                                    return 0;                                }
                            } else {
                                return 2;                            }
                        }
                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 77
int predict_tree_77(const float* features) {
    // Max depth: 8
    if (features[0] <= -0.129886694252491f) {
        if (features[20] <= -0.04678337648510933f) {
            if (features[26] <= -0.26310113072395325f) {
                if (features[10] <= -0.31900057196617126f) {
                    return 0;                } else {
                    if (features[22] <= -0.07802077382802963f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[20] <= -0.0822293572127819f) {
                    if (features[7] <= 0.36480066180229187f) {
                        if (features[20] <= -0.08350379019975662f) {
                            if (features[27] <= -0.0768093578517437f) {
                                if (features[7] <= -2.3266626596450806f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        } else {
                            if (features[20] <= -0.08348504826426506f) {
                                return 0;                            } else {
                                return 0;                            }
                        }
                    } else {
                        if (features[10] <= -0.32720883190631866f) {
                            return 0;                        } else {
                            if (features[12] <= 0.09967281296849251f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    if (features[10] <= -0.32356564700603485f) {
                        return 0;                    } else {
                        if (features[6] <= -0.12188391387462616f) {
                            return 1;                        } else {
                            if (features[19] <= -0.34709177911281586f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    }
                }
            }
        } else {
            if (features[10] <= -0.32007797062397003f) {
                if (features[4] <= 6.756311655044556f) {
                    return 0;                } else {
                    if (features[21] <= 15.220935821533203f) {
                        if (features[13] <= 21.408869743347168f) {
                            if (features[13] <= 14.472229480743408f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            return 2;                        }
                    } else {
                        if (features[21] <= 16.052390575408936f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[10] <= -0.3188894987106323f) {
                    return 1;                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[2] <= -0.9637487679719925f) {
            return 0;        } else {
            return 2;        }
    }
}

// Tree 78
int predict_tree_78(const float* features) {
    // Max depth: 8
    if (features[21] <= -0.07737887650728226f) {
        if (features[10] <= -0.32237717509269714f) {
            return 0;        } else {
            if (features[6] <= -1.1965942978858948f) {
                return 2;            } else {
                if (features[22] <= -0.08257435634732246f) {
                    return 0;                } else {
                    if (features[21] <= -0.08221390843391418f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            }
        }
    } else {
        if (features[26] <= 0.00323287071660161f) {
            if (features[0] <= -0.1342502385377884f) {
                if (features[0] <= -0.34192925691604614f) {
                    if (features[4] <= 6.57856559753418f) {
                        return 0;                    } else {
                        if (features[4] <= 13.695127487182617f) {
                            return 1;                        } else {
                            if (features[17] <= -0.5220097899436951f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    return 1;                }
            } else {
                if (features[0] <= 0.7993685007095337f) {
                    return 2;                } else {
                    if (features[17] <= 2.3223767280578613f) {
                        if (features[9] <= -0.04451783560216427f) {
                            return 0;                        } else {
                            if (features[18] <= 1.0199807286262512f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[12] <= 0.149349142157007f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[1] <= -0.15575318038463593f) {
                if (features[2] <= -0.37508074939250946f) {
                    return 0;                } else {
                    if (features[10] <= -0.33334003388881683f) {
                        return 0;                    } else {
                        if (features[22] <= -0.04926941730082035f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[8] <= 0.19782355427742004f) {
                    if (features[20] <= -0.04943428561091423f) {
                        if (features[19] <= 1.0147969722747803f) {
                            if (features[20] <= -0.059765130281448364f) {
                                return 2;                            } else {
                                return 0;                            }
                        } else {
                            if (features[17] <= 0.9927140176296234f) {
                                return 2;                            } else {
                                if (features[11] <= -4.573607504367828f) {
                                    return 2;                                } else {
                                    return 0;                                }
                            }
                        }
                    } else {
                        if (features[16] <= 5.114441957324743f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    return 1;                }
            }
        }
    }
}

// Tree 79
int predict_tree_79(const float* features) {
    // Max depth: 8
    if (features[9] <= -0.07766801118850708f) {
        if (features[18] <= -0.37725116312503815f) {
            if (features[9] <= -0.08354319632053375f) {
                if (features[9] <= -0.08354444429278374f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                return 0;            }
        } else {
            if (features[18] <= -0.35242606699466705f) {
                if (features[3] <= 0.3413196802139282f) {
                    if (features[10] <= -0.31236954033374786f) {
                        if (features[18] <= -0.375148206949234f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                } else {
                    return 0;                }
            } else {
                if (features[0] <= -0.3414929062128067f) {
                    return 0;                } else {
                    if (features[21] <= -0.07912160828709602f) {
                        if (features[9] <= -0.08251188322901726f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[1] <= -0.07292553782463074f) {
            if (features[1] <= -0.3082513213157654f) {
                if (features[7] <= -0.5195372104644775f) {
                    if (features[20] <= 7.332235813140869f) {
                        return 0;                    } else {
                        if (features[27] <= 12.022491455078125f) {
                            return 2;                        } else {
                            if (features[20] <= 13.932217121124268f) {
                                if (features[1] <= -0.46812838315963745f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[25] <= -0.015940948389470577f) {
                        return 0;                    } else {
                        return 0;                    }
                }
            } else {
                if (features[4] <= -0.07555126026272774f) {
                    return 2;                } else {
                    if (features[17] <= -0.13138239085674286f) {
                        if (features[0] <= -0.34192925691604614f) {
                            return 0;                        } else {
                            if (features[4] <= -0.048404511064291f) {
                                if (features[10] <= -0.16869721561670303f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[20] <= -0.04311791621148586f) {
                            if (features[21] <= -0.04883853159844875f) {
                                return 2;                            } else {
                                return 2;                            }
                        } else {
                            return 1;                        }
                    }
                }
            }
        } else {
            if (features[18] <= 0.9484290480613708f) {
                if (features[7] <= 1.664268970489502f) {
                    if (features[11] <= 1.1588601469993591f) {
                        if (features[6] <= -2.8683661222457886f) {
                            return 2;                        } else {
                            return 2;                        }
                    } else {
                        if (features[27] <= 0.007100547198206186f) {
                            return 2;                        } else {
                            if (features[12] <= 2.970965027809143f) {
                                return 1;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    return 0;                }
            } else {
                if (features[20] <= -0.04837808758020401f) {
                    if (features[1] <= 0.7893174886703491f) {
                        return 2;                    } else {
                        if (features[26] <= 2.1315414905548096f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 80
int predict_tree_80(const float* features) {
    // Max depth: 9
    if (features[4] <= -0.0776638500392437f) {
        if (features[18] <= -0.39427994191646576f) {
            if (features[20] <= -0.08189325407147408f) {
                return 0;            } else {
                if (features[20] <= -0.08188825845718384f) {
                    if (features[26] <= 0.12881329096853733f) {
                        if (features[17] <= -0.525448739528656f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[11] <= 0.5102028250694275f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            }
        } else {
            if (features[18] <= -0.35306721925735474f) {
                if (features[10] <= -0.309937059879303f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                if (features[7] <= -0.09259678423404694f) {
                    if (features[1] <= -0.06439485400915146f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    if (features[3] <= 0.3095178157091141f) {
                        if (features[11] <= -0.06270979531109333f) {
                            if (features[0] <= -0.3782750219106674f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[21] <= -0.0819254033267498f) {
                            if (features[0] <= -0.3414929062128067f) {
                                return 0;                            } else {
                                return 1;                            }
                        } else {
                            return 0;                        }
                    }
                }
            }
        }
    } else {
        if (features[20] <= -0.07045789808034897f) {
            if (features[21] <= -0.07265974581241608f) {
                if (features[0] <= -0.11179082095623016f) {
                    if (features[27] <= -0.07712998241186142f) {
                        if (features[18] <= -0.3799952566623688f) {
                            if (features[2] <= -0.16914095729589462f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    } else {
                        return 0;                    }
                } else {
                    if (features[26] <= -0.3074209690093994f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[17] <= -0.2673744186758995f) {
                    if (features[10] <= -0.32388776540756226f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[18] <= -0.11235618218779564f) {
                if (features[10] <= -0.3188894987106323f) {
                    if (features[16] <= 5.114441957324743f) {
                        if (features[7] <= -3.8182917833328247f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[27] <= 12.022491455078125f) {
                            if (features[27] <= 2.8197720050811768f) {
                                return 0;                            } else {
                                if (features[21] <= 9.037244081497192f) {
                                    return 0;                                } else {
                                    if (features[18] <= -0.520893007516861f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                }
                            }
                        } else {
                            if (features[9] <= 13.232214450836182f) {
                                if (features[20] <= 7.332235813140869f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            } else {
                                if (features[0] <= -0.5207318961620331f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                } else {
                    if (features[1] <= 0.10100666433572769f) {
                        if (features[20] <= -0.048688365146517754f) {
                            if (features[1] <= -0.18318020552396774f) {
                                return 1;                            } else {
                                if (features[7] <= 0.10607565939426422f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[10] <= -0.10380864143371582f) {
                                return 1;                            } else {
                                if (features[13] <= 0.06775042042136192f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[9] <= -0.049727270379662514f) {
                    if (features[8] <= -0.21863184124231339f) {
                        return 2;                    } else {
                        if (features[6] <= 1.7887123823165894f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[8] <= -0.3369876593351364f) {
                        return 1;                    } else {
                        if (features[1] <= -0.17740198224782944f) {
                            return 1;                        } else {
                            if (features[21] <= -0.049335917457938194f) {
                                if (features[7] <= 1.1211586892604828f) {
                                    return 2;                                } else {
                                    if (features[21] <= -0.04977910593152046f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                }
                            } else {
                                if (features[9] <= -0.0486193485558033f) {
                                    if (features[6] <= -0.0024716556072235107f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                } else {
                                    if (features[4] <= -0.04858146049082279f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

// Tree 81
int predict_tree_81(const float* features) {
    // Max depth: 6
    if (features[18] <= -0.10671412199735641f) {
        if (features[0] <= -0.34192925691604614f) {
            if (features[16] <= 5.114441957324743f) {
                return 0;            } else {
                if (features[9] <= 13.232214450836182f) {
                    if (features[20] <= 7.2288596630096436f) {
                        if (features[22] <= 0.10016629472374916f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[3] <= -0.2708662748336792f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[10] <= -0.09096865728497505f) {
                if (features[22] <= -0.04764656908810139f) {
                    if (features[1] <= -0.19411197304725647f) {
                        return 1;                    } else {
                        if (features[2] <= 0.6677832901477814f) {
                            return 1;                        } else {
                            return 2;                        }
                    }
                } else {
                    return 1;                }
            } else {
                return 2;            }
        }
    } else {
        if (features[3] <= 1.8876855373382568f) {
            if (features[2] <= -0.4465484172105789f) {
                if (features[7] <= -0.15229563415050507f) {
                    return 2;                } else {
                    return 1;                }
            } else {
                if (features[18] <= 0.0021777453366667032f) {
                    if (features[11] <= -0.35046563297510147f) {
                        return 1;                    } else {
                        if (features[12] <= -0.07610498368740082f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[17] <= -0.037376197054982185f) {
                        return 2;                    } else {
                        if (features[16] <= 5.114441957324743f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[11] <= -1.5746347308158875f) {
                return 0;            } else {
                return 0;            }
        }
    }
}

// Tree 82
int predict_tree_82(const float* features) {
    // Max depth: 9
    if (features[1] <= -0.06462910771369934f) {
        if (features[18] <= -0.3522721976041794f) {
            if (features[34] <= -2.0574225783348083f) {
                if (features[4] <= 7.0539209842681885f) {
                    return 0;                } else {
                    if (features[4] <= 13.57824420928955f) {
                        return 1;                    } else {
                        if (features[11] <= -0.013327178545296192f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[11] <= 0.27071569859981537f) {
                    if (features[10] <= -0.3195892572402954f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[1] <= -0.2959335595369339f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            }
        } else {
            if (features[18] <= -0.156800277531147f) {
                if (features[10] <= -0.3220328539609909f) {
                    return 0;                } else {
                    if (features[18] <= -0.34370651841163635f) {
                        if (features[26] <= -0.2629103809595108f) {
                            if (features[0] <= -0.3467805087566376f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[12] <= 0.39365480840206146f) {
                            if (features[20] <= -0.08245550468564034f) {
                                return 1;                            } else {
                                if (features[19] <= -0.33633334934711456f) {
                                    if (features[0] <= -0.34223727881908417f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[0] <= -0.13712504506111145f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[0] <= -0.1311187595129013f) {
                    if (features[0] <= -0.2607160061597824f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[9] <= -0.07719294726848602f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[2] <= -0.9637487679719925f) {
            return 0;        } else {
            return 2;        }
    }
}

// Tree 83
int predict_tree_83(const float* features) {
    // Max depth: 10
    if (features[19] <= -0.10784485563635826f) {
        if (features[18] <= -0.3502974808216095f) {
            if (features[9] <= 7.0539209842681885f) {
                if (features[28] <= 0.5426585469394922f) {
                    if (features[29] <= -0.5103712691925466f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[26] <= -0.05453410744667053f) {
                        if (features[11] <= 0.11922616139054298f) {
                            return 0;                        } else {
                            if (features[29] <= -0.008806705474853516f) {
                                if (features[3] <= 0.2975921034812927f) {
                                    if (features[26] <= -0.22937016934156418f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    if (features[0] <= -0.34223727881908417f) {
                                        if (features[6] <= -0.36070846021175385f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                if (features[27] <= -0.0779184140264988f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            }
                        }
                    } else {
                        if (features[27] <= -0.07732317596673965f) {
                            return 0;                        } else {
                            if (features[0] <= -0.34205760061740875f) {
                                if (features[17] <= -0.4930098056793213f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        }
                    }
                }
            } else {
                if (features[27] <= 10.103565216064453f) {
                    return 2;                } else {
                    if (features[20] <= 13.932217121124268f) {
                        if (features[27] <= 21.51391315460205f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        if (features[29] <= -0.008806705474853516f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[21] <= -0.08274173364043236f) {
                return 0;            } else {
                if (features[1] <= -0.30871982872486115f) {
                    return 0;                } else {
                    if (features[26] <= 0.5643077194690704f) {
                        if (features[6] <= -0.36070844158530235f) {
                            if (features[17] <= -0.12956026196479797f) {
                                if (features[8] <= -0.08428952470421791f) {
                                    if (features[10] <= -0.16145528852939606f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 0;                                }
                            } else {
                                if (features[3] <= -0.8075228035449982f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[17] <= -0.15229831635951996f) {
                                if (features[22] <= 0.029818225651979446f) {
                                    if (features[0] <= -0.3414929062128067f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[17] <= -0.3413628935813904f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                return 2;                            }
                        }
                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[4] <= -0.06667416170239449f) {
            if (features[18] <= -0.1469266600906849f) {
                return 0;            } else {
                return 2;            }
        } else {
            if (features[34] <= -2.0574225783348083f) {
                return 2;            } else {
                if (features[10] <= -0.1179148517549038f) {
                    if (features[19] <= -0.08822353556752205f) {
                        return 2;                    } else {
                        if (features[15] <= 0.7420355677604675f) {
                            return 0;                        } else {
                            if (features[9] <= -0.042602187022566795f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    if (features[3] <= 1.8876855373382568f) {
                        return 2;                    } else {
                        if (features[27] <= -0.07736144587397575f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                }
            }
        }
    }
}

// Tree 84
int predict_tree_84(const float* features) {
    // Max depth: 10
    if (features[18] <= -0.10289290174841881f) {
        if (features[22] <= -0.0457062516361475f) {
            if (features[1] <= -0.3088759779930115f) {
                return 0;            } else {
                if (features[9] <= -0.04953782819211483f) {
                    if (features[17] <= -0.3813726305961609f) {
                        return 0;                    } else {
                        if (features[7] <= -1.3793938159942627f) {
                            return 0;                        } else {
                            if (features[13] <= -0.01177049521356821f) {
                                return 0;                            } else {
                                if (features[12] <= 0.9630220234394073f) {
                                    if (features[22] <= -0.08092895150184631f) {
                                        if (features[17] <= -0.34056733548641205f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[22] <= -0.08045107871294022f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                } else {
                    if (features[10] <= -0.17346222698688507f) {
                        return 1;                    } else {
                        if (features[4] <= -0.04927385784685612f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[19] <= -0.34271156787872314f) {
                if (features[4] <= 7.6278157234191895f) {
                    if (features[21] <= 0.05099284276366234f) {
                        if (features[3] <= -0.4616774767637253f) {
                            if (features[4] <= -0.009003599174320698f) {
                                if (features[4] <= -0.046872738748788834f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        } else {
                            if (features[4] <= 0.03543020784854889f) {
                                if (features[17] <= -0.3478301614522934f) {
                                    return 0;                                } else {
                                    return 2;                                }
                            } else {
                                if (features[0] <= -0.35966578125953674f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            }
                        }
                    } else {
                        return 0;                    }
                } else {
                    if (features[0] <= -0.523991733789444f) {
                        return 1;                    } else {
                        if (features[19] <= -0.5170749127864838f) {
                            if (features[2] <= -0.3007919490337372f) {
                                return 2;                            } else {
                                return 2;                            }
                        } else {
                            if (features[9] <= 13.973915100097656f) {
                                return 1;                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                if (features[8] <= 0.45224764943122864f) {
                    if (features[16] <= 5.114441957324743f) {
                        if (features[17] <= -0.34185050427913666f) {
                            return 0;                        } else {
                            if (features[17] <= -0.11752398312091827f) {
                                return 1;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[12] <= -0.6615214943885803f) {
                            return 1;                        } else {
                            return 0;                        }
                    }
                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[7] <= 1.9298940896987915f) {
            if (features[10] <= -0.15176976472139359f) {
                return 1;            } else {
                if (features[10] <= 1.2266626358032227f) {
                    return 2;                } else {
                    if (features[3] <= 1.42655847966671f) {
                        return 2;                    } else {
                        return 0;                    }
                }
            }
        } else {
            if (features[34] <= -2.0574225783348083f) {
                return 2;            } else {
                if (features[4] <= -0.039782216772437096f) {
                    return 0;                } else {
                    if (features[10] <= 2.249340772628784f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 85
int predict_tree_85(const float* features) {
    // Max depth: 10
    if (features[9] <= -0.0776638500392437f) {
        if (features[0] <= -0.3417752683162689f) {
            return 0;        } else {
            if (features[12] <= 0.013821917120367289f) {
                if (features[6] <= -1.1965942978858948f) {
                    return 2;                } else {
                    return 1;                }
            } else {
                return 1;            }
        }
    } else {
        if (features[4] <= -0.04679279960691929f) {
            if (features[8] <= -0.21449828147888184f) {
                if (features[7] <= -0.40938524901866913f) {
                    if (features[21] <= -0.07107627764344215f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    if (features[22] <= -0.061088431626558304f) {
                        if (features[8] <= -0.242311991751194f) {
                            if (features[22] <= -0.07646685093641281f) {
                                if (features[1] <= -0.30852461606264114f) {
                                    return 0;                                } else {
                                    return 2;                                }
                            } else {
                                return 2;                            }
                        } else {
                            if (features[3] <= 0.0908799790777266f) {
                                if (features[3] <= -0.4270929545164108f) {
                                    return 0;                                } else {
                                    if (features[9] <= -0.07714798301458359f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                }
                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[1] <= -0.19391676038503647f) {
                            return 1;                        } else {
                            if (features[11] <= -0.8584011197090149f) {
                                if (features[7] <= -0.15743210911750793f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                if (features[22] <= -0.07197132706642151f) {
                    if (features[11] <= 0.07615560665726662f) {
                        if (features[18] <= 0.060470543801784515f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        if (features[22] <= -0.07214301452040672f) {
                            if (features[18] <= -0.20657868310809135f) {
                                return 0;                            } else {
                                return 2;                            }
                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[18] <= 3.051662802696228f) {
                        if (features[21] <= -0.048896484076976776f) {
                            if (features[10] <= 0.00942981243133545f) {
                                return 0;                            } else {
                                if (features[9] <= -0.05868680961430073f) {
                                    return 2;                                } else {
                                    if (features[26] <= 3.1029378175735474f) {
                                        return 0;                                    } else {
                                        return 2;                                    }
                                }
                            }
                        } else {
                            if (features[17] <= -0.0955301821231842f) {
                                if (features[30] <= 0.23382475972175598f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                if (features[4] <= -0.0493625421077013f) {
                                    return 0;                                } else {
                                    if (features[2] <= 0.5361322462558746f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                }
                            }
                        }
                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[12] <= -0.16424863785505295f) {
                if (features[10] <= -0.16153442859649658f) {
                    if (features[1] <= -0.27208375930786133f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            } else {
                if (features[17] <= -0.11128769814968109f) {
                    if (features[0] <= -0.3427506536245346f) {
                        if (features[7] <= -0.5195372104644775f) {
                            if (features[3] <= -0.21521300077438354f) {
                                if (features[21] <= 7.972423315048218f) {
                                    if (features[4] <= -0.046734509989619255f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    if (features[18] <= -0.5199697911739349f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                }
                            } else {
                                if (features[4] <= 6.871181488037109f) {
                                    return 0;                                } else {
                                    if (features[4] <= 14.024089336395264f) {
                                        return 1;                                    } else {
                                        if (features[8] <= -0.03662358224391937f) {
                                            return 2;                                        } else {
                                            return 2;                                        }
                                    }
                                }
                            }
                        } else {
                            return 0;                        }
                    } else {
                        if (features[7] <= -0.792737603187561f) {
                            return 1;                        } else {
                            if (features[8] <= 0.3307151198387146f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 86
int predict_tree_86(const float* features) {
    // Max depth: 10
    if (features[4] <= -0.07763345539569855f) {
        if (features[10] <= -0.32228831946849823f) {
            return 0;        } else {
            if (features[6] <= -1.1965942978858948f) {
                return 2;            } else {
                if (features[17] <= -0.33933547139167786f) {
                    if (features[0] <= -0.3389774560928345f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[11] <= -0.4217548221349716f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            }
        }
    } else {
        if (features[4] <= -0.04635770991444588f) {
            if (features[8] <= -0.21449828147888184f) {
                if (features[1] <= -0.1496235877275467f) {
                    if (features[19] <= -0.4060838222503662f) {
                        return 0;                    } else {
                        if (features[17] <= -0.13138239085674286f) {
                            return 1;                        } else {
                            if (features[3] <= -0.8393246531486511f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[29] <= -0.5103712691925466f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[2] <= -0.37696145474910736f) {
                    if (features[4] <= -0.07219002768397331f) {
                        if (features[10] <= -0.3296746462583542f) {
                            if (features[10] <= -0.3719710558652878f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[12] <= 3.0104511976242065f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[8] <= -0.10034355893731117f) {
                        if (features[17] <= 0.05262645334005356f) {
                            if (features[6] <= 0.7140019237995148f) {
                                if (features[10] <= -0.3247874528169632f) {
                                    if (features[29] <= -0.008806705474853516f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                return 0;                            }
                        } else {
                            if (features[7] <= -0.4302580654621124f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[6] <= 2.1469491124153137f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[15] <= 0.7420355677604675f) {
                if (features[1] <= -0.10343687422573566f) {
                    if (features[2] <= 0.7242051362991333f) {
                        if (features[17] <= -0.3413628935813904f) {
                            if (features[9] <= 7.0539209842681885f) {
                                return 0;                            } else {
                                if (features[3] <= -0.21918823570013046f) {
                                    return 2;                                } else {
                                    if (features[19] <= -0.5211221575737f) {
                                        return 1;                                    } else {
                                        if (features[22] <= 17.1138858795166f) {
                                            return 1;                                        } else {
                                            return 2;                                        }
                                    }
                                }
                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[17] <= -0.3300452083349228f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[22] <= 0.06432578340172768f) {
                        return 2;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[2] <= 0.24461933970451355f) {
                    if (features[1] <= -0.06796720251441002f) {
                        if (features[20] <= -0.009266231674700975f) {
                            return 0;                        } else {
                            if (features[22] <= 0.07265515439212322f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[10] <= -0.13656393438577652f) {
                        if (features[22] <= 0.024340225383639336f) {
                            return 1;                        } else {
                            return 0;                        }
                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 87
int predict_tree_87(const float* features) {
    // Max depth: 10
    if (features[18] <= -0.08578718453645706f) {
        if (features[20] <= -0.05226636677980423f) {
            if (features[19] <= -0.35613398253917694f) {
                if (features[26] <= -0.13508740812540054f) {
                    if (features[12] <= 0.0680837631225586f) {
                        return 0;                    } else {
                        if (features[26] <= -0.18460242450237274f) {
                            if (features[11] <= 0.016005353536456823f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            if (features[12] <= 0.07852852717041969f) {
                                return 1;                            } else {
                                return 0;                            }
                        }
                    }
                } else {
                    if (features[0] <= -0.3404662013053894f) {
                        if (features[31] <= 0.24120032787322998f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                }
            } else {
                if (features[9] <= -0.07231951504945755f) {
                    if (features[8] <= -0.07134003564715385f) {
                        if (features[18] <= -0.3504769951105118f) {
                            return 0;                        } else {
                            if (features[17] <= -0.34369830787181854f) {
                                return 0;                            } else {
                                if (features[18] <= -0.33880817890167236f) {
                                    if (features[28] <= 0.03530806303024292f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[7] <= 0.363038569688797f) {
                                        return 1;                                    } else {
                                        if (features[17] <= -0.3384115844964981f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        return 0;                    }
                } else {
                    if (features[8] <= -0.17382001131772995f) {
                        return 2;                    } else {
                        return 0;                    }
                }
            }
        } else {
            if (features[10] <= -0.31994467973709106f) {
                if (features[21] <= 6.56263542175293f) {
                    return 0;                } else {
                    if (features[4] <= 13.232214450836182f) {
                        return 1;                    } else {
                        if (features[17] <= -0.5213938653469086f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[10] <= -0.07023141533136368f) {
                    if (features[8] <= -0.3244227170944214f) {
                        return 2;                    } else {
                        if (features[12] <= 0.058912742882966995f) {
                            if (features[0] <= -0.1342502385377884f) {
                                if (features[10] <= -0.3188894987106323f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            } else {
                                return 2;                            }
                        } else {
                            if (features[11] <= 0.11291410028934479f) {
                                return 2;                            } else {
                                if (features[0] <= -0.12929633632302284f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[2] <= -0.9656295031309128f) {
            return 0;        } else {
            if (features[18] <= 0.16395115107297897f) {
                if (features[8] <= -0.1607220619916916f) {
                    return 2;                } else {
                    if (features[26] <= 2.5853132009506226f) {
                        if (features[0] <= -0.09297624975442886f) {
                            return 2;                        } else {
                            if (features[28] <= 0.03530806303024292f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        return 1;                    }
                }
            } else {
                if (features[3] <= -0.17188295722007751f) {
                    return 2;                } else {
                    if (features[1] <= 0.045742686837911606f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 88
int predict_tree_88(const float* features) {
    // Max depth: 10
    if (features[2] <= -0.37884218990802765f) {
        if (features[26] <= -0.22627540677785873f) {
            if (features[10] <= -0.03299988806247711f) {
                if (features[17] <= -0.5538584887981415f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[2] <= -0.9543451368808746f) {
                    return 0;                } else {
                    if (features[9] <= -0.07764261588454247f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[8] <= -0.28917570412158966f) {
                return 2;            } else {
                if (features[9] <= -0.07213173806667328f) {
                    if (features[8] <= -0.15488015115261078f) {
                        return 0;                    } else {
                        if (features[27] <= -0.07670092582702637f) {
                            return 0;                        } else {
                            if (features[10] <= -0.3148575723171234f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    return 0;                }
            }
        }
    } else {
        if (features[6] <= 1.4304755330085754f) {
            if (features[17] <= -0.09825694561004639f) {
                if (features[10] <= -0.3214108347892761f) {
                    if (features[22] <= 5.547876358032227f) {
                        if (features[5] <= -0.01776828709989786f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[7] <= -0.6849594712257385f) {
                            return 2;                        } else {
                            if (features[20] <= 14.232638835906982f) {
                                if (features[1] <= -0.4728134423494339f) {
                                    if (features[1] <= -0.4767566919326782f) {
                                        return 1;                                    } else {
                                        return 0;                                    }
                                } else {
                                    if (features[27] <= 15.31184434890747f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                if (features[21] <= 16.34786605834961f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                } else {
                    if (features[0] <= -0.1322481408715248f) {
                        if (features[3] <= 0.7229420840740204f) {
                            if (features[18] <= -0.33455097675323486f) {
                                if (features[21] <= -0.08218597620725632f) {
                                    return 0;                                } else {
                                    if (features[30] <= 0.23382475972175598f) {
                                        if (features[18] <= -0.3408598452806473f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[26] <= -0.2626219242811203f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            } else {
                                if (features[12] <= -0.6889708489179611f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        } else {
                            return 0;                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[10] <= -0.13438691198825836f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[9] <= -0.04524770751595497f) {
                if (features[21] <= -0.04835865646600723f) {
                    if (features[12] <= 0.16692693158984184f) {
                        if (features[18] <= -0.20791226252913475f) {
                            return 0;                        } else {
                            return 2;                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[6] <= 2.027536928653717f) {
                        if (features[8] <= -0.39920474588871f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[12] <= -8.062530994415283f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[20] <= -0.044629745185375214f) {
                    if (features[17] <= 1.1660211086273193f) {
                        if (features[7] <= -0.8585321307182312f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[1] <= -0.21425765752792358f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 89
int predict_tree_89(const float* features) {
    // Max depth: 8
    if (features[22] <= -0.0771949365735054f) {
        if (features[17] <= -0.37721510231494904f) {
            return 0;        } else {
            if (features[22] <= -0.07879898697137833f) {
                if (features[27] <= -0.0778425894677639f) {
                    return 0;                } else {
                    if (features[0] <= -0.34195494651794434f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[0] <= -0.13045138865709305f) {
            if (features[19] <= -0.34814201295375824f) {
                if (features[9] <= 6.475581407546997f) {
                    if (features[18] <= -0.3898688703775406f) {
                        if (features[1] <= -0.30532315373420715f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        if (features[10] <= -0.31852295994758606f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[7] <= -0.6581640541553497f) {
                        if (features[28] <= 0.03530806303024292f) {
                            return 2;                        } else {
                            return 2;                        }
                    } else {
                        if (features[1] <= -0.4689873158931732f) {
                            if (features[11] <= -0.019267944153398275f) {
                                return 2;                            } else {
                                if (features[21] <= 15.815736293792725f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[0] <= -0.34185226261615753f) {
                    return 0;                } else {
                    if (features[9] <= -0.06561370380222797f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            }
        } else {
            if (features[18] <= 0.9486342072486877f) {
                if (features[7] <= 1.664268970489502f) {
                    return 2;                } else {
                    return 0;                }
            } else {
                if (features[2] <= -0.7615704536437988f) {
                    return 0;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 90
int predict_tree_90(const float* features) {
    // Max depth: 6
    if (features[1] <= -0.07353068888187408f) {
        if (features[20] <= -0.05226636677980423f) {
            if (features[6] <= 0.23635287210345268f) {
                if (features[15] <= 0.7420355677604675f) {
                    if (features[26] <= -0.03056611679494381f) {
                        if (features[10] <= -0.21756913512945175f) {
                            return 0;                        } else {
                            return 2;                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[1] <= -0.3095592260360718f) {
                        return 0;                    } else {
                        if (features[10] <= -0.32268817722797394f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[10] <= -0.3222438842058182f) {
                    if (features[30] <= 0.23382475972175598f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[0] <= -0.3414929062128067f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            }
        } else {
            if (features[10] <= -0.31994467973709106f) {
                if (features[9] <= 6.756311655044556f) {
                    return 0;                } else {
                    if (features[4] <= 13.145212650299072f) {
                        return 1;                    } else {
                        if (features[28] <= 0.03530806303024292f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[0] <= -0.13170911371707916f) {
                    if (features[7] <= 1.2658986449241638f) {
                        return 1;                    } else {
                        return 0;                    }
                } else {
                    if (features[29] <= -0.008806705474853516f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[0] <= -0.1588400937616825f) {
            return 1;        } else {
            if (features[9] <= -0.0612211637198925f) {
                return 2;            } else {
                if (features[4] <= -0.049727270379662514f) {
                    if (features[2] <= -0.5923048853874207f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    if (features[2] <= -0.8085886687040329f) {
                        return 0;                    } else {
                        if (features[6] <= -2.8683661222457886f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    }
}

// Tree 91
int predict_tree_91(const float* features) {
    // Max depth: 10
    if (features[18] <= 0.004408925771713257f) {
        if (features[3] <= -1.0420615673065186f) {
            if (features[22] <= -0.06073712557554245f) {
                if (features[31] <= 0.24120032787322998f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[9] <= -0.03071484062820673f) {
                    return 1;                } else {
                    return 2;                }
            }
        } else {
            if (features[1] <= -0.3081732392311096f) {
                if (features[4] <= 6.756311655044556f) {
                    if (features[23] <= -0.017388807609677315f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[18] <= -0.5225600004196167f) {
                        return 1;                    } else {
                        if (features[7] <= -0.6849594712257385f) {
                            return 2;                        } else {
                            if (features[21] <= 11.747964859008789f) {
                                return 1;                            } else {
                                if (features[9] <= 16.00044870376587f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                }
            } else {
                if (features[13] <= 0.08287175372242928f) {
                    if (features[2] <= 0.3010411858558655f) {
                        if (features[7] <= 1.2658986449241638f) {
                            if (features[19] <= -0.05853540077805519f) {
                                if (features[12] <= 0.5345318019390106f) {
                                    if (features[18] <= -0.16121134161949158f) {
                                        if (features[10] <= -0.3214108347892761f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[9] <= 0.02666843682527542f) {
                                            return 2;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    if (features[18] <= -0.254331074655056f) {
                                        return 1;                                    } else {
                                        if (features[3] <= -0.54515740275383f) {
                                            return 2;                                        } else {
                                            return 2;                                        }
                                    }
                                }
                            } else {
                                if (features[12] <= -0.17698615789413452f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[1] <= -0.29999393224716187f) {
                                return 0;                            } else {
                                return 0;                            }
                        }
                    } else {
                        if (features[17] <= -0.13138239085674286f) {
                            if (features[12] <= 0.40766608715057373f) {
                                if (features[8] <= -0.31556612253189087f) {
                                    return 1;                                } else {
                                    if (features[7] <= -0.19311965815722942f) {
                                        return 0;                                    } else {
                                        if (features[29] <= 0.49275785544887185f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            } else {
                                return 1;                            }
                        } else {
                            return 2;                        }
                    }
                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[6] <= 0.23635287210345268f) {
            return 2;        } else {
            if (features[22] <= -0.0473767202347517f) {
                if (features[3] <= 1.7600805312395096f) {
                    if (features[8] <= -0.16704322397708893f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    return 0;                }
            } else {
                return 2;            }
        }
    }
}

// Tree 92
int predict_tree_92(const float* features) {
    // Max depth: 8
    if (features[17] <= -0.12956026196479797f) {
        if (features[27] <= -0.07525331899523735f) {
            if (features[18] <= -0.36135078966617584f) {
                if (features[11] <= 0.17232175916433334f) {
                    if (features[11] <= 0.020089630037546158f) {
                        return 0;                    } else {
                        if (features[10] <= -0.32781971991062164f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[20] <= -0.08190616592764854f) {
                        return 0;                    } else {
                        if (features[0] <= -0.34185226261615753f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[17] <= -0.34382662177085876f) {
                    return 0;                } else {
                    if (features[10] <= -0.32773086428642273f) {
                        return 0;                    } else {
                        if (features[10] <= -0.1117614321410656f) {
                            if (features[20] <= -0.08245467394590378f) {
                                return 1;                            } else {
                                if (features[0] <= -0.33784806728363037f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        } else {
                            return 1;                        }
                    }
                }
            }
        } else {
            if (features[0] <= -0.34192925691604614f) {
                if (features[9] <= 6.761305093765259f) {
                    return 0;                } else {
                    if (features[17] <= -0.5238575637340546f) {
                        return 1;                    } else {
                        if (features[13] <= 9.1866295337677f) {
                            if (features[11] <= 0.01823314093053341f) {
                                if (features[7] <= -0.7291221618652344f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            } else {
                                return 1;                            }
                        } else {
                            if (features[18] <= -0.5187644362449646f) {
                                return 2;                            } else {
                                return 1;                            }
                        }
                    }
                }
            } else {
                if (features[26] <= 0.34504418075084686f) {
                    if (features[21] <= 0.009289044421166182f) {
                        if (features[26] <= -0.30431635677814484f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        if (features[12] <= 0.07852852949872613f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[11] <= 0.3772781938314438f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            }
        }
    } else {
        if (features[21] <= -0.06503925658762455f) {
            return 2;        } else {
            if (features[3] <= 1.8876855373382568f) {
                if (features[17] <= -0.10328061878681183f) {
                    if (features[0] <= -0.12801294028759003f) {
                        return 1;                    } else {
                        if (features[31] <= 0.24120032787322998f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[10] <= -0.13729701191186905f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[13] <= -0.05665380321443081f) {
                    return 0;                } else {
                    return 0;                }
            }
        }
    }
}

// Tree 93
int predict_tree_93(const float* features) {
    // Max depth: 9
    if (features[18] <= -0.08191467449069023f) {
        if (features[9] <= -0.04636145569384098f) {
            if (features[18] <= -0.35237477719783783f) {
                if (features[11] <= 0.11922616139054298f) {
                    if (features[7] <= -2.5726723670959473f) {
                        if (features[19] <= -0.49414925277233124f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        if (features[18] <= -0.364402636885643f) {
                            if (features[2] <= -2.849179267883301f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            if (features[0] <= -0.3451377600431442f) {
                                if (features[21] <= -0.08218139037489891f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    if (features[8] <= -0.19107474386692047f) {
                        return 0;                    } else {
                        if (features[18] <= -0.46834488213062286f) {
                            return 0;                        } else {
                            if (features[1] <= -0.30499130487442017f) {
                                return 0;                            } else {
                                if (features[6] <= -0.8383575081825256f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        }
                    }
                }
            } else {
                if (features[8] <= -0.3140636533498764f) {
                    return 2;                } else {
                    if (features[19] <= -0.10374640673398972f) {
                        if (features[0] <= -0.3414929062128067f) {
                            return 0;                        } else {
                            if (features[11] <= 1.428422451019287f) {
                                if (features[4] <= -0.04794318974018097f) {
                                    if (features[19] <= -0.3773178458213806f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                return 2;                            }
                        }
                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[17] <= -0.3382832556962967f) {
                if (features[27] <= 11.75828742980957f) {
                    if (features[15] <= 0.7420355677604675f) {
                        if (features[16] <= 5.114441957324743f) {
                            return 0;                        } else {
                            if (features[10] <= -0.46333932876586914f) {
                                if (features[20] <= 9.766444563865662f) {
                                    return 0;                                } else {
                                    if (features[2] <= -0.3007919490337372f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                }
                            } else {
                                if (features[31] <= 0.24120032787322998f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            }
                        }
                    } else {
                        if (features[31] <= 0.24120032787322998f) {
                            return 1;                        } else {
                            if (features[8] <= -0.08997421991080046f) {
                                return 0;                            } else {
                                return 0;                            }
                        }
                    }
                } else {
                    if (features[2] <= -0.28198467195034027f) {
                        if (features[4] <= 12.842154026031494f) {
                            if (features[1] <= -0.4652392864227295f) {
                                if (features[22] <= 6.220737934112549f) {
                                    return 0;                                } else {
                                    if (features[9] <= 7.329918384552002f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                return 0;                            }
                        } else {
                            return 2;                        }
                    } else {
                        if (features[22] <= 16.804487228393555f) {
                            return 1;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[16] <= 5.114441957324743f) {
                    if (features[8] <= 0.000858592800796032f) {
                        if (features[10] <= -0.08956914395093918f) {
                            return 1;                        } else {
                            return 2;                        }
                    } else {
                        if (features[9] <= 0.008107336703687906f) {
                            return 1;                        } else {
                            return 2;                        }
                    }
                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[3] <= 1.8876855373382568f) {
            if (features[12] <= -1.0866999626159668f) {
                if (features[17] <= 0.03982025757431984f) {
                    return 1;                } else {
                    if (features[31] <= 0.24120032787322998f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[1] <= -0.23645304888486862f) {
                    return 0;                } else {
                    return 2;                }
            }
        } else {
            if (features[27] <= -0.07768252491950989f) {
                return 0;            } else {
                return 0;            }
        }
    }
}

// Tree 94
int predict_tree_94(const float* features) {
    // Max depth: 10
    if (features[18] <= -0.08578718453645706f) {
        if (features[20] <= -0.05226636677980423f) {
            if (features[1] <= -0.3029611110687256f) {
                return 0;            } else {
                if (features[26] <= 0.7703214585781097f) {
                    if (features[4] <= -0.07960406318306923f) {
                        if (features[21] <= -0.08221849799156189f) {
                            if (features[19] <= -0.32022133469581604f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            if (features[12] <= -0.3833340108394623f) {
                                return 1;                            } else {
                                if (features[19] <= -0.37127262353897095f) {
                                    if (features[18] <= -0.3731478303670883f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[20] <= -0.08245467394590378f) {
                                        return 1;                                    } else {
                                        if (features[20] <= -0.08227850124239922f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        if (features[0] <= -0.342545285820961f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[1] <= -0.3047765791416168f) {
                if (features[16] <= 5.114441957324743f) {
                    return 0;                } else {
                    if (features[22] <= 16.727456092834473f) {
                        if (features[9] <= 6.756311655044556f) {
                            return 0;                        } else {
                            if (features[13] <= 18.119739532470703f) {
                                if (features[7] <= -0.6861324608325958f) {
                                    return 2;                                } else {
                                    return 1;                                }
                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[19] <= -0.5194827914237976f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[12] <= 2.2046756744384766f) {
                    if (features[20] <= -0.04836767539381981f) {
                        if (features[18] <= -0.20134694129228592f) {
                            return 1;                        } else {
                            if (features[2] <= 0.7712233662605286f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[7] <= 1.2658986449241638f) {
                            if (features[26] <= -0.15583711117506027f) {
                                if (features[20] <= -0.04668175429105759f) {
                                    return 1;                                } else {
                                    if (features[10] <= -0.3177565634250641f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                if (features[7] <= -0.782524436712265f) {
                                    if (features[20] <= 0.01145459758117795f) {
                                        return 1;                                    } else {
                                        if (features[3] <= -0.5332316756248474f) {
                                            return 2;                                        } else {
                                            return 2;                                        }
                                    }
                                } else {
                                    if (features[27] <= 0.12195323407649994f) {
                                        if (features[17] <= -0.36833547055721283f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 1;                                    }
                                }
                            }
                        } else {
                            return 0;                        }
                    }
                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[7] <= 1.918724775314331f) {
            if (features[8] <= -0.1530732363462448f) {
                return 2;            } else {
                if (features[4] <= -0.0574194248765707f) {
                    if (features[3] <= 0.19542860239744186f) {
                        return 2;                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[22] <= -0.03767137695103884f) {
                return 0;            } else {
                if (features[15] <= 0.7420355677604675f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 95
int predict_tree_95(const float* features) {
    // Max depth: 7
    if (features[0] <= -0.13170911371707916f) {
        if (features[10] <= -0.3220328539609909f) {
            if (features[20] <= 7.332235813140869f) {
                return 0;            } else {
                if (features[22] <= 16.649717330932617f) {
                    if (features[21] <= 15.220935821533203f) {
                        if (features[7] <= -0.6476379632949829f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[20] <= 17.638296127319336f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[7] <= 1.2658986449241638f) {
                if (features[19] <= -0.3364870399236679f) {
                    if (features[9] <= -0.07547631859779358f) {
                        if (features[17] <= -0.34374962747097015f) {
                            return 1;                        } else {
                            if (features[26] <= -0.2826375812292099f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[4] <= -0.07384462654590607f) {
                            return 0;                        } else {
                            if (features[10] <= -0.3199780136346817f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    if (features[15] <= 0.7420355677604675f) {
                        if (features[17] <= -0.33877086639404297f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        if (features[9] <= -0.07667000591754913f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                return 0;            }
        }
    } else {
        if (features[2] <= -0.9637487679719925f) {
            return 0;        } else {
            return 2;        }
    }
}

// Tree 96
int predict_tree_96(const float* features) {
    // Max depth: 10
    if (features[21] <= -0.07733635231852531f) {
        if (features[0] <= -0.3414929062128067f) {
            return 0;        } else {
            if (features[6] <= -1.1965942978858948f) {
                return 2;            } else {
                return 1;            }
        }
    } else {
        if (features[18] <= -0.10650895535945892f) {
            if (features[17] <= -0.3523726314306259f) {
                if (features[6] <= -0.36070844903588295f) {
                    if (features[27] <= 12.639601707458496f) {
                        if (features[9] <= 9.972887516021729f) {
                            return 0;                        } else {
                            if (features[9] <= 16.679646492004395f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[12] <= 0.0028676482324954122f) {
                            if (features[20] <= 14.232638835906982f) {
                                return 1;                            } else {
                                return 2;                            }
                        } else {
                            if (features[13] <= -19.904497146606445f) {
                                if (features[3] <= -0.12775786966085434f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            } else {
                                if (features[7] <= -0.6183675229549408f) {
                                    if (features[21] <= 7.9369330406188965f) {
                                        return 0;                                    } else {
                                        return 2;                                    }
                                } else {
                                    return 1;                                }
                            }
                        }
                    }
                } else {
                    if (features[12] <= 0.3106061816215515f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[11] <= 1.428422451019287f) {
                    if (features[10] <= -0.3220328539609909f) {
                        return 0;                    } else {
                        if (features[6] <= -0.36070844158530235f) {
                            if (features[31] <= 0.24120032787322998f) {
                                if (features[0] <= -0.13045138865709305f) {
                                    if (features[3] <= 0.4247995913028717f) {
                                        if (features[10] <= -0.3068048059940338f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 0;                                    }
                                } else {
                                    if (features[3] <= -0.8035475611686707f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                }
                            } else {
                                if (features[22] <= -0.05164249241352081f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[9] <= 0.013146063312888145f) {
                                return 1;                            } else {
                                if (features[3] <= -0.044277966022491455f) {
                                    return 2;                                } else {
                                    if (features[10] <= -0.3163237124681473f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        }
                    }
                } else {
                    if (features[29] <= -0.008806705474853516f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[2] <= -0.9656295031309128f) {
                return 0;            } else {
                if (features[18] <= -0.013081477489322424f) {
                    if (features[6] <= -0.36070844158530235f) {
                        return 2;                    } else {
                        if (features[30] <= 0.23382475972175598f) {
                            if (features[8] <= -0.10951624438166618f) {
                                return 1;                            } else {
                                return 2;                            }
                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[12] <= -3.8219553232192993f) {
                        if (features[9] <= -0.06489257887005806f) {
                            return 2;                        } else {
                            return 2;                        }
                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 97
int predict_tree_97(const float* features) {
    // Max depth: 10
    if (features[6] <= 1.4304755330085754f) {
        if (features[2] <= -0.3844843804836273f) {
            if (features[19] <= -0.34399233758449554f) {
                if (features[27] <= -0.07663780823349953f) {
                    return 0;                } else {
                    if (features[3] <= 0.07100380910560489f) {
                        if (features[7] <= -2.5597293376922607f) {
                            return 1;                        } else {
                            if (features[9] <= -0.08369266614317894f) {
                                return 0;                            } else {
                                return 0;                            }
                        }
                    } else {
                        if (features[9] <= -0.08378010243177414f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                }
            } else {
                if (features[1] <= 0.4952529966831207f) {
                    if (features[26] <= 1.7062731981277466f) {
                        if (features[18] <= -0.029622986912727356f) {
                            return 0;                        } else {
                            if (features[9] <= -0.07788493111729622f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        return 1;                    }
                } else {
                    return 0;                }
            }
        } else {
            if (features[20] <= -0.07740690931677818f) {
                if (features[4] <= -0.08201392367482185f) {
                    if (features[10] <= -0.32079994678497314f) {
                        if (features[20] <= -0.08354252204298973f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[0] <= -0.3412362188100815f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[8] <= 0.3815668821334839f) {
                        if (features[20] <= -0.08185077458620071f) {
                            if (features[10] <= -0.320822149515152f) {
                                return 0;                            } else {
                                return 1;                            }
                        } else {
                            if (features[9] <= -0.07743818312883377f) {
                                return 0;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[20] <= -0.07965507730841637f) {
                            return 1;                        } else {
                            return 0;                        }
                    }
                }
            } else {
                if (features[4] <= -0.04619283229112625f) {
                    if (features[7] <= -0.3977237492799759f) {
                        if (features[18] <= -0.3269854784011841f) {
                            if (features[13] <= -0.0193380294367671f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            if (features[8] <= -0.1772095412015915f) {
                                if (features[15] <= 0.7420355677604675f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[27] <= -0.07771015167236328f) {
                            if (features[15] <= 0.7420355677604675f) {
                                if (features[18] <= -0.36966001987457275f) {
                                    return 0;                                } else {
                                    return 2;                                }
                            } else {
                                return 1;                            }
                        } else {
                            if (features[4] <= -0.07337580993771553f) {
                                if (features[18] <= -0.31262387335300446f) {
                                    if (features[26] <= -0.20747339725494385f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 2;                                }
                            } else {
                                if (features[17] <= -0.14649831503629684f) {
                                    if (features[8] <= -0.10271256789565086f) {
                                        if (features[26] <= -0.20361074060201645f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 0;                                    }
                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                } else {
                    if (features[15] <= 0.7420355677604675f) {
                        if (features[34] <= -2.0574225783348083f) {
                            if (features[9] <= 6.761305093765259f) {
                                if (features[1] <= -0.2576528564095497f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            } else {
                                if (features[3] <= -0.21521300077438354f) {
                                    return 2;                                } else {
                                    if (features[22] <= 16.804487228393555f) {
                                        if (features[19] <= -0.5179202258586884f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[9] <= 16.412925720214844f) {
                                            return 2;                                        } else {
                                            return 2;                                        }
                                    }
                                }
                            }
                        } else {
                            if (features[18] <= -0.1435927115380764f) {
                                if (features[1] <= -0.3076656758785248f) {
                                    return 0;                                } else {
                                    if (features[22] <= 0.029818225651979446f) {
                                        return 1;                                    } else {
                                        if (features[12] <= 0.008726908185053617f) {
                                            return 1;                                        } else {
                                            return 0;                                        }
                                    }
                                }
                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[17] <= -0.09178968891501427f) {
                            if (features[20] <= 0.04657905176281929f) {
                                if (features[18] <= -0.44575096666812897f) {
                                    return 0;                                } else {
                                    if (features[0] <= -0.1299893744289875f) {
                                        if (features[19] <= -0.4210944026708603f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 2;                                    }
                                }
                            } else {
                                return 2;                            }
                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    } else {
        if (features[26] <= -0.2366994544863701f) {
            if (features[19] <= 0.9304714500904083f) {
                return 0;            } else {
                return 2;            }
        } else {
            if (features[2] <= -1.27877077460289f) {
                return 0;            } else {
                return 2;            }
        }
    }
}

// Tree 98
int predict_tree_98(const float* features) {
    // Max depth: 7
    if (features[0] <= -0.1342502385377884f) {
        if (features[1] <= -0.30885645747184753f) {
            if (features[4] <= 6.761305093765259f) {
                return 0;            } else {
                if (features[4] <= 13.378913402557373f) {
                    return 1;                } else {
                    if (features[9] <= 15.500205516815186f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[20] <= -0.08352836221456528f) {
                return 0;            } else {
                if (features[19] <= -0.3354111909866333f) {
                    if (features[0] <= -0.3415699154138565f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[17] <= -0.33807794749736786f) {
                        return 0;                    } else {
                        if (features[19] <= -0.31914548575878143f) {
                            if (features[0] <= -0.33890044689178467f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            return 1;                        }
                    }
                }
            }
        }
    } else {
        if (features[2] <= -0.9637487679719925f) {
            return 0;        } else {
            return 2;        }
    }
}

// Tree 99
int predict_tree_99(const float* features) {
    // Max depth: 8
    if (features[10] <= -0.07267500832676888f) {
        if (features[22] <= -0.04563356749713421f) {
            if (features[0] <= -0.3415955752134323f) {
                return 0;            } else {
                if (features[19] <= -0.23507606238126755f) {
                    if (features[22] <= -0.06354254484176636f) {
                        if (features[29] <= -0.008806705474853516f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[4] <= -0.07467275485396385f) {
                        return 2;                    } else {
                        if (features[17] <= -0.12956026196479797f) {
                            if (features[17] <= -0.1545310541987419f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            if (features[7] <= 0.06209121271967888f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                }
            }
        } else {
            if (features[1] <= -0.3076656758785248f) {
                if (features[16] <= 5.114441957324743f) {
                    return 0;                } else {
                    if (features[20] <= 13.932217121124268f) {
                        if (features[20] <= 6.15005898475647f) {
                            return 0;                        } else {
                            if (features[22] <= 10.957460880279541f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[12] <= -0.02770240418612957f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[10] <= -0.3191782832145691f) {
                    return 0;                } else {
                    if (features[18] <= -0.0921473316848278f) {
                        if (features[11] <= 0.17083656042814255f) {
                            return 1;                        } else {
                            if (features[7] <= -0.792737603187561f) {
                                if (features[18] <= -0.191242516040802f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            } else {
                                return 1;                            }
                        }
                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[19] <= 1.0329838395118713f) {
            if (features[6] <= 0.23635287210345268f) {
                return 2;            } else {
                if (features[9] <= -0.06163668446242809f) {
                    if (features[29] <= -0.008806705474853516f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    if (features[3] <= 1.915512204170227f) {
                        if (features[1] <= -0.03228279389441013f) {
                            return 2;                        } else {
                            return 2;                        }
                    } else {
                        return 0;                    }
                }
            }
        } else {
            if (features[4] <= -0.048392850905656815f) {
                if (features[13] <= -0.033731453120708466f) {
                    return 2;                } else {
                    if (features[0] <= 0.8005492091178894f) {
                        return 2;                    } else {
                        if (features[27] <= -0.05388747528195381f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                return 2;            }
        }
    }
}

// Tree 100
int predict_tree_100(const float* features) {
    // Max depth: 7
    if (features[0] <= -0.1342502385377884f) {
        if (features[9] <= -0.05116993933916092f) {
            if (features[17] <= -0.3439292758703232f) {
                if (features[0] <= -0.3325861394405365f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                if (features[8] <= -0.029448275454342365f) {
                    if (features[22] <= -0.06792360730469227f) {
                        if (features[26] <= -0.28316234052181244f) {
                            if (features[13] <= -0.0013874531723558903f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            return 1;                        }
                    } else {
                        return 1;                    }
                } else {
                    return 1;                }
            }
        } else {
            if (features[10] <= -0.31994467973709106f) {
                if (features[20] <= 7.632521390914917f) {
                    return 0;                } else {
                    if (features[8] <= 0.09915485233068466f) {
                        if (features[4] <= 14.705083847045898f) {
                            return 1;                        } else {
                            if (features[7] <= -0.7128814458847046f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[3] <= 0.7229420840740204f) {
                    return 1;                } else {
                    return 0;                }
            }
        }
    } else {
        if (features[7] <= 1.918724775314331f) {
            if (features[1] <= -0.17552797496318817f) {
                return 2;            } else {
                return 2;            }
        } else {
            if (features[10] <= 2.2971686124801636f) {
                if (features[18] <= 2.552186131477356f) {
                    return 0;                } else {
                    return 2;                }
            } else {
                if (features[2] <= 0.21640843152999878f) {
                    return 0;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 101
int predict_tree_101(const float* features) {
    // Max depth: 7
    if (features[17] <= -0.09930915758013725f) {
        if (features[10] <= -0.3220328539609909f) {
            if (features[13] <= -18.825251579284668f) {
                if (features[4] <= 13.695127487182617f) {
                    if (features[18] <= -0.5207647979259491f) {
                        return 1;                    } else {
                        return 0;                    }
                } else {
                    if (features[0] <= -0.521886944770813f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[21] <= 6.087066411972046f) {
                    if (features[28] <= -0.4720424022525549f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[21] <= 10.24644422531128f) {
                        return 1;                    } else {
                        if (features[8] <= 0.03990209195762873f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[18] <= -0.15685156732797623f) {
                if (features[21] <= -0.08221390843391418f) {
                    if (features[18] <= -0.3308323472738266f) {
                        return 1;                    } else {
                        return 1;                    }
                } else {
                    if (features[11] <= 0.2243034616112709f) {
                        if (features[0] <= -0.3414929062128067f) {
                            return 0;                        } else {
                            if (features[0] <= -0.17241841554641724f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[18] <= -0.2833620607852936f) {
                            if (features[1] <= -0.2912875711917877f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[21] <= -0.0480192806571722f) {
                    if (features[22] <= -0.048296960070729256f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    if (features[10] <= -0.12417934462428093f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            }
        }
    } else {
        if (features[18] <= 0.9484290480613708f) {
            if (features[12] <= -1.8430540561676025f) {
                return 2;            } else {
                if (features[10] <= 0.7321343719959259f) {
                    return 2;                } else {
                    if (features[26] <= -0.17575440928339958f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[21] <= -0.047753287479281425f) {
                if (features[7] <= 1.2650699615478516f) {
                    return 2;                } else {
                    return 0;                }
            } else {
                return 2;            }
        }
    }
}

// Tree 102
int predict_tree_102(const float* features) {
    // Max depth: 7
    if (features[17] <= -0.10286999866366386f) {
        if (features[0] <= -0.34192925691604614f) {
            if (features[4] <= 6.761305093765259f) {
                return 0;            } else {
                if (features[18] <= -0.5226625800132751f) {
                    return 1;                } else {
                    if (features[8] <= 0.08564617112278938f) {
                        if (features[4] <= 13.854605674743652f) {
                            return 1;                        } else {
                            if (features[27] <= 4.363201379776001f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[0] <= -0.13478926569223404f) {
                return 1;            } else {
                return 2;            }
        }
    } else {
        if (features[3] <= 1.8876855373382568f) {
            if (features[10] <= -0.13438691198825836f) {
                return 2;            } else {
                return 2;            }
        } else {
            if (features[19] <= 0.8764999806880951f) {
                return 0;            } else {
                return 0;            }
        }
    }
}

// Tree 103
int predict_tree_103(const float* features) {
    // Max depth: 10
    if (features[19] <= -0.05909893848001957f) {
        if (features[4] <= -0.05116993933916092f) {
            if (features[0] <= -0.3415699154138565f) {
                return 0;            } else {
                if (features[0] <= -0.12100560590624809f) {
                    if (features[17] <= -0.3603797107934952f) {
                        return 1;                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[4] <= 13.57824420928955f) {
                if (features[1] <= -0.30901263654232025f) {
                    if (features[22] <= 6.220737934112549f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[22] <= -0.04748491011559963f) {
                        if (features[18] <= -0.2487402930855751f) {
                            return 1;                        } else {
                            if (features[17] <= -0.1304328292608261f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[18] <= -0.07696504518389702f) {
                            if (features[17] <= -0.11621513217687607f) {
                                if (features[10] <= -0.09598913416266441f) {
                                    if (features[4] <= 0.02988686040043831f) {
                                        return 1;                                    } else {
                                        if (features[19] <= -0.3271118551492691f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                return 2;                            }
                        } else {
                            return 2;                        }
                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[9] <= -0.0668477825820446f) {
            if (features[6] <= 0.4751773923635483f) {
                return 2;            } else {
                return 1;            }
        } else {
            if (features[9] <= -0.04967314377427101f) {
                if (features[3] <= -0.2947176620364189f) {
                    return 2;                } else {
                    if (features[6] <= 1.1916509866714478f) {
                        return 0;                    } else {
                        if (features[4] <= -0.06534723937511444f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[18] <= 0.0021777453366667032f) {
                    if (features[22] <= 0.02964236494153738f) {
                        if (features[22] <= -0.044281404465436935f) {
                            return 2;                        } else {
                            if (features[21] <= -0.040906187146902084f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[3] <= 1.8876855671405792f) {
                        return 2;                    } else {
                        if (features[7] <= 1.9582127928733826f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                }
            }
        }
    }
}

// Tree 104
int predict_tree_104(const float* features) {
    // Max depth: 9
    if (features[0] <= -0.1342502385377884f) {
        if (features[10] <= -0.3220328539609909f) {
            if (features[9] <= 6.761305093765259f) {
                if (features[26] <= -0.31034791469573975f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[9] <= 13.491242408752441f) {
                    return 1;                } else {
                    if (features[28] <= 0.03530806303024292f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[19] <= -0.3300832211971283f) {
                if (features[3] <= 0.7229420840740204f) {
                    if (features[4] <= 0.014507543769695985f) {
                        if (features[22] <= -0.08184250816702843f) {
                            if (features[30] <= 0.23382475972175598f) {
                                return 0;                            } else {
                                return 1;                            }
                        } else {
                            if (features[13] <= -0.00817213929258287f) {
                                return 1;                            } else {
                                if (features[10] <= -0.3142911046743393f) {
                                    if (features[8] <= -0.08699887990951538f) {
                                        return 1;                                    } else {
                                        return 0;                                    }
                                } else {
                                    return 1;                                }
                            }
                        }
                    } else {
                        return 1;                    }
                } else {
                    return 0;                }
            } else {
                if (features[19] <= -0.3194016367197037f) {
                    if (features[6] <= 0.11694060638546944f) {
                        return 1;                    } else {
                        if (features[26] <= -0.200673408806324f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[0] <= -0.3301733583211899f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            }
        }
    } else {
        if (features[6] <= 0.23635287210345268f) {
            return 2;        } else {
            if (features[19] <= 2.2775033712387085f) {
                if (features[18] <= 1.0307006239891052f) {
                    if (features[0] <= 0.8025769889354706f) {
                        return 2;                    } else {
                        if (features[7] <= 1.615963637828827f) {
                            return 2;                        } else {
                            if (features[1] <= 0.8269930481910706f) {
                                return 0;                            } else {
                                return 0;                            }
                        }
                    }
                } else {
                    if (features[9] <= -0.04699431546032429f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[9] <= -0.05172952078282833f) {
                    return 0;                } else {
                    if (features[4] <= -0.050661152228713036f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 105
int predict_tree_105(const float* features) {
    // Max depth: 9
    if (features[15] <= 0.7420355677604675f) {
        if (features[21] <= -0.04598887450993061f) {
            if (features[17] <= -0.34382662177085876f) {
                return 0;            } else {
                if (features[0] <= -0.17139169573783875f) {
                    if (features[10] <= -0.3186229169368744f) {
                        return 0;                    } else {
                        if (features[11] <= -0.11357760429382324f) {
                            return 1;                        } else {
                            if (features[21] <= -0.08218556270003319f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    if (features[7] <= 1.4665948152542114f) {
                        return 2;                    } else {
                        return 0;                    }
                }
            }
        } else {
            if (features[18] <= -0.14123329892754555f) {
                if (features[6] <= -0.0024716556072235107f) {
                    if (features[8] <= 0.09915485233068466f) {
                        if (features[9] <= 14.816052913665771f) {
                            if (features[0] <= -0.42280882596969604f) {
                                if (features[21] <= 6.75391149520874f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            } else {
                                return 1;                            }
                        } else {
                            return 2;                        }
                    } else {
                        if (features[18] <= -0.5220214128494263f) {
                            if (features[8] <= 0.39495212584733963f) {
                                return 1;                            } else {
                                return 0;                            }
                        } else {
                            if (features[9] <= 9.69106125831604f) {
                                return 0;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[12] <= -0.013436379376798868f) {
                        if (features[17] <= -0.3434673249721527f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        if (features[18] <= -0.3551701605319977f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[2] <= -0.5048509985208511f) {
            return 0;        } else {
            if (features[17] <= -0.09658880159258842f) {
                if (features[19] <= -0.3832605928182602f) {
                    if (features[10] <= -0.317034587264061f) {
                        if (features[9] <= -0.08248773589730263f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[1] <= -0.31106235086917877f) {
                        return 0;                    } else {
                        if (features[0] <= -0.1342502385377884f) {
                            if (features[21] <= -0.07217986509203911f) {
                                if (features[22] <= -0.07337027788162231f) {
                                    if (features[10] <= -0.3187673091888428f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                return 1;                            }
                        } else {
                            if (features[8] <= -0.30631914734840393f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                if (features[22] <= -0.07674505189061165f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 106
int predict_tree_106(const float* features) {
    // Max depth: 9
    if (features[18] <= -0.10296984016895294f) {
        if (features[10] <= -0.3220328539609909f) {
            if (features[20] <= 7.051158905029297f) {
                return 0;            } else {
                if (features[21] <= 15.220935821533203f) {
                    if (features[13] <= 14.472229480743408f) {
                        return 1;                    } else {
                        return 1;                    }
                } else {
                    if (features[30] <= 0.23382475972175598f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[17] <= -0.13138239085674286f) {
                if (features[1] <= -0.023947323439642787f) {
                    if (features[8] <= -0.09369833394885063f) {
                        return 1;                    } else {
                        if (features[7] <= 1.2658986449241638f) {
                            if (features[2] <= -0.28198467195034027f) {
                                return 0;                            } else {
                                if (features[0] <= -0.34213460981845856f) {
                                    return 0;                                } else {
                                    if (features[1] <= -0.064121562987566f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        } else {
                            return 0;                        }
                    }
                } else {
                    return 1;                }
            } else {
                return 2;            }
        }
    } else {
        if (features[2] <= -0.9750331491231918f) {
            return 0;        } else {
            if (features[17] <= -0.10133017599582672f) {
                return 1;            } else {
                if (features[8] <= -0.33922989666461945f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 107
int predict_tree_107(const float* features) {
    // Max depth: 9
    if (features[18] <= -0.10296984016895294f) {
        if (features[10] <= -0.3220328539609909f) {
            if (features[4] <= 7.354115009307861f) {
                return 0;            } else {
                if (features[21] <= 15.041060447692871f) {
                    if (features[8] <= 0.15700668096542358f) {
                        return 1;                    } else {
                        return 2;                    }
                } else {
                    if (features[1] <= -0.4766590744256973f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[7] <= -1.704147219657898f) {
                return 0;            } else {
                if (features[26] <= 0.5643077194690704f) {
                    if (features[17] <= -0.13138239085674286f) {
                        if (features[17] <= -0.3440575897693634f) {
                            if (features[19] <= -0.36732786893844604f) {
                                return 1;                            } else {
                                if (features[3] <= 0.4247995913028717f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            }
                        } else {
                            if (features[17] <= -0.15299123525619507f) {
                                if (features[8] <= -0.09369833394885063f) {
                                    return 1;                                } else {
                                    if (features[0] <= -0.34185226261615753f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                return 1;                            }
                        }
                    } else {
                        return 2;                    }
                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[17] <= 1.013963520526886f) {
            if (features[11] <= -0.48636065423488617f) {
                if (features[1] <= -0.15881798416376114f) {
                    return 1;                } else {
                    if (features[21] <= -0.0768752358853817f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[3] <= 1.9234626293182373f) {
                    return 2;                } else {
                    if (features[11] <= 0.030114672612398863f) {
                        return 0;                    } else {
                        return 0;                    }
                }
            }
        } else {
            if (features[20] <= -0.0484618004411459f) {
                if (features[4] <= -0.06295986101031303f) {
                    return 2;                } else {
                    if (features[21] <= -0.048080986365675926f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            } else {
                return 2;            }
        }
    }
}

// Tree 108
int predict_tree_108(const float* features) {
    // Max depth: 8
    if (features[34] <= -2.0574225783348083f) {
        if (features[0] <= 0.023992404341697693f) {
            if (features[19] <= -0.5131301581859589f) {
                if (features[18] <= -0.5233293771743774f) {
                    if (features[29] <= -0.008806705474853516f) {
                        if (features[11] <= 0.026401693001389503f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        return 0;                    }
                } else {
                    if (features[19] <= -0.5151281654834747f) {
                        if (features[4] <= 9.988794803619385f) {
                            return 0;                        } else {
                            return 2;                        }
                    } else {
                        return 1;                    }
                }
            } else {
                if (features[15] <= 0.7420355677604675f) {
                    return 0;                } else {
                    return 1;                }
            }
        } else {
            return 2;        }
    } else {
        if (features[10] <= -0.3220328539609909f) {
            return 0;        } else {
            if (features[10] <= -0.1153935082256794f) {
                if (features[0] <= -0.1322738081216812f) {
                    if (features[8] <= -0.09369833394885063f) {
                        return 1;                    } else {
                        if (features[22] <= -0.058539073914289474f) {
                            if (features[10] <= -0.3175455182790756f) {
                                return 0;                            } else {
                                if (features[1] <= -0.2929273247718811f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        } else {
                            if (features[10] <= -0.3188894987106323f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    return 2;                }
            } else {
                if (features[3] <= 1.8876855373382568f) {
                    if (features[12] <= 2.169774889945984f) {
                        return 2;                    } else {
                        if (features[1] <= 0.16997439786791801f) {
                            return 1;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[27] <= -0.07728051021695137f) {
                        return 0;                    } else {
                        return 0;                    }
                }
            }
        }
    }
}

// Tree 109
int predict_tree_109(const float* features) {
    // Max depth: 10
    if (features[18] <= 0.0021777453366667032f) {
        if (features[27] <= -0.07509423792362213f) {
            if (features[19] <= -0.3542640805244446f) {
                if (features[18] <= -0.34798935055732727f) {
                    if (features[11] <= 0.17269305139780045f) {
                        if (features[9] <= -0.08354319632053375f) {
                            if (features[7] <= -2.5723416805267334f) {
                                if (features[21] <= -0.08352888002991676f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            } else {
                                return 0;                            }
                        } else {
                            if (features[17] <= -0.5538584887981415f) {
                                return 0;                            } else {
                                return 0;                            }
                        }
                    } else {
                        if (features[1] <= -0.29378625750541687f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                } else {
                    return 1;                }
            } else {
                if (features[7] <= -0.092048529535532f) {
                    if (features[10] <= -0.1447610855102539f) {
                        if (features[13] <= -0.00245871942024678f) {
                            return 0;                        } else {
                            if (features[26] <= -0.26549132168293f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[13] <= -0.0033377071376889944f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[18] <= -0.3512207269668579f) {
                        return 0;                    } else {
                        if (features[27] <= -0.07666880637407303f) {
                            if (features[17] <= -0.34369830787181854f) {
                                return 0;                            } else {
                                if (features[18] <= -0.2634866088628769f) {
                                    if (features[3] <= 0.567907989025116f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 1;                                }
                            }
                        } else {
                            if (features[12] <= 0.00032014399766921997f) {
                                if (features[8] <= -0.2236509546637535f) {
                                    return 2;                                } else {
                                    if (features[19] <= -0.3141248971223831f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                return 1;                            }
                        }
                    }
                }
            }
        } else {
            if (features[4] <= -0.04916976951062679f) {
                if (features[10] <= -0.32515399158000946f) {
                    return 0;                } else {
                    if (features[18] <= -0.3516054153442383f) {
                        return 1;                    } else {
                        if (features[10] <= -0.23045355081558228f) {
                            if (features[10] <= -0.3193337768316269f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[2] <= 0.22581204771995544f) {
                    if (features[27] <= -0.05042671971023083f) {
                        if (features[12] <= 0.04897747561335564f) {
                            return 0;                        } else {
                            return 2;                        }
                    } else {
                        if (features[9] <= 12.842154026031494f) {
                            if (features[0] <= -0.1287573091685772f) {
                                if (features[27] <= 11.75828742980957f) {
                                    if (features[1] <= -0.31488844752311707f) {
                                        return 0;                                    } else {
                                        if (features[19] <= -0.4210944026708603f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    if (features[4] <= 6.756311655044556f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                if (features[11] <= -0.0348624512553215f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[18] <= -0.5207391381263733f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[10] <= -0.31994467973709106f) {
                        return 0;                    } else {
                        if (features[17] <= -0.09727530926465988f) {
                            if (features[4] <= -0.04831457696855068f) {
                                if (features[17] <= -0.17239300161600113f) {
                                    return 1;                                } else {
                                    if (features[9] <= -0.04891953989863396f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                }
                            } else {
                                if (features[20] <= -0.04794536158442497f) {
                                    return 2;                                } else {
                                    if (features[7] <= 1.2658986449241638f) {
                                        if (features[1] <= -0.09512092918157578f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 0;                                    }
                                }
                            }
                        } else {
                            if (features[7] <= -0.3538781851530075f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                }
            }
        }
    } else {
        if (features[22] <= -0.06408767215907574f) {
            if (features[6] <= 0.23635287210345268f) {
                return 2;            } else {
                if (features[18] <= 0.34152233600616455f) {
                    return 1;                } else {
                    return 2;                }
            }
        } else {
            if (features[2] <= -0.16914095357060432f) {
                return 0;            } else {
                if (features[3] <= -2.155126929283142f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 110
int predict_tree_110(const float* features) {
    // Max depth: 10
    if (features[9] <= -0.07767300680279732f) {
        if (features[12] <= 0.0563652403652668f) {
            if (features[2] <= 0.00012461841106414795f) {
                if (features[17] <= -0.3426204174757004f) {
                    if (features[26] <= -0.31034791469573975f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[3] <= 0.32541875541210175f) {
                        if (features[27] <= -0.07645418867468834f) {
                            if (features[26] <= -0.1188681460916996f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            return 2;                        }
                    } else {
                        return 1;                    }
                }
            } else {
                if (features[10] <= -0.3219439834356308f) {
                    if (features[12] <= -0.3181179016828537f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    return 1;                }
            }
        } else {
            if (features[19] <= -0.49583984911441803f) {
                if (features[26] <= 0.31444698572158813f) {
                    if (features[2] <= -1.7677602767944336f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    return 1;                }
            } else {
                if (features[3] <= 0.567907989025116f) {
                    if (features[21] <= -0.08164522796869278f) {
                        if (features[22] <= -0.08190808817744255f) {
                            return 0;                        } else {
                            if (features[0] <= -0.34118489921092987f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[26] <= -0.015861937776207924f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                } else {
                    return 0;                }
            }
        }
    } else {
        if (features[17] <= -0.12116822972893715f) {
            if (features[9] <= -0.05116993933916092f) {
                if (features[10] <= -0.32457640767097473f) {
                    return 0;                } else {
                    if (features[11] <= 1.0805163234472275f) {
                        if (features[9] <= -0.07408444583415985f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[21] <= 14.85464859008789f) {
                    if (features[1] <= -0.3033124953508377f) {
                        if (features[9] <= 7.048927545547485f) {
                            return 0;                        } else {
                            if (features[9] <= 13.145212650299072f) {
                                return 1;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[10] <= -0.3188894987106323f) {
                            return 0;                        } else {
                            if (features[1] <= -0.06837714463472366f) {
                                if (features[26] <= 0.2933348938822746f) {
                                    if (features[6] <= -0.36070844158530235f) {
                                        if (features[9] <= -0.04894660413265228f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[2] <= -0.9571662247180939f) {
                return 0;            } else {
                if (features[0] <= -0.1354823037981987f) {
                    return 1;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 111
int predict_tree_111(const float* features) {
    // Max depth: 8
    if (features[1] <= -0.07353068888187408f) {
        if (features[9] <= -0.05137520097196102f) {
            if (features[17] <= -0.3523726314306259f) {
                if (features[26] <= 0.4631226360797882f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                if (features[7] <= -0.10183418914675713f) {
                    if (features[0] <= -0.2196473591029644f) {
                        return 0;                    } else {
                        if (features[20] <= -0.07716867700219154f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[18] <= -0.15331245213747025f) {
                        if (features[9] <= -0.08190608769655228f) {
                            if (features[19] <= -0.3274192214012146f) {
                                if (features[0] <= -0.34187793731689453f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            } else {
                                return 1;                            }
                        } else {
                            if (features[0] <= -0.3414672315120697f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[3] <= -0.3344700187444687f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[10] <= -0.3182230591773987f) {
                if (features[4] <= 6.756311655044556f) {
                    return 0;                } else {
                    if (features[9] <= 13.145212650299072f) {
                        return 1;                    } else {
                        if (features[27] <= 3.4643077850341797f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[21] <= -0.0480192806571722f) {
                    if (features[20] <= -0.04905903711915016f) {
                        return 1;                    } else {
                        if (features[1] <= -0.17775336652994156f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[0] <= -0.12834662199020386f) {
                        return 1;                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[22] <= -0.05980059504508972f) {
            if (features[18] <= -0.2819002494215965f) {
                return 1;            } else {
                return 2;            }
        } else {
            if (features[3] <= 1.8876855373382568f) {
                if (features[17] <= -0.16728591918945312f) {
                    return 1;                } else {
                    if (features[13] <= -0.43887609243392944f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[29] <= -0.008806705474853516f) {
                    return 0;                } else {
                    return 0;                }
            }
        }
    }
}

// Tree 112
int predict_tree_112(const float* features) {
    // Max depth: 9
    if (features[9] <= -0.0776638500392437f) {
        if (features[18] <= -0.3502718359231949f) {
            if (features[0] <= -0.33114874362945557f) {
                if (features[15] <= 0.7420355677604675f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                return 1;            }
        } else {
            if (features[11] <= 0.003381225629709661f) {
                if (features[1] <= -0.3081732392311096f) {
                    return 0;                } else {
                    if (features[21] <= -0.07920290529727936f) {
                        if (features[17] <= -0.3395407795906067f) {
                            return 0;                        } else {
                            if (features[2] <= 0.4138849228620529f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[4] <= -0.08198561146855354f) {
                    return 1;                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[4] <= -0.0706399418413639f) {
            if (features[0] <= -0.11179082095623016f) {
                if (features[7] <= -0.1267346516251564f) {
                    if (features[1] <= -0.30508890748023987f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[26] <= -0.13575343042612076f) {
                        if (features[12] <= -0.08425699919462204f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                }
            } else {
                if (features[6] <= -1.1965942978858948f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[1] <= -0.07936747372150421f) {
                if (features[0] <= -0.34000417590141296f) {
                    if (features[0] <= -0.5160603225231171f) {
                        if (features[9] <= 6.756311655044556f) {
                            return 0;                        } else {
                            if (features[3] <= -0.21521300077438354f) {
                                return 2;                            } else {
                                if (features[9] <= 13.744702816009521f) {
                                    return 1;                                } else {
                                    if (features[11] <= -0.017782752867788076f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                }
                            }
                        }
                    } else {
                        return 0;                    }
                } else {
                    if (features[20] <= -0.048404326662421227f) {
                        if (features[26] <= -0.30183814465999603f) {
                            return 1;                        } else {
                            if (features[22] <= -0.047816162928938866f) {
                                return 2;                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[12] <= -0.36473722755908966f) {
                            return 1;                        } else {
                            if (features[0] <= -0.1342502385377884f) {
                                return 1;                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                if (features[2] <= -0.9035654515028f) {
                    return 0;                } else {
                    if (features[27] <= -0.07786087691783905f) {
                        if (features[4] <= -0.018486497458070517f) {
                            return 2;                        } else {
                            return 1;                        }
                    } else {
                        if (features[8] <= 0.1475760042667389f) {
                            if (features[10] <= -0.06054588779807091f) {
                                return 2;                            } else {
                                return 2;                            }
                        } else {
                            return 1;                        }
                    }
                }
            }
        }
    }
}

// Tree 113
int predict_tree_113(const float* features) {
    // Max depth: 10
    if (features[17] <= -0.10328061878681183f) {
        if (features[17] <= -0.3438779413700104f) {
            if (features[22] <= 5.547876358032227f) {
                if (features[2] <= 0.28223390877246857f) {
                    if (features[31] <= 0.24120032787322998f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[2] <= 0.3010411858558655f) {
                        if (features[1] <= -0.3205495625734329f) {
                            if (features[4] <= -0.08204348385334015f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[10] <= -0.329852357506752f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[20] <= 14.808661937713623f) {
                    if (features[19] <= -0.5256560444831848f) {
                        return 0;                    } else {
                        if (features[8] <= 0.16243749111890793f) {
                            return 1;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[17] <= -0.5215735137462616f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[18] <= -0.11235618218779564f) {
                if (features[10] <= -0.08314915001392365f) {
                    if (features[10] <= -0.32773086428642273f) {
                        return 0;                    } else {
                        if (features[18] <= -0.14656762033700943f) {
                            if (features[29] <= 0.49275785544887185f) {
                                if (features[8] <= 0.10338497348129749f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            } else {
                                if (features[17] <= -0.3426717519760132f) {
                                    return 1;                                } else {
                                    if (features[4] <= -0.08239738643169403f) {
                                        if (features[0] <= -0.3415699154138565f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 1;                                    }
                                }
                            }
                        } else {
                            return 1;                        }
                    }
                } else {
                    return 2;                }
            } else {
                if (features[8] <= -0.3139767199754715f) {
                    return 2;                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[0] <= 0.949140727519989f) {
            return 2;        } else {
            if (features[3] <= 1.7644532918930054f) {
                return 2;            } else {
                return 0;            }
        }
    }
}

// Tree 114
int predict_tree_114(const float* features) {
    // Max depth: 10
    if (features[4] <= -0.07770590111613274f) {
        if (features[22] <= -0.08198495209217072f) {
            if (features[7] <= -2.5726723670959473f) {
                if (features[10] <= -0.31930047273635864f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                return 0;            }
        } else {
            if (features[0] <= -0.34182658791542053f) {
                if (features[0] <= -0.5510200262069702f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[17] <= 0.034533530473709106f) {
                    if (features[4] <= -0.08250980079174042f) {
                        return 1;                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[17] <= -0.10286999866366386f) {
            if (features[0] <= -0.34192925691604614f) {
                if (features[34] <= -2.0574225783348083f) {
                    if (features[0] <= -0.5146229565143585f) {
                        if (features[27] <= 12.022491455078125f) {
                            if (features[26] <= -0.2954734116792679f) {
                                if (features[27] <= 10.936853885650635f) {
                                    if (features[27] <= 3.711496114730835f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                } else {
                                    return 2;                                }
                            } else {
                                return 0;                            }
                        } else {
                            if (features[17] <= -0.5238575637340546f) {
                                return 1;                            } else {
                                if (features[27] <= 14.966695785522461f) {
                                    if (features[4] <= 6.8710243701934814f) {
                                        return 0;                                    } else {
                                        if (features[12] <= 0.0023581474961247295f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    if (features[9] <= 9.983801364898682f) {
                                        return 0;                                    } else {
                                        return 2;                                    }
                                }
                            }
                        }
                    } else {
                        return 0;                    }
                } else {
                    return 0;                }
            } else {
                if (features[20] <= -0.04794536158442497f) {
                    if (features[17] <= -0.15394078940153122f) {
                        return 1;                    } else {
                        if (features[3] <= -0.795597106218338f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[10] <= -0.06934283301234245f) {
                        if (features[20] <= 0.0493748988956213f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[7] <= 1.918724775314331f) {
                if (features[17] <= -0.03796646371483803f) {
                    if (features[19] <= 0.03693283093161881f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    return 2;                }
            } else {
                if (features[9] <= -0.040576620027422905f) {
                    return 0;                } else {
                    if (features[8] <= -0.08669807761907578f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 115
int predict_tree_115(const float* features) {
    // Max depth: 8
    if (features[1] <= -0.07353068888187408f) {
        if (features[19] <= -0.3542640805244446f) {
            if (features[20] <= 7.332235813140869f) {
                if (features[3] <= 0.4208243638277054f) {
                    if (features[1] <= -0.3096177875995636f) {
                        if (features[22] <= -0.08348081260919571f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[26] <= -0.18359705060720444f) {
                            return 0;                        } else {
                            if (features[0] <= -0.3426993042230606f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    return 0;                }
            } else {
                if (features[9] <= 13.145212650299072f) {
                    return 1;                } else {
                    if (features[0] <= -0.5229136645793915f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[21] <= -0.04668513312935829f) {
                if (features[0] <= -0.3414929062128067f) {
                    return 0;                } else {
                    if (features[22] <= -0.05207817628979683f) {
                        if (features[17] <= -0.14593371003866196f) {
                            if (features[19] <= -0.35303452610969543f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            return 2;                        }
                    } else {
                        if (features[1] <= -0.19817234575748444f) {
                            return 1;                        } else {
                            if (features[9] <= -0.04915894381701946f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                if (features[16] <= 5.114441957324743f) {
                    if (features[18] <= 0.034388810861855745f) {
                        if (features[13] <= -0.20267563313245773f) {
                            return 1;                        } else {
                            if (features[9] <= 0.024064553901553154f) {
                                return 1;                            } else {
                                if (features[18] <= -0.33873124420642853f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            }
                        }
                    } else {
                        return 2;                    }
                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[19] <= -0.1934511959552765f) {
            if (features[1] <= 0.13263070210814476f) {
                if (features[2] <= -0.028086312115192413f) {
                    return 2;                } else {
                    return 1;                }
            } else {
                if (features[11] <= 1.3920353055000305f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[17] <= 1.0248449444770813f) {
                if (features[3] <= 1.9234626293182373f) {
                    return 2;                } else {
                    if (features[20] <= -0.051715776324272156f) {
                        return 0;                    } else {
                        return 0;                    }
                }
            } else {
                if (features[4] <= -0.04917309992015362f) {
                    if (features[12] <= 1.7512198090553284f) {
                        if (features[4] <= -0.06313348188996315f) {
                            return 2;                        } else {
                            return 0;                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[22] <= -0.04857934080064297f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 116
int predict_tree_116(const float* features) {
    // Max depth: 8
    if (features[17] <= -0.12956026196479797f) {
        if (features[17] <= -0.34377528727054596f) {
            if (features[10] <= -0.3142911046743393f) {
                if (features[22] <= 6.399320602416992f) {
                    return 0;                } else {
                    if (features[21] <= 12.292087078094482f) {
                        if (features[21] <= 11.498578548431396f) {
                            if (features[21] <= 7.811189413070679f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            return 1;                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[3] <= -0.1396835600025952f) {
                    return 1;                } else {
                    return 1;                }
            }
        } else {
            if (features[19] <= -0.328930526971817f) {
                if (features[8] <= -0.18428893387317657f) {
                    return 1;                } else {
                    if (features[13] <= 0.14934519678354263f) {
                        if (features[17] <= -0.34190183877944946f) {
                            return 1;                        } else {
                            if (features[20] <= -0.08236179500818253f) {
                                return 1;                            } else {
                                if (features[10] <= -0.3183119148015976f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        }
                    } else {
                        return 1;                    }
                }
            } else {
                if (features[17] <= -0.1416992023587227f) {
                    if (features[18] <= -0.11189455911517143f) {
                        if (features[17] <= -0.15394078940153122f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        return 1;                    }
                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[17] <= 0.949804276227951f) {
            if (features[17] <= -0.09825694561004639f) {
                if (features[27] <= -0.008402779814787209f) {
                    if (features[12] <= -0.028466655872762203f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    return 1;                }
            } else {
                if (features[1] <= -0.15913031995296478f) {
                    return 2;                } else {
                    if (features[2] <= -0.4672364294528961f) {
                        return 2;                    } else {
                        if (features[27] <= -0.07781131193041801f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[3] <= 1.4504098445177078f) {
                return 2;            } else {
                return 0;            }
        }
    }
}

// Tree 117
int predict_tree_117(const float* features) {
    // Max depth: 8
    if (features[0] <= -0.13170911371707916f) {
        if (features[1] <= -0.30885645747184753f) {
            if (features[13] <= -3.49600887298584f) {
                if (features[17] <= -0.5239345729351044f) {
                    return 1;                } else {
                    if (features[22] <= 13.290234088897705f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[20] <= 7.237483978271484f) {
                    return 0;                } else {
                    if (features[3] <= -0.19136159867048264f) {
                        if (features[10] <= -0.49190717935562134f) {
                            return 2;                        } else {
                            return 2;                        }
                    } else {
                        if (features[10] <= -0.49169614911079407f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            }
        } else {
            if (features[27] <= -0.07464341819286346f) {
                if (features[1] <= -0.3081732392311096f) {
                    return 0;                } else {
                    if (features[8] <= -0.08578091859817505f) {
                        return 1;                    } else {
                        if (features[1] <= -0.29320062696933746f) {
                            return 0;                        } else {
                            if (features[6] <= -0.4801207222044468f) {
                                return 1;                            } else {
                                if (features[28] <= -0.4720424022525549f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        }
                    }
                }
            } else {
                if (features[0] <= -0.3423656225204468f) {
                    return 0;                } else {
                    if (features[19] <= -0.38149313628673553f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            }
        }
    } else {
        if (features[3] <= 1.8876855373382568f) {
            return 2;        } else {
            if (features[0] <= 0.9688023328781128f) {
                return 0;            } else {
                return 0;            }
        }
    }
}

// Tree 118
int predict_tree_118(const float* features) {
    // Max depth: 8
    if (features[15] <= 0.7420355677604675f) {
        if (features[0] <= -0.34185226261615753f) {
            if (features[7] <= -0.5550342202186584f) {
                if (features[20] <= 7.173644065856934f) {
                    return 0;                } else {
                    if (features[3] <= -0.2032873034477234f) {
                        return 2;                    } else {
                        if (features[8] <= 0.14571243524551392f) {
                            if (features[19] <= -0.5195083916187286f) {
                                return 1;                            } else {
                                if (features[4] <= 15.237154006958008f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[27] <= 9.724195182323456f) {
                    if (features[25] <= -0.015940936282277107f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[22] <= -0.04603583365678787f) {
                if (features[1] <= -0.21160279214382172f) {
                    return 1;                } else {
                    if (features[3] <= 1.7724037915468216f) {
                        return 2;                    } else {
                        return 0;                    }
                }
            } else {
                if (features[3] <= -1.503188669681549f) {
                    return 2;                } else {
                    if (features[2] <= 1.4482856392860413f) {
                        if (features[10] <= -0.11356080695986748f) {
                            if (features[3] <= -1.495238184928894f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            if (features[1] <= -0.02057018829509616f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[31] <= 0.24120032787322998f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    } else {
        if (features[18] <= -0.10296984016895294f) {
            if (features[0] <= -0.3426993042230606f) {
                return 0;            } else {
                if (features[17] <= -0.1284310594201088f) {
                    if (features[17] <= -0.14796114712953568f) {
                        return 1;                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[4] <= -0.04918142780661583f) {
                if (features[2] <= -0.9731524139642715f) {
                    return 0;                } else {
                    if (features[10] <= -0.22863195836544037f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[20] <= -0.04285386577248573f) {
                    if (features[10] <= -0.08388222754001617f) {
                        return 1;                    } else {
                        if (features[26] <= -0.2039031684398651f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 119
int predict_tree_119(const float* features) {
    // Max depth: 7
    if (features[0] <= -0.1342502385377884f) {
        if (features[10] <= -0.3220328539609909f) {
            if (features[21] <= 5.94169807434082f) {
                if (features[1] <= -0.5099619328975677f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[4] <= 14.111091136932373f) {
                    if (features[8] <= -0.16090145707130432f) {
                        return 1;                    } else {
                        return 1;                    }
                } else {
                    if (features[28] <= 0.03530806303024292f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[27] <= -0.0769944041967392f) {
                if (features[17] <= -0.3388735204935074f) {
                    if (features[8] <= -0.09665514156222343f) {
                        return 1;                    } else {
                        return 0;                    }
                } else {
                    return 1;                }
            } else {
                if (features[9] <= 0.028738969936966896f) {
                    if (features[10] <= -0.32079994678497314f) {
                        return 1;                    } else {
                        if (features[2] <= -0.3468698114156723f) {
                            return 1;                        } else {
                            if (features[30] <= 0.23382475972175598f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    if (features[18] <= -0.33785928785800934f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            }
        }
    } else {
        if (features[1] <= 0.8183257281780243f) {
            return 2;        } else {
            if (features[2] <= -0.7803777381777763f) {
                return 0;            } else {
                return 2;            }
        }
    }
}

// Tree 120
int predict_tree_120(const float* features) {
    // Max depth: 8
    if (features[17] <= -0.09930915758013725f) {
        if (features[8] <= -0.2820924371480942f) {
            if (features[9] <= -0.05629235319793224f) {
                return 0;            } else {
                if (features[17] <= -0.3517310470342636f) {
                    if (features[9] <= 0.42697572708129883f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    if (features[0] <= -0.13478926569223404f) {
                        return 1;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[19] <= -0.35613398253917694f) {
                if (features[4] <= 6.761305093765259f) {
                    if (features[10] <= -0.3206111192703247f) {
                        return 0;                    } else {
                        if (features[10] <= -0.31339141726493835f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[4] <= 13.57824420928955f) {
                        return 1;                    } else {
                        if (features[22] <= 11.982985496520996f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[17] <= -0.34364697337150574f) {
                    return 0;                } else {
                    if (features[1] <= -0.3125849813222885f) {
                        return 0;                    } else {
                        if (features[28] <= 0.5426585469394922f) {
                            if (features[1] <= -0.29868602752685547f) {
                                if (features[6] <= 0.11694060638546944f) {
                                    return 1;                                } else {
                                    return 0;                                }
                            } else {
                                if (features[11] <= -0.36828793585300446f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        } else {
                            if (features[8] <= -0.27717818319797516f) {
                                return 1;                            } else {
                                if (features[7] <= -0.792737603187561f) {
                                    return 2;                                } else {
                                    return 1;                                }
                            }
                        }
                    }
                }
            }
        }
    } else {
        if (features[27] <= -0.06029519438743591f) {
            if (features[18] <= 0.9484290480613708f) {
                if (features[10] <= 1.1826556324958801f) {
                    if (features[0] <= 0.7895376980304718f) {
                        return 2;                    } else {
                        if (features[11] <= 0.5335945724509656f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    return 2;                }
            } else {
                if (features[4] <= -0.048392850905656815f) {
                    if (features[3] <= 1.3391033113002777f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[22] <= -0.04793730191886425f) {
                if (features[3] <= 1.8387901782989502f) {
                    return 2;                } else {
                    return 0;                }
            } else {
                return 2;            }
        }
    }
}

// Tree 121
int predict_tree_121(const float* features) {
    // Max depth: 10
    if (features[21] <= -0.07734093442559242f) {
        if (features[17] <= -0.3439292758703232f) {
            return 0;        } else {
            if (features[17] <= 0.029272466897964478f) {
                if (features[13] <= -0.0005496680678334087f) {
                    if (features[4] <= -0.08193065598607063f) {
                        if (features[10] <= -0.320844367146492f) {
                            return 1;                        } else {
                            if (features[3] <= 0.567907989025116f) {
                                return 1;                            } else {
                                if (features[10] <= -0.31723451614379883f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        }
                    } else {
                        return 1;                    }
                } else {
                    return 0;                }
            } else {
                return 2;            }
        }
    } else {
        if (features[26] <= -0.12413404509425163f) {
            if (features[17] <= -0.13972309231758118f) {
                if (features[17] <= -0.34185050427913666f) {
                    if (features[17] <= -0.5151062607765198f) {
                        if (features[6] <= -0.36070844903588295f) {
                            if (features[4] <= 13.378913402557373f) {
                                if (features[26] <= -0.29688867926597595f) {
                                    if (features[3] <= -0.19931206852197647f) {
                                        return 0;                                    } else {
                                        if (features[12] <= -0.002227360240794951f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    if (features[29] <= -0.008806705474853516f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                }
                            } else {
                                if (features[30] <= 0.23382475972175598f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            return 0;                        }
                    } else {
                        return 0;                    }
                } else {
                    return 1;                }
            } else {
                if (features[18] <= 0.7285167276859283f) {
                    if (features[2] <= -0.2142784371972084f) {
                        if (features[12] <= -0.3260151669383049f) {
                            return 2;                        } else {
                            return 2;                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[22] <= -0.030293578281998634f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[0] <= -0.1322738081216812f) {
                if (features[1] <= -0.30532315373420715f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                if (features[1] <= 0.9024026989936829f) {
                    if (features[1] <= 0.8204730451107025f) {
                        return 2;                    } else {
                        if (features[4] <= -0.04935421422123909f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[3] <= 1.7684285640716553f) {
                        return 2;                    } else {
                        return 0;                    }
                }
            }
        }
    }
}

// Tree 122
int predict_tree_122(const float* features) {
    // Max depth: 10
    if (features[0] <= -0.13170911371707916f) {
        if (features[22] <= -0.04599782079458237f) {
            if (features[19] <= -0.3562108278274536f) {
                if (features[11] <= 0.07504171505570412f) {
                    if (features[15] <= 0.7420355677604675f) {
                        if (features[12] <= -0.07508598268032074f) {
                            if (features[4] <= -0.07512366771697998f) {
                                if (features[4] <= -0.08342578262090683f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        } else {
                            if (features[3] <= 0.007400073576718569f) {
                                if (features[10] <= -0.529827356338501f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                if (features[0] <= -0.34542010724544525f) {
                                    if (features[28] <= -0.4720424022525549f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    return 1;                                }
                            }
                        }
                    } else {
                        if (features[12] <= -0.27149856090545654f) {
                            return 1;                        } else {
                            if (features[10] <= -0.4975830018520355f) {
                                return 0;                            } else {
                                return 0;                            }
                        }
                    }
                } else {
                    if (features[4] <= -0.08101717010140419f) {
                        if (features[13] <= -0.002348845941014588f) {
                            if (features[19] <= -0.4961472302675247f) {
                                return 0;                            } else {
                                if (features[17] <= -0.3782159984111786f) {
                                    if (features[1] <= -0.42920349538326263f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    if (features[1] <= -0.2944890111684799f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        } else {
                            return 0;                        }
                    } else {
                        return 0;                    }
                }
            } else {
                if (features[10] <= -0.3186229169368744f) {
                    return 0;                } else {
                    if (features[0] <= -0.3414929062128067f) {
                        return 0;                    } else {
                        if (features[10] <= -0.31724561750888824f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            }
        } else {
            if (features[17] <= -0.34231245517730713f) {
                if (features[16] <= 5.114441957324743f) {
                    if (features[10] <= -0.3195003867149353f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[20] <= 13.58247423171997f) {
                        if (features[10] <= -0.48939694464206696f) {
                            if (features[11] <= -0.017040157224982977f) {
                                return 0;                            } else {
                                if (features[21] <= 6.75391149520874f) {
                                    return 0;                                } else {
                                    if (features[27] <= 18.131539344787598f) {
                                        return 1;                                    } else {
                                        if (features[27] <= 20.405571937561035f) {
                                            return 2;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        } else {
                            if (features[18] <= -0.5176360011100769f) {
                                return 0;                            } else {
                                return 0;                            }
                        }
                    } else {
                        if (features[12] <= -0.025409650057554245f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[26] <= -0.3076953589916229f) {
                    return 1;                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[17] <= 1.0317742228507996f) {
            if (features[10] <= 0.8691978752613068f) {
                if (features[3] <= 0.6831897795200348f) {
                    return 2;                } else {
                    return 2;                }
            } else {
                if (features[11] <= 0.42220522463321686f) {
                    if (features[3] <= 1.4424593150615692f) {
                        return 2;                    } else {
                        if (features[21] <= -0.05116662010550499f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[21] <= -0.052433643490076065f) {
                        return 2;                    } else {
                        if (features[3] <= -1.2129966020584106f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[18] <= 2.1905810832977295f) {
                if (features[6] <= -0.12188391387462616f) {
                    return 2;                } else {
                    if (features[6] <= 1.3110632300376892f) {
                        if (features[7] <= 0.5944039225578308f) {
                            return 2;                        } else {
                            return 0;                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[20] <= -0.05021560750901699f) {
                    return 0;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 123
int predict_tree_123(const float* features) {
    // Max depth: 8
    if (features[10] <= -0.1128721609711647f) {
        if (features[0] <= -0.34185226261615753f) {
            if (features[7] <= -0.5195505023002625f) {
                if (features[16] <= 5.114441957324743f) {
                    return 0;                } else {
                    if (features[22] <= 16.578267097473145f) {
                        if (features[22] <= 6.399320602416992f) {
                            return 0;                        } else {
                            if (features[9] <= 13.232214450836182f) {
                                if (features[8] <= -0.17630131542682648f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            } else {
                                if (features[22] <= 11.521055698394775f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        }
                    } else {
                        if (features[8] <= -0.28633929789066315f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[4] <= 0.592946857213974f) {
                    return 0;                } else {
                    return 2;                }
            }
        } else {
            if (features[19] <= -0.14524319767951965f) {
                if (features[10] <= -0.15315816551446915f) {
                    return 1;                } else {
                    if (features[6] <= -0.36070844158530235f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[26] <= -0.1622837781906128f) {
                    if (features[2] <= 0.7712233662605286f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    if (features[10] <= -0.1547798290848732f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            }
        }
    } else {
        if (features[7] <= 1.918724775314331f) {
            if (features[26] <= -0.3096549063920975f) {
                if (features[13] <= -0.018513977993279696f) {
                    return 2;                } else {
                    return 1;                }
            } else {
                return 2;            }
        } else {
            if (features[3] <= 1.3311528414487839f) {
                return 2;            } else {
                return 0;            }
        }
    }
}

// Tree 124
int predict_tree_124(const float* features) {
    // Max depth: 8
    if (features[9] <= -0.07767258957028389f) {
        if (features[0] <= -0.3415699154138565f) {
            return 0;        } else {
            if (features[22] <= -0.07860850542783737f) {
                return 1;            } else {
                return 2;            }
        }
    } else {
        if (features[17] <= -0.12116822972893715f) {
            if (features[2] <= 0.22581204771995544f) {
                if (features[10] <= -0.322732612490654f) {
                    if (features[21] <= 6.56263542175293f) {
                        return 0;                    } else {
                        if (features[3] <= -0.21521300077438354f) {
                            return 2;                        } else {
                            if (features[4] <= 13.232214450836182f) {
                                if (features[20] <= 7.332235813140869f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            } else {
                                if (features[1] <= -0.4771861433982849f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                } else {
                    if (features[0] <= -0.07683113496750593f) {
                        if (features[0] <= -0.34192925691604614f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[1] <= -0.30901263654232025f) {
                    return 0;                } else {
                    if (features[0] <= -0.13042572140693665f) {
                        if (features[0] <= -0.3427506536245346f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[3] <= 1.8876855373382568f) {
                if (features[11] <= -4.685739517211914f) {
                    if (features[4] <= -0.05796485207974911f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    return 2;                }
            } else {
                return 0;            }
        }
    }
}

// Tree 125
int predict_tree_125(const float* features) {
    // Max depth: 10
    if (features[27] <= -0.07595403864979744f) {
        if (features[19] <= -0.3801611512899399f) {
            if (features[2] <= -1.8617966771125793f) {
                if (features[10] <= -0.31930047273635864f) {
                    if (features[3] <= -0.4855288714170456f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    return 1;                }
            } else {
                if (features[6] <= -0.4801207035779953f) {
                    if (features[0] <= -0.33114874362945557f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[21] <= -0.08362602069973946f) {
                        return 0;                    } else {
                        return 0;                    }
                }
            }
        } else {
            if (features[2] <= 0.00012461841106414795f) {
                if (features[0] <= 0.10784944891929626f) {
                    if (features[2] <= -0.3675578236579895f) {
                        return 0;                    } else {
                        if (features[13] <= -0.0005771364376414567f) {
                            if (features[9] <= -0.08245109766721725f) {
                                if (features[21] <= -0.08204589039087296f) {
                                    if (features[19] <= -0.3483213186264038f) {
                                        return 0;                                    } else {
                                        if (features[0] <= -0.34321266412734985f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    return 0;                                }
                            } else {
                                if (features[19] <= -0.35626205801963806f) {
                                    if (features[0] <= -0.3439826965332031f) {
                                        if (features[30] <= 0.23382475972175598f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[11] <= -0.26098285242915154f) {
                                        return 0;                                    } else {
                                        if (features[18] <= -0.3482714593410492f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[21] <= -0.06670944392681122f) {
                        return 2;                    } else {
                        return 0;                    }
                }
            } else {
                if (features[17] <= -0.1296629160642624f) {
                    if (features[22] <= -0.08046987652778625f) {
                        if (features[1] <= -0.3033124953508377f) {
                            if (features[4] <= -0.08211759477853775f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[20] <= 0.15753161162137985f) {
                            return 1;                        } else {
                            return 0;                        }
                    }
                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[17] <= -0.13138239085674286f) {
            if (features[6] <= 0.7140019237995148f) {
                if (features[10] <= -0.320211261510849f) {
                    if (features[27] <= 2.9142324924468994f) {
                        if (features[22] <= 1.5706894993782043f) {
                            return 0;                        } else {
                            return 2;                        }
                    } else {
                        if (features[10] <= -0.48955243825912476f) {
                            if (features[8] <= 0.17305199801921844f) {
                                if (features[20] <= 14.415037631988525f) {
                                    if (features[21] <= 6.75391149520874f) {
                                        return 0;                                    } else {
                                        if (features[8] <= -0.17630131542682648f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    if (features[12] <= -0.017002885229885578f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                }
                            } else {
                                if (features[19] <= -0.5191497802734375f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[20] <= 11.554230690002441f) {
                                return 0;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[13] <= 0.06235288828611374f) {
                        if (features[2] <= -0.28198467195034027f) {
                            if (features[13] <= -0.0034063778584823012f) {
                                return 0;                            } else {
                                return 1;                            }
                        } else {
                            if (features[22] <= -0.05149754323065281f) {
                                return 1;                            } else {
                                if (features[3] <= 0.7229420840740204f) {
                                    return 1;                                } else {
                                    return 0;                                }
                            }
                        }
                    } else {
                        if (features[17] <= -0.2178691029548645f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[29] <= -0.008806705474853516f) {
                    return 0;                } else {
                    return 0;                }
            }
        } else {
            if (features[2] <= -0.9750331491231918f) {
                return 0;            } else {
                if (features[21] <= -0.07746059447526932f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 126
int predict_tree_126(const float* features) {
    // Max depth: 9
    if (features[0] <= -0.13170911371707916f) {
        if (features[10] <= -0.32167741656303406f) {
            if (features[2] <= -0.24437010288238525f) {
                if (features[4] <= 6.761305093765259f) {
                    return 0;                } else {
                    if (features[7] <= -0.6849594712257385f) {
                        return 2;                    } else {
                        if (features[22] <= 17.1138858795166f) {
                            if (features[4] <= 13.232214450836182f) {
                                return 1;                            } else {
                                return 2;                            }
                        } else {
                            if (features[9] <= 15.793853759765625f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                return 0;            }
        } else {
            if (features[11] <= -0.4470030814409256f) {
                return 1;            } else {
                if (features[6] <= -1.1965942978858948f) {
                    if (features[0] <= -0.3290439695119858f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[18] <= -0.3346792012453079f) {
                        if (features[3] <= 0.7229420840740204f) {
                            if (features[22] <= -0.08183415234088898f) {
                                if (features[11] <= -0.00961419939994812f) {
                                    return 0;                                } else {
                                    if (features[19] <= -0.3718617856502533f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                if (features[21] <= 0.03018096834421158f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        } else {
                            return 0;                        }
                    } else {
                        if (features[12] <= -0.1950734406709671f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            }
        }
    } else {
        if (features[4] <= -0.06163668446242809f) {
            return 2;        } else {
            if (features[27] <= -0.061369651928544044f) {
                if (features[6] <= 0.11694060638546944f) {
                    return 2;                } else {
                    if (features[34] <= -2.0574225783348083f) {
                        return 2;                    } else {
                        if (features[1] <= 2.1852062940597534f) {
                            if (features[7] <= 1.5369973182678223f) {
                                return 2;                            } else {
                                return 0;                            }
                        } else {
                            if (features[22] <= -0.04822970740497112f) {
                                return 0;                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                if (features[3] <= 1.9115369319915771f) {
                    return 2;                } else {
                    return 0;                }
            }
        }
    }
}

// Tree 127
int predict_tree_127(const float* features) {
    // Max depth: 8
    if (features[22] <= -0.07712392508983612f) {
        if (features[4] <= -0.08251771330833435f) {
            return 0;        } else {
            if (features[9] <= -0.08211925998330116f) {
                if (features[1] <= -0.30545981228351593f) {
                    return 0;                } else {
                    if (features[8] <= -0.07603812590241432f) {
                        if (features[8] <= -0.09547554329037666f) {
                            return 1;                        } else {
                            if (features[26] <= -0.2706797271966934f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    } else {
                        return 1;                    }
                }
            } else {
                if (features[0] <= -0.33120007812976837f) {
                    if (features[10] <= -0.5264618694782257f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[1] <= 0.06309685856103897f) {
                        return 1;                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[17] <= -0.10192044079303741f) {
            if (features[0] <= -0.3414672315120697f) {
                if (features[27] <= 2.8197720050811768f) {
                    return 0;                } else {
                    if (features[3] <= -0.1834111362695694f) {
                        if (features[1] <= -0.4649074226617813f) {
                            if (features[22] <= 7.133705019950867f) {
                                return 0;                            } else {
                                return 2;                            }
                        } else {
                            return 0;                        }
                    } else {
                        if (features[9] <= 14.060916900634766f) {
                            if (features[20] <= 7.332235813140869f) {
                                return 0;                            } else {
                                return 1;                            }
                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[20] <= -0.04794536158442497f) {
                    if (features[10] <= -0.16863057017326355f) {
                        return 1;                    } else {
                        if (features[28] <= 0.03530806303024292f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[27] <= -0.013682824559509754f) {
                        return 1;                    } else {
                        if (features[3] <= -0.5252811908721924f) {
                            return 1;                        } else {
                            if (features[8] <= -0.11025786399841309f) {
                                if (features[20] <= 0.04112396575510502f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            } else {
                                return 1;                            }
                        }
                    }
                }
            }
        } else {
            if (features[20] <= -0.06589366868138313f) {
                return 2;            } else {
                if (features[10] <= 2.2829846143722534f) {
                    if (features[3] <= 1.8876855373382568f) {
                        if (features[26] <= -0.3085063099861145f) {
                            return 2;                        } else {
                            return 2;                        }
                    } else {
                        return 0;                    }
                } else {
                    if (features[27] <= -0.07314261049032211f) {
                        if (features[9] <= -0.04900697432458401f) {
                            return 0;                        } else {
                            return 2;                        }
                    } else {
                        if (features[0] <= 2.694250226020813f) {
                            if (features[22] <= -0.0492740124464035f) {
                                return 0;                            } else {
                                return 2;                            }
                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    }
}

// Tree 128
int predict_tree_128(const float* features) {
    // Max depth: 8
    if (features[4] <= -0.0776401162147522f) {
        if (features[19] <= -0.3767799288034439f) {
            if (features[1] <= -0.3045228123664856f) {
                if (features[6] <= -1.1965942978858948f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[13] <= -0.0018269470310769975f) {
                    return 1;                } else {
                    return 0;                }
            }
        } else {
            if (features[4] <= -0.081146240234375f) {
                if (features[22] <= -0.08198495209217072f) {
                    return 0;                } else {
                    if (features[13] <= -0.0005496680678334087f) {
                        if (features[26] <= -0.2996162623167038f) {
                            return 0;                        } else {
                            if (features[1] <= -0.30809515714645386f) {
                                return 0;                            } else {
                                if (features[8] <= -0.07603812590241432f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        }
                    } else {
                        return 0;                    }
                }
            } else {
                if (features[22] <= -0.07737163454294205f) {
                    if (features[19] <= -0.34314702451229095f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[21] <= -0.07043463364243507f) {
            if (features[18] <= -0.340193048119545f) {
                if (features[26] <= -0.18326056748628616f) {
                    return 0;                } else {
                    if (features[20] <= -0.07242827489972115f) {
                        if (features[18] <= -0.3694804906845093f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        return 0;                    }
                }
            } else {
                if (features[8] <= -0.16054745763540268f) {
                    return 2;                } else {
                    return 1;                }
            }
        } else {
            if (features[0] <= -0.1322481408715248f) {
                if (features[0] <= -0.3428276479244232f) {
                    if (features[9] <= 6.761305093765259f) {
                        return 0;                    } else {
                        if (features[4] <= 13.232214450836182f) {
                            return 1;                        } else {
                            if (features[4] <= 14.484671115875244f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    return 1;                }
            } else {
                if (features[9] <= -0.05010740086436272f) {
                    if (features[0] <= 0.45552124083042145f) {
                        return 2;                    } else {
                        if (features[21] <= -0.04851583577692509f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[27] <= -0.061374278739094734f) {
                        if (features[4] <= -0.0497189424932003f) {
                            if (features[15] <= 0.7420355677604675f) {
                                return 2;                            } else {
                                return 0;                            }
                        } else {
                            if (features[2] <= -0.6581303775310516f) {
                                return 0;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[2] <= -0.8367996066808701f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    }
}

// Tree 129
int predict_tree_129(const float* features) {
    // Max depth: 8
    if (features[27] <= -0.07635943219065666f) {
        if (features[0] <= -0.3415699154138565f) {
            return 0;        } else {
            if (features[1] <= -0.15616312623023987f) {
                return 1;            } else {
                if (features[9] <= -0.005204777233302593f) {
                    if (features[6] <= 0.23635287210345268f) {
                        if (features[2] <= -0.4136356711387634f) {
                            return 2;                        } else {
                            return 2;                        }
                    } else {
                        if (features[2] <= -0.8367995992302895f) {
                            return 0;                        } else {
                            if (features[12] <= -0.6289134323596954f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[0] <= -0.13686836510896683f) {
            if (features[3] <= -0.9943587481975555f) {
                if (features[20] <= -0.06121365539729595f) {
                    return 0;                } else {
                    if (features[1] <= -0.2989007532596588f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[17] <= -0.3413628935813904f) {
                    if (features[20] <= 7.332235813140869f) {
                        if (features[15] <= 0.7420355677604675f) {
                            return 0;                        } else {
                            if (features[22] <= -0.015066791791468859f) {
                                if (features[28] <= 0.03530806303024292f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[17] <= -0.5238575637340546f) {
                            return 1;                        } else {
                            if (features[20] <= 11.84300184249878f) {
                                return 1;                            } else {
                                if (features[17] <= -0.5219328105449677f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                } else {
                    if (features[12] <= -0.4803302437067032f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            }
        } else {
            if (features[6] <= 0.23635287210345268f) {
                return 2;            } else {
                if (features[20] <= -0.04854884557425976f) {
                    if (features[3] <= 1.81096351146698f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 130
int predict_tree_130(const float* features) {
    // Max depth: 7
    if (features[18] <= -0.11235618218779564f) {
        if (features[1] <= -0.3081732392311096f) {
            if (features[9] <= 6.487092971801758f) {
                return 0;            } else {
                if (features[27] <= 11.219933032989502f) {
                    return 2;                } else {
                    if (features[12] <= 0.005415152758359909f) {
                        if (features[21] <= 11.855807781219482f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        if (features[20] <= 12.498983383178711f) {
                            return 1;                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[10] <= -0.07023141533136368f) {
                if (features[0] <= -0.34192925691604614f) {
                    return 0;                } else {
                    if (features[22] <= -0.04687253013253212f) {
                        if (features[2] <= 0.7900306284427643f) {
                            if (features[1] <= -0.15575318038463593f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            return 2;                        }
                    } else {
                        if (features[13] <= 0.06632206216454506f) {
                            return 1;                        } else {
                            if (features[17] <= -0.19587530195713043f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[8] <= -0.21319157630205154f) {
            if (features[9] <= -0.010692439042031765f) {
                if (features[1] <= -0.18161852657794952f) {
                    return 1;                } else {
                    return 2;                }
            } else {
                return 1;            }
        } else {
            if (features[27] <= -0.0634336769580841f) {
                if (features[2] <= -0.9524644017219543f) {
                    return 0;                } else {
                    if (features[9] <= -0.06489257887005806f) {
                        if (features[6] <= 0.4751773923635483f) {
                            return 2;                        } else {
                            return 1;                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[3] <= 0.6911402344703674f) {
                    return 2;                } else {
                    if (features[18] <= 1.0745548605918884f) {
                        return 1;                    } else {
                        if (features[2] <= -1.6549165844917297f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                }
            }
        }
    }
}

// Tree 131
int predict_tree_131(const float* features) {
    // Max depth: 6
    if (features[0] <= -0.13294117897748947f) {
        if (features[1] <= -0.3081732392311096f) {
            if (features[4] <= 6.756311655044556f) {
                return 0;            } else {
                if (features[3] <= -0.21521300077438354f) {
                    return 2;                } else {
                    if (features[4] <= 13.608125686645508f) {
                        return 1;                    } else {
                        if (features[30] <= 0.23382475972175598f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[1] <= -0.2904481589794159f) {
                if (features[0] <= -0.34185226261615753f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                if (features[0] <= -0.33890044689178467f) {
                    return 0;                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[3] <= 1.8876855373382568f) {
            if (features[10] <= -0.14922620356082916f) {
                return 2;            } else {
                return 2;            }
        } else {
            if (features[7] <= 1.9274999499320984f) {
                return 0;            } else {
                return 0;            }
        }
    }
}

// Tree 132
int predict_tree_132(const float* features) {
    // Max depth: 10
    if (features[0] <= -0.13170911371707916f) {
        if (features[18] <= -0.3522721976041794f) {
            if (features[13] <= -0.1440856084227562f) {
                if (features[20] <= 14.415037631988525f) {
                    if (features[22] <= 9.717023849487305f) {
                        if (features[1] <= -0.3440333306789398f) {
                            if (features[25] <= -0.01594119891524315f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[4] <= 17.057092666625977f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[21] <= 6.472424745559692f) {
                    if (features[0] <= -0.34210893511772156f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[13] <= 10.341097354888916f) {
                        if (features[10] <= -0.49151842296123505f) {
                            return 2;                        } else {
                            return 2;                        }
                    } else {
                        if (features[4] <= 13.145212650299072f) {
                            return 1;                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[16] <= 5.114441957324743f) {
                if (features[21] <= -0.08272755891084671f) {
                    return 0;                } else {
                    if (features[20] <= -0.060261161997914314f) {
                        if (features[13] <= -0.0042304289527237415f) {
                            return 0;                        } else {
                            if (features[10] <= -0.3234656900167465f) {
                                return 0;                            } else {
                                if (features[4] <= -0.08151887729763985f) {
                                    if (features[1] <= -0.29950590431690216f) {
                                        if (features[18] <= -0.34462976455688477f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[0] <= -0.33995282649993896f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        }
                    } else {
                        if (features[19] <= -0.3396633416414261f) {
                            return 0;                        } else {
                            if (features[3] <= -1.487287700176239f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    }
                }
            } else {
                return 0;            }
        }
    } else {
        if (features[7] <= 1.918724775314331f) {
            if (features[4] <= -0.07786203175783157f) {
                return 2;            } else {
                return 2;            }
        } else {
            if (features[1] <= 2.2031853199005127f) {
                return 0;            } else {
                if (features[10] <= 2.6512012481689453f) {
                    if (features[0] <= 2.556208372116089f) {
                        if (features[19] <= 2.54610538482666f) {
                            return 0;                        } else {
                            return 2;                        }
                    } else {
                        return 0;                    }
                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 133
int predict_tree_133(const float* features) {
    // Max depth: 10
    if (features[1] <= -0.08752725273370743f) {
        if (features[19] <= -0.3613082617521286f) {
            if (features[4] <= 6.761305093765259f) {
                if (features[11] <= 0.07504171505570412f) {
                    if (features[10] <= -0.32404325902462006f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[17] <= -0.37806200981140137f) {
                        return 0;                    } else {
                        if (features[26] <= -0.17171873897314072f) {
                            return 0;                        } else {
                            if (features[4] <= -0.08120577782392502f) {
                                if (features[17] <= -0.36915670335292816f) {
                                    return 0;                                } else {
                                    if (features[12] <= 0.09330405294895172f) {
                                        return 1;                                    } else {
                                        if (features[22] <= -0.08112945780158043f) {
                                            return 1;                                        } else {
                                            return 0;                                        }
                                    }
                                }
                            } else {
                                return 1;                            }
                        }
                    }
                }
            } else {
                if (features[9] <= 13.57824420928955f) {
                    return 1;                } else {
                    if (features[17] <= -0.5215991735458374f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[0] <= -0.34185226261615753f) {
                return 0;            } else {
                if (features[20] <= -0.04794536158442497f) {
                    if (features[19] <= -0.12390565127134323f) {
                        if (features[0] <= -0.1322481408715248f) {
                            if (features[21] <= -0.08220473676919937f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            return 2;                        }
                    } else {
                        if (features[22] <= -0.060607630759477615f) {
                            if (features[26] <= -0.1894681677222252f) {
                                return 2;                            } else {
                                return 1;                            }
                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[17] <= -0.07954809628427029f) {
                        if (features[20] <= 0.0493748988956213f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[7] <= 1.9464809894561768f) {
            if (features[0] <= -0.12013289332389832f) {
                return 1;            } else {
                if (features[11] <= -0.06456628441810608f) {
                    if (features[3] <= 1.8876855373382568f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    if (features[2] <= -0.47193825244903564f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[1] <= 2.3250744342803955f) {
                if (features[8] <= -0.08420116733759642f) {
                    return 0;                } else {
                    return 2;                }
            } else {
                if (features[22] <= -0.04151441529393196f) {
                    return 0;                } else {
                    if (features[4] <= -0.023861639201641083f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 134
int predict_tree_134(const float* features) {
    // Max depth: 10
    if (features[17] <= -0.12116822972893715f) {
        if (features[1] <= -0.3088759779930115f) {
            if (features[22] <= 6.220737934112549f) {
                if (features[0] <= -0.5539204776287079f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[4] <= 13.695127487182617f) {
                    if (features[0] <= -0.5186784565448761f) {
                        return 1;                    } else {
                        if (features[7] <= -0.5785778760910034f) {
                            return 1;                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[0] <= -0.5229136645793915f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[21] <= -0.08275965973734856f) {
                return 1;            } else {
                if (features[12] <= 1.9764192700386047f) {
                    if (features[17] <= -0.393537238240242f) {
                        return 0;                    } else {
                        if (features[4] <= -0.048746753484010696f) {
                            if (features[0] <= -0.3414929062128067f) {
                                return 0;                            } else {
                                if (features[10] <= -0.14012935757637024f) {
                                    if (features[18] <= -0.18290764838457108f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[0] <= -0.1287573091685772f) {
                                if (features[10] <= -0.32007797062397003f) {
                                    return 0;                                } else {
                                    if (features[13] <= 0.051200730726122856f) {
                                        if (features[7] <= 1.2554377913475037f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[19] <= -0.3373067378997803f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[2] <= -0.9656295031309128f) {
            return 0;        } else {
            if (features[3] <= -1.4670140147209167f) {
                if (features[1] <= -0.04258988797664642f) {
                    return 1;                } else {
                    return 2;                }
            } else {
                return 2;            }
        }
    }
}

// Tree 135
int predict_tree_135(const float* features) {
    // Max depth: 9
    if (features[21] <= -0.07733343169093132f) {
        if (features[0] <= -0.3413645625114441f) {
            return 0;        } else {
            if (features[9] <= -0.07951954007148743f) {
                return 1;            } else {
                return 2;            }
        }
    } else {
        if (features[12] <= -0.18819518387317657f) {
            if (features[2] <= -0.9524644017219543f) {
                return 0;            } else {
                if (features[2] <= -0.1559758558869362f) {
                    if (features[10] <= -0.11220711469650269f) {
                        return 1;                    } else {
                        if (features[27] <= -0.07649868354201317f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[18] <= 0.005793795920908451f) {
                        return 1;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[10] <= -0.09856601804494858f) {
                if (features[18] <= -0.3493485748767853f) {
                    if (features[34] <= -2.0574225783348083f) {
                        if (features[1] <= -0.4649659991264343f) {
                            if (features[4] <= 13.145212650299072f) {
                                if (features[22] <= 4.732909083366394f) {
                                    return 0;                                } else {
                                    if (features[11] <= 0.02194611867889762f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                if (features[3] <= -0.2708662748336792f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[20] <= 5.9291346073150635f) {
                                return 0;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[17] <= -0.36027707159519196f) {
                            if (features[0] <= -0.35512256622314453f) {
                                return 0;                            } else {
                                return 1;                            }
                        } else {
                            if (features[0] <= -0.34300731122493744f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    if (features[0] <= -0.13478926569223404f) {
                        if (features[3] <= 0.7229420840740204f) {
                            if (features[2] <= -0.37225964665412903f) {
                                return 0;                            } else {
                                if (features[6] <= -0.9577697515487671f) {
                                    if (features[26] <= -0.2291036918759346f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[3] <= 0.7149916291236877f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        } else {
                            return 0;                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[0] <= 0.9494487345218658f) {
                    if (features[18] <= -0.3158552199602127f) {
                        return 1;                    } else {
                        return 2;                    }
                } else {
                    if (features[20] <= -0.04852135851979256f) {
                        if (features[9] <= -0.05445955879986286f) {
                            return 2;                        } else {
                            return 0;                        }
                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 136
int predict_tree_136(const float* features) {
    // Max depth: 7
    if (features[22] <= -0.0771949365735054f) {
        if (features[4] <= -0.08249939233064651f) {
            return 0;        } else {
            if (features[10] <= -0.32079994678497314f) {
                if (features[0] <= -0.550814688205719f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[0] <= 0.04101021587848663f) {
                    if (features[0] <= -0.3412362188100815f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[17] <= -0.13138239085674286f) {
            if (features[0] <= -0.3428276479244232f) {
                if (features[6] <= -0.5995329767465591f) {
                    if (features[4] <= 6.761305093765259f) {
                        return 0;                    } else {
                        if (features[20] <= 13.932217121124268f) {
                            if (features[7] <= -0.6581640541553497f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            if (features[7] <= -0.7407416999340057f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    return 0;                }
            } else {
                if (features[1] <= -0.0835840106010437f) {
                    if (features[0] <= -0.1322481408715248f) {
                        return 1;                    } else {
                        return 2;                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[7] <= 1.918724775314331f) {
                if (features[13] <= -0.0893239863216877f) {
                    if (features[10] <= -0.0027992771938443184f) {
                        return 1;                    } else {
                        return 2;                    }
                } else {
                    return 2;                }
            } else {
                if (features[3] <= 1.3311528414487839f) {
                    return 2;                } else {
                    return 0;                }
            }
        }
    }
}

// Tree 137
int predict_tree_137(const float* features) {
    // Max depth: 6
    if (features[15] <= 0.7420355677604675f) {
        if (features[17] <= -0.3438779413700104f) {
            if (features[16] <= 5.114441957324743f) {
                return 0;            } else {
                if (features[22] <= 13.974401950836182f) {
                    if (features[20] <= 7.332235813140869f) {
                        return 0;                    } else {
                        if (features[22] <= 11.256550312042236f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[26] <= -0.3051961809396744f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[18] <= -0.156800277531147f) {
                if (features[26] <= 0.09611405618488789f) {
                    if (features[0] <= -0.3412362188100815f) {
                        return 0;                    } else {
                        if (features[9] <= -0.08249606192111969f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                } else {
                    return 1;                }
            } else {
                if (features[7] <= 1.917502522468567f) {
                    return 2;                } else {
                    return 0;                }
            }
        }
    } else {
        if (features[0] <= -0.13481493294239044f) {
            if (features[0] <= -0.3415955752134323f) {
                return 0;            } else {
                return 1;            }
        } else {
            if (features[21] <= -0.048184799030423164f) {
                if (features[2] <= -0.9750331491231918f) {
                    return 0;                } else {
                    return 2;                }
            } else {
                if (features[4] <= -0.04964524693787098f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 138
int predict_tree_138(const float* features) {
    // Max depth: 10
    if (features[1] <= -0.07353068888187408f) {
        if (features[2] <= 0.7712233662605286f) {
            if (features[17] <= -0.3523726314306259f) {
                if (features[13] <= 2.1700005531311035f) {
                    if (features[8] <= -0.21015237271785736f) {
                        if (features[4] <= 0.5580925643444061f) {
                            return 0;                        } else {
                            return 2;                        }
                    } else {
                        if (features[13] <= -18.95891284942627f) {
                            if (features[19] <= -0.519098550081253f) {
                                return 1;                            } else {
                                return 2;                            }
                        } else {
                            if (features[13] <= -0.1423138976097107f) {
                                if (features[2] <= 0.18819747865200043f) {
                                    if (features[22] <= 14.744259357452393f) {
                                        if (features[12] <= -0.02540964912623167f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        return 2;                                    }
                                } else {
                                    if (features[0] <= -0.4014787971973419f) {
                                        if (features[34] <= -2.0574225783348083f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                if (features[11] <= 0.2673740088939667f) {
                                    return 0;                                } else {
                                    if (features[17] <= -0.3770354688167572f) {
                                        if (features[21] <= -0.08344841375946999f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        return 1;                                    }
                                }
                            }
                        }
                    }
                } else {
                    if (features[19] <= -0.5169980823993683f) {
                        if (features[26] <= -0.2923865020275116f) {
                            if (features[20] <= 9.809130668640137f) {
                                return 0;                            } else {
                                return 2;                            }
                        } else {
                            if (features[0] <= -0.5170870423316956f) {
                                return 0;                            } else {
                                return 0;                            }
                        }
                    } else {
                        if (features[12] <= 0.011274412740021944f) {
                            if (features[13] <= 8.399097919464111f) {
                                if (features[10] <= -0.4566638618707657f) {
                                    return 2;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[7] <= 1.2658986449241638f) {
                    if (features[19] <= -0.060661472380161285f) {
                        if (features[17] <= -0.11801159009337425f) {
                            if (features[12] <= -0.19048792868852615f) {
                                return 1;                            } else {
                                if (features[22] <= -0.058592960238456726f) {
                                    if (features[20] <= -0.07285808399319649f) {
                                        if (features[10] <= -0.3226437568664551f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 0;                                    }
                                } else {
                                    if (features[13] <= -0.023334676399827003f) {
                                        if (features[22] <= 0.03016994707286358f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 1;                                    }
                                }
                            }
                        } else {
                            if (features[1] <= -0.17045250535011292f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[10] <= -0.11551568657159805f) {
                            return 2;                        } else {
                            if (features[31] <= 0.24120032787322998f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[10] <= -0.31994467973709106f) {
                        return 0;                    } else {
                        return 0;                    }
                }
            }
        } else {
            if (features[0] <= -0.3504253327846527f) {
                return 0;            } else {
                if (features[18] <= -0.156800277531147f) {
                    if (features[1] <= -0.1950489804148674f) {
                        if (features[21] <= -0.04664385877549648f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[1] <= -0.18144283443689346f) {
                        return 1;                    } else {
                        if (features[10] <= -0.1475156843662262f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    } else {
        if (features[22] <= -0.06277978606522083f) {
            return 2;        } else {
            if (features[4] <= -0.04967314377427101f) {
                if (features[0] <= 0.6555255651473999f) {
                    return 2;                } else {
                    if (features[27] <= -0.053419508039951324f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[0] <= -0.10537384822964668f) {
                    return 1;                } else {
                    if (features[18] <= 1.3032637238502502f) {
                        if (features[22] <= -0.04916791059076786f) {
                            if (features[22] <= -0.04938303679227829f) {
                                if (features[20] <= -0.04957838915288448f) {
                                    return 0;                                } else {
                                    if (features[10] <= 0.5864071920514107f) {
                                        return 2;                                    } else {
                                        return 0;                                    }
                                }
                            } else {
                                return 0;                            }
                        } else {
                            if (features[3] <= 1.8876855373382568f) {
                                return 2;                            } else {
                                return 0;                            }
                        }
                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 139
int predict_tree_139(const float* features) {
    // Max depth: 8
    if (features[22] <= -0.07712935656309128f) {
        if (features[26] <= -0.26722539961338043f) {
            if (features[10] <= -0.3180231302976608f) {
                if (features[30] <= 0.23382475972175598f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[7] <= 0.39292147755622864f) {
                    return 1;                } else {
                    return 1;                }
            }
        } else {
            if (features[17] <= -0.3770354688167572f) {
                return 0;            } else {
                if (features[19] <= 0.03070831298828125f) {
                    if (features[19] <= -0.3697613328695297f) {
                        if (features[3] <= -0.27881672978401184f) {
                            if (features[27] <= -0.07746493071317673f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            if (features[12] <= -0.1611916348338127f) {
                                return 1;                            } else {
                                if (features[22] <= -0.0819619745016098f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            }
                        }
                    } else {
                        if (features[10] <= -0.32244381308555603f) {
                            return 0;                        } else {
                            if (features[20] <= -0.08186868205666542f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    if (features[8] <= -0.3184710890054703f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[17] <= -0.12116822972893715f) {
            if (features[0] <= -0.3414672315120697f) {
                if (features[1] <= -0.4643608331680298f) {
                    if (features[4] <= 6.756311655044556f) {
                        return 0;                    } else {
                        if (features[20] <= 13.932217121124268f) {
                            if (features[1] <= -0.46875306963920593f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            if (features[30] <= 0.23382475972175598f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    return 0;                }
            } else {
                if (features[12] <= 0.039806462824344635f) {
                    return 1;                } else {
                    if (features[1] <= -0.06837714463472366f) {
                        if (features[20] <= -0.047104066237807274f) {
                            if (features[0] <= -0.1322481408715248f) {
                                return 1;                            } else {
                                return 2;                            }
                        } else {
                            return 1;                        }
                    } else {
                        return 1;                    }
                }
            }
        } else {
            if (features[8] <= -0.21321126073598862f) {
                return 2;            } else {
                if (features[4] <= -0.04916852153837681f) {
                    if (features[2] <= -0.9731524139642715f) {
                        return 0;                    } else {
                        if (features[0] <= 0.44227658212184906f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[26] <= -0.13517270982265472f) {
                        if (features[21] <= -0.03577263653278351f) {
                            return 0;                        } else {
                            return 2;                        }
                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 140
int predict_tree_140(const float* features) {
    // Max depth: 8
    if (features[4] <= -0.0776638500392437f) {
        if (features[17] <= -0.3439292758703232f) {
            if (features[10] <= -0.31441326439380646f) {
                return 0;            } else {
                return 1;            }
        } else {
            if (features[0] <= 0.03236013650894165f) {
                if (features[17] <= -0.3358965367078781f) {
                    if (features[18] <= -0.330396369099617f) {
                        if (features[9] <= -0.08245234563946724f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        return 0;                    }
                } else {
                    return 1;                }
            } else {
                return 2;            }
        }
    } else {
        if (features[15] <= 0.7420355677604675f) {
            if (features[17] <= -0.15086115151643753f) {
                if (features[0] <= -0.34110789000988007f) {
                    if (features[9] <= 6.761305093765259f) {
                        return 0;                    } else {
                        if (features[21] <= 14.85464859008789f) {
                            if (features[0] <= -0.5203212201595306f) {
                                if (features[29] <= -0.008806705474853516f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            } else {
                                return 1;                            }
                        } else {
                            if (features[0] <= -0.5210912525653839f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    return 1;                }
            } else {
                if (features[22] <= -0.05424197390675545f) {
                    if (features[20] <= -0.07755975425243378f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    if (features[2] <= -0.8085886687040329f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[1] <= -0.0744091346859932f) {
                if (features[0] <= -0.3470371812582016f) {
                    return 0;                } else {
                    if (features[20] <= -0.07620077207684517f) {
                        return 2;                    } else {
                        if (features[11] <= -0.6805958449840546f) {
                            return 1;                        } else {
                            if (features[10] <= -0.1108950711786747f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    }
                }
            } else {
                if (features[21] <= -0.049031564965844154f) {
                    if (features[4] <= -0.05962027795612812f) {
                        return 2;                    } else {
                        if (features[19] <= 2.6918052434921265f) {
                            if (features[7] <= 0.9384034238755703f) {
                                return 2;                            } else {
                                return 0;                            }
                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[3] <= 1.8916608095169067f) {
                        return 2;                    } else {
                        return 0;                    }
                }
            }
        }
    }
}

// Tree 141
int predict_tree_141(const float* features) {
    // Max depth: 6
    if (features[0] <= -0.13170911371707916f) {
        if (features[17] <= -0.3441859185695648f) {
            if (features[20] <= 7.332235813140869f) {
                if (features[1] <= -0.3043666332960129f) {
                    return 0;                } else {
                    if (features[12] <= 0.36614176630973816f) {
                        if (features[19] <= -0.4527549147605896f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                }
            } else {
                if (features[9] <= 13.188183784484863f) {
                    return 1;                } else {
                    if (features[12] <= -0.025154899805784225f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[0] <= -0.34185226261615753f) {
                return 0;            } else {
                return 1;            }
        }
    } else {
        if (features[21] <= -0.06008998490869999f) {
            return 2;        } else {
            if (features[9] <= -0.04967314377427101f) {
                if (features[3] <= 1.3112766742706299f) {
                    return 2;                } else {
                    return 0;                }
            } else {
                if (features[20] <= -0.048755837604403496f) {
                    if (features[7] <= 1.143470510840416f) {
                        return 2;                    } else {
                        if (features[21] <= -0.050141410902142525f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[20] <= -0.04846804775297642f) {
                        if (features[26] <= -0.19857855886220932f) {
                            return 2;                        } else {
                            return 2;                        }
                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 142
int predict_tree_142(const float* features) {
    // Max depth: 8
    if (features[17] <= -0.10286999866366386f) {
        if (features[4] <= -0.055767329409718513f) {
            if (features[10] <= -0.3226437568664551f) {
                return 0;            } else {
                if (features[26] <= -0.28233306109905243f) {
                    if (features[8] <= -0.07853119820356369f) {
                        if (features[10] <= -0.28788915276527405f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        return 0;                    }
                } else {
                    if (features[27] <= -0.06738802045583725f) {
                        if (features[11] <= -0.11432019993662834f) {
                            return 1;                        } else {
                            if (features[8] <= -0.07089575752615929f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[17] <= -0.3606363534927368f) {
                if (features[20] <= 7.509936571121216f) {
                    if (features[12] <= 0.2423330545425415f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[20] <= 13.23633861541748f) {
                        if (features[8] <= 0.16239147633314133f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[1] <= -0.3033124953508377f) {
                    return 0;                } else {
                    if (features[22] <= -0.04763779602944851f) {
                        if (features[3] <= -0.7558447420597076f) {
                            return 2;                        } else {
                            if (features[17] <= -0.13138239085674286f) {
                                if (features[29] <= 0.49275785544887185f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[0] <= -0.1287573091685772f) {
                            if (features[20] <= 0.029001831077039242f) {
                                return 1;                            } else {
                                if (features[17] <= -0.33997705578804016f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            }
                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    } else {
        if (features[2] <= -0.9656295031309128f) {
            return 0;        } else {
            if (features[28] <= -0.4720424022525549f) {
                return 2;            } else {
                return 2;            }
        }
    }
}

// Tree 143
int predict_tree_143(const float* features) {
    // Max depth: 10
    if (features[21] <= -0.07734093442559242f) {
        if (features[6] <= 0.23635287210345268f) {
            if (features[17] <= -0.36915670335292816f) {
                if (features[21] <= -0.0837164930999279f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[17] <= 0.027424678206443787f) {
                    if (features[21] <= -0.0814075879752636f) {
                        if (features[7] <= -2.585624098777771f) {
                            return 0;                        } else {
                            if (features[3] <= -0.38614805042743683f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    } else {
                        return 0;                    }
                } else {
                    if (features[21] <= -0.07756982743740082f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[0] <= -0.3416982591152191f) {
                if (features[11] <= -0.19414924085140228f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                return 1;            }
        }
    } else {
        if (features[20] <= -0.07077151164412498f) {
            if (features[0] <= -0.1997804008424282f) {
                if (features[10] <= -0.32388776540756226f) {
                    return 0;                } else {
                    if (features[27] <= -0.0681784451007843f) {
                        return 1;                    } else {
                        return 0;                    }
                }
            } else {
                if (features[22] <= -0.07710136845707893f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[10] <= -0.07465210184454918f) {
                if (features[21] <= -0.0554200503975153f) {
                    return 0;                } else {
                    if (features[18] <= -0.3601967394351959f) {
                        if (features[6] <= -0.36070844903588295f) {
                            if (features[20] <= 13.932217121124268f) {
                                if (features[27] <= 11.763341903686523f) {
                                    return 0;                                } else {
                                    if (features[10] <= -0.48916368186473846f) {
                                        if (features[26] <= -0.2907668948173523f) {
                                            return 1;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        return 0;                                    }
                                }
                            } else {
                                if (features[3] <= -0.2708662748336792f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[11] <= 0.2651462256908417f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[20] <= -0.04836767539381981f) {
                            if (features[22] <= -0.04757722467184067f) {
                                if (features[9] <= -0.04927385784685612f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            } else {
                                return 1;                            }
                        } else {
                            if (features[3] <= 0.7229420840740204f) {
                                if (features[11] <= -0.6291711032390594f) {
                                    return 1;                                } else {
                                    if (features[17] <= -0.33933547139167786f) {
                                        return 0;                                    } else {
                                        if (features[10] <= -0.11329423636198044f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            } else {
                                if (features[27] <= -0.05562985874712467f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            }
                        }
                    }
                }
            } else {
                if (features[2] <= -0.9637487679719925f) {
                    return 0;                } else {
                    if (features[27] <= 0.009761057794094086f) {
                        return 2;                    } else {
                        if (features[0] <= -0.10047127678990364f) {
                            return 1;                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    }
}

// Tree 144
int predict_tree_144(const float* features) {
    // Max depth: 6
    if (features[17] <= -0.09930915758013725f) {
        if (features[0] <= -0.34192925691604614f) {
            if (features[8] <= -0.05490726977586746f) {
                if (features[21] <= 7.375215530395508f) {
                    if (features[7] <= -3.737254500389099f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[17] <= -0.5198796987533569f) {
                        return 1;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[21] <= 6.281148672103882f) {
                    if (features[26] <= -0.31034791469573975f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[21] <= 15.220935821533203f) {
                        if (features[4] <= 13.57824420928955f) {
                            return 1;                        } else {
                            return 2;                        }
                    } else {
                        if (features[28] <= 0.03530806303024292f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[19] <= -0.13169270008802414f) {
                if (features[27] <= -0.039656881242990494f) {
                    if (features[10] <= -0.15315816551446915f) {
                        return 1;                    } else {
                        return 2;                    }
                } else {
                    if (features[0] <= -0.13371121138334274f) {
                        return 1;                    } else {
                        if (features[2] <= -0.1315263845026493f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[26] <= -0.166021928191185f) {
                    return 2;                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[8] <= -0.21305333822965622f) {
            if (features[10] <= 1.6171159148216248f) {
                return 2;            } else {
                return 2;            }
        } else {
            if (features[22] <= -0.04814198613166809f) {
                if (features[22] <= -0.05980059504508972f) {
                    return 2;                } else {
                    if (features[9] <= -0.04871594160795212f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[20] <= -0.049473851919174194f) {
                    if (features[6] <= 1.3110633045434952f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 145
int predict_tree_145(const float* features) {
    // Max depth: 7
    if (features[20] <= -0.07756267115473747f) {
        if (features[10] <= -0.32188844680786133f) {
            if (features[33] <= -14.303120225667953f) {
                return 0;            } else {
                return 0;            }
        } else {
            if (features[10] <= 0.04044125974178314f) {
                if (features[20] <= -0.08299234881997108f) {
                    return 1;                } else {
                    if (features[18] <= -0.3342175781726837f) {
                        if (features[19] <= -0.3389461189508438f) {
                            if (features[22] <= -0.0818374939262867f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[0] <= -0.1342502385377884f) {
            if (features[19] <= -0.34911538660526276f) {
                if (features[21] <= 6.75391149520874f) {
                    if (features[0] <= -0.3435976803302765f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[1] <= -0.4691239595413208f) {
                        if (features[22] <= 16.18192481994629f) {
                            return 1;                        } else {
                            if (features[7] <= -0.6733314990997314f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[20] <= 13.842621326446533f) {
                            return 1;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[22] <= -0.05448341742157936f) {
                    if (features[11] <= 0.1563559416681528f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[10] <= -0.3188894987106323f) {
                        return 0;                    } else {
                        if (features[0] <= -0.33543528616428375f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            }
        } else {
            if (features[7] <= 1.918724775314331f) {
                return 2;            } else {
                if (features[21] <= -0.038934567011892796f) {
                    return 0;                } else {
                    if (features[3] <= -1.4395849108695984f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 146
int predict_tree_146(const float* features) {
    // Max depth: 10
    if (features[4] <= -0.07767258957028389f) {
        if (features[4] <= -0.08253103494644165f) {
            return 0;        } else {
            if (features[22] <= -0.08170925453305244f) {
                if (features[22] <= -0.08189806342124939f) {
                    if (features[1] <= -0.3056940734386444f) {
                        return 0;                    } else {
                        if (features[0] <= -0.3393881320953369f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[6] <= 0.23635287210345268f) {
                        if (features[11] <= 0.18717367202043533f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        if (features[13] <= -0.0008380858926102519f) {
                            if (features[19] <= -0.3502424508333206f) {
                                if (features[0] <= -0.3415185809135437f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            } else {
                                if (features[17] <= -0.33995141088962555f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            }
                        } else {
                            return 0;                        }
                    }
                }
            } else {
                if (features[0] <= -0.33120007812976837f) {
                    if (features[1] <= -0.5068385601043701f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[22] <= -0.07860850542783737f) {
                        return 1;                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[8] <= -0.3198172301054001f) {
            if (features[0] <= -0.13743306696414948f) {
                if (features[19] <= -0.5194827914237976f) {
                    if (features[10] <= -0.5008485317230225f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    return 1;                }
            } else {
                return 2;            }
        } else {
            if (features[20] <= -0.0731850266456604f) {
                if (features[7] <= -0.5096129477024078f) {
                    return 0;                } else {
                    if (features[3] <= 0.32820141315460205f) {
                        if (features[3] <= 0.1413654461503029f) {
                            if (features[18] <= -0.28951704129576683f) {
                                return 0;                            } else {
                                return 2;                            }
                        } else {
                            if (features[10] <= -0.12051394581794739f) {
                                return 0;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[10] <= -0.1599113829433918f) {
                            if (features[3] <= 0.4247995913028717f) {
                                return 1;                            } else {
                                return 0;                            }
                        } else {
                            if (features[17] <= 0.20606980100274086f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                if (features[1] <= -0.08430628851056099f) {
                    if (features[10] <= -0.3188894987106323f) {
                        if (features[4] <= 6.761305093765259f) {
                            return 0;                        } else {
                            if (features[11] <= -0.011841987259685993f) {
                                if (features[19] <= -0.516869992017746f) {
                                    if (features[17] <= -0.5192637741565704f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                if (features[27] <= 10.740880489349365f) {
                                    if (features[20] <= 16.84990882873535f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                } else {
                                    if (features[17] <= -0.5211628973484039f) {
                                        return 1;                                    } else {
                                        if (features[17] <= -0.5191867649555206f) {
                                            return 2;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        if (features[20] <= -0.04840515926480293f) {
                            if (features[2] <= 0.7900306284427643f) {
                                if (features[4] <= -0.04883418790996075f) {
                                    if (features[3] <= -0.7717456817626953f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 2;                                }
                            } else {
                                if (features[26] <= -0.21416398137807846f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[10] <= -0.1128721609711647f) {
                                if (features[11] <= -0.4529438465833664f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[9] <= -0.04916852153837681f) {
                        if (features[9] <= -0.05965733341872692f) {
                            return 2;                        } else {
                            if (features[0] <= 0.5270320177078247f) {
                                return 2;                            } else {
                                if (features[11] <= -3.125917136669159f) {
                                    return 2;                                } else {
                                    return 0;                                }
                            }
                        }
                    } else {
                        if (features[8] <= 0.28126396238803864f) {
                            if (features[2] <= -0.817992314696312f) {
                                return 0;                            } else {
                                return 2;                            }
                        } else {
                            return 1;                        }
                    }
                }
            }
        }
    }
}

// Tree 147
int predict_tree_147(const float* features) {
    // Max depth: 6
    if (features[1] <= -0.07353068888187408f) {
        if (features[0] <= -0.34192925691604614f) {
            if (features[20] <= 7.051158905029297f) {
                return 0;            } else {
                if (features[20] <= 13.23633861541748f) {
                    if (features[13] <= 18.209753036499023f) {
                        return 1;                    } else {
                        return 1;                    }
                } else {
                    if (features[2] <= -0.3007919490337372f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[10] <= -0.10146501287817955f) {
                if (features[6] <= -0.36070844158530235f) {
                    if (features[17] <= -0.13138239085674286f) {
                        if (features[27] <= -0.07196692004799843f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        if (features[10] <= -0.1542355716228485f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[12] <= -0.17724090814590454f) {
                        if (features[2] <= 0.15998654812574387f) {
                            return 1;                        } else {
                            return 2;                        }
                    } else {
                        return 1;                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[3] <= 1.8876855373382568f) {
            if (features[4] <= -0.07953161373734474f) {
                return 1;            } else {
                if (features[10] <= -0.07465210184454918f) {
                    return 1;                } else {
                    if (features[0] <= -0.10493749380111694f) {
                        return 1;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[9] <= -0.054111069068312645f) {
                return 0;            } else {
                return 0;            }
        }
    }
}

// Tree 148
int predict_tree_148(const float* features) {
    // Max depth: 10
    if (features[21] <= -0.07737887650728226f) {
        if (features[22] <= -0.0819665715098381f) {
            if (features[7] <= -2.5726723670959473f) {
                if (features[0] <= -0.35422419011592865f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                return 0;            }
        } else {
            if (features[0] <= -0.3412875682115555f) {
                if (features[6] <= -1.1965942978858948f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[0] <= 0.03259114921092987f) {
                    return 1;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[1] <= -0.07146146520972252f) {
            if (features[6] <= 0.7140019237995148f) {
                if (features[19] <= -0.35359805822372437f) {
                    if (features[17] <= -0.5146443247795105f) {
                        if (features[9] <= 13.232214450836182f) {
                            if (features[21] <= 8.017754793167114f) {
                                return 0;                            } else {
                                return 1;                            }
                        } else {
                            if (features[29] <= -0.008806705474853516f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[0] <= -0.34103088080883026f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[21] <= -0.07590464130043983f) {
                        return 2;                    } else {
                        if (features[20] <= -0.04729231633245945f) {
                            if (features[21] <= -0.05238236300647259f) {
                                if (features[27] <= -0.07048537582159042f) {
                                    if (features[15] <= 0.7420355677604675f) {
                                        if (features[17] <= -0.3471629023551941f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[28] <= 0.03530806303024292f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    return 0;                                }
                            } else {
                                if (features[8] <= -0.30631914734840393f) {
                                    return 2;                                } else {
                                    return 1;                                }
                            }
                        } else {
                            if (features[20] <= 1.2339768409729004f) {
                                if (features[18] <= -0.08427408337593079f) {
                                    if (features[17] <= -0.3413628935813904f) {
                                        return 0;                                    } else {
                                        if (features[1] <= -0.30378101766109467f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    return 2;                                }
                            } else {
                                return 0;                            }
                        }
                    }
                }
            } else {
                if (features[15] <= 0.7420355677604675f) {
                    return 0;                } else {
                    return 0;                }
            }
        } else {
            if (features[0] <= 0.9496540725231171f) {
                return 2;            } else {
                if (features[8] <= -0.16548050940036774f) {
                    if (features[7] <= 1.2897919118404388f) {
                        return 2;                    } else {
                        if (features[9] <= -0.04876840300858021f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[9] <= -0.050602862611413f) {
                        if (features[21] <= -0.052217261865735054f) {
                            return 2;                        } else {
                            return 0;                        }
                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 149
int predict_tree_149(const float* features) {
    // Max depth: 9
    if (features[21] <= -0.07734385505318642f) {
        if (features[7] <= 0.3678558021783829f) {
            if (features[12] <= 0.13279037177562714f) {
                if (features[10] <= -0.3161793351173401f) {
                    if (features[31] <= 0.24120032787322998f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[6] <= -1.1965942978858948f) {
                        return 2;                    } else {
                        if (features[6] <= -0.12188391387462616f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[26] <= 0.17196421325206757f) {
                    if (features[18] <= -0.5363574326038361f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[22] <= -0.08245447278022766f) {
                        return 0;                    } else {
                        if (features[1] <= -0.3013603985309601f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                }
            }
        } else {
            if (features[26] <= -0.2927909940481186f) {
                return 0;            } else {
                if (features[8] <= -0.17019599676132202f) {
                    return 0;                } else {
                    if (features[26] <= -0.2723449766635895f) {
                        if (features[7] <= 0.5494182407855988f) {
                            return 0;                        } else {
                            if (features[8] <= -0.14685709029436111f) {
                                if (features[17] <= -0.3967452049255371f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            } else {
                                if (features[4] <= -0.0829036720097065f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            }
                        }
                    } else {
                        if (features[17] <= -0.34444254636764526f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                }
            }
        }
    } else {
        if (features[10] <= -0.10146501287817955f) {
            if (features[10] <= -0.3220328539609909f) {
                if (features[7] <= -0.5195372104644775f) {
                    if (features[9] <= 6.761305093765259f) {
                        return 0;                    } else {
                        if (features[8] <= 0.19005953520536423f) {
                            if (features[20] <= 13.882895946502686f) {
                                return 1;                            } else {
                                if (features[20] <= 16.29111385345459f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[3] <= -0.26291580498218536f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    return 0;                }
            } else {
                if (features[6] <= -0.36070844158530235f) {
                    if (features[19] <= -0.10802416503429413f) {
                        if (features[17] <= -0.13138239085674286f) {
                            if (features[21] <= -0.048227325081825256f) {
                                if (features[18] <= -0.3431166708469391f) {
                                    return 0;                                } else {
                                    if (features[8] <= -0.30135294795036316f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                return 1;                            }
                        } else {
                            if (features[19] <= -0.17078165709972382f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[4] <= -0.04871719144284725f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[18] <= 0.014256895054131746f) {
                        if (features[10] <= -0.1128721609711647f) {
                            if (features[21] <= 0.030044634826481342f) {
                                return 1;                            } else {
                                if (features[21] <= 0.03088598232716322f) {
                                    return 1;                                } else {
                                    if (features[18] <= -0.3367052227258682f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        } else {
                            return 1;                        }
                    } else {
                        return 1;                    }
                }
            }
        } else {
            if (features[3] <= 1.8876855373382568f) {
                if (features[12] <= 2.169774889945984f) {
                    return 2;                } else {
                    if (features[8] <= 0.14421937614679337f) {
                        return 2;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[27] <= -0.07764431461691856f) {
                    return 0;                } else {
                    return 0;                }
            }
        }
    }
}

// Tree 150
int predict_tree_150(const float* features) {
    // Max depth: 10
    if (features[9] <= -0.07763345539569855f) {
        if (features[18] <= -0.3614277243614197f) {
            if (features[17] <= -0.3769328147172928f) {
                return 0;            } else {
                if (features[1] <= -0.30499130487442017f) {
                    return 0;                } else {
                    if (features[11] <= 0.45525074005126953f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            }
        } else {
            if (features[2] <= -0.38542474806308746f) {
                if (features[20] <= -0.08070044964551926f) {
                    return 0;                } else {
                    return 2;                }
            } else {
                if (features[3] <= -0.398073747754097f) {
                    return 0;                } else {
                    if (features[19] <= -0.35336752235889435f) {
                        if (features[0] <= -0.34210893511772156f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        if (features[1] <= -0.30264878273010254f) {
                            return 0;                        } else {
                            if (features[3] <= 0.567907989025116f) {
                                if (features[0] <= -0.3392341285943985f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            } else {
                                return 1;                            }
                        }
                    }
                }
            }
        }
    } else {
        if (features[4] <= -0.06989841535687447f) {
            if (features[10] <= -0.1300661861896515f) {
                if (features[17] <= -0.3413372337818146f) {
                    return 0;                } else {
                    if (features[19] <= -0.3449144810438156f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[1] <= -0.12410962581634521f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[21] <= -0.049335917457938194f) {
                if (features[13] <= 0.04143572598695755f) {
                    if (features[12] <= 2.2011090517044067f) {
                        if (features[2] <= 0.10356469452381134f) {
                            if (features[27] <= -0.07784682884812355f) {
                                if (features[12] <= -2.7199049592018127f) {
                                    return 2;                                } else {
                                    return 0;                                }
                            } else {
                                return 0;                            }
                        } else {
                            if (features[9] <= -0.05353400111198425f) {
                                return 1;                            } else {
                                return 2;                            }
                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[4] <= -0.05094677209854126f) {
                        if (features[6] <= 1.072238713502884f) {
                            return 2;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                }
            } else {
                if (features[21] <= -0.04133603535592556f) {
                    if (features[0] <= -0.1354823037981987f) {
                        if (features[18] <= -0.4272090941667557f) {
                            if (features[27] <= -0.07686963304877281f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[19] <= 1.1406449675559998f) {
                            return 2;                        } else {
                            if (features[7] <= 1.0234191194176674f) {
                                return 2;                            } else {
                                if (features[19] <= 1.1557068228721619f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            }
                        }
                    }
                } else {
                    if (features[1] <= 0.01675398414954543f) {
                        if (features[22] <= 15.93189811706543f) {
                            if (features[8] <= -0.14196016639471054f) {
                                if (features[21] <= 0.8138227760791779f) {
                                    if (features[18] <= -0.24653476476669312f) {
                                        return 0;                                    } else {
                                        return 2;                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                if (features[26] <= -0.2791913002729416f) {
                                    if (features[6] <= 0.23635287210345268f) {
                                        if (features[9] <= 13.145212650299072f) {
                                            return 1;                                        } else {
                                            return 2;                                        }
                                    } else {
                                        if (features[19] <= -0.3328752964735031f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    if (features[0] <= -0.13034871965646744f) {
                                        if (features[17] <= -0.382245197892189f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 2;                                    }
                                }
                            }
                        } else {
                            return 2;                        }
                    } else {
                        if (features[20] <= -0.04403834231197834f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    }
}

// Tree 151
int predict_tree_151(const float* features) {
    // Max depth: 7
    if (features[8] <= -0.2939704656600952f) {
        if (features[20] <= -0.04787706024944782f) {
            if (features[10] <= -0.16434317082166672f) {
                if (features[27] <= -0.07795123755931854f) {
                    return 1;                } else {
                    return 0;                }
            } else {
                if (features[12] <= -0.8951276242733002f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[10] <= -0.13131020218133926f) {
                if (features[0] <= -0.3345625773072243f) {
                    if (features[9] <= 0.18819039314985275f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    return 1;                }
            } else {
                return 2;            }
        }
    } else {
        if (features[0] <= -0.34210893511772156f) {
            if (features[20] <= 7.632521390914917f) {
                return 0;            } else {
                if (features[3] <= -0.21521300077438354f) {
                    return 2;                } else {
                    if (features[4] <= 13.695127487182617f) {
                        return 1;                    } else {
                        if (features[3] <= -0.19136159867048264f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[1] <= -0.04501049406826496f) {
                if (features[18] <= -0.07204106077551842f) {
                    if (features[11] <= -0.4488595873117447f) {
                        return 1;                    } else {
                        return 1;                    }
                } else {
                    if (features[0] <= -0.04726170934736729f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[9] <= -0.049112312495708466f) {
                    if (features[28] <= 0.5426585469394922f) {
                        if (features[10] <= 0.8379864990711212f) {
                            if (features[3] <= 0.20973945781588554f) {
                                return 2;                            } else {
                                return 2;                            }
                        } else {
                            if (features[7] <= 0.8870063796639442f) {
                                return 2;                            } else {
                                return 0;                            }
                        }
                    } else {
                        if (features[18] <= 0.7683445811271667f) {
                            return 2;                        } else {
                            if (features[3] <= 1.402707040309906f) {
                                return 2;                            } else {
                                return 0;                            }
                        }
                    }
                } else {
                    if (features[6] <= 0.4751773923635483f) {
                        if (features[3] <= 1.8916608095169067f) {
                            return 2;                        } else {
                            return 0;                        }
                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 152
int predict_tree_152(const float* features) {
    // Max depth: 10
    if (features[24] <= -0.01594116259366274f) {
        if (features[10] <= -0.1153935082256794f) {
            if (features[18] <= -0.35240042209625244f) {
                if (features[27] <= 2.930159330368042f) {
                    if (features[1] <= -0.30460087954998016f) {
                        if (features[34] <= -2.0574225783348083f) {
                            if (features[3] <= -0.24303964525461197f) {
                                return 2;                            } else {
                                return 0;                            }
                        } else {
                            return 0;                        }
                    } else {
                        if (features[18] <= -0.44436608254909515f) {
                            return 0;                        } else {
                            if (features[2] <= -0.3713192790746689f) {
                                return 1;                            } else {
                                if (features[12] <= 0.06146024726331234f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            }
                        }
                    }
                } else {
                    if (features[19] <= -0.5224285125732422f) {
                        if (features[13] <= -18.850028038024902f) {
                            return 1;                        } else {
                            return 0;                        }
                    } else {
                        if (features[3] <= -0.2072625383734703f) {
                            if (features[13] <= 8.446260690689087f) {
                                return 2;                            } else {
                                return 2;                            }
                        } else {
                            if (features[31] <= 0.24120032787322998f) {
                                if (features[19] <= -0.5195083916187286f) {
                                    return 1;                                } else {
                                    if (features[20] <= 15.490281105041504f) {
                                        return 0;                                    } else {
                                        return 2;                                    }
                                }
                            } else {
                                if (features[18] <= -0.5186361968517303f) {
                                    return 2;                                } else {
                                    if (features[22] <= 5.547876358032227f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                if (features[3] <= 0.7229420840740204f) {
                    if (features[7] <= -1.7110967636108398f) {
                        return 0;                    } else {
                        if (features[1] <= -0.3092859238386154f) {
                            return 0;                        } else {
                            if (features[20] <= -0.04794536158442497f) {
                                if (features[9] <= -0.048652658239006996f) {
                                    if (features[9] <= -0.04953782819211483f) {
                                        if (features[0] <= -0.3414929062128067f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[20] <= -0.048698777332901955f) {
                                            return 2;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    return 2;                                }
                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    return 0;                }
            }
        } else {
            if (features[17] <= 0.9494706392288208f) {
                if (features[27] <= 0.009923761710524559f) {
                    return 2;                } else {
                    if (features[27] <= 0.014273877255618572f) {
                        return 1;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[2] <= -0.7615704536437988f) {
                    return 0;                } else {
                    return 2;                }
            }
        }
    } else {
        return 0;    }
}

// Tree 153
int predict_tree_153(const float* features) {
    // Max depth: 8
    if (features[10] <= -0.1004764661192894f) {
        if (features[10] <= -0.3220328539609909f) {
            if (features[4] <= 7.0539209842681885f) {
                if (features[21] <= -0.08372358232736588f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[27] <= 12.022491455078125f) {
                    return 2;                } else {
                    if (features[13] <= 18.119739532470703f) {
                        if (features[4] <= 13.695127487182617f) {
                            return 1;                        } else {
                            return 2;                        }
                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[0] <= -0.1322481408715248f) {
                if (features[3] <= 0.7229420840740204f) {
                    if (features[22] <= -0.07213465869426727f) {
                        if (features[9] <= -0.07547631859779358f) {
                            if (features[3] <= 0.567907989025116f) {
                                if (features[0] <= -0.3417752683162689f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            } else {
                                return 1;                            }
                        } else {
                            return 0;                        }
                    } else {
                        if (features[7] <= 1.228622853755951f) {
                            if (features[10] <= -0.32071107625961304f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            if (features[0] <= -0.34085121750831604f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    return 0;                }
            } else {
                return 2;            }
        }
    } else {
        if (features[7] <= 1.918283224105835f) {
            if (features[10] <= -0.07465210184454918f) {
                if (features[26] <= -0.256854310631752f) {
                    return 1;                } else {
                    if (features[4] <= -0.07717171311378479f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                return 2;            }
        } else {
            if (features[20] <= -0.043262017890810966f) {
                return 0;            } else {
                if (features[10] <= 2.3603800535202026f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 154
int predict_tree_154(const float* features) {
    // Max depth: 8
    if (features[20] <= -0.077583909034729f) {
        if (features[3] <= 0.3095178157091141f) {
            if (features[10] <= -0.3203001171350479f) {
                if (features[10] <= -0.5298162400722504f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[6] <= -0.8383575081825256f) {
                    return 1;                } else {
                    if (features[22] <= -0.0809256099164486f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            }
        } else {
            if (features[1] <= -0.3082122802734375f) {
                if (features[30] <= 0.23382475972175598f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[0] <= 0.030845731496810913f) {
                    if (features[17] <= -0.34444254636764526f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[26] <= 0.010950110387057066f) {
            if (features[17] <= -0.12116822972893715f) {
                if (features[9] <= -0.04632273688912392f) {
                    if (features[10] <= -0.32457640767097473f) {
                        return 0;                    } else {
                        if (features[3] <= 0.4247995913028717f) {
                            if (features[4] <= -0.07384462654590607f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[17] <= -0.34185050427913666f) {
                        if (features[9] <= 6.761305093765259f) {
                            return 0;                        } else {
                            if (features[9] <= 13.57824420928955f) {
                                return 1;                            } else {
                                if (features[2] <= -0.3007919490337372f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        }
                    } else {
                        if (features[12] <= -1.0400806292891502f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[3] <= 1.8876855373382568f) {
                    if (features[12] <= -0.6470007300376892f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    if (features[19] <= 0.8764999806880951f) {
                        return 0;                    } else {
                        return 0;                    }
                }
            }
        } else {
            if (features[7] <= 2.0992778539657593f) {
                if (features[13] <= 0.2278497815132141f) {
                    if (features[13] <= -0.0032827703980728984f) {
                        if (features[4] <= -0.05009574443101883f) {
                            if (features[9] <= -0.051562145352363586f) {
                                if (features[22] <= -0.07648731768131256f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            } else {
                                return 0;                            }
                        } else {
                            return 2;                        }
                    } else {
                        if (features[1] <= -0.14179565757513046f) {
                            if (features[17] <= -0.2725841552019119f) {
                                if (features[10] <= -0.4993046075105667f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        } else {
                            if (features[4] <= -0.04929717443883419f) {
                                if (features[4] <= -0.05122073367238045f) {
                                    return 2;                                } else {
                                    return 0;                                }
                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[10] <= 0.21509171766228974f) {
                        return 1;                    } else {
                        if (features[22] <= -0.03636516164988279f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[10] <= 2.2496073246002197f) {
                    if (features[26] <= 3.070347547531128f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    if (features[20] <= -0.045110782608389854f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 155
int predict_tree_155(const float* features) {
    // Max depth: 9
    if (features[18] <= -0.10671412199735641f) {
        if (features[17] <= -0.3523726314306259f) {
            if (features[10] <= -0.3183119297027588f) {
                if (features[20] <= 6.873358488082886f) {
                    return 0;                } else {
                    if (features[20] <= 13.23633861541748f) {
                        if (features[13] <= 15.01750373840332f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        if (features[21] <= 13.163492679595947f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                return 1;            }
        } else {
            if (features[17] <= -0.13138239085674286f) {
                if (features[13] <= 0.39113547652959824f) {
                    if (features[10] <= -0.3222438842058182f) {
                        return 0;                    } else {
                        if (features[8] <= -0.09369833394885063f) {
                            if (features[26] <= 0.1886681765317917f) {
                                return 1;                            } else {
                                if (features[18] <= -0.2995445281267166f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[1] <= -0.30022817850112915f) {
                                return 0;                            } else {
                                if (features[0] <= -0.34185226261615753f) {
                                    return 0;                                } else {
                                    if (features[19] <= -0.23056776821613312f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        }
                    }
                } else {
                    return 2;                }
            } else {
                return 2;            }
        }
    } else {
        if (features[17] <= 1.0248706340789795f) {
            if (features[17] <= -0.09825694561004639f) {
                if (features[0] <= -0.12957868725061417f) {
                    return 1;                } else {
                    return 2;                }
            } else {
                if (features[17] <= 0.9432857036590576f) {
                    if (features[19] <= 0.8005762100219727f) {
                        if (features[9] <= -0.0677088014781475f) {
                            return 2;                        } else {
                            if (features[27] <= -0.07752268761396408f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[27] <= -0.07679126039147377f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[17] <= 0.9616096019744873f) {
                        return 0;                    } else {
                        if (features[3] <= 1.4822117239236832f) {
                            if (features[27] <= -0.07427464053034782f) {
                                return 2;                            } else {
                                return 2;                            }
                        } else {
                            return 0;                        }
                    }
                }
            }
        } else {
            if (features[9] <= -0.048484865576028824f) {
                if (features[21] <= -0.0606707576662302f) {
                    return 2;                } else {
                    if (features[19] <= 2.6435203552246094f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            } else {
                return 2;            }
        }
    }
}

// Tree 156
int predict_tree_156(const float* features) {
    // Max depth: 10
    if (features[4] <= -0.07766551524400711f) {
        if (features[11] <= 0.0334563534706831f) {
            if (features[7] <= 0.3677860200405121f) {
                if (features[10] <= -0.32545387744903564f) {
                    if (features[10] <= -0.529871791601181f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[2] <= -0.38542474806308746f) {
                        if (features[26] <= -0.11708429083228111f) {
                            return 2;                        } else {
                            return 1;                        }
                    } else {
                        if (features[9] <= -0.08151887729763985f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[17] <= -0.3395407795906067f) {
                    return 0;                } else {
                    return 1;                }
            }
        } else {
            if (features[8] <= -0.17110329121351242f) {
                if (features[12] <= 0.46014468371868134f) {
                    if (features[17] <= -0.40346910059452057f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    return 1;                }
            } else {
                if (features[19] <= -0.49583984911441803f) {
                    return 0;                } else {
                    if (features[10] <= -0.3180009126663208f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            }
        }
    } else {
        if (features[17] <= -0.09825694561004639f) {
            if (features[17] <= -0.34231245517730713f) {
                if (features[20] <= 7.051158905029297f) {
                    if (features[27] <= 0.06268145702779293f) {
                        if (features[10] <= -0.3199780136346817f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        if (features[1] <= -0.34516555070877075f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[8] <= 0.17305199801921844f) {
                        if (features[3] <= -0.21521300077438354f) {
                            return 2;                        } else {
                            if (features[27] <= 8.978099346160889f) {
                                return 2;                            } else {
                                if (features[21] <= 15.755089282989502f) {
                                    if (features[22] <= 11.718480110168457f) {
                                        return 1;                                    } else {
                                        if (features[20] <= 12.073167324066162f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    return 2;                                }
                            }
                        }
                    } else {
                        if (features[20] <= 14.719066143035889f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[20] <= -0.04805156588554382f) {
                    if (features[1] <= -0.18318020552396774f) {
                        return 1;                    } else {
                        if (features[20] <= -0.06020493805408478f) {
                            return 1;                        } else {
                            if (features[19] <= -0.19606395810842514f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[9] <= -0.03071484062820673f) {
                        return 1;                    } else {
                        if (features[2] <= 0.4138849228620529f) {
                            if (features[18] <= -0.18290764838457108f) {
                                return 1;                            } else {
                                if (features[30] <= 0.23382475972175598f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[3] <= 1.8876855373382568f) {
                if (features[26] <= -0.3094809502363205f) {
                    return 2;                } else {
                    return 2;                }
            } else {
                if (features[7] <= 1.9252211451530457f) {
                    return 0;                } else {
                    return 0;                }
            }
        }
    }
}

// Tree 157
int predict_tree_157(const float* features) {
    // Max depth: 6
    if (features[0] <= -0.1342502385377884f) {
        if (features[22] <= -0.04742141626775265f) {
            if (features[12] <= 0.05789374187588692f) {
                if (features[19] <= -0.3515232354402542f) {
                    if (features[0] <= -0.3426479697227478f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[10] <= -0.3187006711959839f) {
                        return 0;                    } else {
                        if (features[22] <= -0.08094565942883492f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[19] <= -0.46187396347522736f) {
                    if (features[0] <= -0.3326374739408493f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[1] <= -0.30483514070510864f) {
                        return 0;                    } else {
                        if (features[0] <= -0.33974748849868774f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            }
        } else {
            if (features[0] <= -0.34328965842723846f) {
                if (features[4] <= 7.171375513076782f) {
                    return 0;                } else {
                    if (features[21] <= 14.85464859008789f) {
                        if (features[22] <= 11.46861457824707f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        if (features[17] <= -0.5220097899436951f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                return 1;            }
        }
    } else {
        if (features[13] <= -0.0186375854536891f) {
            if (features[21] <= -0.04798717983067036f) {
                if (features[0] <= 0.8387686908245087f) {
                    if (features[13] <= -0.04356512613594532f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    return 0;                }
            } else {
                return 2;            }
        } else {
            if (features[0] <= 1.048578143119812f) {
                if (features[10] <= 0.8786945641040802f) {
                    return 2;                } else {
                    if (features[2] <= -0.8273959681391716f) {
                        return 0;                    } else {
                        if (features[12] <= -1.384503185749054f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[2] <= -0.7521668104454875f) {
                    return 0;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 158
int predict_tree_158(const float* features) {
    // Max depth: 7
    if (features[1] <= -0.06425821036100388f) {
        if (features[10] <= -0.3222438842058182f) {
            if (features[21] <= 6.281148672103882f) {
                return 0;            } else {
                if (features[22] <= 15.250558376312256f) {
                    if (features[22] <= 10.761457443237305f) {
                        if (features[20] <= 8.102927684783936f) {
                            return 1;                        } else {
                            if (features[20] <= 8.757321834564209f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[8] <= 0.1301920935511589f) {
                            return 1;                        } else {
                            return 2;                        }
                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[17] <= -0.13138239085674286f) {
                if (features[0] <= -0.34185226261615753f) {
                    return 0;                } else {
                    if (features[7] <= -0.11217788234353065f) {
                        if (features[11] <= 1.1243295073509216f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        return 1;                    }
                }
            } else {
                if (features[9] <= -0.025664975866675377f) {
                    return 2;                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[19] <= 0.9468396008014679f) {
            if (features[0] <= -0.10493749380111694f) {
                return 1;            } else {
                if (features[20] <= -0.06035112030804157f) {
                    return 2;                } else {
                    if (features[9] <= -0.050689881667494774f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[21] <= -0.047753287479281425f) {
                if (features[3] <= 1.3868061006069183f) {
                    return 2;                } else {
                    return 0;                }
            } else {
                return 2;            }
        }
    }
}

// Tree 159
int predict_tree_159(const float* features) {
    // Max depth: 7
    if (features[0] <= -0.13478926569223404f) {
        if (features[18] <= -0.35240042209625244f) {
            if (features[21] <= 6.087066411972046f) {
                if (features[17] <= -0.3440319299697876f) {
                    if (features[0] <= -0.3325861394405365f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    return 1;                }
            } else {
                if (features[4] <= 13.232214450836182f) {
                    if (features[20] <= 7.509936571121216f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[10] <= -0.3220328539609909f) {
                return 0;            } else {
                if (features[0] <= -0.34185226261615753f) {
                    return 0;                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[19] <= 0.9445854425430298f) {
            if (features[27] <= -0.07790148258209229f) {
                return 2;            } else {
                if (features[12] <= -0.40014752745628357f) {
                    if (features[19] <= 0.7951457798480988f) {
                        return 2;                    } else {
                        if (features[19] <= 0.8070056438446045f) {
                            return 2;                        } else {
                            if (features[20] <= -0.0737522728741169f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[3] <= 1.446434609591961f) {
                return 2;            } else {
                return 0;            }
        }
    }
}

// Tree 160
int predict_tree_160(const float* features) {
    // Max depth: 10
    if (features[18] <= -0.089890506118536f) {
        if (features[1] <= -0.30885645747184753f) {
            if (features[9] <= 6.761305093765259f) {
                if (features[5] <= -0.017767815850675106f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[7] <= -0.6849594712257385f) {
                    return 2;                } else {
                    if (features[21] <= 15.70427942276001f) {
                        if (features[4] <= 13.232214450836182f) {
                            return 1;                        } else {
                            return 2;                        }
                    } else {
                        if (features[29] <= -0.008806705474853516f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[20] <= -0.08352836221456528f) {
                return 0;            } else {
                if (features[0] <= -0.12714023143053055f) {
                    if (features[3] <= 0.7229420840740204f) {
                        if (features[1] <= -0.3082122802734375f) {
                            if (features[10] <= -0.3247096985578537f) {
                                return 0;                            } else {
                                return 1;                            }
                        } else {
                            if (features[1] <= -0.29770997166633606f) {
                                if (features[10] <= -0.3206000179052353f) {
                                    return 0;                                } else {
                                    if (features[26] <= -0.28146788477897644f) {
                                        return 1;                                    } else {
                                        if (features[2] <= -0.3468698114156723f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            } else {
                                if (features[17] <= -0.34811246395111084f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        }
                    } else {
                        return 0;                    }
                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[3] <= 1.8876855373382568f) {
            if (features[18] <= 0.0021777453366667032f) {
                if (features[10] <= -0.11478260904550552f) {
                    return 1;                } else {
                    return 2;                }
            } else {
                if (features[26] <= 2.5755695104599f) {
                    if (features[2] <= -0.21521880477666855f) {
                        if (features[8] <= -0.2559703290462494f) {
                            return 2;                        } else {
                            return 2;                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[22] <= -0.06990903615951538f) {
                        return 1;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[26] <= -0.30632951855659485f) {
                return 0;            } else {
                return 0;            }
        }
    }
}

// Tree 161
int predict_tree_161(const float* features) {
    // Max depth: 9
    if (features[4] <= -0.0776638500392437f) {
        if (features[4] <= -0.08253145217895508f) {
            return 0;        } else {
            if (features[10] <= -0.3186229169368744f) {
                if (features[15] <= 0.7420355677604675f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[22] <= -0.07855169475078583f) {
                    if (features[20] <= -0.08245092257857323f) {
                        return 1;                    } else {
                        if (features[17] <= -0.34803546965122223f) {
                            return 1;                        } else {
                            if (features[11] <= -0.11357760429382324f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[13] <= -19.152124404907227f) {
            if (features[20] <= 14.415037631988525f) {
                if (features[9] <= 5.4742196798324585f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                return 2;            }
        } else {
            if (features[10] <= -0.09856601804494858f) {
                if (features[18] <= -0.3523234874010086f) {
                    if (features[0] <= -0.33992716670036316f) {
                        if (features[16] <= 5.114441957324743f) {
                            return 0;                        } else {
                            if (features[9] <= 13.491242408752441f) {
                                if (features[20] <= 7.716284513473511f) {
                                    if (features[7] <= -0.686127632856369f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                if (features[1] <= -0.4766590744256973f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[17] <= -0.12116822972893715f) {
                        if (features[17] <= -0.3413628935813904f) {
                            return 0;                        } else {
                            if (features[9] <= -0.048746753484010696f) {
                                if (features[10] <= -0.1640988141298294f) {
                                    if (features[10] <= -0.3133469820022583f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 2;                                }
                            } else {
                                return 1;                            }
                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[2] <= -0.9656295031309128f) {
                    return 0;                } else {
                    if (features[27] <= -0.07789356634020805f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 162
int predict_tree_162(const float* features) {
    // Max depth: 10
    if (features[20] <= -0.07762181013822556f) {
        if (features[11] <= 0.0334563534706831f) {
            if (features[15] <= 0.7420355677604675f) {
                if (features[18] <= -0.3444758802652359f) {
                    if (features[33] <= -14.303120225667953f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[6] <= -0.4801207035779953f) {
                        return 2;                    } else {
                        if (features[10] <= -0.31976696848869324f) {
                            return 0;                        } else {
                            if (features[0] <= -0.33964481949806213f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    }
                }
            } else {
                if (features[0] <= -0.34639547765254974f) {
                    if (features[31] <= 0.24120032787322998f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    return 1;                }
            }
        } else {
            if (features[10] <= -0.32197731733322144f) {
                return 0;            } else {
                if (features[7] <= -0.07515044882893562f) {
                    return 1;                } else {
                    if (features[0] <= -0.3395164757966995f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            }
        }
    } else {
        if (features[10] <= -0.09877705574035645f) {
            if (features[22] <= -0.04559806175529957f) {
                if (features[1] <= -0.30460087954998016f) {
                    return 0;                } else {
                    if (features[18] <= -0.11220230907201767f) {
                        if (features[17] <= -0.13138239085674286f) {
                            if (features[3] <= 0.4247995913028717f) {
                                if (features[27] <= -0.06702940911054611f) {
                                    if (features[10] <= -0.16052227467298508f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 2;                                }
                            } else {
                                return 0;                            }
                        } else {
                            return 2;                        }
                    } else {
                        if (features[0] <= -0.1143576130270958f) {
                            return 1;                        } else {
                            if (features[26] <= -0.28648215532302856f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                if (features[4] <= 13.608125686645508f) {
                    if (features[7] <= 0.27762121334671974f) {
                        if (features[26] <= -0.27037516236305237f) {
                            if (features[18] <= -0.5265607237815857f) {
                                return 0;                            } else {
                                if (features[10] <= -0.5021369755268097f) {
                                    return 0;                                } else {
                                    if (features[6] <= 0.23635286465287209f) {
                                        if (features[7] <= -0.6604635417461395f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 0;                                    }
                                }
                            }
                        } else {
                            if (features[11] <= -0.4509481191635132f) {
                                return 1;                            } else {
                                if (features[6] <= 1.072238713502884f) {
                                    if (features[13] <= 0.07213162258267403f) {
                                        if (features[18] <= -0.3889969140291214f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 0;                                    }
                                } else {
                                    return 0;                                }
                            }
                        }
                    } else {
                        if (features[13] <= -0.058810070157051086f) {
                            if (features[19] <= -0.42158108949661255f) {
                                if (features[25] <= -0.015940936282277107f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                if (features[0] <= -0.3401068449020386f) {
                                    if (features[13] <= -1.0059879422187805f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    return 1;                                }
                            }
                        } else {
                            if (features[17] <= -0.3394894450902939f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[8] <= -0.21305333822965622f) {
                return 2;            } else {
                if (features[1] <= 2.04539692401886f) {
                    if (features[10] <= 0.9333533942699432f) {
                        if (features[17] <= -0.11683105677366257f) {
                            return 1;                        } else {
                            if (features[22] <= -0.04923934116959572f) {
                                if (features[4] <= -0.06163668446242809f) {
                                    return 2;                                } else {
                                    return 0;                                }
                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[4] <= -0.048392850905656815f) {
                            if (features[21] <= -0.056391892954707146f) {
                                return 2;                            } else {
                                return 0;                            }
                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[27] <= -0.07023181021213531f) {
                        if (features[4] <= -0.048486530780792236f) {
                            return 0;                        } else {
                            return 2;                        }
                    } else {
                        if (features[1] <= 2.14954149723053f) {
                            if (features[20] <= -0.050545044243335724f) {
                                return 0;                            } else {
                                return 2;                            }
                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    }
}

// Tree 163
int predict_tree_163(const float* features) {
    // Max depth: 9
    if (features[17] <= -0.09930915758013725f) {
        if (features[22] <= -0.04599573276937008f) {
            if (features[26] <= -0.23131448775529861f) {
                if (features[0] <= -0.3416982591152191f) {
                    if (features[7] <= -3.5252227783203125f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[1] <= -0.17763623595237732f) {
                        return 1;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[9] <= -0.08224749937653542f) {
                    if (features[8] <= -0.16870573163032532f) {
                        return 0;                    } else {
                        if (features[17] <= -0.34629033505916595f) {
                            return 0;                        } else {
                            if (features[18] <= -0.3561190515756607f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    if (features[10] <= -0.32356564700603485f) {
                        return 0;                    } else {
                        if (features[18] <= -0.12004990875720978f) {
                            if (features[8] <= -0.30321694910526276f) {
                                return 2;                            } else {
                                if (features[10] <= -0.1764834001660347f) {
                                    if (features[12] <= -0.5675185769796371f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 1;                                }
                            }
                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[3] <= -0.4696279466152191f) {
                if (features[1] <= -0.39353862404823303f) {
                    return 0;                } else {
                    if (features[9] <= 0.014231500681489706f) {
                        if (features[10] <= -0.1360641084611416f) {
                            if (features[19] <= -0.36563725769519806f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            return 1;                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[19] <= -0.33172260224819183f) {
                    if (features[27] <= 12.027545928955078f) {
                        if (features[20] <= 9.876328825950623f) {
                            if (features[3] <= 0.6434374153614044f) {
                                return 0;                            } else {
                                if (features[18] <= -0.4183613061904907f) {
                                    if (features[0] <= -0.4145951122045517f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[4] <= 0.014547097496688366f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                }
                            }
                        } else {
                            if (features[13] <= -11.527374267578125f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[20] <= 12.498983383178711f) {
                            if (features[8] <= -0.16936920583248138f) {
                                return 0;                            } else {
                                if (features[9] <= 6.57856559753418f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            }
                        } else {
                            if (features[31] <= 0.24120032787322998f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[1] <= -0.30711910128593445f) {
                        return 0;                    } else {
                        if (features[21] <= 0.04863557033240795f) {
                            return 1;                        } else {
                            if (features[26] <= -0.07103982754051685f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    }
                }
            }
        }
    } else {
        if (features[7] <= 1.9464809894561768f) {
            if (features[2] <= -1.012647733092308f) {
                return 0;            } else {
                if (features[6] <= -2.8683661222457886f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[22] <= -0.03975705988705158f) {
                return 0;            } else {
                if (features[22] <= -0.02958052698522806f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 164
int predict_tree_164(const float* features) {
    // Max depth: 9
    if (features[0] <= -0.1342502385377884f) {
        if (features[20] <= -0.05226636677980423f) {
            if (features[22] <= -0.08198495209217072f) {
                if (features[17] <= -0.34564873576164246f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                if (features[10] <= -0.3222438842058182f) {
                    if (features[8] <= -0.35939715802669525f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[20] <= -0.07538904622197151f) {
                        if (features[18] <= -0.2654869705438614f) {
                            if (features[17] <= -0.3395407795906067f) {
                                if (features[9] <= -0.0823969691991806f) {
                                    return 0;                                } else {
                                    if (features[27] <= -0.07728347927331924f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                return 1;                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[9] <= -0.07384462654590607f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                }
            }
        } else {
            if (features[6] <= 1.072238713502884f) {
                if (features[18] <= -0.36068400740623474f) {
                    if (features[9] <= 6.475581407546997f) {
                        if (features[15] <= 0.7420355677604675f) {
                            return 0;                        } else {
                            if (features[4] <= -0.009336682967841625f) {
                                return 0;                            } else {
                                if (features[13] <= -0.07880703825503588f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        }
                    } else {
                        if (features[20] <= 13.932217121124268f) {
                            if (features[13] <= 14.657215118408203f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            if (features[18] <= -0.5213802754878998f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[13] <= 1.0508844181895256f) {
                        if (features[10] <= -0.31892281770706177f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        return 0;                    }
                }
            } else {
                if (features[22] <= -0.05420897342264652f) {
                    return 0;                } else {
                    return 0;                }
            }
        }
    } else {
        if (features[1] <= 0.893930584192276f) {
            if (features[3] <= 1.9632149934768677f) {
                return 2;            } else {
                if (features[26] <= -0.23392026871442795f) {
                    return 0;                } else {
                    return 0;                }
            }
        } else {
            if (features[10] <= 2.0951387882232666f) {
                if (features[2] <= -0.7803777381777763f) {
                    return 0;                } else {
                    return 2;                }
            } else {
                if (features[4] <= -0.050145288929343224f) {
                    return 0;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 165
int predict_tree_165(const float* features) {
    // Max depth: 7
    if (features[17] <= -0.09825694561004639f) {
        if (features[19] <= -0.3829531967639923f) {
            if (features[4] <= 7.0539209842681885f) {
                if (features[10] <= -0.31339141726493835f) {
                    if (features[15] <= 0.7420355677604675f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[20] <= -0.08270206302404404f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[7] <= -0.6849594712257385f) {
                    return 2;                } else {
                    if (features[20] <= 14.415037631988525f) {
                        if (features[21] <= 11.552336692810059f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        if (features[30] <= 0.23382475972175598f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[0] <= -0.34185226261615753f) {
                if (features[1] <= -0.4840184897184372f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[22] <= -0.04748491011559963f) {
                    if (features[21] <= -0.053537651896476746f) {
                        if (features[0] <= -0.21158764511346817f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        if (features[4] <= -0.04823672026395798f) {
                            if (features[29] <= -0.008806705474853516f) {
                                return 2;                            } else {
                                return 2;                            }
                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[16] <= 5.114441957324743f) {
                        if (features[7] <= -0.792737603187561f) {
                            if (features[26] <= -0.04779954068362713f) {
                                return 2;                            } else {
                                return 1;                            }
                        } else {
                            if (features[18] <= -0.08427408337593079f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    } else {
                        return 1;                    }
                }
            }
        }
    } else {
        if (features[17] <= 1.0182493925094604f) {
            if (features[3] <= 1.9234626293182373f) {
                return 2;            } else {
                if (features[26] <= -0.2452961578965187f) {
                    return 0;                } else {
                    return 0;                }
            }
        } else {
            if (features[9] <= -0.048392850905656815f) {
                if (features[13] <= -0.033731453120708466f) {
                    return 2;                } else {
                    if (features[19] <= 0.6994726061820984f) {
                        return 2;                    } else {
                        if (features[8] <= -0.177724190056324f) {
                            return 0;                        } else {
                            if (features[7] <= 1.9274999499320984f) {
                                return 2;                            } else {
                                return 0;                            }
                        }
                    }
                }
            } else {
                return 2;            }
        }
    }
}

// Tree 166
int predict_tree_166(const float* features) {
    // Max depth: 10
    if (features[9] <= -0.0776713415980339f) {
        if (features[6] <= 0.23635287210345268f) {
            if (features[19] <= -0.38021238148212433f) {
                if (features[26] <= 0.014917654916644096f) {
                    if (features[10] <= -0.529871791601181f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[20] <= -0.08187034726142883f) {
                        if (features[18] <= -0.474038228392601f) {
                            return 0;                        } else {
                            if (features[1] <= -0.3073728680610657f) {
                                return 0;                            } else {
                                if (features[10] <= -0.3058495819568634f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        }
                    } else {
                        if (features[27] <= -0.07748953253030777f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                }
            } else {
                if (features[0] <= -0.3527097851037979f) {
                    if (features[20] <= -0.08345048129558563f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[28] <= 0.03530806303024292f) {
                        return 1;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[0] <= -0.3414929062128067f) {
                return 0;            } else {
                return 1;            }
        }
    } else {
        if (features[18] <= -0.089890506118536f) {
            if (features[6] <= 0.7140019237995148f) {
                if (features[22] <= 0.05469145439565182f) {
                    if (features[18] <= -0.3523234874010086f) {
                        if (features[30] <= 0.23382475972175598f) {
                            return 0;                        } else {
                            if (features[19] <= -0.3823896646499634f) {
                                if (features[15] <= 0.7420355677604675f) {
                                    return 0;                                } else {
                                    if (features[17] <= -0.36833547055721283f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                return 0;                            }
                        }
                    } else {
                        if (features[12] <= 2.2046756744384766f) {
                            if (features[6] <= -0.36070844158530235f) {
                                if (features[15] <= 0.7420355677604675f) {
                                    if (features[21] <= -0.06072620488703251f) {
                                        return 0;                                    } else {
                                        return 2;                                    }
                                } else {
                                    if (features[26] <= 0.1036276095546782f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                if (features[22] <= -0.07214217633008957f) {
                                    return 0;                                } else {
                                    if (features[0] <= -0.34321266412734985f) {
                                        return 0;                                    } else {
                                        if (features[27] <= -0.018145435489714146f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[0] <= -0.5145202875137329f) {
                        if (features[19] <= -0.5170749127864838f) {
                            if (features[4] <= 13.232214450836182f) {
                                if (features[9] <= 7.048927545547485f) {
                                    if (features[30] <= 0.23382475972175598f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                if (features[7] <= -0.7314606010913849f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[9] <= 13.30506706237793f) {
                                if (features[2] <= -0.3195992410182953f) {
                                    return 0;                                } else {
                                    if (features[13] <= 12.720585346221924f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                if (features[2] <= -0.3007919490337372f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        }
                    } else {
                        return 0;                    }
                }
            } else {
                if (features[9] <= -0.07710093632340431f) {
                    return 0;                } else {
                    return 0;                }
            }
        } else {
            if (features[11] <= -0.814216673374176f) {
                if (features[10] <= -0.046850645914673805f) {
                    return 0;                } else {
                    if (features[0] <= 2.4923208951950073f) {
                        if (features[17] <= 1.573997139930725f) {
                            return 2;                        } else {
                            if (features[9] <= -0.05101297236979008f) {
                                return 0;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[9] <= -0.04563949629664421f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[20] <= -0.06332147307693958f) {
                    if (features[2] <= -0.4296218603849411f) {
                        if (features[26] <= 0.8315562456846237f) {
                            return 2;                        } else {
                            return 2;                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[9] <= -0.049672311171889305f) {
                        if (features[8] <= -0.26632464677095413f) {
                            return 2;                        } else {
                            return 0;                        }
                    } else {
                        if (features[0] <= -0.12957868725061417f) {
                            return 1;                        } else {
                            if (features[20] <= -0.04960837587714195f) {
                                if (features[18] <= 0.6431163810193539f) {
                                    return 2;                                } else {
                                    return 0;                                }
                            } else {
                                if (features[21] <= -0.049318406730890274f) {
                                    if (features[2] <= -0.6299194544553757f) {
                                        return 0;                                    } else {
                                        return 2;                                    }
                                } else {
                                    if (features[1] <= 1.0076990127563477f) {
                                        return 2;                                    } else {
                                        if (features[21] <= -0.04774828255176544f) {
                                            return 0;                                        } else {
                                            return 2;                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

// Tree 167
int predict_tree_167(const float* features) {
    // Max depth: 5
    if (features[17] <= -0.10133017599582672f) {
        if (features[0] <= -0.3415699154138565f) {
            if (features[21] <= 7.811189413070679f) {
                return 0;            } else {
                if (features[9] <= 13.232214450836182f) {
                    if (features[0] <= -0.517549067735672f) {
                        return 1;                    } else {
                        return 1;                    }
                } else {
                    if (features[10] <= -0.4972497671842575f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[1] <= -0.0835840106010437f) {
                if (features[0] <= -0.12714023143053055f) {
                    if (features[31] <= 0.24120032787322998f) {
                        return 1;                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            } else {
                if (features[26] <= 0.6426395177841187f) {
                    if (features[2] <= -0.10331545397639275f) {
                        return 2;                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[27] <= -0.061841847375035286f) {
            if (features[9] <= -0.0681992694735527f) {
                return 2;            } else {
                if (features[2] <= 0.00012461841106414795f) {
                    return 0;                } else {
                    return 2;                }
            }
        } else {
            if (features[21] <= -0.048030123114585876f) {
                if (features[10] <= 0.8975769281387329f) {
                    return 2;                } else {
                    if (features[21] <= -0.062404314056038857f) {
                        return 2;                    } else {
                        return 0;                    }
                }
            } else {
                return 2;            }
        }
    }
}

// Tree 168
int predict_tree_168(const float* features) {
    // Max depth: 10
    if (features[9] <= -0.07770590111613274f) {
        if (features[18] <= -0.3481175899505615f) {
            if (features[1] <= -0.3045228123664856f) {
                return 0;            } else {
                if (features[10] <= -0.31339141726493835f) {
                    return 0;                } else {
                    return 1;                }
            }
        } else {
            if (features[7] <= -0.09259678423404694f) {
                if (features[22] <= -0.07927728071808815f) {
                    return 0;                } else {
                    return 2;                }
            } else {
                if (features[8] <= -0.12253183126449585f) {
                    return 1;                } else {
                    if (features[10] <= -0.3220217376947403f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            }
        }
    } else {
        if (features[15] <= 0.7420355677604675f) {
            if (features[17] <= -0.15083548426628113f) {
                if (features[1] <= -0.30885645747184753f) {
                    if (features[7] <= -0.517400324344635f) {
                        if (features[20] <= 7.332235813140869f) {
                            return 0;                        } else {
                            if (features[22] <= 16.578267097473145f) {
                                if (features[3] <= -0.21918823570013046f) {
                                    return 2;                                } else {
                                    if (features[21] <= 11.498578548431396f) {
                                        return 1;                                    } else {
                                        if (features[13] <= -7.265905141830444f) {
                                            return 1;                                        } else {
                                            return 2;                                        }
                                    }
                                }
                            } else {
                                if (features[7] <= -0.7314606010913849f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        }
                    } else {
                        if (features[27] <= 2.0355663299560547f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[17] <= -0.3394894450902939f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[18] <= 1.0374197959899902f) {
                    if (features[7] <= 1.615963637828827f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    if (features[9] <= -0.04656213894486427f) {
                        return 0;                    } else {
                        if (features[6] <= -1.196594387292862f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[10] <= -0.1004764661192894f) {
                if (features[10] <= -0.31605714559555054f) {
                    return 0;                } else {
                    if (features[9] <= -0.07550587877631187f) {
                        return 1;                    } else {
                        if (features[7] <= 0.06985331326723099f) {
                            return 1;                        } else {
                            if (features[0] <= -0.1342502385377884f) {
                                return 1;                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                if (features[20] <= -0.0484618004411459f) {
                    if (features[22] <= -0.06277978606522083f) {
                        return 2;                    } else {
                        if (features[3] <= 1.3112766742706299f) {
                            return 2;                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[27] <= -0.07783950120210648f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 169
int predict_tree_169(const float* features) {
    // Max depth: 8
    if (features[22] <= -0.07715734466910362f) {
        if (features[3] <= 0.3095178157091141f) {
            if (features[1] <= -0.3043666332960129f) {
                if (features[20] <= -0.08395484462380409f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[7] <= -2.5770103931427f) {
                    return 0;                } else {
                    if (features[0] <= -0.3416982591152191f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            }
        } else {
            if (features[19] <= -0.3802636116743088f) {
                if (features[17] <= -0.5538584887981415f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[19] <= -0.35613398253917694f) {
                    if (features[0] <= -0.340568870306015f) {
                        if (features[22] <= -0.0819619745016098f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[18] <= -0.3481175899505615f) {
                        return 0;                    } else {
                        if (features[6] <= -0.36070846021175385f) {
                            return 2;                        } else {
                            if (features[26] <= -0.3019617348909378f) {
                                return 0;                            } else {
                                if (features[0] <= -0.33995282649993896f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            }
                        }
                    }
                }
            }
        }
    } else {
        if (features[20] <= -0.07042333111166954f) {
            if (features[0] <= -0.11179082095623016f) {
                if (features[10] <= -0.3105035275220871f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                if (features[26] <= -0.3072061836719513f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[20] <= -0.04974581487476826f) {
                if (features[6] <= -0.0024716556072235107f) {
                    if (features[17] <= 0.1036202572286129f) {
                        return 1;                    } else {
                        if (features[22] <= -0.07220107689499855f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[20] <= -0.051628315821290016f) {
                        if (features[15] <= 0.7420355677604675f) {
                            return 0;                        } else {
                            if (features[6] <= 1.1916509866714478f) {
                                return 0;                            } else {
                                if (features[0] <= -0.4148004502058029f) {
                                    return 0;                                } else {
                                    return 2;                                }
                            }
                        }
                    } else {
                        if (features[6] <= 1.9081246256828308f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[0] <= -0.13170911371707916f) {
                    if (features[18] <= -0.3601967394351959f) {
                        if (features[21] <= 7.811189413070679f) {
                            if (features[17] <= -0.3515257388353348f) {
                                return 0;                            } else {
                                return 1;                            }
                        } else {
                            if (features[4] <= 13.232214450836182f) {
                                if (features[26] <= -0.2899303585290909f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[1] <= -0.3111794590950012f) {
                            return 0;                        } else {
                            if (features[21] <= 0.030073819682002068f) {
                                return 1;                            } else {
                                if (features[18] <= -0.336653932929039f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            }
                        }
                    }
                } else {
                    if (features[4] <= -0.04972643777728081f) {
                        if (features[17] <= 0.6431998834013939f) {
                            return 2;                        } else {
                            return 0;                        }
                    } else {
                        if (features[2] <= -0.817992314696312f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    }
}

// Tree 170
int predict_tree_170(const float* features) {
    // Max depth: 10
    if (features[4] <= -0.07770590111613274f) {
        if (features[17] <= -0.3439292758703232f) {
            if (features[10] <= -0.31527964770793915f) {
                return 0;            } else {
                return 1;            }
        } else {
            if (features[22] <= -0.078634824603796f) {
                if (features[13] <= -0.0005496680678334087f) {
                    if (features[10] <= -0.3186229169368744f) {
                        return 1;                    } else {
                        if (features[12] <= -0.09979677572846413f) {
                            return 1;                        } else {
                            if (features[13] <= -0.0012089088559150696f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    return 0;                }
            } else {
                return 2;            }
        }
    } else {
        if (features[26] <= 0.010404390282928944f) {
            if (features[21] <= -0.048100996762514114f) {
                if (features[8] <= -0.24244234710931778f) {
                    if (features[0] <= -0.12793593481183052f) {
                        if (features[19] <= -0.3768567591905594f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        if (features[29] <= -0.5103712691925466f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[20] <= -0.07252240180969238f) {
                        if (features[26] <= -0.18326056748628616f) {
                            return 0;                        } else {
                            if (features[20] <= -0.07578887045383453f) {
                                return 2;                            } else {
                                if (features[13] <= -0.008460556855425239f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        }
                    } else {
                        if (features[21] <= -0.04852917604148388f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                }
            } else {
                if (features[1] <= -0.10048920288681984f) {
                    if (features[22] <= 13.974401950836182f) {
                        if (features[18] <= -0.33765411376953125f) {
                            if (features[16] <= 5.114441957324743f) {
                                if (features[1] <= -0.29454757273197174f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            } else {
                                if (features[18] <= -0.5108398795127869f) {
                                    if (features[2] <= -0.3195992410182953f) {
                                        return 0;                                    } else {
                                        if (features[21] <= 6.75391149520874f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    return 0;                                }
                            }
                        } else {
                            if (features[10] <= -0.36088602244853973f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    } else {
                        return 2;                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[18] <= -0.3151371479034424f) {
                if (features[9] <= -0.050488363951444626f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                if (features[2] <= -0.9731524139642715f) {
                    return 0;                } else {
                    if (features[10] <= -0.17303043603897095f) {
                        return 1;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 171
int predict_tree_171(const float* features) {
    // Max depth: 10
    if (features[26] <= -0.1316431686282158f) {
        if (features[22] <= -0.0457062516361475f) {
            if (features[13] <= -0.00020631351071642712f) {
                if (features[8] <= -0.2958826720714569f) {
                    if (features[0] <= -0.19839433953166008f) {
                        if (features[19] <= -0.43082819879055023f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[3] <= 0.3095178157091141f) {
                        if (features[0] <= -0.34090255200862885f) {
                            if (features[3] <= -1.4316344261169434f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            if (features[7] <= 0.01765842316672206f) {
                                if (features[19] <= 0.0923643559217453f) {
                                    return 1;                                } else {
                                    if (features[31] <= 0.24120032787322998f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                }
                            } else {
                                if (features[27] <= -0.0759703628718853f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        }
                    } else {
                        if (features[17] <= -0.3523726314306259f) {
                            if (features[7] <= -3.806751012802124f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            if (features[0] <= 0.27066098153591156f) {
                                if (features[20] <= -0.07285808399319649f) {
                                    if (features[18] <= -0.3440655469894409f) {
                                        if (features[18] <= -0.34619414806365967f) {
                                            return 1;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        if (features[17] <= -0.3384115844964981f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    return 0;                                }
                            } else {
                                return 0;                            }
                        }
                    }
                }
            } else {
                if (features[19] <= -0.2063613012433052f) {
                    if (features[17] <= -0.3414142280817032f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[1] <= 0.618762418627739f) {
                        if (features[27] <= -0.07708058133721352f) {
                            return 2;                        } else {
                            return 2;                        }
                    } else {
                        return 0;                    }
                }
            }
        } else {
            if (features[19] <= -0.14670327305793762f) {
                if (features[26] <= -0.28463487327098846f) {
                    if (features[10] <= -0.31804534792900085f) {
                        if (features[21] <= 6.56263542175293f) {
                            return 0;                        } else {
                            if (features[7] <= -0.6301346123218536f) {
                                if (features[8] <= 0.029010399244725704f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            } else {
                                if (features[9] <= 14.618082046508789f) {
                                    return 1;                                } else {
                                    if (features[3] <= -0.1198073998093605f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                }
                            }
                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[17] <= -0.3413628935813904f) {
                        if (features[4] <= 6.475581407546997f) {
                            if (features[34] <= -2.0574225783348083f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[17] <= -0.33420273661613464f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[18] <= 0.0021777453366667032f) {
            if (features[27] <= -0.07515648752450943f) {
                if (features[10] <= -0.32268817722797394f) {
                    return 0;                } else {
                    if (features[0] <= -0.07739582937210798f) {
                        if (features[22] <= -0.08243734389543533f) {
                            return 0;                        } else {
                            if (features[10] <= -0.29246534407138824f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[0] <= -0.129886694252491f) {
                    if (features[17] <= -0.39517970383167267f) {
                        return 0;                    } else {
                        if (features[31] <= 0.24120032787322998f) {
                            return 1;                        } else {
                            if (features[13] <= 0.0027328016003593802f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    if (features[3] <= -1.077838659286499f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[7] <= 2.054752230644226f) {
                if (features[3] <= 1.8996112644672394f) {
                    return 2;                } else {
                    if (features[29] <= -0.008806705474853516f) {
                        return 0;                    } else {
                        return 0;                    }
                }
            } else {
                if (features[8] <= -0.13053115084767342f) {
                    return 0;                } else {
                    if (features[3] <= -1.2686498761177063f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 172
int predict_tree_172(const float* features) {
    // Max depth: 8
    if (features[17] <= -0.1317160204052925f) {
        if (features[18] <= -0.35237477719783783f) {
            if (features[16] <= 5.114441957324743f) {
                if (features[11] <= 0.2673740088939667f) {
                    if (features[7] <= -2.5726723670959473f) {
                        if (features[20] <= -0.08348254859447479f) {
                            if (features[11] <= 0.01934703439474106f) {
                                return 0;                            } else {
                                return 1;                            }
                        } else {
                            if (features[30] <= 0.23382475972175598f) {
                                return 0;                            } else {
                                return 0;                            }
                        }
                    } else {
                        if (features[20] <= -0.07318044453859329f) {
                            return 0;                        } else {
                            if (features[10] <= -0.3206111192703247f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    if (features[8] <= -0.14422956109046936f) {
                        if (features[8] <= -0.18780449777841568f) {
                            return 1;                        } else {
                            if (features[6] <= -0.9577697813510895f) {
                                return 0;                            } else {
                                return 0;                            }
                        }
                    } else {
                        if (features[20] <= -0.08114983513951302f) {
                            return 0;                        } else {
                            if (features[27] <= -0.07571783289313316f) {
                                return 0;                            } else {
                                if (features[1] <= -0.3356392830610275f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            }
                        }
                    }
                }
            } else {
                if (features[4] <= 13.57824420928955f) {
                    if (features[1] <= -0.4667814373970032f) {
                        if (features[7] <= -0.6604635417461395f) {
                            return 0;                        } else {
                            if (features[20] <= 7.716284513473511f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    } else {
                        return 0;                    }
                } else {
                    if (features[26] <= -0.3048498332500458f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[10] <= -0.3231102526187897f) {
                return 0;            } else {
                if (features[0] <= -0.3416982591152191f) {
                    return 0;                } else {
                    if (features[27] <= 0.12195323407649994f) {
                        if (features[1] <= -0.09154858067631721f) {
                            return 1;                        } else {
                            if (features[4] <= -0.05602338723838329f) {
                                return 2;                            } else {
                                return 1;                            }
                        }
                    } else {
                        return 1;                    }
                }
            }
        }
    } else {
        if (features[17] <= 0.9489573836326599f) {
            if (features[7] <= -0.8111158013343811f) {
                if (features[9] <= 0.022251327522099018f) {
                    return 1;                } else {
                    return 2;                }
            } else {
                if (features[3] <= 1.9234626293182373f) {
                    if (features[7] <= -0.4864022880792618f) {
                        if (features[7] <= -0.71625155210495f) {
                            return 2;                        } else {
                            return 2;                        }
                    } else {
                        return 2;                    }
                } else {
                    return 0;                }
            }
        } else {
            if (features[21] <= -0.048030123114585876f) {
                if (features[22] <= -0.06389802508056164f) {
                    return 2;                } else {
                    return 0;                }
            } else {
                return 2;            }
        }
    }
}

// Tree 173
int predict_tree_173(const float* features) {
    // Max depth: 8
    if (features[21] <= -0.07745100557804108f) {
        if (features[17] <= -0.34382662177085876f) {
            if (features[12] <= 0.641781747341156f) {
                return 0;            } else {
                return 1;            }
        } else {
            if (features[22] <= -0.0787864588201046f) {
                if (features[0] <= -0.3415699154138565f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                return 2;            }
        }
    } else {
        if (features[10] <= -0.1004764661192894f) {
            if (features[20] <= -0.04626402258872986f) {
                if (features[0] <= -0.33995282649993896f) {
                    return 0;                } else {
                    if (features[2] <= 0.7900306284427643f) {
                        if (features[19] <= -0.10728131979703903f) {
                            if (features[0] <= -0.12177563831210136f) {
                                return 1;                            } else {
                                return 2;                            }
                        } else {
                            if (features[10] <= -0.15070346742868423f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[9] <= 13.232214450836182f) {
                    if (features[21] <= 0.0036293385783210397f) {
                        if (features[10] <= -0.32071107625961304f) {
                            return 0;                        } else {
                            if (features[2] <= -0.15033367276191711f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[1] <= -0.29638253152370453f) {
                            if (features[16] <= 5.114441957324743f) {
                                return 0;                            } else {
                                if (features[22] <= 6.220737934112549f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            }
                        } else {
                            return 1;                        }
                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[1] <= 0.8513162136077881f) {
                if (features[3] <= 1.9234626293182373f) {
                    return 2;                } else {
                    if (features[17] <= 0.9537564814090729f) {
                        return 0;                    } else {
                        return 0;                    }
                }
            } else {
                if (features[17] <= 2.1901315450668335f) {
                    if (features[3] <= 1.8717845976352692f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    if (features[8] <= -0.16589505970478058f) {
                        if (features[3] <= 1.5537659227848053f) {
                            if (features[21] <= -0.04611770436167717f) {
                                return 2;                            } else {
                                return 2;                            }
                        } else {
                            return 0;                        }
                    } else {
                        if (features[13] <= -0.012580811977386475f) {
                            if (features[10] <= 2.5466264486312866f) {
                                if (features[7] <= 1.6550596356391907f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            } else {
                                return 2;                            }
                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    }
}

// Tree 174
int predict_tree_174(const float* features) {
    // Max depth: 7
    if (features[17] <= -0.12116822972893715f) {
        if (features[19] <= -0.3828251212835312f) {
            if (features[27] <= 2.6237025260925293f) {
                if (features[0] <= -0.34205760061740875f) {
                    if (features[4] <= 1.5966901779174805f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    return 1;                }
            } else {
                if (features[20] <= 13.932217121124268f) {
                    if (features[20] <= 7.332235813140869f) {
                        return 0;                    } else {
                        if (features[12] <= 0.003631899686297402f) {
                            return 1;                        } else {
                            if (features[1] <= -0.4725206196308136f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[0] <= -0.34185226261615753f) {
                if (features[8] <= -0.2564416378736496f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[10] <= -0.033633013255894184f) {
                    if (features[1] <= -0.06837714463472366f) {
                        if (features[21] <= -0.04830445535480976f) {
                            if (features[0] <= -0.1322481408715248f) {
                                return 1;                            } else {
                                return 2;                            }
                        } else {
                            return 1;                        }
                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[17] <= 0.9494706392288208f) {
            if (features[13] <= 0.021219010464847088f) {
                if (features[12] <= -3.363914132118225f) {
                    return 2;                } else {
                    if (features[18] <= 0.8016840815544128f) {
                        return 2;                    } else {
                        if (features[27] <= -0.07544571906328201f) {
                            return 2;                        } else {
                            if (features[6] <= -2.8683661222457886f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                if (features[7] <= 0.06919432245194912f) {
                    return 2;                } else {
                    if (features[1] <= -0.04501049220561981f) {
                        return 1;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[2] <= -0.7521668104454875f) {
                return 0;            } else {
                return 2;            }
        }
    }
}

// Tree 175
int predict_tree_175(const float* features) {
    // Max depth: 10
    if (features[1] <= -0.06462910771369934f) {
        if (features[9] <= -0.05137520097196102f) {
            if (features[7] <= 0.3678558021783829f) {
                if (features[27] <= -0.07797317206859589f) {
                    if (features[4] <= -0.061661247164011f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[26] <= -0.18567485362291336f) {
                        if (features[8] <= -0.2990015298128128f) {
                            if (features[17] <= -0.26016290858387947f) {
                                return 0;                            } else {
                                if (features[4] <= -0.07723958045244217f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[26] <= -0.22656605392694473f) {
                                if (features[1] <= -0.5096105635166168f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                if (features[10] <= -0.3271532952785492f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            }
                        }
                    } else {
                        if (features[2] <= 0.3010411858558655f) {
                            if (features[0] <= -0.3417495936155319f) {
                                return 0;                            } else {
                                if (features[11] <= 0.9798946380615234f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        } else {
                            if (features[0] <= -0.18404598161578178f) {
                                return 0;                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                if (features[0] <= -0.34187793731689453f) {
                    return 0;                } else {
                    if (features[7] <= 0.3697815537452698f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            }
        } else {
            if (features[6] <= 1.072238713502884f) {
                if (features[10] <= -0.31994467973709106f) {
                    if (features[3] <= -0.0959559977054596f) {
                        if (features[21] <= 6.56263542175293f) {
                            return 0;                        } else {
                            if (features[11] <= -0.011841987259685993f) {
                                return 2;                            } else {
                                if (features[17] <= -0.5210602283477783f) {
                                    if (features[4] <= 14.474074840545654f) {
                                        return 1;                                    } else {
                                        return 2;                                    }
                                } else {
                                    if (features[21] <= 11.498578548431396f) {
                                        return 1;                                    } else {
                                        if (features[12] <= -0.02770240418612957f) {
                                            return 2;                                        } else {
                                            return 2;                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        return 0;                    }
                } else {
                    if (features[12] <= -0.20246120542287827f) {
                        if (features[17] <= -0.05821513384580612f) {
                            return 1;                        } else {
                            return 2;                        }
                    } else {
                        if (features[17] <= -0.12091159075498581f) {
                            if (features[20] <= -0.04871460422873497f) {
                                return 1;                            } else {
                                if (features[3] <= 0.7189668715000153f) {
                                    if (features[20] <= -0.048457635566592216f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 0;                                }
                            }
                        } else {
                            if (features[2] <= 0.7712233662605286f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                if (features[8] <= -0.38734279572963715f) {
                    return 0;                } else {
                    return 0;                }
            }
        }
    } else {
        if (features[2] <= -0.9637487679719925f) {
            return 0;        } else {
            if (features[10] <= -0.06934283301234245f) {
                return 1;            } else {
                return 2;            }
        }
    }
}

// Tree 176
int predict_tree_176(const float* features) {
    // Max depth: 7
    if (features[0] <= -0.13170911371707916f) {
        if (features[4] <= -0.05115703120827675f) {
            if (features[10] <= -0.3222438842058182f) {
                return 0;            } else {
                if (features[27] <= -0.06760673597455025f) {
                    if (features[0] <= -0.3416982591152191f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    return 0;                }
            }
        } else {
            if (features[18] <= -0.3601967394351959f) {
                if (features[2] <= -0.26317739486694336f) {
                    if (features[20] <= 7.332235813140869f) {
                        return 0;                    } else {
                        if (features[9] <= 13.232214450836182f) {
                            return 1;                        } else {
                            if (features[17] <= -0.5220097899436951f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[10] <= -0.31550177931785583f) {
                        if (features[7] <= -0.5953164398670197f) {
                            if (features[26] <= -0.30540136992931366f) {
                                return 2;                            } else {
                                return 0;                            }
                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                }
            } else {
                if (features[18] <= -0.33873124420642853f) {
                    if (features[21] <= 0.02392256259918213f) {
                        return 1;                    } else {
                        if (features[17] <= -0.3585062623023987f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[11] <= -0.5361145734786987f) {
                        return 1;                    } else {
                        if (features[11] <= -0.34675265848636627f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            }
        }
    } else {
        if (features[18] <= 0.9534812867641449f) {
            if (features[18] <= 0.9489676058292389f) {
                if (features[20] <= -0.06035112030804157f) {
                    return 2;                } else {
                    if (features[22] <= -0.05323568359017372f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                return 2;            }
        } else {
            if (features[20] <= -0.0484618004411459f) {
                if (features[12] <= -1.317503809928894f) {
                    if (features[27] <= -0.0649179257452488f) {
                        return 0;                    } else {
                        if (features[2] <= -0.6863413453102112f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[1] <= 0.8220347166061401f) {
                        return 2;                    } else {
                        return 0;                    }
                }
            } else {
                return 2;            }
        }
    }
}

// Tree 177
int predict_tree_177(const float* features) {
    // Max depth: 10
    if (features[19] <= -0.06555399484932423f) {
        if (features[18] <= -0.35237477719783783f) {
            if (features[1] <= -0.30434711277484894f) {
                if (features[2] <= -0.24437010288238525f) {
                    if (features[9] <= 7.0539209842681885f) {
                        return 0;                    } else {
                        if (features[21] <= 15.70427942276001f) {
                            if (features[18] <= -0.521867573261261f) {
                                return 1;                            } else {
                                if (features[27] <= 18.131539344787598f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[31] <= 0.24120032787322998f) {
                        return 0;                    } else {
                        return 0;                    }
                }
            } else {
                if (features[10] <= -0.3206111192703247f) {
                    return 0;                } else {
                    if (features[21] <= -0.08269253745675087f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            }
        } else {
            if (features[18] <= -0.10671412199735641f) {
                if (features[10] <= -0.31994467973709106f) {
                    return 0;                } else {
                    if (features[10] <= -0.09598913416266441f) {
                        if (features[2] <= -0.2537737488746643f) {
                            if (features[3] <= 0.4208243489265442f) {
                                return 1;                            } else {
                                return 0;                            }
                        } else {
                            if (features[7] <= 1.2658986449241638f) {
                                if (features[1] <= -0.16984735429286957f) {
                                    if (features[20] <= -0.08241885527968407f) {
                                        if (features[26] <= -0.25885502994060516f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[0] <= -0.12354672327637672f) {
                                        return 1;                                    } else {
                                        return 2;                                    }
                                }
                            } else {
                                return 0;                            }
                        }
                    } else {
                        if (features[2] <= 0.7900306284427643f) {
                            return 2;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[0] <= 0.9496540725231171f) {
            if (features[10] <= -0.2084500789642334f) {
                if (features[11] <= -1.0043211877346039f) {
                    return 1;                } else {
                    return 0;                }
            } else {
                return 2;            }
        } else {
            if (features[4] <= -0.048392850905656815f) {
                if (features[27] <= -0.05147404782474041f) {
                    if (features[22] <= -0.05604945495724678f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    if (features[0] <= 1.407415509223938f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                return 2;            }
        }
    }
}

// Tree 178
int predict_tree_178(const float* features) {
    // Max depth: 7
    if (features[0] <= -0.1322481408715248f) {
        if (features[20] <= -0.05226636677980423f) {
            if (features[17] <= -0.3439292758703232f) {
                return 0;            } else {
                if (features[1] <= -0.3129753917455673f) {
                    return 0;                } else {
                    if (features[8] <= -0.09547554329037666f) {
                        return 1;                    } else {
                        if (features[19] <= -0.33879242837429047f) {
                            if (features[2] <= -0.9966615326702595f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            return 1;                        }
                    }
                }
            }
        } else {
            if (features[20] <= 13.23633861541748f) {
                if (features[18] <= -0.33785928785800934f) {
                    if (features[4] <= 6.871181488037109f) {
                        if (features[0] <= -0.34439338743686676f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[16] <= 5.114441957324743f) {
                        return 1;                    } else {
                        return 0;                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[3] <= 1.8876855373382568f) {
            if (features[0] <= -0.12406008318066597f) {
                return 2;            } else {
                return 2;            }
        } else {
            if (features[21] <= -0.056391892954707146f) {
                return 0;            } else {
                return 0;            }
        }
    }
}

// Tree 179
int predict_tree_179(const float* features) {
    // Max depth: 9
    if (features[9] <= -0.07767258957028389f) {
        if (features[0] <= -0.3414929062128067f) {
            return 0;        } else {
            if (features[2] <= -0.26317738369107246f) {
                return 2;            } else {
                if (features[22] <= -0.08195779845118523f) {
                    return 1;                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[26] <= 0.010404390282928944f) {
            if (features[0] <= -0.1342502385377884f) {
                if (features[10] <= -0.3220328539609909f) {
                    if (features[9] <= 7.437852382659912f) {
                        return 0;                    } else {
                        if (features[8] <= 0.15700668096542358f) {
                            if (features[17] <= -0.519186794757843f) {
                                if (features[4] <= 13.695127487182617f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            } else {
                                if (features[7] <= -0.6849594712257385f) {
                                    if (features[18] <= -0.519533783197403f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                } else {
                                    if (features[21] <= 13.552465438842773f) {
                                        return 1;                                    } else {
                                        return 2;                                    }
                                }
                            }
                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[0] <= -0.34192925691604614f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[19] <= 0.9908210933208466f) {
                    if (features[1] <= 0.8387056291103363f) {
                        return 2;                    } else {
                        if (features[7] <= 1.6232175827026367f) {
                            return 2;                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[3] <= 1.3748804032802582f) {
                        return 2;                    } else {
                        if (features[11] <= -0.5680462121963501f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                }
            }
        } else {
            if (features[10] <= -0.11710957810282707f) {
                if (features[17] <= -0.30304698646068573f) {
                    if (features[26] <= 0.4156236797571182f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[21] <= -0.048484982922673225f) {
                        return 2;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[7] <= 2.100879192352295f) {
                    if (features[27] <= 0.009923761710524559f) {
                        if (features[21] <= -0.05000841245055199f) {
                            if (features[4] <= -0.051311083137989044f) {
                                return 2;                            } else {
                                if (features[21] <= -0.05071968026459217f) {
                                    return 2;                                } else {
                                    return 0;                                }
                            }
                        } else {
                            return 2;                        }
                    } else {
                        if (features[0] <= -0.070195984095335f) {
                            return 1;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[1] <= 2.3250744342803955f) {
                        return 0;                    } else {
                        if (features[10] <= 2.6894102096557617f) {
                            if (features[20] <= -0.015424339566379786f) {
                                return 2;                            } else {
                                return 2;                            }
                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    }
}

// Tree 180
int predict_tree_180(const float* features) {
    // Max depth: 7
    if (features[17] <= -0.12091159075498581f) {
        if (features[19] <= -0.35626205801963806f) {
            if (features[21] <= 6.56263542175293f) {
                if (features[12] <= 0.058403242379426956f) {
                    if (features[17] <= -0.3433903306722641f) {
                        if (features[11] <= -0.25244300812482834f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[20] <= -0.009689793922007084f) {
                        if (features[1] <= -0.2912875711917877f) {
                            return 0;                        } else {
                            if (features[20] <= -0.08238553628325462f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[26] <= -0.03756431583315134f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[7] <= -0.6849594712257385f) {
                    return 2;                } else {
                    if (features[4] <= 13.57824420928955f) {
                        if (features[4] <= 7.630112409591675f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        if (features[26] <= -0.3029572516679764f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[1] <= -0.3082122802734375f) {
                return 0;            } else {
                if (features[18] <= -0.33455097675323486f) {
                    if (features[26] <= -0.26666635274887085f) {
                        return 0;                    } else {
                        if (features[26] <= -0.20238173007965088f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[17] <= -0.14231512695550919f) {
                        if (features[12] <= -0.3833340108394623f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        if (features[19] <= -0.13458723202347755f) {
                            return 2;                        } else {
                            return 1;                        }
                    }
                }
            }
        }
    } else {
        if (features[8] <= -0.21319157630205154f) {
            return 2;        } else {
            if (features[20] <= -0.04910193383693695f) {
                if (features[3] <= 1.630090393126011f) {
                    return 2;                } else {
                    return 0;                }
            } else {
                if (features[9] <= -0.048543987795710564f) {
                    if (features[7] <= 0.8886180371046066f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 181
int predict_tree_181(const float* features) {
    // Max depth: 9
    if (features[17] <= -0.10328061878681183f) {
        if (features[17] <= -0.3438779413700104f) {
            if (features[34] <= -2.0574225783348083f) {
                if (features[19] <= -0.5134119391441345f) {
                    if (features[22] <= 16.578267097473145f) {
                        if (features[8] <= 0.17305199801921844f) {
                            if (features[22] <= 5.72645902633667f) {
                                return 0;                            } else {
                                if (features[20] <= 15.293379306793213f) {
                                    if (features[11] <= 0.02046092739328742f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[20] <= 7.196182072162628f) {
                                return 0;                            } else {
                                if (features[4] <= 14.484671115875244f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        }
                    } else {
                        if (features[18] <= -0.5198928415775299f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    return 0;                }
            } else {
                if (features[27] <= -0.07478080689907074f) {
                    if (features[28] <= -0.4720424022525549f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[21] <= -0.08042990788817406f) {
                        if (features[8] <= -0.09962687641382217f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        if (features[0] <= -0.3447013944387436f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                }
            }
        } else {
            if (features[0] <= -0.12929633632302284f) {
                if (features[22] <= -0.08198202773928642f) {
                    return 1;                } else {
                    if (features[0] <= -0.34205761551856995f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[4] <= -0.06676784157752991f) {
            return 2;        } else {
            if (features[11] <= -0.814216673374176f) {
                if (features[21] <= -0.050666315481066704f) {
                    if (features[6] <= 1.1916509866714478f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    return 2;                }
            } else {
                if (features[3] <= 1.8876855373382568f) {
                    return 2;                } else {
                    return 0;                }
            }
        }
    }
}

// Tree 182
int predict_tree_182(const float* features) {
    // Max depth: 10
    if (features[22] <= -0.07712267339229584f) {
        if (features[17] <= -0.34562307596206665f) {
            if (features[22] <= -0.08133581280708313f) {
                return 0;            } else {
                if (features[0] <= -0.3505536913871765f) {
                    return 0;                } else {
                    return 1;                }
            }
        } else {
            if (features[6] <= -0.8383575081825256f) {
                return 2;            } else {
                if (features[10] <= -0.3188561648130417f) {
                    return 0;                } else {
                    if (features[8] <= -0.08483344689011574f) {
                        return 1;                    } else {
                        if (features[7] <= 0.37760813534259796f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            }
        }
    } else {
        if (features[22] <= -0.07025199010968208f) {
            if (features[9] <= -0.07334958016872406f) {
                if (features[27] <= -0.07753606885671616f) {
                    if (features[0] <= -0.046851031482219696f) {
                        return 1;                    } else {
                        if (features[11] <= -0.20603076554834843f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[26] <= -0.2653909921646118f) {
                        if (features[17] <= -0.18414698168635368f) {
                            return 0;                        } else {
                            return 2;                        }
                    } else {
                        if (features[18] <= -0.39115116000175476f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[10] <= -0.14831540826708078f) {
                    if (features[21] <= -0.0722740925848484f) {
                        if (features[27] <= -0.0721205286681652f) {
                            if (features[20] <= -0.07297470048069954f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            if (features[26] <= -0.19280441850423813f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    } else {
                        return 0;                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[23] <= -0.01738923881202936f) {
                if (features[10] <= -0.1004764661192894f) {
                    if (features[20] <= -0.05226636677980423f) {
                        return 0;                    } else {
                        if (features[17] <= -0.3606363534927368f) {
                            if (features[27] <= 2.876171588897705f) {
                                if (features[4] <= 1.7041438817977905f) {
                                    return 0;                                } else {
                                    return 2;                                }
                            } else {
                                if (features[7] <= -0.6849594712257385f) {
                                    if (features[26] <= -0.29530400037765503f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                } else {
                                    if (features[3] <= -0.11185693368315697f) {
                                        if (features[9] <= 13.57824420928955f) {
                                            return 1;                                        } else {
                                            return 2;                                        }
                                    } else {
                                        return 2;                                    }
                                }
                            }
                        } else {
                            if (features[11] <= -0.18895107507705688f) {
                                if (features[8] <= -0.31202657520771027f) {
                                    return 2;                                } else {
                                    if (features[12] <= -0.2760840803384781f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                if (features[0] <= -0.13170911371707916f) {
                                    if (features[1] <= -0.31114043295383453f) {
                                        return 0;                                    } else {
                                        if (features[17] <= -0.34231245517730713f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                } else {
                    if (features[21] <= -0.049335917457938194f) {
                        if (features[6] <= -0.0024716556072235107f) {
                            return 2;                        } else {
                            if (features[7] <= 0.920181680470705f) {
                                return 2;                            } else {
                                return 0;                            }
                        }
                    } else {
                        if (features[22] <= -0.049170417711138725f) {
                            if (features[10] <= 0.5557956006377935f) {
                                return 2;                            } else {
                                return 0;                            }
                        } else {
                            if (features[10] <= -0.006808996433392167f) {
                                if (features[1] <= -0.0061832034843973815f) {
                                    return 2;                                } else {
                                    return 1;                                }
                            } else {
                                if (features[3] <= 1.8837102949619293f) {
                                    return 2;                                } else {
                                    if (features[2] <= -1.542072832584381f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                return 0;            }
        }
    }
}

// Tree 183
int predict_tree_183(const float* features) {
    // Max depth: 7
    if (features[0] <= -0.1322481408715248f) {
        if (features[3] <= -1.0420615673065186f) {
            if (features[21] <= -0.06119607575237751f) {
                if (features[13] <= -0.00568625214509666f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                return 1;            }
        } else {
            if (features[20] <= -0.012467730790376663f) {
                if (features[0] <= -0.3404148519039154f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                if (features[10] <= -0.3188894987106323f) {
                    if (features[20] <= 6.680717468261719f) {
                        return 0;                    } else {
                        if (features[4] <= 12.916000366210938f) {
                            return 1;                        } else {
                            if (features[13] <= -18.96922779083252f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[1] <= 0.893930584192276f) {
            if (features[7] <= 1.6449432373046875f) {
                return 2;            } else {
                if (features[29] <= 0.49275785544887185f) {
                    return 0;                } else {
                    return 0;                }
            }
        } else {
            if (features[20] <= -0.0484618004411459f) {
                if (features[26] <= 2.6787363290786743f) {
                    if (features[3] <= 1.362954705953598f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    if (features[27] <= -0.020317644346505404f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                return 2;            }
        }
    }
}

// Tree 184
int predict_tree_184(const float* features) {
    // Max depth: 10
    if (features[17] <= -0.09930915758013725f) {
        if (features[1] <= -0.3088759779930115f) {
            if (features[9] <= 7.0539209842681885f) {
                return 0;            } else {
                if (features[8] <= 0.12991198897361755f) {
                    if (features[22] <= 16.0717134475708f) {
                        return 1;                    } else {
                        if (features[29] <= -0.008806705474853516f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[4] <= 14.301224708557129f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[0] <= -0.13478926569223404f) {
                if (features[22] <= -0.08199121803045273f) {
                    return 0;                } else {
                    if (features[10] <= -0.3220328539609909f) {
                        return 0;                    } else {
                        if (features[7] <= 1.228622853755951f) {
                            if (features[17] <= -0.3440575897693634f) {
                                if (features[0] <= -0.34192925691604614f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            } else {
                                if (features[9] <= -0.08233368396759033f) {
                                    if (features[17] <= -0.3395407795906067f) {
                                        if (features[30] <= 0.23382475972175598f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 1;                                }
                            }
                        } else {
                            if (features[0] <= -0.3427506536245346f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[7] <= 1.918724775314331f) {
            if (features[7] <= -1.4435431957244873f) {
                return 2;            } else {
                return 2;            }
        } else {
            if (features[3] <= 1.3311528414487839f) {
                return 2;            } else {
                return 0;            }
        }
    }
}

// Tree 185
int predict_tree_185(const float* features) {
    // Max depth: 10
    if (features[1] <= -0.06447293981909752f) {
        if (features[6] <= -0.2412961833178997f) {
            if (features[21] <= -0.06332988105714321f) {
                if (features[10] <= -0.31765659153461456f) {
                    if (features[21] <= -0.08372775465250015f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[8] <= -0.2705805152654648f) {
                        if (features[31] <= 0.24120032787322998f) {
                            return 2;                        } else {
                            return 2;                        }
                    } else {
                        if (features[17] <= -0.3518080413341522f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[7] <= -0.6849594712257385f) {
                    if (features[0] <= -0.5217329561710358f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    if (features[3] <= -0.8432998955249786f) {
                        return 2;                    } else {
                        if (features[10] <= -0.16434317082166672f) {
                            if (features[19] <= -0.5267831087112427f) {
                                return 0;                            } else {
                                if (features[9] <= 13.57824420928955f) {
                                    if (features[7] <= -0.6265419721603394f) {
                                        if (features[3] <= -0.2072625383734703f) {
                                            return 1;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        if (features[7] <= -0.6148913502693176f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    if (features[7] <= -0.6640121638774872f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                }
                            }
                        } else {
                            if (features[0] <= -0.12426542490720749f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                }
            }
        } else {
            if (features[17] <= -0.3438779413700104f) {
                if (features[27] <= -0.07159145176410675f) {
                    return 0;                } else {
                    if (features[1] <= -0.3038005232810974f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[12] <= -0.1897236779332161f) {
                    if (features[1] <= -0.16703633219003677f) {
                        if (features[12] <= -1.5037264227867126f) {
                            return 0;                        } else {
                            if (features[3] <= -0.39012327790260315f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[26] <= 0.16069991514086723f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[2] <= -0.10331545397639275f) {
                        if (features[26] <= -0.2826375812292099f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        if (features[8] <= -0.08775477856397629f) {
                            return 1;                        } else {
                            if (features[10] <= -0.31609046459198f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    }
                }
            }
        }
    } else {
        if (features[11] <= 0.10957241430878639f) {
            if (features[17] <= 0.9553733170032501f) {
                if (features[27] <= -0.07790148258209229f) {
                    return 2;                } else {
                    return 2;                }
            } else {
                if (features[2] <= -0.7521668104454875f) {
                    return 0;                } else {
                    return 2;                }
            }
        } else {
            if (features[17] <= -0.2178691029548645f) {
                return 1;            } else {
                if (features[9] <= -0.04856938496232033f) {
                    if (features[19] <= 0.9637456834316254f) {
                        if (features[27] <= -0.07766403257846832f) {
                            return 2;                        } else {
                            return 2;                        }
                    } else {
                        return 0;                    }
                } else {
                    if (features[26] <= -0.1849077232182026f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 186
int predict_tree_186(const float* features) {
    // Max depth: 9
    if (features[27] <= -0.07635965943336487f) {
        if (features[19] <= -0.38021238148212433f) {
            if (features[1] <= -0.2944890111684799f) {
                return 0;            } else {
                if (features[17] <= -0.35121777653694153f) {
                    return 0;                } else {
                    if (features[3] <= -0.13570833252742887f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            }
        } else {
            if (features[9] <= -0.08112625405192375f) {
                if (features[17] <= -0.3439292758703232f) {
                    return 0;                } else {
                    if (features[13] <= -0.0007144782575778663f) {
                        if (features[11] <= -0.26283935457468033f) {
                            return 1;                        } else {
                            if (features[17] <= -0.33807794749736786f) {
                                if (features[7] <= 0.5456224679946899f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            } else {
                                if (features[31] <= 0.24120032787322998f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        }
                    } else {
                        return 1;                    }
                }
            } else {
                if (features[1] <= -0.1496235877275467f) {
                    if (features[15] <= 0.7420355677604675f) {
                        if (features[27] <= -0.0777994878590107f) {
                            return 1;                        } else {
                            if (features[20] <= -0.060062916949391365f) {
                                return 0;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[20] <= 0.15753161162137985f) {
                            if (features[0] <= -0.3312257379293442f) {
                                return 0;                            } else {
                                return 1;                            }
                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[8] <= -0.21556375175714493f) {
                        return 2;                    } else {
                        if (features[8] <= -0.15362519770860672f) {
                            if (features[11] <= -0.6864902079105377f) {
                                return 2;                            } else {
                                if (features[19] <= 0.8764999806880951f) {
                                    return 2;                                } else {
                                    return 0;                                }
                            }
                        } else {
                            return 1;                        }
                    }
                }
            }
        }
    } else {
        if (features[18] <= -0.08427408337593079f) {
            if (features[22] <= -0.04599573276937008f) {
                if (features[22] <= -0.05169178359210491f) {
                    if (features[12] <= 0.2907356470823288f) {
                        if (features[20] <= -0.08233097940683365f) {
                            if (features[20] <= -0.08234555274248123f) {
                                return 0;                            } else {
                                return 1;                            }
                        } else {
                            if (features[2] <= -0.36285600066185f) {
                                if (features[8] <= -0.15067283064126968f) {
                                    if (features[10] <= -0.33286242187023163f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 0;                                }
                            } else {
                                return 0;                            }
                        }
                    } else {
                        if (features[8] <= -0.180160254240036f) {
                            return 2;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[7] <= -0.24316653609275818f) {
                        if (features[7] <= -1.4407630562782288f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[26] <= -0.11283556371927261f) {
                            if (features[13] <= -0.005109416786581278f) {
                                return 2;                            } else {
                                return 2;                            }
                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[4] <= 0.038218121975660324f) {
                    if (features[0] <= -0.3440083712339401f) {
                        if (features[19] <= -0.5351849496364594f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[0] <= -0.1287573091685772f) {
                            if (features[1] <= -0.30339057743549347f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[4] <= 7.0683913230896f) {
                        return 0;                    } else {
                        if (features[21] <= 15.407347679138184f) {
                            if (features[4] <= 13.232214450836182f) {
                                return 1;                            } else {
                                return 2;                            }
                        } else {
                            if (features[29] <= -0.008806705474853516f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                }
            }
        } else {
            if (features[19] <= 1.028859794139862f) {
                if (features[1] <= -0.15594839304685593f) {
                    return 1;                } else {
                    if (features[3] <= 1.967190146446228f) {
                        return 2;                    } else {
                        if (features[13] <= -0.004065618850290775f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                }
            } else {
                if (features[4] <= -0.048322902992367744f) {
                    if (features[3] <= 1.5120259635150433f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 187
int predict_tree_187(const float* features) {
    // Max depth: 10
    if (features[18] <= -0.08578718453645706f) {
        if (features[17] <= -0.3440575897693634f) {
            if (features[0] <= -0.34205760061740875f) {
                if (features[20] <= 7.332235813140869f) {
                    return 0;                } else {
                    if (features[27] <= 12.022491455078125f) {
                        if (features[22] <= 15.645354270935059f) {
                            return 2;                        } else {
                            return 2;                        }
                    } else {
                        if (features[18] <= -0.521790623664856f) {
                            return 1;                        } else {
                            if (features[18] <= -0.5174564719200134f) {
                                if (features[8] <= -0.07524299621582031f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            } else {
                                return 1;                            }
                        }
                    }
                }
            } else {
                return 1;            }
        } else {
            if (features[26] <= 0.5643077194690704f) {
                if (features[4] <= -0.04739026911556721f) {
                    if (features[4] <= -0.04884001798927784f) {
                        if (features[2] <= 0.7900306284427643f) {
                            if (features[9] <= -0.04910315200686455f) {
                                if (features[10] <= -0.3227548152208328f) {
                                    return 0;                                } else {
                                    if (features[8] <= -0.08530277013778687f) {
                                        return 1;                                    } else {
                                        if (features[10] <= -0.31723451614379883f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            } else {
                                if (features[11] <= 0.4778999239206314f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            return 2;                        }
                    } else {
                        if (features[11] <= -0.21457062661647797f) {
                            return 1;                        } else {
                            if (features[11] <= -0.022238326724618673f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[18] <= -0.10066172480583191f) {
                        if (features[10] <= -0.31963369250297546f) {
                            return 0;                        } else {
                            if (features[8] <= -0.04509698785841465f) {
                                return 1;                            } else {
                                if (features[21] <= 0.009289044421166182f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        }
                    } else {
                        return 1;                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[1] <= 0.8628336191177368f) {
            if (features[1] <= -0.17242413014173508f) {
                return 1;            } else {
                if (features[7] <= 1.6511622667312622f) {
                    return 2;                } else {
                    return 0;                }
            }
        } else {
            if (features[21] <= -0.048030123114585876f) {
                if (features[6] <= -0.12188391387462616f) {
                    return 2;                } else {
                    return 0;                }
            } else {
                return 2;            }
        }
    }
}

// Tree 188
int predict_tree_188(const float* features) {
    // Max depth: 9
    if (features[22] <= -0.07715734466910362f) {
        if (features[10] <= -0.3186229169368744f) {
            return 0;        } else {
            if (features[6] <= -1.1965942978858948f) {
                return 2;            } else {
                if (features[4] <= -0.08242486789822578f) {
                    if (features[7] <= 0.37653397023677826f) {
                        if (features[10] <= -0.31085896492004395f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[4] <= -0.08151887729763985f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            }
        }
    } else {
        if (features[0] <= -0.1342502385377884f) {
            if (features[18] <= -0.35242606699466705f) {
                if (features[27] <= 2.857832908630371f) {
                    if (features[26] <= -0.13575343042612076f) {
                        if (features[26] <= -0.30419905483722687f) {
                            if (features[8] <= 0.06021219305694103f) {
                                return 0;                            } else {
                                if (features[26] <= -0.30525563657283783f) {
                                    return 0;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            return 0;                        }
                    } else {
                        if (features[10] <= -0.3206111192703247f) {
                            if (features[8] <= -0.2499295324087143f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[19] <= -0.516280859708786f) {
                        if (features[4] <= 13.232214450836182f) {
                            if (features[27] <= 11.763341903686523f) {
                                return 0;                            } else {
                                if (features[0] <= -0.5164453387260437f) {
                                    if (features[0] <= -0.5213992595672607f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 0;                                }
                            }
                        } else {
                            return 2;                        }
                    } else {
                        if (features[21] <= 5.94169807434082f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[21] <= 0.15802235901355743f) {
                    if (features[2] <= -0.33088360726833344f) {
                        if (features[26] <= -0.19280441850423813f) {
                            return 0;                        } else {
                            if (features[4] <= -0.0727929137647152f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[0] <= -0.34321266412734985f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                } else {
                    return 0;                }
            }
        } else {
            if (features[2] <= -0.9656295031309128f) {
                return 0;            } else {
                if (features[17] <= -0.1437266319990158f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 189
int predict_tree_189(const float* features) {
    // Max depth: 10
    if (features[19] <= -0.060661472380161285f) {
        if (features[20] <= -0.05226636677980423f) {
            if (features[0] <= -0.3415699154138565f) {
                return 0;            } else {
                if (features[19] <= -0.1782357133924961f) {
                    if (features[9] <= -0.07043342664837837f) {
                        if (features[13] <= -0.005809859838336706f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[19] <= -0.33489890396595f) {
                if (features[2] <= -0.1315263845026493f) {
                    if (features[19] <= -0.5242728292942047f) {
                        return 0;                    } else {
                        if (features[21] <= 15.220935821533203f) {
                            if (features[9] <= -0.009003599174320698f) {
                                return 0;                            } else {
                                if (features[1] <= -0.46920204162597656f) {
                                    if (features[0] <= -0.5275595486164093f) {
                                        return 0;                                    } else {
                                        if (features[20] <= 8.970057010650635f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    if (features[27] <= 16.93702983856201f) {
                                        if (features[20] <= 0.5527391638606787f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 2;                                    }
                                }
                            }
                        } else {
                            if (features[12] <= -0.02770240418612957f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[26] <= 1.00619538128376f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[26] <= 0.5638849139213562f) {
                    if (features[17] <= -0.12116822972893715f) {
                        if (features[0] <= -0.129886694252491f) {
                            if (features[9] <= 0.24772290140390396f) {
                                return 1;                            } else {
                                return 0;                            }
                        } else {
                            return 2;                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[20] <= 0.3013271242380142f) {
                        return 2;                    } else {
                        return 0;                    }
                }
            }
        }
    } else {
        if (features[17] <= 0.9494706392288208f) {
            if (features[17] <= -0.13333282619714737f) {
                return 1;            } else {
                if (features[13] <= 0.12921088561415672f) {
                    if (features[0] <= -0.10681125149130821f) {
                        return 2;                    } else {
                        if (features[6] <= -2.8683661222457886f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[22] <= -0.0453724917024374f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[22] <= -0.04771758057177067f) {
                if (features[8] <= -0.22691435366868973f) {
                    return 2;                } else {
                    if (features[4] <= -0.056670403108000755f) {
                        return 2;                    } else {
                        if (features[7] <= 1.9252211451530457f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                }
            } else {
                return 2;            }
        }
    }
}

// Tree 190
int predict_tree_190(const float* features) {
    // Max depth: 10
    if (features[1] <= -0.07353068888187408f) {
        if (features[7] <= -0.861983060836792f) {
            if (features[11] <= 0.020089630037546158f) {
                return 0;            } else {
                if (features[0] <= -0.38982556760311127f) {
                    return 0;                } else {
                    return 1;                }
            }
        } else {
            if (features[21] <= -0.05924738757312298f) {
                if (features[15] <= 0.7420355677604675f) {
                    if (features[6] <= 0.23635287210345268f) {
                        if (features[1] <= -0.28605592250823975f) {
                            if (features[21] <= -0.08352846652269363f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            if (features[8] <= -0.3009869158267975f) {
                                if (features[13] <= -0.004614986013621092f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[0] <= -0.3412362188100815f) {
                            if (features[1] <= -0.5060381889343262f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[4] <= -0.07638230547308922f) {
                        if (features[3] <= -0.398073747754097f) {
                            if (features[20] <= -0.07792584225535393f) {
                                return 0;                            } else {
                                return 2;                            }
                        } else {
                            if (features[8] <= -0.19107474386692047f) {
                                return 0;                            } else {
                                if (features[26] <= -0.15227144956588745f) {
                                    return 0;                                } else {
                                    if (features[3] <= -0.2867671996355057f) {
                                        if (features[1] <= -0.31035958230495453f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[22] <= -0.08168085291981697f) {
                                            return 1;                                        } else {
                                            return 0;                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        if (features[20] <= -0.07236621901392937f) {
                            if (features[13] <= 0.00828141113743186f) {
                                if (features[18] <= -0.37750761210918427f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            } else {
                                return 0;                            }
                        } else {
                            return 0;                        }
                    }
                }
            } else {
                if (features[34] <= -2.0574225783348083f) {
                    if (features[17] <= -0.515568196773529f) {
                        if (features[21] <= 15.220935821533203f) {
                            if (features[9] <= 6.756311655044556f) {
                                if (features[22] <= 1.504109263420105f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                if (features[4] <= 13.232214450836182f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[20] <= 15.883905410766602f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[1] <= -0.33235976099967957f) {
                            if (features[27] <= -0.07031996920704842f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[18] <= -0.376507431268692f) {
                        if (features[7] <= 1.0745882987976074f) {
                            return 0;                        } else {
                            if (features[11] <= 0.42591819912195206f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[0] <= -0.13371121138334274f) {
                            if (features[1] <= -0.30901263654232025f) {
                                return 0;                            } else {
                                if (features[18] <= -0.336653932929039f) {
                                    if (features[3] <= 0.12268182635307312f) {
                                        return 1;                                    } else {
                                        if (features[0] <= -0.3483975827693939f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    }
                                } else {
                                    if (features[3] <= -1.495238184928894f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        } else {
                            if (features[29] <= -0.008806705474853516f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                }
            }
        }
    } else {
        if (features[2] <= -0.9750331491231918f) {
            return 0;        } else {
            if (features[22] <= 0.09105077758431435f) {
                return 2;            } else {
                if (features[3] <= -0.668389618396759f) {
                    return 2;                } else {
                    return 1;                }
            }
        }
    }
}

// Tree 191
int predict_tree_191(const float* features) {
    // Max depth: 8
    if (features[20] <= -0.07769386097788811f) {
        if (features[19] <= -0.3624609708786011f) {
            if (features[10] <= -0.32228831946849823f) {
                if (features[2] <= -2.087484121322632f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[17] <= -0.34803546965122223f) {
                    return 1;                } else {
                    return 1;                }
            }
        } else {
            if (features[1] <= -0.3064553886651993f) {
                return 0;            } else {
                if (features[20] <= -0.08149301260709763f) {
                    if (features[1] <= -0.3023364394903183f) {
                        return 1;                    } else {
                        if (features[0] <= -0.3404405266046524f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[0] <= -0.1322481408715248f) {
            if (features[17] <= -0.3523726314306259f) {
                if (features[27] <= 2.857832908630371f) {
                    if (features[15] <= 0.7420355677604675f) {
                        if (features[4] <= 1.7428911328315735f) {
                            return 0;                        } else {
                            return 2;                        }
                    } else {
                        if (features[10] <= -0.33186276257038116f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[9] <= 13.145212650299072f) {
                        if (features[9] <= 6.761305093765259f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        if (features[9] <= 14.783897399902344f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[3] <= 0.7229420840740204f) {
                    if (features[10] <= -0.3247874528169632f) {
                        return 0;                    } else {
                        if (features[22] <= -0.07247259467840195f) {
                            if (features[4] <= -0.07547298818826675f) {
                                return 1;                            } else {
                                return 0;                            }
                        } else {
                            if (features[10] <= -0.32007797062397003f) {
                                return 1;                            } else {
                                if (features[9] <= -0.07330003008246422f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        }
                    }
                } else {
                    if (features[7] <= 1.2763668298721313f) {
                        return 0;                    } else {
                        return 0;                    }
                }
            }
        } else {
            if (features[2] <= -0.9731524139642715f) {
                return 0;            } else {
                if (features[9] <= -0.07768258452415466f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 192
int predict_tree_192(const float* features) {
    // Max depth: 6
    if (features[22] <= -0.07707338407635689f) {
        if (features[11] <= 0.038654522970318794f) {
            if (features[26] <= -0.2621595710515976f) {
                if (features[10] <= -0.3180231302976608f) {
                    if (features[2] <= -2.087484121322632f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    return 1;                }
            } else {
                if (features[0] <= -0.34310999512672424f) {
                    return 0;                } else {
                    if (features[2] <= -0.24437010660767555f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            }
        } else {
            if (features[0] <= -0.340543195605278f) {
                return 0;            } else {
                if (features[10] <= 0.010240644216537476f) {
                    return 1;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[0] <= -0.1342502385377884f) {
            if (features[0] <= -0.3423656225204468f) {
                if (features[9] <= 7.0539209842681885f) {
                    return 0;                } else {
                    if (features[17] <= -0.5239345729351044f) {
                        return 1;                    } else {
                        if (features[4] <= 11.995749950408936f) {
                            return 1;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                return 1;            }
        } else {
            if (features[18] <= 0.9486342072486877f) {
                if (features[12] <= 1.9183361530303955f) {
                    if (features[3] <= 0.6831897795200348f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    if (features[9] <= -0.05033348128199577f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[7] <= 1.918283224105835f) {
                    return 2;                } else {
                    if (features[2] <= 0.2916375398635864f) {
                        return 0;                    } else {
                        if (features[3] <= -1.5508914589881897f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    }
}

// Tree 193
int predict_tree_193(const float* features) {
    // Max depth: 10
    if (features[19] <= -0.060661472380161285f) {
        if (features[9] <= -0.05116993933916092f) {
            if (features[13] <= -0.0005634022527374327f) {
                if (features[26] <= -0.2800528109073639f) {
                    if (features[18] <= -0.344270721077919f) {
                        if (features[3] <= -1.4713867902755737f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[18] <= -0.41956664621829987f) {
                        if (features[18] <= -0.4485720098018646f) {
                            return 0;                        } else {
                            if (features[1] <= -0.28131231665611267f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[17] <= -0.3440575897693634f) {
                            return 0;                        } else {
                            if (features[17] <= -0.20062308758497238f) {
                                if (features[26] <= -0.21858666092157364f) {
                                    if (features[4] <= -0.08235824853181839f) {
                                        return 1;                                    } else {
                                        if (features[18] <= -0.31775300204753876f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    if (features[9] <= -0.08188194036483765f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                if (features[26] <= 0.7244131043553352f) {
                    return 0;                } else {
                    return 2;                }
            }
        } else {
            if (features[19] <= -0.34355686604976654f) {
                if (features[4] <= 6.761305093765259f) {
                    if (features[7] <= -0.7500584721565247f) {
                        if (features[0] <= -0.35096436738967896f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        if (features[0] <= -0.28871969878673553f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[7] <= -0.6849594712257385f) {
                        return 2;                    } else {
                        if (features[27] <= 10.103565216064453f) {
                            return 2;                        } else {
                            if (features[9] <= 13.232214450836182f) {
                                return 1;                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                if (features[22] <= -0.04748491011559963f) {
                    if (features[10] <= -0.16856393218040466f) {
                        return 1;                    } else {
                        return 2;                    }
                } else {
                    if (features[17] <= -0.11621513217687607f) {
                        if (features[1] <= -0.35855697095394135f) {
                            return 0;                        } else {
                            if (features[13] <= 0.39113547652959824f) {
                                if (features[19] <= -0.3357442021369934f) {
                                    return 1;                                } else {
                                    if (features[22] <= -0.04727354273200035f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                return 1;                            }
                        }
                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[7] <= 1.9464809894561768f) {
            if (features[8] <= -0.31153571605682373f) {
                return 2;            } else {
                if (features[18] <= 0.16384857147932053f) {
                    if (features[28] <= 0.03530806303024292f) {
                        if (features[17] <= -0.09160362929105759f) {
                            if (features[0] <= -0.3412618935108185f) {
                                if (features[8] <= -0.10418319702148438f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        } else {
                            if (features[13] <= -0.052835701033473015f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[0] <= -0.03260533604770899f) {
                        return 2;                    } else {
                        if (features[3] <= 1.8797350525856018f) {
                            return 2;                        } else {
                            if (features[2] <= -1.5608801245689392f) {
                                return 0;                            } else {
                                return 0;                            }
                        }
                    }
                }
            }
        } else {
            if (features[21] <= -0.03903838247060776f) {
                return 0;            } else {
                if (features[0] <= 2.1947271823883057f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 194
int predict_tree_194(const float* features) {
    // Max depth: 5
    if (features[10] <= -0.07465210184454918f) {
        if (features[1] <= -0.3082122802734375f) {
            if (features[22] <= 6.7672810554504395f) {
                if (features[29] <= -0.5103712691925466f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[4] <= 13.232214450836182f) {
                    return 1;                } else {
                    if (features[22] <= 14.533020496368408f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[10] <= -0.15333588421344757f) {
                if (features[0] <= -0.34185226261615753f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                if (features[9] <= -0.04579771310091019f) {
                    if (features[7] <= -0.25714749097824097f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    if (features[17] <= -0.1416992023587227f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            }
        }
    } else {
        if (features[26] <= 0.8577961027622223f) {
            if (features[19] <= 0.950579434633255f) {
                if (features[13] <= 0.18859748542308807f) {
                    if (features[7] <= 1.65190851688385f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    return 1;                }
            } else {
                if (features[21] <= -0.047929227352142334f) {
                    return 0;                } else {
                    return 2;                }
            }
        } else {
            if (features[7] <= 2.144145369529724f) {
                return 2;            } else {
                if (features[6] <= 1.3110632300376892f) {
                    return 0;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 195
int predict_tree_195(const float* features) {
    // Max depth: 10
    if (features[22] <= -0.07708466053009033f) {
        if (features[18] <= -0.3771485835313797f) {
            if (features[3] <= -0.2867671996355057f) {
                if (features[28] <= 0.5426585469394922f) {
                    return 0;                } else {
                    if (features[10] <= -0.32855281233787537f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[18] <= -0.5536426305770874f) {
                    return 0;                } else {
                    return 0;                }
            }
        } else {
            if (features[10] <= -0.32228831946849823f) {
                return 0;            } else {
                if (features[2] <= -0.40423204004764557f) {
                    return 2;                } else {
                    if (features[27] <= -0.07645604014396667f) {
                        if (features[10] <= -0.31813420355319977f) {
                            return 1;                        } else {
                            if (features[9] <= -0.08190733939409256f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    } else {
                        return 1;                    }
                }
            }
        }
    } else {
        if (features[19] <= -0.05853540077805519f) {
            if (features[1] <= -0.3082122802734375f) {
                if (features[9] <= 6.761305093765259f) {
                    return 0;                } else {
                    if (features[7] <= -0.6849594712257385f) {
                        return 2;                    } else {
                        if (features[20] <= 13.23633861541748f) {
                            return 1;                        } else {
                            if (features[21] <= 16.34786605834961f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                if (features[1] <= 0.016246437560766935f) {
                    if (features[8] <= -0.320157453417778f) {
                        return 2;                    } else {
                        if (features[4] <= -0.07556042075157166f) {
                            return 2;                        } else {
                            if (features[0] <= -0.13170911371707916f) {
                                if (features[15] <= 0.7420355677604675f) {
                                    if (features[21] <= -0.07258177921175957f) {
                                        return 0;                                    } else {
                                        if (features[0] <= -0.3427506536245346f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    if (features[0] <= -0.3470371812582016f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[10] <= 0.8734408318996429f) {
                if (features[4] <= -0.04226494021713734f) {
                    if (features[17] <= -0.27982131391763687f) {
                        return 0;                    } else {
                        if (features[26] <= -0.30814819037914276f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[1] <= -0.15881798416376114f) {
                        return 1;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[20] <= -0.04852135851979256f) {
                    if (features[9] <= -0.06135897524654865f) {
                        return 2;                    } else {
                        if (features[27] <= -0.03477079980075359f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 196
int predict_tree_196(const float* features) {
    // Max depth: 9
    if (features[17] <= -0.10328061878681183f) {
        if (features[19] <= -0.3624609708786011f) {
            if (features[21] <= 8.017754793167114f) {
                if (features[10] <= -0.3226437568664551f) {
                    return 0;                } else {
                    if (features[1] <= -0.2936105579137802f) {
                        return 1;                    } else {
                        if (features[22] <= -0.08248245716094971f) {
                            return 1;                        } else {
                            if (features[3] <= -0.378197580575943f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    }
                }
            } else {
                if (features[1] <= -0.4691239595413208f) {
                    if (features[3] <= -0.21123776584863663f) {
                        return 2;                    } else {
                        if (features[9] <= 13.695127487182617f) {
                            return 1;                        } else {
                            if (features[4] <= 17.36750602722168f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[2] <= -0.3007919490337372f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[4] <= -0.06057414598762989f) {
                if (features[10] <= -0.32063333690166473f) {
                    return 0;                } else {
                    if (features[13] <= -0.006839923793449998f) {
                        return 0;                    } else {
                        if (features[20] <= -0.07541820034384727f) {
                            if (features[2] <= -0.10331545397639275f) {
                                if (features[13] <= -0.0013737190165556967f) {
                                    return 1;                                } else {
                                    return 0;                                }
                            } else {
                                if (features[8] <= -0.08530277013778687f) {
                                    return 1;                                } else {
                                    if (features[30] <= 0.23382475972175598f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[8] <= -0.3244227170944214f) {
                    return 2;                } else {
                    if (features[4] <= 0.24772290140390396f) {
                        if (features[8] <= -0.055997032672166824f) {
                            if (features[22] <= -0.04803003557026386f) {
                                if (features[18] <= -0.2444830983877182f) {
                                    return 1;                                } else {
                                    if (features[17] <= -0.12701955437660217f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                }
                            } else {
                                if (features[18] <= -0.3364487737417221f) {
                                    return 0;                                } else {
                                    if (features[1] <= -0.11530565097928047f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        } else {
                            if (features[17] <= -0.1657974272966385f) {
                                if (features[17] <= -0.32906998693943024f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            } else {
                                return 2;                            }
                        }
                    } else {
                        return 0;                    }
                }
            }
        }
    } else {
        if (features[10] <= 0.8855366706848145f) {
            if (features[27] <= -0.07789356634020805f) {
                return 2;            } else {
                return 2;            }
        } else {
            if (features[2] <= -0.7615704536437988f) {
                return 0;            } else {
                return 2;            }
        }
    }
}

// Tree 197
int predict_tree_197(const float* features) {
    // Max depth: 8
    if (features[26] <= -0.2605990022420883f) {
        if (features[26] <= -0.284633994102478f) {
            if (features[0] <= -0.34187793731689453f) {
                if (features[9] <= 7.171375513076782f) {
                    if (features[31] <= 0.24120032787322998f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[20] <= 13.932217121124268f) {
                        if (features[8] <= 0.17305199801921844f) {
                            return 1;                        } else {
                            return 2;                        }
                    } else {
                        if (features[26] <= -0.3051961809396744f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[18] <= -0.15259436890482903f) {
                    return 1;                } else {
                    if (features[19] <= 0.7186328768730164f) {
                        return 2;                    } else {
                        if (features[10] <= 1.857954502105713f) {
                            if (features[31] <= 0.24120032787322998f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[18] <= -0.34486056864261627f) {
                if (features[17] <= -0.5212142169475555f) {
                    if (features[21] <= 5.210179030895233f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    return 0;                }
            } else {
                if (features[2] <= 1.4482856392860413f) {
                    if (features[19] <= -0.152850940823555f) {
                        if (features[13] <= -0.04230158217251301f) {
                            return 1;                        } else {
                            if (features[17] <= -0.3346133530139923f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[8] <= -0.24493581801652908f) {
                            if (features[1] <= -0.15922792255878448f) {
                                return 2;                            } else {
                                return 2;                            }
                        } else {
                            return 0;                        }
                    }
                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[19] <= -0.06099447049200535f) {
            if (features[27] <= -0.07515648752450943f) {
                if (features[10] <= -0.3214108347892761f) {
                    return 0;                } else {
                    if (features[8] <= -0.2560139298439026f) {
                        return 2;                    } else {
                        if (features[0] <= -0.3416982591152191f) {
                            return 0;                        } else {
                            if (features[13] <= -0.0003299211421108339f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    }
                }
            } else {
                if (features[0] <= -0.1342502385377884f) {
                    if (features[0] <= -0.34411104023456573f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[27] <= -0.06349121034145355f) {
                if (features[18] <= 0.9481213092803955f) {
                    if (features[12] <= -1.0487421751022339f) {
                        if (features[2] <= 0.5107424259185791f) {
                            return 1;                        } else {
                            return 2;                        }
                    } else {
                        if (features[10] <= -0.13840773701667786f) {
                            if (features[10] <= -0.3512338250875473f) {
                                return 0;                            } else {
                                return 1;                            }
                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[7] <= 1.7793582081794739f) {
                        return 2;                    } else {
                        if (features[1] <= 2.5768563747406006f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[1] <= -0.17670410871505737f) {
                    return 1;                } else {
                    if (features[9] <= -0.0494899470359087f) {
                        if (features[20] <= -0.0610495638102293f) {
                            if (features[29] <= -0.008806705474853516f) {
                                return 2;                            } else {
                                return 2;                            }
                        } else {
                            if (features[11] <= -5.623637914657593f) {
                                return 2;                            } else {
                                if (features[18] <= 1.1584420800209045f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            }
                        }
                    } else {
                        if (features[21] <= -0.04906700551509857f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    }
}

// Tree 198
int predict_tree_198(const float* features) {
    // Max depth: 9
    if (features[9] <= -0.07767258957028389f) {
        if (features[9] <= -0.08253145217895508f) {
            if (features[10] <= -0.3250429183244705f) {
                return 0;            } else {
                return 1;            }
        } else {
            if (features[17] <= -0.3769328147172928f) {
                if (features[2] <= -0.8273959755897522f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[4] <= -0.07807895168662071f) {
                    if (features[8] <= -0.14804405719041824f) {
                        if (features[2] <= -0.08450816571712494f) {
                            return 1;                        } else {
                            if (features[17] <= -0.3441602438688278f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[7] <= 0.363038569688797f) {
                            if (features[19] <= -0.3054925352334976f) {
                                if (features[30] <= 0.23382475972175598f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        } else {
                            if (features[6] <= 0.4751773923635483f) {
                                if (features[1] <= -0.29950590431690216f) {
                                    return 0;                                } else {
                                    if (features[0] <= -0.336205318570137f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                if (features[0] <= -0.34105655550956726f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            }
                        }
                    }
                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[0] <= -0.1342502385377884f) {
            if (features[9] <= -0.05151468142867088f) {
                if (features[17] <= -0.35250094532966614f) {
                    return 0;                } else {
                    if (features[1] <= -0.3109647333621979f) {
                        return 0;                    } else {
                        if (features[11] <= 0.05350643675774336f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[10] <= -0.3188894987106323f) {
                    if (features[21] <= 6.75391149520874f) {
                        return 0;                    } else {
                        if (features[4] <= 13.232214450836182f) {
                            if (features[8] <= -0.17630131542682648f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            if (features[19] <= -0.5206610858440399f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    return 1;                }
            }
        } else {
            if (features[7] <= 1.918283224105835f) {
                return 2;            } else {
                if (features[21] <= -0.03906881622970104f) {
                    return 0;                } else {
                    if (features[15] <= 0.7420355677604675f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 199
int predict_tree_199(const float* features) {
    // Max depth: 10
    if (features[18] <= -0.08578718453645706f) {
        if (features[3] <= -0.9943587481975555f) {
            if (features[22] <= -0.06083737872540951f) {
                if (features[22] <= -0.08273518085479736f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[16] <= 5.114441957324743f) {
                    return 1;                } else {
                    return 2;                }
            }
        } else {
            if (features[21] <= -0.010239963419735432f) {
                if (features[0] <= -0.3415699154138565f) {
                    return 0;                } else {
                    if (features[10] <= -0.15463542938232422f) {
                        if (features[8] <= -0.298250749707222f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        if (features[8] <= -0.20303136855363846f) {
                            return 2;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[19] <= -0.34271156787872314f) {
                    if (features[16] <= 5.114441957324743f) {
                        if (features[22] <= -0.002715601003728807f) {
                            return 1;                        } else {
                            if (features[10] <= -0.31425777077674866f) {
                                return 0;                            } else {
                                if (features[19] <= -0.41463933885097504f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            }
                        }
                    } else {
                        if (features[18] <= -0.5108398795127869f) {
                            if (features[21] <= 15.220935821533203f) {
                                if (features[18] <= -0.527304470539093f) {
                                    return 0;                                } else {
                                    if (features[20] <= 7.332235813140869f) {
                                        return 0;                                    } else {
                                        if (features[9] <= 13.232214450836182f) {
                                            return 1;                                        } else {
                                            return 2;                                        }
                                    }
                                }
                            } else {
                                if (features[9] <= 15.682548522949219f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[19] <= -0.20897407084703445f) {
                        if (features[19] <= -0.3347708284854889f) {
                            return 1;                        } else {
                            if (features[22] <= 0.03777540288865566f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[20] <= 0.025484638288617134f) {
                            return 2;                        } else {
                            if (features[13] <= 0.1811123602092266f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    }
                }
            }
        }
    } else {
        if (features[20] <= -0.06654129922389984f) {
            if (features[0] <= -0.08383847400546074f) {
                return 2;            } else {
                return 2;            }
        } else {
            if (features[13] <= -0.024611955508589745f) {
                if (features[20] <= -0.049167320132255554f) {
                    if (features[11] <= -7.473815202713013f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    return 2;                }
            } else {
                if (features[1] <= 0.9027931094169617f) {
                    if (features[2] <= -0.15973730757832527f) {
                        return 0;                    } else {
                        if (features[11] <= -0.4726226329803467f) {
                            if (features[7] <= 0.08248608186841011f) {
                                return 2;                            } else {
                                return 1;                            }
                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[22] <= -0.0478758979588747f) {
                        if (features[7] <= 1.9252211451530457f) {
                            return 2;                        } else {
                            return 0;                        }
                    } else {
                        if (features[2] <= -0.06570088118314743f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    }
}

// ════════════════════════════════════════════════════════════════════════
// RANDOM FOREST ENSEMBLE PREDICTION
// ════════════════════════════════════════════════════════════════════════

int predict(float features[NUM_FEATURES]) {
    // Create copy for normalization
    float normalized_features[NUM_FEATURES];
    for (int i = 0; i < NUM_FEATURES; i++) {
        normalized_features[i] = features[i];
    }
    
    // Normalize features using scaler parameters
    normalize_features(normalized_features);
    
    // Vote from all trees
    int votes[NUM_CLASSES] = {0};
    
    int vote_0 = predict_tree_0(normalized_features);
    votes[vote_0]++;
    int vote_1 = predict_tree_1(normalized_features);
    votes[vote_1]++;
    int vote_2 = predict_tree_2(normalized_features);
    votes[vote_2]++;
    int vote_3 = predict_tree_3(normalized_features);
    votes[vote_3]++;
    int vote_4 = predict_tree_4(normalized_features);
    votes[vote_4]++;
    int vote_5 = predict_tree_5(normalized_features);
    votes[vote_5]++;
    int vote_6 = predict_tree_6(normalized_features);
    votes[vote_6]++;
    int vote_7 = predict_tree_7(normalized_features);
    votes[vote_7]++;
    int vote_8 = predict_tree_8(normalized_features);
    votes[vote_8]++;
    int vote_9 = predict_tree_9(normalized_features);
    votes[vote_9]++;
    int vote_10 = predict_tree_10(normalized_features);
    votes[vote_10]++;
    int vote_11 = predict_tree_11(normalized_features);
    votes[vote_11]++;
    int vote_12 = predict_tree_12(normalized_features);
    votes[vote_12]++;
    int vote_13 = predict_tree_13(normalized_features);
    votes[vote_13]++;
    int vote_14 = predict_tree_14(normalized_features);
    votes[vote_14]++;
    int vote_15 = predict_tree_15(normalized_features);
    votes[vote_15]++;
    int vote_16 = predict_tree_16(normalized_features);
    votes[vote_16]++;
    int vote_17 = predict_tree_17(normalized_features);
    votes[vote_17]++;
    int vote_18 = predict_tree_18(normalized_features);
    votes[vote_18]++;
    int vote_19 = predict_tree_19(normalized_features);
    votes[vote_19]++;
    int vote_20 = predict_tree_20(normalized_features);
    votes[vote_20]++;
    int vote_21 = predict_tree_21(normalized_features);
    votes[vote_21]++;
    int vote_22 = predict_tree_22(normalized_features);
    votes[vote_22]++;
    int vote_23 = predict_tree_23(normalized_features);
    votes[vote_23]++;
    int vote_24 = predict_tree_24(normalized_features);
    votes[vote_24]++;
    int vote_25 = predict_tree_25(normalized_features);
    votes[vote_25]++;
    int vote_26 = predict_tree_26(normalized_features);
    votes[vote_26]++;
    int vote_27 = predict_tree_27(normalized_features);
    votes[vote_27]++;
    int vote_28 = predict_tree_28(normalized_features);
    votes[vote_28]++;
    int vote_29 = predict_tree_29(normalized_features);
    votes[vote_29]++;
    int vote_30 = predict_tree_30(normalized_features);
    votes[vote_30]++;
    int vote_31 = predict_tree_31(normalized_features);
    votes[vote_31]++;
    int vote_32 = predict_tree_32(normalized_features);
    votes[vote_32]++;
    int vote_33 = predict_tree_33(normalized_features);
    votes[vote_33]++;
    int vote_34 = predict_tree_34(normalized_features);
    votes[vote_34]++;
    int vote_35 = predict_tree_35(normalized_features);
    votes[vote_35]++;
    int vote_36 = predict_tree_36(normalized_features);
    votes[vote_36]++;
    int vote_37 = predict_tree_37(normalized_features);
    votes[vote_37]++;
    int vote_38 = predict_tree_38(normalized_features);
    votes[vote_38]++;
    int vote_39 = predict_tree_39(normalized_features);
    votes[vote_39]++;
    int vote_40 = predict_tree_40(normalized_features);
    votes[vote_40]++;
    int vote_41 = predict_tree_41(normalized_features);
    votes[vote_41]++;
    int vote_42 = predict_tree_42(normalized_features);
    votes[vote_42]++;
    int vote_43 = predict_tree_43(normalized_features);
    votes[vote_43]++;
    int vote_44 = predict_tree_44(normalized_features);
    votes[vote_44]++;
    int vote_45 = predict_tree_45(normalized_features);
    votes[vote_45]++;
    int vote_46 = predict_tree_46(normalized_features);
    votes[vote_46]++;
    int vote_47 = predict_tree_47(normalized_features);
    votes[vote_47]++;
    int vote_48 = predict_tree_48(normalized_features);
    votes[vote_48]++;
    int vote_49 = predict_tree_49(normalized_features);
    votes[vote_49]++;
    int vote_50 = predict_tree_50(normalized_features);
    votes[vote_50]++;
    int vote_51 = predict_tree_51(normalized_features);
    votes[vote_51]++;
    int vote_52 = predict_tree_52(normalized_features);
    votes[vote_52]++;
    int vote_53 = predict_tree_53(normalized_features);
    votes[vote_53]++;
    int vote_54 = predict_tree_54(normalized_features);
    votes[vote_54]++;
    int vote_55 = predict_tree_55(normalized_features);
    votes[vote_55]++;
    int vote_56 = predict_tree_56(normalized_features);
    votes[vote_56]++;
    int vote_57 = predict_tree_57(normalized_features);
    votes[vote_57]++;
    int vote_58 = predict_tree_58(normalized_features);
    votes[vote_58]++;
    int vote_59 = predict_tree_59(normalized_features);
    votes[vote_59]++;
    int vote_60 = predict_tree_60(normalized_features);
    votes[vote_60]++;
    int vote_61 = predict_tree_61(normalized_features);
    votes[vote_61]++;
    int vote_62 = predict_tree_62(normalized_features);
    votes[vote_62]++;
    int vote_63 = predict_tree_63(normalized_features);
    votes[vote_63]++;
    int vote_64 = predict_tree_64(normalized_features);
    votes[vote_64]++;
    int vote_65 = predict_tree_65(normalized_features);
    votes[vote_65]++;
    int vote_66 = predict_tree_66(normalized_features);
    votes[vote_66]++;
    int vote_67 = predict_tree_67(normalized_features);
    votes[vote_67]++;
    int vote_68 = predict_tree_68(normalized_features);
    votes[vote_68]++;
    int vote_69 = predict_tree_69(normalized_features);
    votes[vote_69]++;
    int vote_70 = predict_tree_70(normalized_features);
    votes[vote_70]++;
    int vote_71 = predict_tree_71(normalized_features);
    votes[vote_71]++;
    int vote_72 = predict_tree_72(normalized_features);
    votes[vote_72]++;
    int vote_73 = predict_tree_73(normalized_features);
    votes[vote_73]++;
    int vote_74 = predict_tree_74(normalized_features);
    votes[vote_74]++;
    int vote_75 = predict_tree_75(normalized_features);
    votes[vote_75]++;
    int vote_76 = predict_tree_76(normalized_features);
    votes[vote_76]++;
    int vote_77 = predict_tree_77(normalized_features);
    votes[vote_77]++;
    int vote_78 = predict_tree_78(normalized_features);
    votes[vote_78]++;
    int vote_79 = predict_tree_79(normalized_features);
    votes[vote_79]++;
    int vote_80 = predict_tree_80(normalized_features);
    votes[vote_80]++;
    int vote_81 = predict_tree_81(normalized_features);
    votes[vote_81]++;
    int vote_82 = predict_tree_82(normalized_features);
    votes[vote_82]++;
    int vote_83 = predict_tree_83(normalized_features);
    votes[vote_83]++;
    int vote_84 = predict_tree_84(normalized_features);
    votes[vote_84]++;
    int vote_85 = predict_tree_85(normalized_features);
    votes[vote_85]++;
    int vote_86 = predict_tree_86(normalized_features);
    votes[vote_86]++;
    int vote_87 = predict_tree_87(normalized_features);
    votes[vote_87]++;
    int vote_88 = predict_tree_88(normalized_features);
    votes[vote_88]++;
    int vote_89 = predict_tree_89(normalized_features);
    votes[vote_89]++;
    int vote_90 = predict_tree_90(normalized_features);
    votes[vote_90]++;
    int vote_91 = predict_tree_91(normalized_features);
    votes[vote_91]++;
    int vote_92 = predict_tree_92(normalized_features);
    votes[vote_92]++;
    int vote_93 = predict_tree_93(normalized_features);
    votes[vote_93]++;
    int vote_94 = predict_tree_94(normalized_features);
    votes[vote_94]++;
    int vote_95 = predict_tree_95(normalized_features);
    votes[vote_95]++;
    int vote_96 = predict_tree_96(normalized_features);
    votes[vote_96]++;
    int vote_97 = predict_tree_97(normalized_features);
    votes[vote_97]++;
    int vote_98 = predict_tree_98(normalized_features);
    votes[vote_98]++;
    int vote_99 = predict_tree_99(normalized_features);
    votes[vote_99]++;
    int vote_100 = predict_tree_100(normalized_features);
    votes[vote_100]++;
    int vote_101 = predict_tree_101(normalized_features);
    votes[vote_101]++;
    int vote_102 = predict_tree_102(normalized_features);
    votes[vote_102]++;
    int vote_103 = predict_tree_103(normalized_features);
    votes[vote_103]++;
    int vote_104 = predict_tree_104(normalized_features);
    votes[vote_104]++;
    int vote_105 = predict_tree_105(normalized_features);
    votes[vote_105]++;
    int vote_106 = predict_tree_106(normalized_features);
    votes[vote_106]++;
    int vote_107 = predict_tree_107(normalized_features);
    votes[vote_107]++;
    int vote_108 = predict_tree_108(normalized_features);
    votes[vote_108]++;
    int vote_109 = predict_tree_109(normalized_features);
    votes[vote_109]++;
    int vote_110 = predict_tree_110(normalized_features);
    votes[vote_110]++;
    int vote_111 = predict_tree_111(normalized_features);
    votes[vote_111]++;
    int vote_112 = predict_tree_112(normalized_features);
    votes[vote_112]++;
    int vote_113 = predict_tree_113(normalized_features);
    votes[vote_113]++;
    int vote_114 = predict_tree_114(normalized_features);
    votes[vote_114]++;
    int vote_115 = predict_tree_115(normalized_features);
    votes[vote_115]++;
    int vote_116 = predict_tree_116(normalized_features);
    votes[vote_116]++;
    int vote_117 = predict_tree_117(normalized_features);
    votes[vote_117]++;
    int vote_118 = predict_tree_118(normalized_features);
    votes[vote_118]++;
    int vote_119 = predict_tree_119(normalized_features);
    votes[vote_119]++;
    int vote_120 = predict_tree_120(normalized_features);
    votes[vote_120]++;
    int vote_121 = predict_tree_121(normalized_features);
    votes[vote_121]++;
    int vote_122 = predict_tree_122(normalized_features);
    votes[vote_122]++;
    int vote_123 = predict_tree_123(normalized_features);
    votes[vote_123]++;
    int vote_124 = predict_tree_124(normalized_features);
    votes[vote_124]++;
    int vote_125 = predict_tree_125(normalized_features);
    votes[vote_125]++;
    int vote_126 = predict_tree_126(normalized_features);
    votes[vote_126]++;
    int vote_127 = predict_tree_127(normalized_features);
    votes[vote_127]++;
    int vote_128 = predict_tree_128(normalized_features);
    votes[vote_128]++;
    int vote_129 = predict_tree_129(normalized_features);
    votes[vote_129]++;
    int vote_130 = predict_tree_130(normalized_features);
    votes[vote_130]++;
    int vote_131 = predict_tree_131(normalized_features);
    votes[vote_131]++;
    int vote_132 = predict_tree_132(normalized_features);
    votes[vote_132]++;
    int vote_133 = predict_tree_133(normalized_features);
    votes[vote_133]++;
    int vote_134 = predict_tree_134(normalized_features);
    votes[vote_134]++;
    int vote_135 = predict_tree_135(normalized_features);
    votes[vote_135]++;
    int vote_136 = predict_tree_136(normalized_features);
    votes[vote_136]++;
    int vote_137 = predict_tree_137(normalized_features);
    votes[vote_137]++;
    int vote_138 = predict_tree_138(normalized_features);
    votes[vote_138]++;
    int vote_139 = predict_tree_139(normalized_features);
    votes[vote_139]++;
    int vote_140 = predict_tree_140(normalized_features);
    votes[vote_140]++;
    int vote_141 = predict_tree_141(normalized_features);
    votes[vote_141]++;
    int vote_142 = predict_tree_142(normalized_features);
    votes[vote_142]++;
    int vote_143 = predict_tree_143(normalized_features);
    votes[vote_143]++;
    int vote_144 = predict_tree_144(normalized_features);
    votes[vote_144]++;
    int vote_145 = predict_tree_145(normalized_features);
    votes[vote_145]++;
    int vote_146 = predict_tree_146(normalized_features);
    votes[vote_146]++;
    int vote_147 = predict_tree_147(normalized_features);
    votes[vote_147]++;
    int vote_148 = predict_tree_148(normalized_features);
    votes[vote_148]++;
    int vote_149 = predict_tree_149(normalized_features);
    votes[vote_149]++;
    int vote_150 = predict_tree_150(normalized_features);
    votes[vote_150]++;
    int vote_151 = predict_tree_151(normalized_features);
    votes[vote_151]++;
    int vote_152 = predict_tree_152(normalized_features);
    votes[vote_152]++;
    int vote_153 = predict_tree_153(normalized_features);
    votes[vote_153]++;
    int vote_154 = predict_tree_154(normalized_features);
    votes[vote_154]++;
    int vote_155 = predict_tree_155(normalized_features);
    votes[vote_155]++;
    int vote_156 = predict_tree_156(normalized_features);
    votes[vote_156]++;
    int vote_157 = predict_tree_157(normalized_features);
    votes[vote_157]++;
    int vote_158 = predict_tree_158(normalized_features);
    votes[vote_158]++;
    int vote_159 = predict_tree_159(normalized_features);
    votes[vote_159]++;
    int vote_160 = predict_tree_160(normalized_features);
    votes[vote_160]++;
    int vote_161 = predict_tree_161(normalized_features);
    votes[vote_161]++;
    int vote_162 = predict_tree_162(normalized_features);
    votes[vote_162]++;
    int vote_163 = predict_tree_163(normalized_features);
    votes[vote_163]++;
    int vote_164 = predict_tree_164(normalized_features);
    votes[vote_164]++;
    int vote_165 = predict_tree_165(normalized_features);
    votes[vote_165]++;
    int vote_166 = predict_tree_166(normalized_features);
    votes[vote_166]++;
    int vote_167 = predict_tree_167(normalized_features);
    votes[vote_167]++;
    int vote_168 = predict_tree_168(normalized_features);
    votes[vote_168]++;
    int vote_169 = predict_tree_169(normalized_features);
    votes[vote_169]++;
    int vote_170 = predict_tree_170(normalized_features);
    votes[vote_170]++;
    int vote_171 = predict_tree_171(normalized_features);
    votes[vote_171]++;
    int vote_172 = predict_tree_172(normalized_features);
    votes[vote_172]++;
    int vote_173 = predict_tree_173(normalized_features);
    votes[vote_173]++;
    int vote_174 = predict_tree_174(normalized_features);
    votes[vote_174]++;
    int vote_175 = predict_tree_175(normalized_features);
    votes[vote_175]++;
    int vote_176 = predict_tree_176(normalized_features);
    votes[vote_176]++;
    int vote_177 = predict_tree_177(normalized_features);
    votes[vote_177]++;
    int vote_178 = predict_tree_178(normalized_features);
    votes[vote_178]++;
    int vote_179 = predict_tree_179(normalized_features);
    votes[vote_179]++;
    int vote_180 = predict_tree_180(normalized_features);
    votes[vote_180]++;
    int vote_181 = predict_tree_181(normalized_features);
    votes[vote_181]++;
    int vote_182 = predict_tree_182(normalized_features);
    votes[vote_182]++;
    int vote_183 = predict_tree_183(normalized_features);
    votes[vote_183]++;
    int vote_184 = predict_tree_184(normalized_features);
    votes[vote_184]++;
    int vote_185 = predict_tree_185(normalized_features);
    votes[vote_185]++;
    int vote_186 = predict_tree_186(normalized_features);
    votes[vote_186]++;
    int vote_187 = predict_tree_187(normalized_features);
    votes[vote_187]++;
    int vote_188 = predict_tree_188(normalized_features);
    votes[vote_188]++;
    int vote_189 = predict_tree_189(normalized_features);
    votes[vote_189]++;
    int vote_190 = predict_tree_190(normalized_features);
    votes[vote_190]++;
    int vote_191 = predict_tree_191(normalized_features);
    votes[vote_191]++;
    int vote_192 = predict_tree_192(normalized_features);
    votes[vote_192]++;
    int vote_193 = predict_tree_193(normalized_features);
    votes[vote_193]++;
    int vote_194 = predict_tree_194(normalized_features);
    votes[vote_194]++;
    int vote_195 = predict_tree_195(normalized_features);
    votes[vote_195]++;
    int vote_196 = predict_tree_196(normalized_features);
    votes[vote_196]++;
    int vote_197 = predict_tree_197(normalized_features);
    votes[vote_197]++;
    int vote_198 = predict_tree_198(normalized_features);
    votes[vote_198]++;
    int vote_199 = predict_tree_199(normalized_features);
    votes[vote_199]++;

    // Return class with most votes
    int predicted_class = 0;
    int max_votes = votes[0];
    
    for (int i = 1; i < NUM_CLASSES; i++) {
        if (votes[i] > max_votes) {
            max_votes = votes[i];
            predicted_class = i;
        }
    }
    
    return CLASS_LABELS[predicted_class];
}

// ════════════════════════════════════════════════════════════════════════
// GET CONFIDENCE SCORE (based on vote distribution)
// ════════════════════════════════════════════════════════════════════════

float get_confidence(float features[NUM_FEATURES]) {
    // Create copy for normalization
    float normalized_features[NUM_FEATURES];
    for (int i = 0; i < NUM_FEATURES; i++) {
        normalized_features[i] = features[i];
    }
    
    // Normalize features
    normalize_features(normalized_features);
    
    // Collect votes
    int votes[NUM_CLASSES] = {0};
    
    int vote_0_conf = predict_tree_0(normalized_features);
    votes[vote_0_conf]++;
    int vote_1_conf = predict_tree_1(normalized_features);
    votes[vote_1_conf]++;
    int vote_2_conf = predict_tree_2(normalized_features);
    votes[vote_2_conf]++;
    int vote_3_conf = predict_tree_3(normalized_features);
    votes[vote_3_conf]++;
    int vote_4_conf = predict_tree_4(normalized_features);
    votes[vote_4_conf]++;
    int vote_5_conf = predict_tree_5(normalized_features);
    votes[vote_5_conf]++;
    int vote_6_conf = predict_tree_6(normalized_features);
    votes[vote_6_conf]++;
    int vote_7_conf = predict_tree_7(normalized_features);
    votes[vote_7_conf]++;
    int vote_8_conf = predict_tree_8(normalized_features);
    votes[vote_8_conf]++;
    int vote_9_conf = predict_tree_9(normalized_features);
    votes[vote_9_conf]++;
    int vote_10_conf = predict_tree_10(normalized_features);
    votes[vote_10_conf]++;
    int vote_11_conf = predict_tree_11(normalized_features);
    votes[vote_11_conf]++;
    int vote_12_conf = predict_tree_12(normalized_features);
    votes[vote_12_conf]++;
    int vote_13_conf = predict_tree_13(normalized_features);
    votes[vote_13_conf]++;
    int vote_14_conf = predict_tree_14(normalized_features);
    votes[vote_14_conf]++;
    int vote_15_conf = predict_tree_15(normalized_features);
    votes[vote_15_conf]++;
    int vote_16_conf = predict_tree_16(normalized_features);
    votes[vote_16_conf]++;
    int vote_17_conf = predict_tree_17(normalized_features);
    votes[vote_17_conf]++;
    int vote_18_conf = predict_tree_18(normalized_features);
    votes[vote_18_conf]++;
    int vote_19_conf = predict_tree_19(normalized_features);
    votes[vote_19_conf]++;
    int vote_20_conf = predict_tree_20(normalized_features);
    votes[vote_20_conf]++;
    int vote_21_conf = predict_tree_21(normalized_features);
    votes[vote_21_conf]++;
    int vote_22_conf = predict_tree_22(normalized_features);
    votes[vote_22_conf]++;
    int vote_23_conf = predict_tree_23(normalized_features);
    votes[vote_23_conf]++;
    int vote_24_conf = predict_tree_24(normalized_features);
    votes[vote_24_conf]++;
    int vote_25_conf = predict_tree_25(normalized_features);
    votes[vote_25_conf]++;
    int vote_26_conf = predict_tree_26(normalized_features);
    votes[vote_26_conf]++;
    int vote_27_conf = predict_tree_27(normalized_features);
    votes[vote_27_conf]++;
    int vote_28_conf = predict_tree_28(normalized_features);
    votes[vote_28_conf]++;
    int vote_29_conf = predict_tree_29(normalized_features);
    votes[vote_29_conf]++;
    int vote_30_conf = predict_tree_30(normalized_features);
    votes[vote_30_conf]++;
    int vote_31_conf = predict_tree_31(normalized_features);
    votes[vote_31_conf]++;
    int vote_32_conf = predict_tree_32(normalized_features);
    votes[vote_32_conf]++;
    int vote_33_conf = predict_tree_33(normalized_features);
    votes[vote_33_conf]++;
    int vote_34_conf = predict_tree_34(normalized_features);
    votes[vote_34_conf]++;
    int vote_35_conf = predict_tree_35(normalized_features);
    votes[vote_35_conf]++;
    int vote_36_conf = predict_tree_36(normalized_features);
    votes[vote_36_conf]++;
    int vote_37_conf = predict_tree_37(normalized_features);
    votes[vote_37_conf]++;
    int vote_38_conf = predict_tree_38(normalized_features);
    votes[vote_38_conf]++;
    int vote_39_conf = predict_tree_39(normalized_features);
    votes[vote_39_conf]++;
    int vote_40_conf = predict_tree_40(normalized_features);
    votes[vote_40_conf]++;
    int vote_41_conf = predict_tree_41(normalized_features);
    votes[vote_41_conf]++;
    int vote_42_conf = predict_tree_42(normalized_features);
    votes[vote_42_conf]++;
    int vote_43_conf = predict_tree_43(normalized_features);
    votes[vote_43_conf]++;
    int vote_44_conf = predict_tree_44(normalized_features);
    votes[vote_44_conf]++;
    int vote_45_conf = predict_tree_45(normalized_features);
    votes[vote_45_conf]++;
    int vote_46_conf = predict_tree_46(normalized_features);
    votes[vote_46_conf]++;
    int vote_47_conf = predict_tree_47(normalized_features);
    votes[vote_47_conf]++;
    int vote_48_conf = predict_tree_48(normalized_features);
    votes[vote_48_conf]++;
    int vote_49_conf = predict_tree_49(normalized_features);
    votes[vote_49_conf]++;
    int vote_50_conf = predict_tree_50(normalized_features);
    votes[vote_50_conf]++;
    int vote_51_conf = predict_tree_51(normalized_features);
    votes[vote_51_conf]++;
    int vote_52_conf = predict_tree_52(normalized_features);
    votes[vote_52_conf]++;
    int vote_53_conf = predict_tree_53(normalized_features);
    votes[vote_53_conf]++;
    int vote_54_conf = predict_tree_54(normalized_features);
    votes[vote_54_conf]++;
    int vote_55_conf = predict_tree_55(normalized_features);
    votes[vote_55_conf]++;
    int vote_56_conf = predict_tree_56(normalized_features);
    votes[vote_56_conf]++;
    int vote_57_conf = predict_tree_57(normalized_features);
    votes[vote_57_conf]++;
    int vote_58_conf = predict_tree_58(normalized_features);
    votes[vote_58_conf]++;
    int vote_59_conf = predict_tree_59(normalized_features);
    votes[vote_59_conf]++;
    int vote_60_conf = predict_tree_60(normalized_features);
    votes[vote_60_conf]++;
    int vote_61_conf = predict_tree_61(normalized_features);
    votes[vote_61_conf]++;
    int vote_62_conf = predict_tree_62(normalized_features);
    votes[vote_62_conf]++;
    int vote_63_conf = predict_tree_63(normalized_features);
    votes[vote_63_conf]++;
    int vote_64_conf = predict_tree_64(normalized_features);
    votes[vote_64_conf]++;
    int vote_65_conf = predict_tree_65(normalized_features);
    votes[vote_65_conf]++;
    int vote_66_conf = predict_tree_66(normalized_features);
    votes[vote_66_conf]++;
    int vote_67_conf = predict_tree_67(normalized_features);
    votes[vote_67_conf]++;
    int vote_68_conf = predict_tree_68(normalized_features);
    votes[vote_68_conf]++;
    int vote_69_conf = predict_tree_69(normalized_features);
    votes[vote_69_conf]++;
    int vote_70_conf = predict_tree_70(normalized_features);
    votes[vote_70_conf]++;
    int vote_71_conf = predict_tree_71(normalized_features);
    votes[vote_71_conf]++;
    int vote_72_conf = predict_tree_72(normalized_features);
    votes[vote_72_conf]++;
    int vote_73_conf = predict_tree_73(normalized_features);
    votes[vote_73_conf]++;
    int vote_74_conf = predict_tree_74(normalized_features);
    votes[vote_74_conf]++;
    int vote_75_conf = predict_tree_75(normalized_features);
    votes[vote_75_conf]++;
    int vote_76_conf = predict_tree_76(normalized_features);
    votes[vote_76_conf]++;
    int vote_77_conf = predict_tree_77(normalized_features);
    votes[vote_77_conf]++;
    int vote_78_conf = predict_tree_78(normalized_features);
    votes[vote_78_conf]++;
    int vote_79_conf = predict_tree_79(normalized_features);
    votes[vote_79_conf]++;
    int vote_80_conf = predict_tree_80(normalized_features);
    votes[vote_80_conf]++;
    int vote_81_conf = predict_tree_81(normalized_features);
    votes[vote_81_conf]++;
    int vote_82_conf = predict_tree_82(normalized_features);
    votes[vote_82_conf]++;
    int vote_83_conf = predict_tree_83(normalized_features);
    votes[vote_83_conf]++;
    int vote_84_conf = predict_tree_84(normalized_features);
    votes[vote_84_conf]++;
    int vote_85_conf = predict_tree_85(normalized_features);
    votes[vote_85_conf]++;
    int vote_86_conf = predict_tree_86(normalized_features);
    votes[vote_86_conf]++;
    int vote_87_conf = predict_tree_87(normalized_features);
    votes[vote_87_conf]++;
    int vote_88_conf = predict_tree_88(normalized_features);
    votes[vote_88_conf]++;
    int vote_89_conf = predict_tree_89(normalized_features);
    votes[vote_89_conf]++;
    int vote_90_conf = predict_tree_90(normalized_features);
    votes[vote_90_conf]++;
    int vote_91_conf = predict_tree_91(normalized_features);
    votes[vote_91_conf]++;
    int vote_92_conf = predict_tree_92(normalized_features);
    votes[vote_92_conf]++;
    int vote_93_conf = predict_tree_93(normalized_features);
    votes[vote_93_conf]++;
    int vote_94_conf = predict_tree_94(normalized_features);
    votes[vote_94_conf]++;
    int vote_95_conf = predict_tree_95(normalized_features);
    votes[vote_95_conf]++;
    int vote_96_conf = predict_tree_96(normalized_features);
    votes[vote_96_conf]++;
    int vote_97_conf = predict_tree_97(normalized_features);
    votes[vote_97_conf]++;
    int vote_98_conf = predict_tree_98(normalized_features);
    votes[vote_98_conf]++;
    int vote_99_conf = predict_tree_99(normalized_features);
    votes[vote_99_conf]++;
    int vote_100_conf = predict_tree_100(normalized_features);
    votes[vote_100_conf]++;
    int vote_101_conf = predict_tree_101(normalized_features);
    votes[vote_101_conf]++;
    int vote_102_conf = predict_tree_102(normalized_features);
    votes[vote_102_conf]++;
    int vote_103_conf = predict_tree_103(normalized_features);
    votes[vote_103_conf]++;
    int vote_104_conf = predict_tree_104(normalized_features);
    votes[vote_104_conf]++;
    int vote_105_conf = predict_tree_105(normalized_features);
    votes[vote_105_conf]++;
    int vote_106_conf = predict_tree_106(normalized_features);
    votes[vote_106_conf]++;
    int vote_107_conf = predict_tree_107(normalized_features);
    votes[vote_107_conf]++;
    int vote_108_conf = predict_tree_108(normalized_features);
    votes[vote_108_conf]++;
    int vote_109_conf = predict_tree_109(normalized_features);
    votes[vote_109_conf]++;
    int vote_110_conf = predict_tree_110(normalized_features);
    votes[vote_110_conf]++;
    int vote_111_conf = predict_tree_111(normalized_features);
    votes[vote_111_conf]++;
    int vote_112_conf = predict_tree_112(normalized_features);
    votes[vote_112_conf]++;
    int vote_113_conf = predict_tree_113(normalized_features);
    votes[vote_113_conf]++;
    int vote_114_conf = predict_tree_114(normalized_features);
    votes[vote_114_conf]++;
    int vote_115_conf = predict_tree_115(normalized_features);
    votes[vote_115_conf]++;
    int vote_116_conf = predict_tree_116(normalized_features);
    votes[vote_116_conf]++;
    int vote_117_conf = predict_tree_117(normalized_features);
    votes[vote_117_conf]++;
    int vote_118_conf = predict_tree_118(normalized_features);
    votes[vote_118_conf]++;
    int vote_119_conf = predict_tree_119(normalized_features);
    votes[vote_119_conf]++;
    int vote_120_conf = predict_tree_120(normalized_features);
    votes[vote_120_conf]++;
    int vote_121_conf = predict_tree_121(normalized_features);
    votes[vote_121_conf]++;
    int vote_122_conf = predict_tree_122(normalized_features);
    votes[vote_122_conf]++;
    int vote_123_conf = predict_tree_123(normalized_features);
    votes[vote_123_conf]++;
    int vote_124_conf = predict_tree_124(normalized_features);
    votes[vote_124_conf]++;
    int vote_125_conf = predict_tree_125(normalized_features);
    votes[vote_125_conf]++;
    int vote_126_conf = predict_tree_126(normalized_features);
    votes[vote_126_conf]++;
    int vote_127_conf = predict_tree_127(normalized_features);
    votes[vote_127_conf]++;
    int vote_128_conf = predict_tree_128(normalized_features);
    votes[vote_128_conf]++;
    int vote_129_conf = predict_tree_129(normalized_features);
    votes[vote_129_conf]++;
    int vote_130_conf = predict_tree_130(normalized_features);
    votes[vote_130_conf]++;
    int vote_131_conf = predict_tree_131(normalized_features);
    votes[vote_131_conf]++;
    int vote_132_conf = predict_tree_132(normalized_features);
    votes[vote_132_conf]++;
    int vote_133_conf = predict_tree_133(normalized_features);
    votes[vote_133_conf]++;
    int vote_134_conf = predict_tree_134(normalized_features);
    votes[vote_134_conf]++;
    int vote_135_conf = predict_tree_135(normalized_features);
    votes[vote_135_conf]++;
    int vote_136_conf = predict_tree_136(normalized_features);
    votes[vote_136_conf]++;
    int vote_137_conf = predict_tree_137(normalized_features);
    votes[vote_137_conf]++;
    int vote_138_conf = predict_tree_138(normalized_features);
    votes[vote_138_conf]++;
    int vote_139_conf = predict_tree_139(normalized_features);
    votes[vote_139_conf]++;
    int vote_140_conf = predict_tree_140(normalized_features);
    votes[vote_140_conf]++;
    int vote_141_conf = predict_tree_141(normalized_features);
    votes[vote_141_conf]++;
    int vote_142_conf = predict_tree_142(normalized_features);
    votes[vote_142_conf]++;
    int vote_143_conf = predict_tree_143(normalized_features);
    votes[vote_143_conf]++;
    int vote_144_conf = predict_tree_144(normalized_features);
    votes[vote_144_conf]++;
    int vote_145_conf = predict_tree_145(normalized_features);
    votes[vote_145_conf]++;
    int vote_146_conf = predict_tree_146(normalized_features);
    votes[vote_146_conf]++;
    int vote_147_conf = predict_tree_147(normalized_features);
    votes[vote_147_conf]++;
    int vote_148_conf = predict_tree_148(normalized_features);
    votes[vote_148_conf]++;
    int vote_149_conf = predict_tree_149(normalized_features);
    votes[vote_149_conf]++;
    int vote_150_conf = predict_tree_150(normalized_features);
    votes[vote_150_conf]++;
    int vote_151_conf = predict_tree_151(normalized_features);
    votes[vote_151_conf]++;
    int vote_152_conf = predict_tree_152(normalized_features);
    votes[vote_152_conf]++;
    int vote_153_conf = predict_tree_153(normalized_features);
    votes[vote_153_conf]++;
    int vote_154_conf = predict_tree_154(normalized_features);
    votes[vote_154_conf]++;
    int vote_155_conf = predict_tree_155(normalized_features);
    votes[vote_155_conf]++;
    int vote_156_conf = predict_tree_156(normalized_features);
    votes[vote_156_conf]++;
    int vote_157_conf = predict_tree_157(normalized_features);
    votes[vote_157_conf]++;
    int vote_158_conf = predict_tree_158(normalized_features);
    votes[vote_158_conf]++;
    int vote_159_conf = predict_tree_159(normalized_features);
    votes[vote_159_conf]++;
    int vote_160_conf = predict_tree_160(normalized_features);
    votes[vote_160_conf]++;
    int vote_161_conf = predict_tree_161(normalized_features);
    votes[vote_161_conf]++;
    int vote_162_conf = predict_tree_162(normalized_features);
    votes[vote_162_conf]++;
    int vote_163_conf = predict_tree_163(normalized_features);
    votes[vote_163_conf]++;
    int vote_164_conf = predict_tree_164(normalized_features);
    votes[vote_164_conf]++;
    int vote_165_conf = predict_tree_165(normalized_features);
    votes[vote_165_conf]++;
    int vote_166_conf = predict_tree_166(normalized_features);
    votes[vote_166_conf]++;
    int vote_167_conf = predict_tree_167(normalized_features);
    votes[vote_167_conf]++;
    int vote_168_conf = predict_tree_168(normalized_features);
    votes[vote_168_conf]++;
    int vote_169_conf = predict_tree_169(normalized_features);
    votes[vote_169_conf]++;
    int vote_170_conf = predict_tree_170(normalized_features);
    votes[vote_170_conf]++;
    int vote_171_conf = predict_tree_171(normalized_features);
    votes[vote_171_conf]++;
    int vote_172_conf = predict_tree_172(normalized_features);
    votes[vote_172_conf]++;
    int vote_173_conf = predict_tree_173(normalized_features);
    votes[vote_173_conf]++;
    int vote_174_conf = predict_tree_174(normalized_features);
    votes[vote_174_conf]++;
    int vote_175_conf = predict_tree_175(normalized_features);
    votes[vote_175_conf]++;
    int vote_176_conf = predict_tree_176(normalized_features);
    votes[vote_176_conf]++;
    int vote_177_conf = predict_tree_177(normalized_features);
    votes[vote_177_conf]++;
    int vote_178_conf = predict_tree_178(normalized_features);
    votes[vote_178_conf]++;
    int vote_179_conf = predict_tree_179(normalized_features);
    votes[vote_179_conf]++;
    int vote_180_conf = predict_tree_180(normalized_features);
    votes[vote_180_conf]++;
    int vote_181_conf = predict_tree_181(normalized_features);
    votes[vote_181_conf]++;
    int vote_182_conf = predict_tree_182(normalized_features);
    votes[vote_182_conf]++;
    int vote_183_conf = predict_tree_183(normalized_features);
    votes[vote_183_conf]++;
    int vote_184_conf = predict_tree_184(normalized_features);
    votes[vote_184_conf]++;
    int vote_185_conf = predict_tree_185(normalized_features);
    votes[vote_185_conf]++;
    int vote_186_conf = predict_tree_186(normalized_features);
    votes[vote_186_conf]++;
    int vote_187_conf = predict_tree_187(normalized_features);
    votes[vote_187_conf]++;
    int vote_188_conf = predict_tree_188(normalized_features);
    votes[vote_188_conf]++;
    int vote_189_conf = predict_tree_189(normalized_features);
    votes[vote_189_conf]++;
    int vote_190_conf = predict_tree_190(normalized_features);
    votes[vote_190_conf]++;
    int vote_191_conf = predict_tree_191(normalized_features);
    votes[vote_191_conf]++;
    int vote_192_conf = predict_tree_192(normalized_features);
    votes[vote_192_conf]++;
    int vote_193_conf = predict_tree_193(normalized_features);
    votes[vote_193_conf]++;
    int vote_194_conf = predict_tree_194(normalized_features);
    votes[vote_194_conf]++;
    int vote_195_conf = predict_tree_195(normalized_features);
    votes[vote_195_conf]++;
    int vote_196_conf = predict_tree_196(normalized_features);
    votes[vote_196_conf]++;
    int vote_197_conf = predict_tree_197(normalized_features);
    votes[vote_197_conf]++;
    int vote_198_conf = predict_tree_198(normalized_features);
    votes[vote_198_conf]++;
    int vote_199_conf = predict_tree_199(normalized_features);
    votes[vote_199_conf]++;

    // Calculate confidence as ratio of max votes to total trees
    int max_votes = 0;
    for (int i = 0; i < NUM_CLASSES; i++) {
        if (votes[i] > max_votes) {
            max_votes = votes[i];
        }
    }
    
    float confidence = (float)max_votes / (float)NUM_TREES;
    return confidence;
}

#endif  // MODEL_H

// ════════════════════════════════════════════════════════════════════════
// END OF MODEL
// ════════════════════════════════════════════════════════════════════════
