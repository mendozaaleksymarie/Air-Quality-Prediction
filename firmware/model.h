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
    134.07452424084192f,  // feature_0
    162.14323362794417f,  // feature_1
    31.488619214313545f,  // feature_2
    58.0965000648259f,  // feature_3
    31.70713266682983f,  // feature_4
    2025.5228309347963f,  // feature_5
    9.035848567353819f,  // feature_6
    28.876780749464636f,  // feature_7
    1.383118165142356f,  // feature_8
    0.015221040309321754f,  // feature_9
    296.21775786878766f,  // feature_10
    0.09802620525892294f,  // feature_11
    0.1607482699775617f,  // feature_12
    0.006447207936576558f,  // feature_13
    0.08623622455594412f,  // feature_14
    0.20270971087773887f,  // feature_15
    0.027421236872812137f,  // feature_16
    133.979688195831f,  // feature_17
    133.9657105316253f,  // feature_18
    133.9819831100208f,  // feature_19
    31.700763441712226f,  // feature_20
    31.691872127864873f,  // feature_21
    31.679676928322014f,  // feature_22
    2025.4318207355666f,  // feature_23
    2025.3949440338886f,  // feature_24
    2025.1809751934027f,  // feature_25
    7.099573126934541f,  // feature_26
    0.34988562356305625f,  // feature_27
    -0.03234798392324647f,  // feature_28
    0.0029819784778944637f,  // feature_29
    0.4146894852845845f,  // feature_30
    0.4209775703357967f,  // feature_31
    0.0f,  // feature_32
    0.3050045377933359f,  // feature_33
    0.896927265655387f,  // feature_34
};

const float SCALER_SCALE[] = {
    217.09293773367168f,  // feature_0
    277.4382221176182f,  // feature_1
    5.326616590400734f,  // feature_2
    12.710276627283905f,  // feature_3
    18.32941177560574f,  // feature_4
    173.79529175567305f,  // feature_5
    4.526433704765894f,  // feature_6
    3.430377341437121f,  // feature_7
    0.9923282491810893f,  // feature_8
    0.006820780351053965f,  // feature_9
    493.74747885559856f,  // feature_10
    20.29403948220556f,  // feature_11
    29.701070836314823f,  // feature_12
    0.8842259782953633f,  // feature_13
    9.621718237023511f,  // feature_14
    0.40201801451378705f,  // feature_15
    0.16330741759383985f,  // feature_16
    216.85094086819902f,  // feature_17
    216.7153199330548f,  // feature_18
    216.81370184707106f,  // feature_19
    18.312325503853632f,  // feature_20
    18.276392489198646f,  // feature_21
    18.231675908235356f,  // feature_22
    173.7156544813136f,  // feature_23
    173.58649144913005f,  // feature_24
    173.04150074522505f,  // feature_25
    19.19470138245911f,  // feature_26
    1.0652337718695708f,  // feature_27
    0.9956751531011598f,  // feature_28
    0.9988280059735472f,  // feature_29
    0.49266836318052687f,  // feature_30
    0.4937159665333429f,  // feature_31
    1.0f,  // feature_32
    0.4604093501643966f,  // feature_33
    0.4421781090511132f,  // feature_34
};

const int NUM_FEATURES = 35;
const int NUM_CLASSES = 2;
const int NUM_TREES = 100;

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
    // Max depth: 5
    if (features[21] <= -0.12490418925881386f) {
        return 1;    } else {
        if (features[19] <= 1.0642229318618774f) {
            if (features[12] <= 0.17903048545122147f) {
                return 1;            } else {
                if (features[22] <= -0.05437479307875037f) {
                    return 0;                } else {
                    return 1;                }
            }
        } else {
            if (features[4] <= 0.07434402033686638f) {
                if (features[0] <= 0.9857386350631714f) {
                    return 1;                } else {
                    if (features[22] <= 0.1795993447303772f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[29] <= -0.5035721659660339f) {
                    return 1;                } else {
                    return 1;                }
            }
        }
    }
}

// Tree 1
int predict_tree_1(const float* features) {
    // Max depth: 3
    if (features[17] <= 1.062720775604248f) {
        if (features[20] <= -0.8257555365562439f) {
            return 1;        } else {
            return 1;        }
    } else {
        if (features[22] <= 0.06929072551429272f) {
            return 0;        } else {
            if (features[34] <= -2.028429754078388f) {
                return 1;            } else {
                return 1;            }
        }
    }
}

// Tree 2
int predict_tree_2(const float* features) {
    // Max depth: 5
    if (features[17] <= 1.062659502029419f) {
        if (features[6] <= -1.4439288973808289f) {
            if (features[17] <= 0.7878123223781586f) {
                if (features[10] <= 0.7379182279109955f) {
                    return 1;                } else {
                    if (features[23] <= 2.2069004997611046f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[21] <= 1.0818539001047611f) {
                    return 0;                } else {
                    return 1;                }
            }
        } else {
            return 1;        }
    } else {
        if (features[2] <= -0.6643277481198311f) {
            return 0;        } else {
            return 1;        }
    }
}

// Tree 3
int predict_tree_3(const float* features) {
    // Max depth: 4
    if (features[7] <= 1.9096187353134155f) {
        if (features[19] <= -0.5002913773059845f) {
            if (features[19] <= -0.6179588735103607f) {
                return 1;            } else {
                return 1;            }
        } else {
            if (features[18] <= -0.4994727671146393f) {
                if (features[18] <= -0.49948807060718536f) {
                    return 1;                } else {
                    return 0;                }
            } else {
                return 1;            }
        }
    } else {
        if (features[4] <= 0.272467203438282f) {
            if (features[9] <= -0.12038109079003334f) {
                return 0;            } else {
                return 0;            }
        } else {
            return 1;        }
    }
}

// Tree 4
int predict_tree_4(const float* features) {
    // Max depth: 4
    if (features[0] <= 1.0607702732086182f) {
        if (features[27] <= -0.32800567150115967f) {
            if (features[1] <= 0.33160983957350254f) {
                if (features[20] <= -0.7865338325500488f) {
                    return 1;                } else {
                    return 1;                }
            } else {
                return 0;            }
        } else {
            if (features[3] <= 2.7539526224136353f) {
                if (features[0] <= -0.6175902783870697f) {
                    return 1;                } else {
                    return 1;                }
            } else {
                return 0;            }
        }
    } else {
        if (features[2] <= -0.6643277481198311f) {
            return 0;        } else {
            if (features[8] <= -0.31540706753730774f) {
                return 1;            } else {
                return 1;            }
        }
    }
}

// Tree 5
int predict_tree_5(const float* features) {
    // Max depth: 4
    if (features[0] <= 1.060834527015686f) {
        if (features[10] <= 0.7451616823673248f) {
            if (features[2] <= -1.71565181016922f) {
                if (features[7] <= 1.0881958603858948f) {
                    return 1;                } else {
                    return 0;                }
            } else {
                return 1;            }
        } else {
            if (features[18] <= 0.402725487947464f) {
                return 0;            } else {
                if (features[3] <= -1.809283971786499f) {
                    return 1;                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[2] <= -0.6643277481198311f) {
            return 0;        } else {
            if (features[12] <= -9.334408283233643f) {
                return 1;            } else {
                return 1;            }
        }
    }
}

// Tree 6
int predict_tree_6(const float* features) {
    // Max depth: 3
    if (features[24] <= 0.3098938763141632f) {
        if (features[25] <= 0.20442508906126022f) {
            return 1;        } else {
            if (features[26] <= -0.36891813576221466f) {
                return 0;            } else {
                return 1;            }
        }
    } else {
        if (features[20] <= 0.06422387063503265f) {
            if (features[7] <= 0.9022425226867199f) {
                return 1;            } else {
                return 0;            }
        } else {
            if (features[20] <= 0.06548794358968735f) {
                return 1;            } else {
                return 1;            }
        }
    }
}

// Tree 7
int predict_tree_7(const float* features) {
    // Max depth: 5
    if (features[0] <= 1.0607702732086182f) {
        if (features[9] <= -0.860076367855072f) {
            if (features[8] <= -0.07437900453805923f) {
                if (features[8] <= -0.07488589733839035f) {
                    if (features[33] <= 0.42352625727653503f) {
                        return 1;                    } else {
                        return 1;                    }
                } else {
                    return 0;                }
            } else {
                return 1;            }
        } else {
            if (features[3] <= 2.8444305658340454f) {
                return 1;            } else {
                return 0;            }
        }
    } else {
        if (features[20] <= 0.072991494089365f) {
            return 0;        } else {
            return 1;        }
    }
}

// Tree 8
int predict_tree_8(const float* features) {
    // Max depth: 3
    if (features[7] <= 1.528453767299652f) {
        if (features[26] <= -0.36987070739269257f) {
            return 1;        } else {
            return 1;        }
    } else {
        if (features[21] <= 0.18869606964290142f) {
            return 0;        } else {
            if (features[9] <= 0.4998035579919815f) {
                return 1;            } else {
                return 1;            }
        }
    }
}

// Tree 9
int predict_tree_9(const float* features) {
    // Max depth: 4
    if (features[7] <= 1.915327250957489f) {
        if (features[27] <= -0.30342911183834076f) {
            if (features[11] <= -0.026621083728969097f) {
                if (features[7] <= 1.087283879518509f) {
                    return 1;                } else {
                    return 0;                }
            } else {
                if (features[15] <= 0.7394949495792389f) {
                    return 1;                } else {
                    return 1;                }
            }
        } else {
            return 1;        }
    } else {
        if (features[6] <= -0.8916177749633789f) {
            return 0;        } else {
            return 1;        }
    }
}

// Tree 10
int predict_tree_10(const float* features) {
    // Max depth: 2
    if (features[3] <= 2.7539526224136353f) {
        if (features[16] <= 2.8937984704971313f) {
            return 1;        } else {
            return 1;        }
    } else {
        return 0;    }
}

// Tree 11
int predict_tree_11(const float* features) {
    // Max depth: 3
    if (features[2] <= -1.4903680682182312f) {
        if (features[18] <= -0.4997304230928421f) {
            if (features[16] <= 2.8937984704971313f) {
                return 1;            } else {
                return 1;            }
        } else {
            if (features[8] <= -0.061074500903487206f) {
                return 0;            } else {
                return 1;            }
        }
    } else {
        if (features[2] <= -1.4715943932533264f) {
            if (features[14] <= 0.820930689573288f) {
                return 1;            } else {
                return 0;            }
        } else {
            return 1;        }
    }
}

// Tree 12
int predict_tree_12(const float* features) {
    // Max depth: 2
    if (features[3] <= 2.671342372894287f) {
        if (features[18] <= -0.6181643009185791f) {
            return 1;        } else {
            return 1;        }
    } else {
        return 0;    }
}

// Tree 13
int predict_tree_13(const float* features) {
    // Max depth: 4
    if (features[25] <= 0.3121063858270645f) {
        if (features[23] <= 0.39625969529151917f) {
            if (features[3] <= 2.7539526224136353f) {
                return 1;            } else {
                return 0;            }
        } else {
            if (features[1] <= 1.1717284321784973f) {
                if (features[11] <= -1.1297289729118347f) {
                    return 1;                } else {
                    return 1;                }
            } else {
                return 0;            }
        }
    } else {
        if (features[22] <= 0.05740664713084698f) {
            if (features[12] <= 1.123494803905487f) {
                return 0;            } else {
                return 1;            }
        } else {
            if (features[27] <= -0.32119008898735046f) {
                return 1;            } else {
                return 1;            }
        }
    }
}

// Tree 14
int predict_tree_14(const float* features) {
    // Max depth: 5
    if (features[1] <= 0.9636527001857758f) {
        if (features[10] <= -0.5997242629528046f) {
            return 1;        } else {
            return 1;        }
    } else {
        if (features[8] <= -0.18528754264116287f) {
            if (features[20] <= 0.06868352368474007f) {
                if (features[10] <= 1.2955692410469055f) {
                    if (features[21] <= 0.06838300079107285f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    return 0;                }
            } else {
                if (features[5] <= 0.6303901374340057f) {
                    return 1;                } else {
                    return 1;                }
            }
        } else {
            if (features[7] <= 2.1607924699783325f) {
                if (features[4] <= 0.030253781005740166f) {
                    return 1;                } else {
                    return 1;                }
            } else {
                if (features[4] <= 0.16239316388964653f) {
                    return 0;                } else {
                    return 1;                }
            }
        }
    }
}

// Tree 15
int predict_tree_15(const float* features) {
    // Max depth: 3
    if (features[0] <= 1.0563396215438843f) {
        if (features[7] <= 2.1573853492736816f) {
            return 1;        } else {
            if (features[1] <= 0.8536505103111267f) {
                return 0;            } else {
                return 1;            }
        }
    } else {
        if (features[3] <= 1.4282537028193474f) {
            if (features[30] <= 0.1731601059436798f) {
                return 1;            } else {
                return 1;            }
        } else {
            return 0;        }
    }
}

// Tree 16
int predict_tree_16(const float* features) {
    // Max depth: 4
    if (features[19] <= 1.0642229318618774f) {
        if (features[1] <= 0.6995346546173096f) {
            if (features[7] <= 1.435052514076233f) {
                return 1;            } else {
                return 0;            }
        } else {
            if (features[22] <= 0.02354210038902238f) {
                return 0;            } else {
                if (features[1] <= 0.7301053106784821f) {
                    return 1;                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[3] <= 1.4321874901652336f) {
            if (features[7] <= -1.7643235921859741f) {
                return 1;            } else {
                return 1;            }
        } else {
            return 0;        }
    }
}

// Tree 17
int predict_tree_17(const float* features) {
    // Max depth: 6
    if (features[19] <= 1.0628926753997803f) {
        if (features[26] <= 2.1478153467178345f) {
            if (features[13] <= 2.511965751647949f) {
                if (features[0] <= 1.090687334537506f) {
                    if (features[4] <= -0.7537826299667358f) {
                        if (features[4] <= -0.7538230419158936f) {
                            return 1;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[18] <= 0.5954481661319733f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[31] <= 0.1600564420223236f) {
                    if (features[17] <= 0.25113406777381897f) {
                        return 1;                    } else {
                        return 0;                    }
                } else {
                    return 1;                }
            }
        } else {
            if (features[3] <= 1.8727759420871735f) {
                return 1;            } else {
                return 0;            }
        }
    } else {
        if (features[9] <= 0.056263819336891174f) {
            if (features[26] <= 1.1346710920333862f) {
                if (features[7] <= 0.992583017796278f) {
                    return 1;                } else {
                    return 0;                }
            } else {
                if (features[13] <= -0.25881914608180523f) {
                    return 1;                } else {
                    return 1;                }
            }
        } else {
            if (features[6] <= -1.0020799934864044f) {
                if (features[31] <= 0.1600564420223236f) {
                    if (features[10] <= 0.5917348563671112f) {
                        return 1;                    } else {
                        return 1;                    }
                } else {
                    return 0;                }
            } else {
                return 1;            }
        }
    }
}

// Tree 18
int predict_tree_18(const float* features) {
    // Max depth: 3
    if (features[7] <= 1.528453767299652f) {
        if (features[33] <= 0.42352625727653503f) {
            return 1;        } else {
            return 1;        }
    } else {
        if (features[9] <= 0.32768040895462036f) {
            return 0;        } else {
            if (features[2] <= 1.6823776960372925f) {
                return 1;            } else {
                return 1;            }
        }
    }
}

// Tree 19
int predict_tree_19(const float* features) {
    // Max depth: 2
    if (features[10] <= 0.9958629608154297f) {
        if (features[7] <= 1.429783046245575f) {
            return 1;        } else {
            return 0;        }
    } else {
        if (features[20] <= 0.072991494089365f) {
            return 0;        } else {
            return 1;        }
    }
}

// Tree 20
int predict_tree_20(const float* features) {
    // Max depth: 3
    if (features[2] <= -1.4715943932533264f) {
        if (features[7] <= 1.2812141180038452f) {
            if (features[1] <= -0.5840546786785126f) {
                return 1;            } else {
                return 1;            }
        } else {
            return 0;        }
    } else {
        if (features[25] <= -0.821080356836319f) {
            return 1;        } else {
            return 1;        }
    }
}

// Tree 21
int predict_tree_21(const float* features) {
    // Max depth: 4
    if (features[0] <= 1.060834527015686f) {
        if (features[11] <= 4.042905211448669f) {
            if (features[3] <= 2.2110848426818848f) {
                return 1;            } else {
                return 0;            }
        } else {
            return 0;        }
    } else {
        if (features[7] <= 1.8802969455718994f) {
            return 1;        } else {
            if (features[6] <= -0.8916177749633789f) {
                return 0;            } else {
                if (features[10] <= 1.2626928091049194f) {
                    return 1;                } else {
                    return 1;                }
            }
        }
    }
}

// Tree 22
int predict_tree_22(const float* features) {
    // Max depth: 4
    if (features[6] <= -1.0020799934864044f) {
        if (features[18] <= 1.0553300380706787f) {
            return 1;        } else {
            if (features[3] <= 1.3849815875291824f) {
                return 1;            } else {
                if (features[31] <= 0.1600564420223236f) {
                    return 0;                } else {
                    return 0;                }
            }
        }
    } else {
        if (features[8] <= -0.5342141538858414f) {
            return 1;        } else {
            return 1;        }
    }
}

// Tree 23
int predict_tree_23(const float* features) {
    // Max depth: 4
    if (features[8] <= -0.1860654577612877f) {
        if (features[1] <= 0.9465315937995911f) {
            if (features[23] <= 0.20218776166439056f) {
                return 1;            } else {
                if (features[2] <= -0.9722155034542084f) {
                    return 0;                } else {
                    return 1;                }
            }
        } else {
            if (features[22] <= 0.05805671587586403f) {
                return 0;            } else {
                if (features[11] <= -2.8869177103042603f) {
                    return 1;                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[3] <= 2.7539526224136353f) {
            return 1;        } else {
            return 0;        }
    }
}

// Tree 24
int predict_tree_24(const float* features) {
    // Max depth: 5
    if (features[0] <= 1.060834527015686f) {
        if (features[16] <= 2.8937984704971313f) {
            if (features[4] <= -0.7537826299667358f) {
                if (features[7] <= 1.0273118615150452f) {
                    if (features[9] <= -0.9425616264343262f) {
                        return 1;                    } else {
                        return 1;                    }
                } else {
                    return 0;                }
            } else {
                return 1;            }
        } else {
            if (features[3] <= 1.9475185573101044f) {
                if (features[17] <= -0.5920916199684143f) {
                    return 1;                } else {
                    return 1;                }
            } else {
                return 0;            }
        }
    } else {
        if (features[8] <= -0.15732450038194656f) {
            if (features[3] <= 1.4282537028193474f) {
                return 1;            } else {
                return 0;            }
        } else {
            if (features[5] <= -0.08687134832143784f) {
                return 1;            } else {
                return 1;            }
        }
    }
}

// Tree 25
int predict_tree_25(const float* features) {
    // Max depth: 4
    if (features[1] <= 0.9473907649517059f) {
        if (features[7] <= 1.435052514076233f) {
            if (features[33] <= 0.42352625727653503f) {
                return 1;            } else {
                return 1;            }
        } else {
            return 0;        }
    } else {
        if (features[7] <= 1.8840453624725342f) {
            if (features[10] <= 0.9170531928539276f) {
                return 1;            } else {
                return 1;            }
        } else {
            if (features[4] <= 0.19700661674141884f) {
                return 0;            } else {
                if (features[27] <= -0.11907272040843964f) {
                    return 1;                } else {
                    return 1;                }
            }
        }
    }
}

// Tree 26
int predict_tree_26(const float* features) {
    // Max depth: 2
    if (features[3] <= 2.258290708065033f) {
        if (features[26] <= -0.36987070739269257f) {
            return 1;        } else {
            return 1;        }
    } else {
        return 0;    }
}

// Tree 27
int predict_tree_27(const float* features) {
    // Max depth: 4
    if (features[5] <= 0.3235636204481125f) {
        if (features[5] <= 0.30339622497558594f) {
            return 1;        } else {
            if (features[20] <= 0.004680894315242767f) {
                return 0;            } else {
                if (features[3] <= -1.4052802324295044f) {
                    return 1;                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[2] <= -0.9844183623790741f) {
            return 0;        } else {
            if (features[0] <= -0.5934189856052399f) {
                return 1;            } else {
                return 1;            }
        }
    }
}

// Tree 28
int predict_tree_28(const float* features) {
    // Max depth: 3
    if (features[2] <= -1.4715943932533264f) {
        if (features[17] <= -0.5059880614280701f) {
            if (features[20] <= -0.8259679079055786f) {
                return 1;            } else {
                return 1;            }
        } else {
            if (features[3] <= 1.8924450278282166f) {
                return 1;            } else {
                return 0;            }
        }
    } else {
        if (features[2] <= -1.4528207778930664f) {
            return 1;        } else {
            return 1;        }
    }
}

// Tree 29
int predict_tree_29(const float* features) {
    // Max depth: 4
    if (features[17] <= 1.0640507936477661f) {
        if (features[1] <= 0.6996140778064728f) {
            if (features[7] <= 1.435052514076233f) {
                return 1;            } else {
                return 0;            }
        } else {
            if (features[2] <= -0.6737145707011223f) {
                return 0;            } else {
                if (features[21] <= 0.08583112806081772f) {
                    return 1;                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[21] <= 0.06838300079107285f) {
            return 0;        } else {
            if (features[10] <= 0.65773706138134f) {
                return 1;            } else {
                return 1;            }
        }
    }
}

// Tree 30
int predict_tree_30(const float* features) {
    // Max depth: 5
    if (features[1] <= 0.9565069377422333f) {
        if (features[14] <= 4.186407089233398f) {
            if (features[21] <= -0.751983106136322f) {
                if (features[3] <= 2.7539526224136353f) {
                    return 1;                } else {
                    return 0;                }
            } else {
                return 1;            }
        } else {
            if (features[0] <= 0.5116741731762886f) {
                return 1;            } else {
                if (features[2] <= -0.3921099305152893f) {
                    return 0;                } else {
                    if (features[5] <= 0.6827218234539032f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            }
        }
    } else {
        if (features[7] <= 1.9096187353134155f) {
            return 1;        } else {
            if (features[3] <= 1.3141727447509766f) {
                return 1;            } else {
                return 0;            }
        }
    }
}

// Tree 31
int predict_tree_31(const float* features) {
    // Max depth: 4
    if (features[2] <= -1.4715943932533264f) {
        if (features[19] <= -0.5003673136234283f) {
            if (features[15] <= 0.7394949495792389f) {
                return 1;            } else {
                return 1;            }
        } else {
            if (features[8] <= -0.07247438281774521f) {
                return 0;            } else {
                if (features[5] <= -0.6586743295192719f) {
                    return 1;                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[8] <= -0.45406824350357056f) {
            return 1;        } else {
            return 1;        }
    }
}

// Tree 32
int predict_tree_32(const float* features) {
    // Max depth: 3
    if (features[19] <= 1.0607203841209412f) {
        if (features[7] <= 1.7287055850028992f) {
            return 1;        } else {
            return 0;        }
    } else {
        if (features[22] <= 0.06979859247803688f) {
            if (features[10] <= 0.6554822027683258f) {
                return 1;            } else {
                return 0;            }
        } else {
            return 1;        }
    }
}

// Tree 33
int predict_tree_33(const float* features) {
    // Max depth: 4
    if (features[6] <= -1.0020799934864044f) {
        if (features[23] <= 0.32221148908138275f) {
            if (features[7] <= 1.540424883365631f) {
                if (features[0] <= -0.5958373844623566f) {
                    return 1;                } else {
                    return 1;                }
            } else {
                if (features[10] <= 1.9055832028388977f) {
                    return 0;                } else {
                    return 0;                }
            }
        } else {
            if (features[25] <= 0.7427738010883331f) {
                if (features[21] <= 0.0881818663328886f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                return 1;            }
        }
    } else {
        if (features[3] <= -2.1515268087387085f) {
            return 1;        } else {
            return 1;        }
    }
}

// Tree 34
int predict_tree_34(const float* features) {
    // Max depth: 4
    if (features[17] <= 1.0640507936477661f) {
        if (features[25] <= -0.6672540605068207f) {
            if (features[3] <= 2.1874818801879883f) {
                return 1;            } else {
                return 0;            }
        } else {
            if (features[9] <= -0.8804697692394257f) {
                return 1;            } else {
                return 1;            }
        }
    } else {
        if (features[9] <= 0.05907308869063854f) {
            if (features[6] <= -1.0020799934864044f) {
                return 0;            } else {
                if (features[10] <= 1.1988133192062378f) {
                    return 1;                } else {
                    return 1;                }
            }
        } else {
            if (features[3] <= 1.5620037391781807f) {
                if (features[19] <= 0.2514533996582031f) {
                    return 1;                } else {
                    return 1;                }
            } else {
                return 0;            }
        }
    }
}

// Tree 35
int predict_tree_35(const float* features) {
    // Max depth: 5
    if (features[23] <= 0.3247443735599518f) {
        if (features[25] <= 0.39388830959796906f) {
            if (features[12] <= 3.5933682918548584f) {
                if (features[19] <= -0.6179588735103607f) {
                    return 1;                } else {
                    return 1;                }
            } else {
                if (features[10] <= 1.0587532222270966f) {
                    return 0;                } else {
                    if (features[17] <= 0.985954076051712f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            }
        } else {
            if (features[7] <= 1.5180916488170624f) {
                return 1;            } else {
                return 0;            }
        }
    } else {
        if (features[22] <= 0.05805671587586403f) {
            if (features[18] <= 0.6908564567565918f) {
                return 1;            } else {
                return 0;            }
        } else {
            return 1;        }
    }
}

// Tree 36
int predict_tree_36(const float* features) {
    // Max depth: 2
    if (features[3] <= 2.793290853500366f) {
        if (features[27] <= -0.3279092609882355f) {
            return 1;        } else {
            return 1;        }
    } else {
        return 0;    }
}

// Tree 37
int predict_tree_37(const float* features) {
    // Max depth: 6
    if (features[2] <= -1.4715943932533264f) {
        if (features[18] <= -0.013787716627120972f) {
            if (features[19] <= -0.5003673136234283f) {
                if (features[24] <= -0.8401668071746826f) {
                    return 1;                } else {
                    return 1;                }
            } else {
                if (features[4] <= -0.7538634538650513f) {
                    if (features[20] <= -0.768508106470108f) {
                        return 1;                    } else {
                        return 1;                    }
                } else {
                    if (features[5] <= -0.6433593928813934f) {
                        return 0;                    } else {
                        if (features[5] <= -0.6203917562961578f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            }
        } else {
            return 0;        }
    } else {
        if (features[25] <= -0.8262139856815338f) {
            return 1;        } else {
            return 1;        }
    }
}

// Tree 38
int predict_tree_38(const float* features) {
    // Max depth: 6
    if (features[0] <= 1.0608671307563782f) {
        if (features[0] <= 0.8025825023651123f) {
            if (features[2] <= -1.71565181016922f) {
                if (features[12] <= -0.021745516918599606f) {
                    if (features[2] <= -1.7438122630119324f) {
                        if (features[18] <= -0.5555682182312012f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        if (features[7] <= 1.0881958603858948f) {
                            return 1;                        } else {
                            return 0;                        }
                    }
                } else {
                    return 1;                }
            } else {
                return 1;            }
        } else {
            if (features[16] <= 2.8937984704971313f) {
                return 1;            } else {
                if (features[27] <= 0.3451301008462906f) {
                    return 0;                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[6] <= -1.0020799934864044f) {
            if (features[14] <= 3.3568601608276367f) {
                return 0;            } else {
                if (features[23] <= 0.3349621966481209f) {
                    return 1;                } else {
                    return 1;                }
            }
        } else {
            if (features[31] <= 0.1600564420223236f) {
                return 1;            } else {
                return 1;            }
        }
    }
}

// Tree 39
int predict_tree_39(const float* features) {
    // Max depth: 3
    if (features[2] <= -1.4903680682182312f) {
        if (features[7] <= 0.2673814594745636f) {
            if (features[17] <= -0.6178421676158905f) {
                return 1;            } else {
                return 1;            }
        } else {
            return 0;        }
    } else {
        if (features[2] <= -1.4715943932533264f) {
            if (features[23] <= -0.1298203319311142f) {
                return 1;            } else {
                return 0;            }
        } else {
            if (features[9] <= -0.9195708930492401f) {
                return 1;            } else {
                return 1;            }
        }
    }
}

// Tree 40
int predict_tree_40(const float* features) {
    // Max depth: 4
    if (features[7] <= 1.8840453624725342f) {
        if (features[2] <= -1.71565181016922f) {
            if (features[2] <= -1.73442542552948f) {
                if (features[18] <= -0.6181643009185791f) {
                    return 1;                } else {
                    return 1;                }
            } else {
                if (features[33] <= 0.42352625727653503f) {
                    return 0;                } else {
                    return 1;                }
            }
        } else {
            return 1;        }
    } else {
        if (features[9] <= 0.3665752410888672f) {
            if (features[24] <= 0.2536586970090866f) {
                return 0;            } else {
                return 0;            }
        } else {
            if (features[13] <= -4.320123910903931f) {
                return 1;            } else {
                return 1;            }
        }
    }
}

// Tree 41
int predict_tree_41(const float* features) {
    // Max depth: 3
    if (features[7] <= 1.8802969455718994f) {
        if (features[15] <= 0.7394949495792389f) {
            return 1;        } else {
            return 1;        }
    } else {
        if (features[9] <= 0.3625824451446533f) {
            if (features[11] <= -0.7431043386459351f) {
                return 0;            } else {
                return 0;            }
        } else {
            return 1;        }
    }
}

// Tree 42
int predict_tree_42(const float* features) {
    // Max depth: 5
    if (features[19] <= 1.0641616582870483f) {
        if (features[12] <= -0.022147592157125473f) {
            if (features[12] <= -0.022159376181662083f) {
                if (features[15] <= 0.7394949495792389f) {
                    return 1;                } else {
                    return 1;                }
            } else {
                return 0;            }
        } else {
            return 1;        }
    } else {
        if (features[4] <= 0.07257596403360367f) {
            if (features[24] <= 0.26642850786447525f) {
                return 1;            } else {
                if (features[13] <= -0.2659398317337036f) {
                    return 1;                } else {
                    if (features[23] <= 0.2609235867857933f) {
                        return 1;                    } else {
                        return 0;                    }
                }
            }
        } else {
            if (features[21] <= 0.09228551760315895f) {
                return 1;            } else {
                return 1;            }
        }
    }
}

// Tree 43
int predict_tree_43(const float* features) {
    // Max depth: 3
    if (features[17] <= 1.062720775604248f) {
        if (features[0] <= -0.5030164420604706f) {
            return 1;        } else {
            if (features[0] <= -0.5029934048652649f) {
                return 0;            } else {
                return 1;            }
        }
    } else {
        if (features[22] <= 0.06929072551429272f) {
            return 0;        } else {
            if (features[0] <= 0.6489271074533463f) {
                return 1;            } else {
                return 1;            }
        }
    }
}

// Tree 44
int predict_tree_44(const float* features) {
    // Max depth: 7
    if (features[18] <= 1.0634503364562988f) {
        if (features[14] <= 4.186580419540405f) {
            if (features[11] <= 3.0956791639328003f) {
                if (features[20] <= -0.7517009675502777f) {
                    if (features[12] <= -0.021941850893199444f) {
                        if (features[10] <= -0.4844386875629425f) {
                            return 1;                        } else {
                            if (features[19] <= -0.487867146730423f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    } else {
                        return 1;                    }
                } else {
                    return 1;                }
            } else {
                if (features[6] <= -1.2230044305324554f) {
                    return 0;                } else {
                    return 1;                }
            }
        } else {
            if (features[9] <= 0.12530377972871065f) {
                if (features[14] <= 5.108626365661621f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                return 1;            }
        }
    } else {
        if (features[9] <= 0.05716391280293465f) {
            if (features[5] <= 0.8984161615371704f) {
                if (features[10] <= 0.9301311373710632f) {
                    return 1;                } else {
                    return 0;                }
            } else {
                if (features[14] <= -0.47007228434085846f) {
                    return 1;                } else {
                    return 1;                }
            }
        } else {
            if (features[2] <= -0.7581959441304207f) {
                return 0;            } else {
                return 1;            }
        }
    }
}

// Tree 45
int predict_tree_45(const float* features) {
    // Max depth: 5
    if (features[10] <= 0.7445376217365265f) {
        if (features[12] <= -7.084193587303162f) {
            return 1;        } else {
            return 1;        }
    } else {
        if (features[9] <= 0.05716391280293465f) {
            if (features[10] <= 0.9411464035511017f) {
                if (features[7] <= 1.0242661759257317f) {
                    return 1;                } else {
                    return 0;                }
            } else {
                if (features[6] <= -1.0020799934864044f) {
                    return 0;                } else {
                    if (features[15] <= 0.7394949495792389f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            }
        } else {
            if (features[22] <= 7.5623393058776855e-06f) {
                return 0;            } else {
                if (features[23] <= -0.09149139374494553f) {
                    return 1;                } else {
                    return 1;                }
            }
        }
    }
}

// Tree 46
int predict_tree_46(const float* features) {
    // Max depth: 4
    if (features[26] <= -0.3180300444364548f) {
        if (features[7] <= 1.435052514076233f) {
            if (features[3] <= -1.520541250705719f) {
                return 1;            } else {
                return 1;            }
        } else {
            return 0;        }
    } else {
        if (features[6] <= -1.0020799934864044f) {
            if (features[21] <= 0.09441334009170532f) {
                if (features[23] <= 0.12301623448729515f) {
                    return 1;                } else {
                    return 0;                }
            } else {
                if (features[15] <= 0.7394949495792389f) {
                    return 1;                } else {
                    return 1;                }
            }
        } else {
            if (features[5] <= -0.7684394717216492f) {
                return 1;            } else {
                return 1;            }
        }
    }
}

// Tree 47
int predict_tree_47(const float* features) {
    // Max depth: 5
    if (features[1] <= 0.9458443522453308f) {
        if (features[30] <= 0.1731601059436798f) {
            return 1;        } else {
            return 1;        }
    } else {
        if (features[26] <= 1.0658167004585266f) {
            if (features[9] <= 0.06237944774329662f) {
                if (features[24] <= 0.8899985253810883f) {
                    return 0;                } else {
                    if (features[10] <= 1.2610373497009277f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            } else {
                return 1;            }
        } else {
            if (features[3] <= 1.5620037391781807f) {
                return 1;            } else {
                return 0;            }
        }
    }
}

// Tree 48
int predict_tree_48(const float* features) {
    // Max depth: 4
    if (features[6] <= -1.0020799934864044f) {
        if (features[0] <= 0.8014679849147797f) {
            if (features[21] <= -0.6070785224437714f) {
                return 1;            } else {
                return 1;            }
        } else {
            if (features[22] <= 0.16500326991081238f) {
                return 0;            } else {
                if (features[16] <= 2.8937984704971313f) {
                    return 1;                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[3] <= 2.7539526224136353f) {
            return 1;        } else {
            return 0;        }
    }
}

// Tree 49
int predict_tree_49(const float* features) {
    // Max depth: 3
    if (features[18] <= 1.0631850361824036f) {
        if (features[7] <= 1.435052514076233f) {
            return 1;        } else {
            if (features[3] <= 1.1961580514907837f) {
                return 1;            } else {
                return 0;            }
        }
    } else {
        if (features[2] <= -0.6643277481198311f) {
            return 0;        } else {
            return 1;        }
    }
}

// Tree 50
int predict_tree_50(const float* features) {
    // Max depth: 2
    if (features[3] <= 2.793290853500366f) {
        if (features[0] <= -0.6175902783870697f) {
            return 1;        } else {
            return 1;        }
    } else {
        return 0;    }
}

// Tree 51
int predict_tree_51(const float* features) {
    // Max depth: 3
    if (features[0] <= 1.0607702732086182f) {
        if (features[12] <= 3.170227527618408f) {
            return 1;        } else {
            return 0;        }
    } else {
        if (features[6] <= -1.0020799934864044f) {
            if (features[20] <= 0.8684181272983551f) {
                return 0;            } else {
                return 1;            }
        } else {
            return 1;        }
    }
}

// Tree 52
int predict_tree_52(const float* features) {
    // Max depth: 4
    if (features[6] <= -1.0020799934864044f) {
        if (features[23] <= 0.32221148908138275f) {
            if (features[0] <= 0.8014679849147797f) {
                if (features[23] <= -0.6073631346225739f) {
                    return 1;                } else {
                    return 1;                }
            } else {
                if (features[9] <= 0.1764024393633008f) {
                    return 0;                } else {
                    return 1;                }
            }
        } else {
            if (features[4] <= 0.21228261291980743f) {
                return 0;            } else {
                if (features[3] <= -1.3136221170425415f) {
                    return 1;                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[22] <= -0.7577395439147949f) {
            if (features[21] <= -0.7522870898246765f) {
                return 1;            } else {
                if (features[2] <= -0.9647060707211494f) {
                    return 0;                } else {
                    return 1;                }
            }
        } else {
            if (features[14] <= -7.907240390777588f) {
                return 1;            } else {
                return 1;            }
        }
    }
}

// Tree 53
int predict_tree_53(const float* features) {
    // Max depth: 2
    if (features[3] <= 2.671342372894287f) {
        if (features[1] <= -0.5840684175491333f) {
            return 1;        } else {
            return 1;        }
    } else {
        return 0;    }
}

// Tree 54
int predict_tree_54(const float* features) {
    // Max depth: 2
    if (features[3] <= 2.2110848426818848f) {
        if (features[13] <= -10.865082263946533f) {
            return 1;        } else {
            return 1;        }
    } else {
        return 0;    }
}

// Tree 55
int predict_tree_55(const float* features) {
    // Max depth: 3
    if (features[1] <= 0.9473907649517059f) {
        if (features[27] <= -0.32800567150115967f) {
            if (features[17] <= 0.25113406777381897f) {
                return 1;            } else {
                return 0;            }
        } else {
            if (features[3] <= 2.7539526224136353f) {
                return 1;            } else {
                return 0;            }
        }
    } else {
        if (features[22] <= 0.06979859247803688f) {
            return 0;        } else {
            return 1;        }
    }
}

// Tree 56
int predict_tree_56(const float* features) {
    // Max depth: 3
    if (features[2] <= -1.4715943932533264f) {
        if (features[17] <= -0.0045025646686553955f) {
            if (features[1] <= -0.5840546786785126f) {
                return 1;            } else {
                return 1;            }
        } else {
            return 0;        }
    } else {
        if (features[25] <= -0.821080356836319f) {
            return 1;        } else {
            return 1;        }
    }
}

// Tree 57
int predict_tree_57(const float* features) {
    // Max depth: 4
    if (features[2] <= -1.4903680682182312f) {
        if (features[23] <= 0.18941785022616386f) {
            return 1;        } else {
            if (features[30] <= 0.1731601059436798f) {
                return 0;            } else {
                return 0;            }
        }
    } else {
        if (features[6] <= -1.4439288973808289f) {
            if (features[2] <= -1.0773479044437408f) {
                return 0;            } else {
                if (features[24] <= -0.288165345788002f) {
                    return 1;                } else {
                    return 1;                }
            }
        } else {
            return 1;        }
    }
}

// Tree 58
int predict_tree_58(const float* features) {
    // Max depth: 6
    if (features[7] <= 1.8802969455718994f) {
        if (features[2] <= -1.71565181016922f) {
            if (features[6] <= -0.11838206276297569f) {
                return 1;            } else {
                if (features[11] <= -0.02665849681943655f) {
                    if (features[8] <= -0.07138924673199654f) {
                        return 0;                    } else {
                        if (features[24] <= -0.6331614553928375f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                } else {
                    return 1;                }
            }
        } else {
            return 1;        }
    } else {
        if (features[26] <= 1.1447789072990417f) {
            if (features[27] <= 1.7257922887802124f) {
                if (features[4] <= 0.35553546994924545f) {
                    return 0;                } else {
                    if (features[34] <= -2.028429754078388f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            } else {
                return 1;            }
        } else {
            if (features[31] <= 0.1600564420223236f) {
                return 1;            } else {
                return 1;            }
        }
    }
}

// Tree 59
int predict_tree_59(const float* features) {
    // Max depth: 5
    if (features[0] <= 1.0607702732086182f) {
        if (features[11] <= -0.02674653474241495f) {
            if (features[26] <= -0.35149693489074707f) {
                if (features[24] <= -0.6357250213623047f) {
                    if (features[12] <= -0.020333455875515938f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[31] <= 0.1600564420223236f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            } else {
                return 1;            }
        } else {
            if (features[27] <= -0.32800567150115967f) {
                return 1;            } else {
                return 1;            }
        }
    } else {
        if (features[7] <= 1.9096187353134155f) {
            if (features[6] <= -1.0020799934864044f) {
                return 1;            } else {
                return 1;            }
        } else {
            if (features[2] <= 0.2931280732154846f) {
                return 0;            } else {
                return 1;            }
        }
    }
}

// Tree 60
int predict_tree_60(const float* features) {
    // Max depth: 5
    if (features[19] <= 1.0628314018249512f) {
        if (features[1] <= 1.183271050453186f) {
            if (features[1] <= 0.6995346546173096f) {
                if (features[7] <= 1.435052514076233f) {
                    if (features[17] <= -0.6178421676158905f) {
                        return 1;                    } else {
                        return 1;                    }
                } else {
                    return 0;                }
            } else {
                if (features[17] <= 0.45283323526382446f) {
                    return 0;                } else {
                    return 1;                }
            }
        } else {
            if (features[1] <= 1.2416986227035522f) {
                return 0;            } else {
                if (features[17] <= 1.1205748915672302f) {
                    return 1;                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[3] <= 1.4361213520169258f) {
            if (features[8] <= -0.32535040378570557f) {
                return 1;            } else {
                return 1;            }
        } else {
            if (features[5] <= 0.3062252253293991f) {
                return 0;            } else {
                return 0;            }
        }
    }
}

// Tree 61
int predict_tree_61(const float* features) {
    // Max depth: 2
    if (features[3] <= 2.7539526224136353f) {
        if (features[23] <= -0.8397544026374817f) {
            return 1;        } else {
            return 1;        }
    } else {
        return 0;    }
}

// Tree 62
int predict_tree_62(const float* features) {
    // Max depth: 6
    if (features[19] <= 1.0628314018249512f) {
        if (features[17] <= 0.8037545680999756f) {
            if (features[12] <= 3.170227527618408f) {
                if (features[12] <= -0.022147592157125473f) {
                    if (features[3] <= 2.0655333399772644f) {
                        if (features[27] <= -0.3276952654123306f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        return 0;                    }
                } else {
                    return 1;                }
            } else {
                return 0;            }
        } else {
            if (features[2] <= -0.6643277481198311f) {
                return 0;            } else {
                if (features[24] <= 0.023629273287951946f) {
                    return 1;                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[2] <= -0.6643277481198311f) {
            return 0;        } else {
            if (features[8] <= -0.3569862097501755f) {
                return 1;            } else {
                return 1;            }
        }
    }
}

// Tree 63
int predict_tree_63(const float* features) {
    // Max depth: 3
    if (features[0] <= 1.060834527015686f) {
        if (features[8] <= -0.5467018187046051f) {
            return 1;        } else {
            return 1;        }
    } else {
        if (features[20] <= 0.06705539673566818f) {
            return 0;        } else {
            if (features[1] <= 0.8721887469291687f) {
                return 1;            } else {
                return 1;            }
        }
    }
}

// Tree 64
int predict_tree_64(const float* features) {
    // Max depth: 4
    if (features[18] <= 1.0631850361824036f) {
        if (features[14] <= 4.186580419540405f) {
            if (features[3] <= 2.7539526224136353f) {
                if (features[31] <= 0.1600564420223236f) {
                    return 1;                } else {
                    return 1;                }
            } else {
                if (features[3] <= 3.0371880531311035f) {
                    return 0;                } else {
                    return 0;                }
            }
        } else {
            if (features[21] <= 0.029454011470079422f) {
                if (features[4] <= -0.042559773894026875f) {
                    return 1;                } else {
                    return 0;                }
            } else {
                return 1;            }
        }
    } else {
        if (features[2] <= -0.6643277481198311f) {
            return 0;        } else {
            return 1;        }
    }
}

// Tree 65
int predict_tree_65(const float* features) {
    // Max depth: 3
    if (features[7] <= 1.9091759324073792f) {
        if (features[9] <= -0.9425616264343262f) {
            return 1;        } else {
            return 1;        }
    } else {
        if (features[2] <= 0.2555807828903198f) {
            return 0;        } else {
            if (features[3] <= -1.588989794254303f) {
                return 1;            } else {
                return 1;            }
        }
    }
}

// Tree 66
int predict_tree_66(const float* features) {
    // Max depth: 5
    if (features[10] <= 0.9958629608154297f) {
        if (features[3] <= 2.8444305658340454f) {
            return 1;        } else {
            return 0;        }
    } else {
        if (features[5] <= 0.29091985523700714f) {
            return 1;        } else {
            if (features[4] <= 0.07257596403360367f) {
                return 0;            } else {
                if (features[7] <= 1.3673575222492218f) {
                    if (features[16] <= 2.8937984704971313f) {
                        return 1;                    } else {
                        return 1;                    }
                } else {
                    return 0;                }
            }
        }
    }
}

// Tree 67
int predict_tree_67(const float* features) {
    // Max depth: 4
    if (features[18] <= 1.0647811889648438f) {
        if (features[17] <= 1.2618278861045837f) {
            if (features[28] <= -0.4696833360940218f) {
                return 1;            } else {
                return 1;            }
        } else {
            if (features[19] <= 0.377274289727211f) {
                if (features[4] <= 0.10370383784174919f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                return 1;            }
        }
    } else {
        if (features[20] <= 0.072991494089365f) {
            if (features[5] <= 0.2679426372051239f) {
                return 1;            } else {
                return 0;            }
        } else {
            if (features[0] <= 0.10526351630687714f) {
                return 1;            } else {
                return 1;            }
        }
    }
}

// Tree 68
int predict_tree_68(const float* features) {
    // Max depth: 3
    if (features[22] <= -0.12442991137504578f) {
        return 1;    } else {
        if (features[7] <= 1.8840453624725342f) {
            if (features[14] <= -14.2560715675354f) {
                return 1;            } else {
                return 1;            }
        } else {
            if (features[5] <= 0.2807067036628723f) {
                return 1;            } else {
                return 0;            }
        }
    }
}

// Tree 69
int predict_tree_69(const float* features) {
    // Max depth: 4
    if (features[2] <= -1.4715943932533264f) {
        if (features[25] <= 0.14802243560552597f) {
            if (features[0] <= -0.5042563676834106f) {
                if (features[10] <= -0.5997165143489838f) {
                    return 1;                } else {
                    return 1;                }
            } else {
                if (features[1] <= -0.46365900337696075f) {
                    return 0;                } else {
                    return 1;                }
            }
        } else {
            return 0;        }
    } else {
        if (features[10] <= -0.5996964573860168f) {
            return 1;        } else {
            return 1;        }
    }
}

// Tree 70
int predict_tree_70(const float* features) {
    // Max depth: 5
    if (features[10] <= 0.9940153360366821f) {
        if (features[3] <= 2.258290708065033f) {
            if (features[0] <= -0.6175902783870697f) {
                return 1;            } else {
                return 1;            }
        } else {
            return 0;        }
    } else {
        if (features[6] <= -1.0020799934864044f) {
            if (features[13] <= 3.4908506870269775f) {
                if (features[20] <= 1.1275129616260529f) {
                    return 0;                } else {
                    if (features[18] <= 1.3798407316207886f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[22] <= 1.249318778514862f) {
                    return 1;                } else {
                    return 1;                }
            }
        } else {
            if (features[34] <= -2.028429754078388f) {
                return 1;            } else {
                return 1;            }
        }
    }
}

// Tree 71
int predict_tree_71(const float* features) {
    // Max depth: 6
    if (features[7] <= 1.8840453624725342f) {
        if (features[12] <= -0.02215015795081854f) {
            if (features[5] <= -0.6484611630439758f) {
                if (features[33] <= 0.42352625727653503f) {
                    if (features[23] <= -0.6380070745944977f) {
                        if (features[31] <= 0.1600564420223236f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        return 0;                    }
                } else {
                    return 1;                }
            } else {
                return 1;            }
        } else {
            return 1;        }
    } else {
        if (features[20] <= 0.24559330940246582f) {
            return 0;        } else {
            if (features[5] <= -0.0588019248098135f) {
                return 1;            } else {
                return 1;            }
        }
    }
}

// Tree 72
int predict_tree_72(const float* features) {
    // Max depth: 3
    if (features[7] <= 1.9022418856620789f) {
        if (features[29] <= -0.5035721659660339f) {
            return 1;        } else {
            return 1;        }
    } else {
        if (features[2] <= 0.2555807828903198f) {
            if (features[20] <= -0.1075386069715023f) {
                return 0;            } else {
                return 0;            }
        } else {
            return 1;        }
    }
}

// Tree 73
int predict_tree_73(const float* features) {
    // Max depth: 4
    if (features[17] <= 1.0640507936477661f) {
        if (features[2] <= -1.4715943932533264f) {
            if (features[10] <= -0.4844386875629425f) {
                if (features[13] <= -1.2228345274925232f) {
                    return 1;                } else {
                    return 1;                }
            } else {
                if (features[7] <= 1.2812141180038452f) {
                    return 1;                } else {
                    return 0;                }
            }
        } else {
            return 1;        }
    } else {
        if (features[9] <= 0.03148012515157461f) {
            if (features[2] <= -0.5986199975013733f) {
                return 0;            } else {
                if (features[0] <= 1.0301050543785095f) {
                    return 1;                } else {
                    return 1;                }
            }
        } else {
            if (features[27] <= -0.3209357261657715f) {
                return 1;            } else {
                return 1;            }
        }
    }
}

// Tree 74
int predict_tree_74(const float* features) {
    // Max depth: 2
    if (features[3] <= 2.7539526224136353f) {
        if (features[31] <= 0.1600564420223236f) {
            return 1;        } else {
            return 1;        }
    } else {
        return 0;    }
}

// Tree 75
int predict_tree_75(const float* features) {
    // Max depth: 5
    if (features[17] <= 1.0647898316383362f) {
        if (features[27] <= -0.32800567150115967f) {
            if (features[18] <= 0.25135572999715805f) {
                return 1;            } else {
                return 0;            }
        } else {
            if (features[13] <= -0.05776446312665939f) {
                if (features[3] <= 2.671342372894287f) {
                    if (features[9] <= -0.9249884188175201f) {
                        return 1;                    } else {
                        return 1;                    }
                } else {
                    return 0;                }
            } else {
                return 1;            }
        }
    } else {
        if (features[8] <= -0.15109679847955704f) {
            if (features[4] <= 0.06664540059864521f) {
                if (features[19] <= 3.038197875022888f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                if (features[17] <= 1.0676741003990173f) {
                    return 1;                } else {
                    return 1;                }
            }
        } else {
            if (features[4] <= 0.129426509141922f) {
                return 1;            } else {
                return 1;            }
        }
    }
}

// Tree 76
int predict_tree_76(const float* features) {
    // Max depth: 4
    if (features[25] <= 0.3121063858270645f) {
        if (features[19] <= 2.1551835536956787f) {
            if (features[6] <= -1.4439288973808289f) {
                if (features[2] <= -1.0773479044437408f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                return 1;            }
        } else {
            if (features[7] <= 2.1650023460388184f) {
                return 1;            } else {
                if (features[23] <= 0.31965942680835724f) {
                    return 1;                } else {
                    return 0;                }
            }
        }
    } else {
        if (features[2] <= -0.988173097372055f) {
            return 0;        } else {
            if (features[16] <= 2.8937984704971313f) {
                return 1;            } else {
                return 1;            }
        }
    }
}

// Tree 77
int predict_tree_77(const float* features) {
    // Max depth: 3
    if (features[7] <= 1.8802969455718994f) {
        if (features[11] <= -10.75693941116333f) {
            return 1;        } else {
            return 1;        }
    } else {
        if (features[20] <= 0.2010372057557106f) {
            return 0;        } else {
            if (features[28] <= 0.032488465309143066f) {
                return 1;            } else {
                return 1;            }
        }
    }
}

// Tree 78
int predict_tree_78(const float* features) {
    // Max depth: 4
    if (features[5] <= 0.3235636204481125f) {
        if (features[17] <= 2.350967049598694f) {
            if (features[24] <= 0.4409908503293991f) {
                return 1;            } else {
                if (features[24] <= 0.44457216560840607f) {
                    return 0;                } else {
                    return 1;                }
            }
        } else {
            if (features[9] <= -0.028121059760451317f) {
                return 0;            } else {
                return 1;            }
        }
    } else {
        if (features[2] <= -0.988173097372055f) {
            return 0;        } else {
            if (features[15] <= 0.7394949495792389f) {
                return 1;            } else {
                return 1;            }
        }
    }
}

// Tree 79
int predict_tree_79(const float* features) {
    // Max depth: 4
    if (features[5] <= 0.3235636204481125f) {
        if (features[7] <= 2.1607924699783325f) {
            if (features[19] <= -0.6179588735103607f) {
                return 1;            } else {
                return 1;            }
        } else {
            if (features[6] <= -1.002079963684082f) {
                return 0;            } else {
                if (features[2] <= 2.123558282852173f) {
                    return 1;                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[1] <= 0.9465315937995911f) {
            return 1;        } else {
            if (features[21] <= 0.07036896422505379f) {
                return 0;            } else {
                if (features[18] <= 0.4397708773612976f) {
                    return 1;                } else {
                    return 1;                }
            }
        }
    }
}

// Tree 80
int predict_tree_80(const float* features) {
    // Max depth: 3
    if (features[2] <= -1.4715943932533264f) {
        if (features[3] <= 2.7539526224136353f) {
            if (features[33] <= 0.42352625727653503f) {
                return 1;            } else {
                return 1;            }
        } else {
            return 0;        }
    } else {
        if (features[22] <= -0.8082925975322723f) {
            return 1;        } else {
            return 1;        }
    }
}

// Tree 81
int predict_tree_81(const float* features) {
    // Max depth: 2
    if (features[3] <= 2.671342372894287f) {
        if (features[9] <= -0.9426045715808868f) {
            return 1;        } else {
            return 1;        }
    } else {
        return 0;    }
}

// Tree 82
int predict_tree_82(const float* features) {
    // Max depth: 3
    if (features[1] <= 0.9449993073940277f) {
        if (features[13] <= 2.511965751647949f) {
            return 1;        } else {
            if (features[13] <= 2.5251599550247192f) {
                return 0;            } else {
                return 1;            }
        }
    } else {
        if (features[4] <= 0.07257596403360367f) {
            if (features[11] <= -2.932814508676529f) {
                return 1;            } else {
                return 0;            }
        } else {
            if (features[17] <= 0.7896144390106201f) {
                return 1;            } else {
                return 1;            }
        }
    }
}

// Tree 83
int predict_tree_83(const float* features) {
    // Max depth: 3
    if (features[7] <= 1.8840453624725342f) {
        if (features[3] <= 2.2110848426818848f) {
            return 1;        } else {
            return 0;        }
    } else {
        if (features[22] <= 0.20773516036570072f) {
            return 0;        } else {
            if (features[31] <= 0.1600564420223236f) {
                return 1;            } else {
                return 1;            }
        }
    }
}

// Tree 84
int predict_tree_84(const float* features) {
    // Max depth: 6
    if (features[18] <= 1.0631850361824036f) {
        if (features[13] <= 2.51217520236969f) {
            if (features[1] <= 1.187128722667694f) {
                if (features[2] <= -1.71565181016922f) {
                    if (features[17] <= -0.5020915865898132f) {
                        return 1;                    } else {
                        if (features[1] <= -0.46365900337696075f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                } else {
                    return 1;                }
            } else {
                if (features[7] <= 1.9698467254638672f) {
                    if (features[5] <= 0.022893806919455528f) {
                        return 1;                    } else {
                        return 1;                    }
                } else {
                    if (features[11] <= 2.3123514652252197f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            }
        } else {
            if (features[14] <= 3.9099491834640503f) {
                if (features[15] <= 0.7394949495792389f) {
                    return 1;                } else {
                    return 1;                }
            } else {
                if (features[21] <= 0.6107746697962284f) {
                    return 0;                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[3] <= 1.4282537028193474f) {
            if (features[31] <= 0.1600564420223236f) {
                return 1;            } else {
                return 1;            }
        } else {
            return 0;        }
    }
}

// Tree 85
int predict_tree_85(const float* features) {
    // Max depth: 3
    if (features[7] <= 1.9091759324073792f) {
        if (features[3] <= 2.7539526224136353f) {
            return 1;        } else {
            return 0;        }
    } else {
        if (features[23] <= 0.1970740407705307f) {
            return 1;        } else {
            if (features[3] <= 1.2354962527751923f) {
                return 1;            } else {
                return 0;            }
        }
    }
}

// Tree 86
int predict_tree_86(const float* features) {
    // Max depth: 4
    if (features[5] <= 0.3235636204481125f) {
        if (features[10] <= 2.2180285453796387f) {
            if (features[20] <= -0.7517009675502777f) {
                if (features[7] <= 1.0881958603858948f) {
                    return 1;                } else {
                    return 0;                }
            } else {
                return 1;            }
        } else {
            if (features[2] <= -0.6643277704715729f) {
                return 0;            } else {
                return 1;            }
        }
    } else {
        if (features[20] <= 0.05769113078713417f) {
            if (features[4] <= 0.05576428771018982f) {
                if (features[17] <= 0.36366572976112366f) {
                    return 1;                } else {
                    return 0;                }
            } else {
                return 1;            }
        } else {
            return 1;        }
    }
}

// Tree 87
int predict_tree_87(const float* features) {
    // Max depth: 3
    if (features[19] <= 1.0628314018249512f) {
        if (features[3] <= 2.840496778488159f) {
            return 1;        } else {
            return 0;        }
    } else {
        if (features[24] <= 0.2868890166282654f) {
            return 1;        } else {
            if (features[3] <= 1.4282537028193474f) {
                return 1;            } else {
                return 0;            }
        }
    }
}

// Tree 88
int predict_tree_88(const float* features) {
    // Max depth: 4
    if (features[2] <= -1.4903680682182312f) {
        if (features[19] <= -0.012547731399536133f) {
            if (features[3] <= 2.7539526224136353f) {
                if (features[17] <= -0.6178421676158905f) {
                    return 1;                } else {
                    return 1;                }
            } else {
                return 0;            }
        } else {
            return 0;        }
    } else {
        if (features[3] <= 2.2425553798675537f) {
            return 1;        } else {
            if (features[24] <= 0.34311458468437195f) {
                return 0;            } else {
                return 0;            }
        }
    }
}

// Tree 89
int predict_tree_89(const float* features) {
    // Max depth: 4
    if (features[5] <= 0.3235636204481125f) {
        if (features[17] <= 1.7966504096984863f) {
            if (features[3] <= 2.671342372894287f) {
                if (features[13] <= -5.861961841583252f) {
                    return 1;                } else {
                    return 1;                }
            } else {
                return 0;            }
        } else {
            if (features[21] <= 0.033922433853149414f) {
                return 0;            } else {
                if (features[15] <= 0.7394949495792389f) {
                    return 1;                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[2] <= -0.9862957298755646f) {
            return 0;        } else {
            if (features[25] <= -0.22629046440124512f) {
                return 1;            } else {
                return 1;            }
        }
    }
}

// Tree 90
int predict_tree_90(const float* features) {
    // Max depth: 3
    if (features[2] <= -1.4715943932533264f) {
        if (features[20] <= -0.125033400952816f) {
            if (features[6] <= -1.0020799934864044f) {
                return 1;            } else {
                return 1;            }
        } else {
            if (features[24] <= 0.14632507041096687f) {
                return 1;            } else {
                return 0;            }
        }
    } else {
        if (features[13] <= -10.610413074493408f) {
            return 1;        } else {
            return 1;        }
    }
}

// Tree 91
int predict_tree_91(const float* features) {
    // Max depth: 2
    if (features[1] <= 0.9483705461025238f) {
        if (features[3] <= 2.258290708065033f) {
            return 1;        } else {
            return 0;        }
    } else {
        if (features[22] <= 0.06322679668664932f) {
            return 0;        } else {
            return 1;        }
    }
}

// Tree 92
int predict_tree_92(const float* features) {
    // Max depth: 3
    if (features[7] <= 1.8840453624725342f) {
        if (features[3] <= -2.1515268087387085f) {
            return 1;        } else {
            return 1;        }
    } else {
        if (features[22] <= 0.20838522911071777f) {
            if (features[28] <= 0.032488465309143066f) {
                return 0;            } else {
                return 0;            }
        } else {
            return 1;        }
    }
}

// Tree 93
int predict_tree_93(const float* features) {
    // Max depth: 5
    if (features[1] <= 0.9475113749504089f) {
        if (features[12] <= 3.170227527618408f) {
            if (features[4] <= -0.7537725269794464f) {
                if (features[23] <= -0.63036048412323f) {
                    return 1;                } else {
                    if (features[7] <= -0.5705532431602478f) {
                        return 1;                    } else {
                        return 0;                    }
                }
            } else {
                return 1;            }
        } else {
            return 0;        }
    } else {
        if (features[26] <= 1.1292750835418701f) {
            if (features[21] <= 0.07623567059636116f) {
                return 0;            } else {
                if (features[34] <= -2.028429754078388f) {
                    return 1;                } else {
                    return 1;                }
            }
        } else {
            if (features[22] <= -0.030291758477687836f) {
                return 0;            } else {
                if (features[2] <= 0.18048620223999023f) {
                    return 1;                } else {
                    return 1;                }
            }
        }
    }
}

// Tree 94
int predict_tree_94(const float* features) {
    // Max depth: 4
    if (features[18] <= 1.0631850361824036f) {
        if (features[7] <= 1.9275118708610535f) {
            return 1;        } else {
            if (features[3] <= 1.2827022075653076f) {
                return 1;            } else {
                return 0;            }
        }
    } else {
        if (features[23] <= 0.29157713055610657f) {
            return 1;        } else {
            if (features[2] <= -0.6643277481198311f) {
                return 0;            } else {
                if (features[16] <= 2.8937984704971313f) {
                    return 1;                } else {
                    return 1;                }
            }
        }
    }
}

// Tree 95
int predict_tree_95(const float* features) {
    // Max depth: 4
    if (features[18] <= 1.063120722770691f) {
        if (features[3] <= 2.8444305658340454f) {
            return 1;        } else {
            return 0;        }
    } else {
        if (features[20] <= 0.0693914070725441f) {
            if (features[21] <= 0.09497062675654888f) {
                if (features[22] <= 0.06816326081752777f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                return 1;            }
        } else {
            if (features[17] <= 0.7509458065032959f) {
                return 1;            } else {
                return 1;            }
        }
    }
}

// Tree 96
int predict_tree_96(const float* features) {
    // Max depth: 2
    if (features[2] <= -1.4715943932533264f) {
        if (features[18] <= -0.01370595395565033f) {
            return 1;        } else {
            return 0;        }
    } else {
        if (features[3] <= -2.1515268087387085f) {
            return 1;        } else {
            return 1;        }
    }
}

// Tree 97
int predict_tree_97(const float* features) {
    // Max depth: 4
    if (features[25] <= 0.3272087424993515f) {
        if (features[2] <= -1.4715943932533264f) {
            if (features[7] <= 0.5946264564990997f) {
                if (features[27] <= -0.3279092609882355f) {
                    return 1;                } else {
                    return 1;                }
            } else {
                if (features[0] <= 1.0633479356765747f) {
                    return 0;                } else {
                    return 0;                }
            }
        } else {
            return 1;        }
    } else {
        if (features[3] <= 1.9003126323223114f) {
            if (features[9] <= -0.06224391423165798f) {
                return 1;            } else {
                return 1;            }
        } else {
            return 0;        }
    }
}

// Tree 98
int predict_tree_98(const float* features) {
    // Max depth: 3
    if (features[0] <= 1.0630593299865723f) {
        if (features[3] <= 2.7539526224136353f) {
            return 1;        } else {
            return 0;        }
    } else {
        if (features[4] <= 0.07434402033686638f) {
            if (features[21] <= 0.06838300079107285f) {
                return 0;            } else {
                return 1;            }
        } else {
            if (features[9] <= -0.04940817318856716f) {
                return 1;            } else {
                return 1;            }
        }
    }
}

// Tree 99
int predict_tree_99(const float* features) {
    // Max depth: 4
    if (features[10] <= 0.9930270910263062f) {
        if (features[22] <= -0.7577395439147949f) {
            if (features[23] <= -0.6329125463962555f) {
                return 1;            } else {
                if (features[19] <= -0.46390873193740845f) {
                    return 0;                } else {
                    return 1;                }
            }
        } else {
            if (features[27] <= -0.3279288411140442f) {
                return 1;            } else {
                return 1;            }
        }
    } else {
        if (features[23] <= 0.2813688814640045f) {
            return 1;        } else {
            if (features[2] <= -0.6643277481198311f) {
                return 0;            } else {
                if (features[17] <= 0.9031425714492798f) {
                    return 1;                } else {
                    return 1;                }
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
    int votes[NUM_CLASSES] = {0, 0, 0};
    
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

    // Return class with most votes
    int predicted_class = 0;
    int max_votes = votes[0];
    
    for (int i = 1; i < NUM_CLASSES; i++) {
        if (votes[i] > max_votes) {
            max_votes = votes[i];
            predicted_class = i;
        }
    }
    
    return predicted_class;
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
    int votes[NUM_CLASSES] = {0, 0, 0};
    
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
