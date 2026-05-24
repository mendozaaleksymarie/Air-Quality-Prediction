/*
 * ════════════════════════════════════════════════════════════════════════
 * RANDOM FOREST MODEL - C++ EMBEDDED VERSION FOR ESP32
 * ════════════════════════════════════════════════════════════════════════
 * 
 * GENERATED: Automated conversion from Python sklearn model
 * Model Type: Random Forest Classifier
 * Features: 35 (Core: PM2.5, PM10, Temp, Humidity, Gas, CO, TimeOfDay, WetBulb + Engineered: ratios, deltas, lags, volatility, trends)
 * Classes: 3 (0=Safe, 1=Caution, 2=Hazardous)
 * Trees: 50
 * Training Data: 20,568 samples from 8 scenarios (MILES Protocol)
 * 
 * USAGE:
 *   float features[35] = {core_sensors[8], engineered_features[27]};
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
    132.52936902590992f,  // feature_0
    160.09185886609623f,  // feature_1
    31.420925709840517f,  // feature_2
    58.13773693763796f,  // feature_3
    31.673464281083884f,  // feature_4
    9.608002290505235f,  // feature_5
    9.036756126021004f,  // feature_6
    28.829387499933976f,  // feature_7
    1.3930797935677222f,  // feature_8
    3.207116869456753f,  // feature_9
    292.62122789200544f,  // feature_10
    -0.025029237478003983f,  // feature_11
    -0.05454967049119379f,  // feature_12
    -0.0014793206275120674f,  // feature_13
    0.0005406456631660812f,  // feature_14
    0.19862569687540516f,  // feature_15
    0.038052638402696744f,  // feature_16
    132.55984611514464f,  // feature_17
    132.56837366882448f,  // feature_18
    132.60006445919012f,  // feature_19
    31.67507584597432f,  // feature_20
    31.67946454038648f,  // feature_21
    31.6887171009983f,  // feature_22
    9.607449327974459f,  // feature_23
    9.606658455421604f,  // feature_24
    9.606273175158808f,  // feature_25
    11.53532865956366f,  // feature_26
    0.4634930042251895f,  // feature_27
    -0.03455205497212498f,  // feature_28
    0.0013613380007779074f,  // feature_29
    0.4095034357578115f,  // feature_30
    0.40250226889666796f,  // feature_31
    0.0f,  // feature_32
    0.808829249319331f,  // feature_33
    0.9008168028004667f,  // feature_34
};

const float SCALER_SCALE[] = {
    218.97198571462252f,  // feature_0
    281.11278596155034f,  // feature_1
    5.320187575354377f,  // feature_2
    12.56323864121045f,  // feature_3
    18.04367209465492f,  // feature_4
    4.3952813312205485f,  // feature_5
    4.519346023371591f,  // feature_6
    3.44665021111661f,  // feature_7
    1.0569838106420366f,  // feature_8
    0.9342833594742934f,  // feature_9
    499.25859425842424f,  // feature_10
    42.226379319845f,  // feature_11
    61.63464827215894f,  // feature_12
    1.2251706012918417f,  // feature_13
    0.09547658714848063f,  // feature_14
    0.39896557422439555f,  // feature_15
    0.1913233783762037f,  // feature_16
    219.12200285632798f,  // feature_17
    219.12187276771354f,  // feature_18
    219.18105158245606f,  // feature_19
    18.071380400810966f,  // feature_20
    18.132469806329567f,  // feature_21
    18.209553393750568f,  // feature_22
    4.394076594681473f,  // feature_23
    4.392295814172844f,  // feature_24
    4.393003250492411f,  // feature_25
    34.345597081419406f,  // feature_26
    1.1559759676417496f,  // feature_27
    0.9944283965059646f,  // feature_28
    0.9893433020535175f,  // feature_29
    0.4917421802737501f,  // feature_30
    0.49040207221187276f,  // feature_31
    1.0f,  // feature_32
    0.3932232123931878f,  // feature_33
    0.43419936410858323f,  // feature_34
};

const int NUM_FEATURES = 35;
const int NUM_CLASSES = 3;
const int NUM_TREES = 50;

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
    // Max depth: 11
    if (features[21] <= 0.12466781586408615f) {
        if (features[19] <= -0.40709754824638367f) {
            if (features[13] <= -0.13890910148620605f) {
                if (features[24] <= -0.2811722755432129f) {
                    return 1;                } else {
                    if (features[12] <= -0.4571063769981265f) {
                        return 0;                    } else {
                        return 0;                    }
                }
            } else {
                if (features[10] <= -0.35858461260795593f) {
                    if (features[19] <= -0.6049794852733612f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[4] <= -0.6188761293888092f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            }
        } else {
            if (features[5] <= -0.36546821892261505f) {
                if (features[24] <= -0.38893671333789825f) {
                    return 0;                } else {
                    if (features[13] <= 0.06786482594907284f) {
                        if (features[6] <= 1.4301281571388245f) {
                            if (features[1] <= -0.3407019376754761f) {
                                if (features[11] <= -0.09836750850081444f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                if (features[27] <= -0.29011695086956024f) {
                                    if (features[0] <= -0.3725171834230423f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 0;                                }
                            }
                        } else {
                            if (features[1] <= -0.3403662443161011f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[21] <= -0.6401664018630981f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                }
            } else {
                if (features[6] <= -1.0038523077964783f) {
                    if (features[3] <= 1.728237733244896f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    if (features[20] <= -0.21738290146458894f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[1] <= -0.2397419586777687f) {
            if (features[23] <= 0.09730159863829613f) {
                if (features[25] <= -0.0769268348813057f) {
                    if (features[13] <= 0.9793025255203247f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[17] <= -0.47142188251018524f) {
                        if (features[3] <= -0.6517218351364136f) {
                            if (features[19] <= -0.5781484246253967f) {
                                return 1;                            } else {
                                if (features[24] <= -0.0311132175847888f) {
                                    return 0;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            return 0;                        }
                    } else {
                        if (features[4] <= 1.451932966709137f) {
                            if (features[11] <= 0.14182796329259872f) {
                                if (features[13] <= 0.6269706189632416f) {
                                    if (features[5] <= 0.0895652286708355f) {
                                        if (features[11] <= 0.04542684368789196f) {
                                            return 1;                                        } else {
                                            if (features[5] <= 0.009934373199939728f) {
                                                return 1;                                            } else {
                                                return 2;                                            }
                                        }
                                    } else {
                                        if (features[2] <= -0.39771637320518494f) {
                                            return 2;                                        } else {
                                            return 2;                                        }
                                    }
                                } else {
                                    if (features[19] <= 0.00023108720779418945f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                }
                            } else {
                                if (features[22] <= 0.9314497113227844f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[3] <= 0.46900828182697296f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                if (features[22] <= 0.5733958780765533f) {
                    return 1;                } else {
                    return 2;                }
            }
        } else {
            if (features[14] <= 1.0242582559585571f) {
                if (features[12] <= -8.6288423538208f) {
                    return 2;                } else {
                    return 2;                }
            } else {
                if (features[5] <= -0.02760588377714157f) {
                    if (features[3] <= -1.3481982946395874f) {
                        return 2;                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 1
int predict_tree_1(const float* features) {
    // Max depth: 16
    if (features[1] <= -0.4178345948457718f) {
        if (features[4] <= 0.22343210875988007f) {
            return 0;        } else {
            if (features[0] <= -0.5056865811347961f) {
                if (features[23] <= 0.0017183751915581524f) {
                    if (features[11] <= -0.016309911385178566f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[11] <= 0.006219336297363043f) {
                        if (features[28] <= 0.034745603799819946f) {
                            if (features[12] <= 0.004720915458165109f) {
                                return 1;                            } else {
                                return 0;                            }
                        } else {
                            if (features[25] <= 0.012609481811523438f) {
                                return 0;                            } else {
                                return 0;                            }
                        }
                    } else {
                        return 1;                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[1] <= -0.2397419586777687f) {
            if (features[4] <= 1.4351218938827515f) {
                if (features[17] <= -0.4262009412050247f) {
                    if (features[19] <= -0.5745867490768433f) {
                        return 1;                    } else {
                        if (features[27] <= -0.3990739732980728f) {
                            return 2;                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[22] <= 1.4316450357437134f) {
                        if (features[3] <= 0.6019358038902283f) {
                            if (features[4] <= -0.6470485031604767f) {
                                return 0;                            } else {
                                if (features[23] <= 0.09730159863829613f) {
                                    if (features[4] <= 0.09273070096969604f) {
                                        if (features[24] <= -0.3654106706380844f) {
                                            if (features[1] <= -0.355979785323143f) {
                                                if (features[21] <= -0.6458652019500732f) {
                                                    return 0;                                                } else {
                                                    return 0;                                                }
                                            } else {
                                                if (features[10] <= -0.3625578433275223f) {
                                                    return 0;                                                } else {
                                                    if (features[23] <= -0.36620116233825684f) {
                                                        if (features[0] <= -0.3722134679555893f) {
                                                            return 0;                                                        } else {
                                                            if (features[12] <= -0.06323207914829254f) {
                                                                return 1;                                                            } else {
                                                                return 1;                                                            }
                                                        }
                                                    } else {
                                                        if (features[9] <= -0.7492547035217285f) {
                                                            return 0;                                                        } else {
                                                            return 0;                                                        }
                                                    }
                                                }
                                            }
                                        } else {
                                            if (features[14] <= -0.09294403344392776f) {
                                                return 0;                                            } else {
                                                return 0;                                            }
                                        }
                                    } else {
                                        if (features[19] <= -0.3880935311317444f) {
                                            if (features[26] <= -0.27620522677898407f) {
                                                if (features[27] <= 0.8968527019023895f) {
                                                    if (features[26] <= -0.30273665487766266f) {
                                                        if (features[21] <= 1.144936978816986f) {
                                                            return 2;                                                        } else {
                                                            if (features[3] <= 0.598353922367096f) {
                                                                if (features[5] <= 0.0895652286708355f) {
                                                                    return 1;                                                                } else {
                                                                    return 2;                                                                }
                                                            } else {
                                                                return 2;                                                            }
                                                        }
                                                    } else {
                                                        if (features[26] <= -0.2993619740009308f) {
                                                            return 2;                                                        } else {
                                                            return 1;                                                        }
                                                    }
                                                } else {
                                                    return 2;                                                }
                                            } else {
                                                if (features[19] <= -0.41071321070194244f) {
                                                    return 2;                                                } else {
                                                    return 2;                                                }
                                            }
                                        } else {
                                            if (features[6] <= -1.0038523524999619f) {
                                                return 2;                                            } else {
                                                if (features[18] <= -0.38823850452899933f) {
                                                    if (features[5] <= 0.09335717558860779f) {
                                                        return 1;                                                    } else {
                                                        return 2;                                                    }
                                                } else {
                                                    if (features[17] <= -0.28979311883449554f) {
                                                        return 1;                                                    } else {
                                                        return 2;                                                    }
                                                }
                                            }
                                        }
                                    }
                                } else {
                                    if (features[25] <= 0.04713407903909683f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                }
                            }
                        } else {
                            if (features[17] <= -0.3922537565231323f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[10] <= -0.3941601514816284f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[31] <= 0.1988118588924408f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[2] <= -0.9691248089075089f) {
                return 0;            } else {
                if (features[1] <= -0.0606569480150938f) {
                    if (features[13] <= 1.0527616441249847f) {
                        if (features[23] <= 0.021441897377371788f) {
                            return 2;                        } else {
                            return 2;                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[26] <= -0.33579370379447937f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 2
int predict_tree_2(const float* features) {
    // Max depth: 15
    if (features[17] <= -0.44509750604629517f) {
        if (features[23] <= 0.0017183751915581524f) {
            if (features[30] <= 0.18403255939483643f) {
                return 0;            } else {
                return 0;            }
        } else {
            if (features[17] <= -0.502814918756485f) {
                if (features[13] <= -0.4354664385318756f) {
                    if (features[21] <= 0.4627353847026825f) {
                        if (features[14] <= -2.659018248319626f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[14] <= -0.40715718269348145f) {
                        return 0;                    } else {
                        if (features[5] <= 0.009555181255564094f) {
                            return 0;                        } else {
                            if (features[7] <= -0.5432323962450027f) {
                                return 1;                            } else {
                                if (features[29] <= -0.001376032829284668f) {
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
        if (features[17] <= -0.2900327444076538f) {
            if (features[25] <= 0.14881090819835663f) {
                if (features[4] <= 1.4371539950370789f) {
                    if (features[2] <= -0.45034609735012054f) {
                        if (features[24] <= -0.11990505084395409f) {
                            return 0;                        } else {
                            if (features[26] <= -0.32938678562641144f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[17] <= -0.4259166717529297f) {
                            return 0;                        } else {
                            if (features[14] <= 0.32600684463977814f) {
                                if (features[5] <= 0.0895652286708355f) {
                                    if (features[20] <= -0.646698921918869f) {
                                        return 0;                                    } else {
                                        if (features[6] <= 0.10250241588801146f) {
                                            if (features[1] <= -0.4028116762638092f) {
                                                return 0;                                            } else {
                                                if (features[0] <= -0.3148026764392853f) {
                                                    if (features[22] <= -0.2364354506134987f) {
                                                        if (features[28] <= 0.034745603799819946f) {
                                                            return 0;                                                        } else {
                                                            return 1;                                                        }
                                                    } else {
                                                        if (features[14] <= -0.2675068974494934f) {
                                                            if (features[19] <= -0.38058704137802124f) {
                                                                return 1;                                                            } else {
                                                                return 2;                                                            }
                                                        } else {
                                                            if (features[30] <= 0.18403255939483643f) {
                                                                return 1;                                                            } else {
                                                                return 1;                                                            }
                                                        }
                                                    }
                                                } else {
                                                    return 2;                                                }
                                            }
                                        } else {
                                            if (features[0] <= -0.3722134679555893f) {
                                                if (features[26] <= -0.3328346610069275f) {
                                                    return 0;                                                } else {
                                                    return 0;                                                }
                                            } else {
                                                if (features[3] <= -0.36119166016578674f) {
                                                    return 1;                                                } else {
                                                    return 1;                                                }
                                            }
                                        }
                                    }
                                } else {
                                    if (features[10] <= -0.3941601514816284f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                }
                            } else {
                                if (features[18] <= -0.40362684428691864f) {
                                    return 2;                                } else {
                                    if (features[23] <= 0.0783366709947586f) {
                                        return 1;                                    } else {
                                        return 2;                                    }
                                }
                            }
                        }
                    }
                } else {
                    if (features[22] <= 1.2236040234565735f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[24] <= 0.13926085829734802f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[3] <= 1.9033518135547638f) {
                return 2;            } else {
                if (features[18] <= 0.7171183973550797f) {
                    return 0;                } else {
                    return 0;                }
            }
        }
    }
}

// Tree 3
int predict_tree_3(const float* features) {
    // Max depth: 13
    if (features[18] <= -0.4517357349395752f) {
        if (features[33] <= -0.785379022359848f) {
            if (features[0] <= -0.5046067833900452f) {
                if (features[25] <= -0.11258960515260696f) {
                    return 0;                } else {
                    if (features[2] <= 0.10884471517056227f) {
                        if (features[4] <= 0.29954373836517334f) {
                            if (features[9] <= -0.5506507754325867f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            if (features[18] <= -0.5783689618110657f) {
                                if (features[14] <= -0.42461346089839935f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            } else {
                                return 1;                            }
                        }
                    } else {
                        return 0;                    }
                }
            } else {
                if (features[5] <= 0.020931005477905273f) {
                    return 0;                } else {
                    return 2;                }
            }
        } else {
            if (features[11] <= 0.1299009993672371f) {
                if (features[23] <= -0.5110931992530823f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[27] <= -0.3417026698589325f) {
                    return 0;                } else {
                    if (features[10] <= -0.3754910081624985f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            }
        }
    } else {
        if (features[0] <= -0.23168553411960602f) {
            if (features[24] <= 0.12673892825841904f) {
                if (features[1] <= -0.3977525234222412f) {
                    return 0;                } else {
                    if (features[17] <= -0.42609161138534546f) {
                        return 0;                    } else {
                        if (features[5] <= 0.08918603509664536f) {
                            if (features[4] <= -0.6470485031604767f) {
                                return 0;                            } else {
                                if (features[5] <= -0.11027029156684875f) {
                                    if (features[9] <= -0.5524116456508636f) {
                                        if (features[17] <= -0.3752165585756302f) {
                                            if (features[3] <= -0.29353393614292145f) {
                                                return 0;                                            } else {
                                                return 0;                                            }
                                        } else {
                                            if (features[13] <= 0.06378376111388206f) {
                                                if (features[2] <= -0.23888739198446274f) {
                                                    if (features[5] <= -0.37039774656295776f) {
                                                        return 0;                                                    } else {
                                                        return 1;                                                    }
                                                } else {
                                                    if (features[0] <= -0.37202994525432587f) {
                                                        return 0;                                                    } else {
                                                        return 1;                                                    }
                                                }
                                            } else {
                                                if (features[25] <= -0.37664586305618286f) {
                                                    return 0;                                                } else {
                                                    return 0;                                                }
                                            }
                                        }
                                    } else {
                                        if (features[3] <= -1.0417487025260925f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    }
                                } else {
                                    if (features[25] <= 0.09304041042923927f) {
                                        return 1;                                    } else {
                                        if (features[15] <= 0.7553892731666565f) {
                                            if (features[0] <= -0.37762200832366943f) {
                                                return 1;                                            } else {
                                                return 2;                                            }
                                        } else {
                                            return 2;                                        }
                                    }
                                }
                            }
                        } else {
                            if (features[13] <= -1.321057379245758f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                if (features[5] <= 0.09487395361065865f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[23] <= 0.09047422185540199f) {
                if (features[9] <= -0.005723699927330017f) {
                    return 0;                } else {
                    return 2;                }
            } else {
                if (features[24] <= 0.1908663660287857f) {
                    if (features[3] <= 1.864349126815796f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    if (features[3] <= 1.9073317348957062f) {
                        return 2;                    } else {
                        if (features[18] <= 1.2682583928108215f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                }
            }
        }
    }
}

// Tree 4
int predict_tree_4(const float* features) {
    // Max depth: 16
    if (features[0] <= -0.4453745186328888f) {
        if (features[4] <= 0.2698010951280594f) {
            if (features[21] <= -0.8337417840957642f) {
                return 0;            } else {
                return 0;            }
        } else {
            if (features[20] <= 0.5927378237247467f) {
                if (features[23] <= 0.0017183751915581524f) {
                    return 0;                } else {
                    if (features[0] <= -0.5650924742221832f) {
                        if (features[13] <= -0.269503153860569f) {
                            if (features[12] <= 0.0017320141196250916f) {
                                return 0;                            } else {
                                return 1;                            }
                        } else {
                            if (features[14] <= -0.023118887096643448f) {
                                return 0;                            } else {
                                return 0;                            }
                        }
                    } else {
                        return 1;                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[18] <= -0.14465460181236267f) {
            if (features[23] <= 0.09730159863829613f) {
                if (features[1] <= -0.3977525234222412f) {
                    return 0;                } else {
                    if (features[25] <= -0.3887863755226135f) {
                        return 0;                    } else {
                        if (features[17] <= -0.4264625906944275f) {
                            return 0;                        } else {
                            if (features[5] <= 0.0895652286708355f) {
                                if (features[9] <= -0.7657530307769775f) {
                                    return 0;                                } else {
                                    if (features[0] <= -0.21659014374017715f) {
                                        if (features[5] <= -0.388219878077507f) {
                                            return 0;                                        } else {
                                            if (features[20] <= -0.43540720641613007f) {
                                                if (features[4] <= -0.5628084540367126f) {
                                                    if (features[0] <= -0.3722134679555893f) {
                                                        if (features[19] <= -0.5007835328578949f) {
                                                            return 0;                                                        } else {
                                                            return 0;                                                        }
                                                    } else {
                                                        return 1;                                                    }
                                                } else {
                                                    return 0;                                                }
                                            } else {
                                                if (features[8] <= -0.18784510344266891f) {
                                                    return 2;                                                } else {
                                                    if (features[11] <= 0.022107720375061035f) {
                                                        if (features[23] <= -0.11055398359894753f) {
                                                            return 0;                                                        } else {
                                                            return 1;                                                        }
                                                    } else {
                                                        if (features[8] <= -0.1338784247636795f) {
                                                            return 2;                                                        } else {
                                                            if (features[18] <= -0.3919436037540436f) {
                                                                return 1;                                                            } else {
                                                                if (features[2] <= 0.24981719255447388f) {
                                                                    return 2;                                                                } else {
                                                                    return 1;                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    } else {
                                        return 2;                                    }
                                }
                            } else {
                                if (features[18] <= -0.4089698940515518f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                }
            } else {
                if (features[17] <= -0.47955629229545593f) {
                    return 1;                } else {
                    return 2;                }
            }
        } else {
            if (features[9] <= -0.1337149813771248f) {
                if (features[4] <= 0.06446594558656216f) {
                    if (features[2] <= -0.6148139908909798f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    return 2;                }
            } else {
                if (features[20] <= 0.2066761925816536f) {
                    if (features[3] <= -1.0895070135593414f) {
                        return 1;                    } else {
                        if (features[9] <= -0.10180320590734482f) {
                            if (features[24] <= 0.2758636772632599f) {
                                return 0;                            } else {
                                if (features[18] <= 1.8551910519599915f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[19] <= 0.2345644310116768f) {
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

// Tree 5
int predict_tree_5(const float* features) {
    // Max depth: 22
    if (features[0] <= -0.4442238211631775f) {
        if (features[20] <= 0.18186716735363007f) {
            if (features[5] <= -0.5110789239406586f) {
                return 0;            } else {
                return 0;            }
        } else {
            if (features[7] <= 0.3142753718420863f) {
                if (features[27] <= 0.3653261959552765f) {
                    return 0;                } else {
                    if (features[12] <= -0.003782533807680011f) {
                        return 0;                    } else {
                        if (features[29] <= -0.001376032829284668f) {
                            if (features[4] <= 0.45657017827033997f) {
                                return 0;                            } else {
                                return 1;                            }
                        } else {
                            return 1;                        }
                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[17] <= -0.28981177508831024f) {
            if (features[4] <= 1.4551658630371094f) {
                if (features[10] <= -0.4101226031780243f) {
                    return 0;                } else {
                    if (features[20] <= -0.6466067135334015f) {
                        return 0;                    } else {
                        if (features[3] <= 0.6238250434398651f) {
                            if (features[10] <= -0.26686516404151917f) {
                                if (features[13] <= -0.8939059972763062f) {
                                    return 2;                                } else {
                                    if (features[2] <= -0.4221515953540802f) {
                                        if (features[4] <= 1.3093160390853882f) {
                                            if (features[23] <= 0.09464650973677635f) {
                                                if (features[24] <= 0.08158411085605621f) {
                                                    if (features[12] <= 0.003126724623143673f) {
                                                        return 2;                                                    } else {
                                                        return 1;                                                    }
                                                } else {
                                                    return 1;                                                }
                                            } else {
                                                return 2;                                            }
                                        } else {
                                            return 2;                                        }
                                    } else {
                                        if (features[27] <= -0.3884178400039673f) {
                                            return 0;                                        } else {
                                            if (features[24] <= 0.14229647815227509f) {
                                                if (features[23] <= 0.1101977489888668f) {
                                                    if (features[0] <= -0.42639899253845215f) {
                                                        return 0;                                                    } else {
                                                        if (features[27] <= 0.6278706192970276f) {
                                                            if (features[18] <= -0.47384124994277954f) {
                                                                return 0;                                                            } else {
                                                                if (features[5] <= 0.0895652286708355f) {
                                                                    if (features[7] <= 0.44753944873809814f) {
                                                                        if (features[17] <= -0.4271029829978943f) {
                                                                            return 0;                                                                        } else {
                                                                            if (features[20] <= 0.08696573041379452f) {
                                                                                if (features[0] <= -0.3710986226797104f) {
                                                                                    return 0;                                                                                } else {
                                                                                    return 1;                                                                                }
                                                                            } else {
                                                                                if (features[5] <= 0.08236053213477135f) {
                                                                                    if (features[15] <= 0.7553892731666565f) {
                                                                                        return 1;                                                                                    } else {
                                                                                        if (features[13] <= -0.00015291385352611542f) {
                                                                                            return 2;                                                                                        } else {
                                                                                            return 1;                                                                                        }
                                                                                    }
                                                                                } else {
                                                                                    if (features[8] <= -0.08322173729538918f) {
                                                                                        if (features[3] <= 0.6090995669364929f) {
                                                                                            return 1;                                                                                        } else {
                                                                                            return 2;                                                                                        }
                                                                                    } else {
                                                                                        if (features[25] <= 0.1264268308877945f) {
                                                                                            return 2;                                                                                        } else {
                                                                                            return 1;                                                                                        }
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    } else {
                                                                        if (features[1] <= -0.33412061631679535f) {
                                                                            return 0;                                                                        } else {
                                                                            if (features[10] <= -0.3509949892759323f) {
                                                                                return 0;                                                                            } else {
                                                                                return 1;                                                                            }
                                                                        }
                                                                    }
                                                                } else {
                                                                    if (features[17] <= -0.4177461117506027f) {
                                                                        return 2;                                                                    } else {
                                                                        return 2;                                                                    }
                                                                }
                                                            }
                                                        } else {
                                                            if (features[18] <= -0.3964938223361969f) {
                                                                return 1;                                                            } else {
                                                                if (features[2] <= 0.27425242960453033f) {
                                                                    return 2;                                                                } else {
                                                                    return 1;                                                                }
                                                            }
                                                        }
                                                    }
                                                } else {
                                                    if (features[5] <= 0.24768934398889542f) {
                                                        return 2;                                                    } else {
                                                        return 1;                                                    }
                                                }
                                            } else {
                                                if (features[7] <= -0.05636722221970558f) {
                                                    return 2;                                                } else {
                                                    return 2;                                                }
                                            }
                                        }
                                    }
                                }
                            } else {
                                if (features[1] <= -0.2516944855451584f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[3] <= 0.6417344510555267f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                if (features[2] <= -0.45598500967025757f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[21] <= 0.06179717741906643f) {
                if (features[17] <= 0.33373330533504486f) {
                    return 2;                } else {
                    return 0;                }
            } else {
                return 2;            }
        }
    }
}

// Tree 6
int predict_tree_6(const float* features) {
    // Max depth: 11
    if (features[21] <= 0.1186932697892189f) {
        if (features[18] <= -0.3925958275794983f) {
            if (features[0] <= -0.3759930282831192f) {
                if (features[29] <= -0.5067617737222463f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[9] <= -0.6451350152492523f) {
                    return 1;                } else {
                    return 1;                }
            }
        } else {
            if (features[6] <= -0.008133061230182648f) {
                if (features[7] <= 0.941732554929331f) {
                    if (features[17] <= -0.1841539314482361f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    return 0;                }
            } else {
                if (features[0] <= -0.3722134679555893f) {
                    return 0;                } else {
                    if (features[5] <= -0.38746149837970734f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            }
        }
    } else {
        if (features[17] <= -0.3192856162786484f) {
            if (features[24] <= 0.14153756946325302f) {
                if (features[20] <= 1.4328323006629944f) {
                    if (features[4] <= 0.1299552023410797f) {
                        return 0;                    } else {
                        if (features[17] <= -0.47039245069026947f) {
                            if (features[23] <= 0.0017183751915581524f) {
                                return 0;                            } else {
                                if (features[7] <= -0.4571647495031357f) {
                                    return 1;                                } else {
                                    if (features[14] <= 2.089091692119837f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        } else {
                            if (features[2] <= -0.3995960056781769f) {
                                if (features[13] <= 0.5045387148857117f) {
                                    if (features[5] <= 0.09335717558860779f) {
                                        if (features[11] <= 0.049110932275652885f) {
                                            return 1;                                        } else {
                                            return 2;                                        }
                                    } else {
                                        return 2;                                    }
                                } else {
                                    return 2;                                }
                            } else {
                                if (features[13] <= 0.6963487267494202f) {
                                    if (features[5] <= 0.0895652286708355f) {
                                        if (features[12] <= 0.06048255413770676f) {
                                            return 1;                                        } else {
                                            if (features[29] <= -0.001376032829284668f) {
                                                return 2;                                            } else {
                                                return 1;                                            }
                                        }
                                    } else {
                                        if (features[12] <= -0.018570836633443832f) {
                                            return 2;                                        } else {
                                            return 2;                                        }
                                    }
                                } else {
                                    if (features[10] <= -0.37703411281108856f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                }
                            }
                        }
                    }
                } else {
                    if (features[23] <= 0.09085352346301079f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[4] <= 0.8179157078266144f) {
                    if (features[12] <= -0.02581434795865789f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[14] <= -23.43199920654297f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[31] <= 0.1988118588924408f) {
                return 2;            } else {
                return 2;            }
        }
    }
}

// Tree 7
int predict_tree_7(const float* features) {
    // Max depth: 20
    if (features[0] <= -0.4452916979789734f) {
        if (features[4] <= 0.26887740194797516f) {
            if (features[31] <= 0.1988118588924408f) {
                return 0;            } else {
                return 0;            }
        } else {
            if (features[4] <= 1.3182757496833801f) {
                if (features[13] <= 0.4582866430282593f) {
                    if (features[3] <= -0.7392788529396057f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[19] <= -0.5803326368331909f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[19] <= -0.2840629518032074f) {
            if (features[20] <= 1.4311721920967102f) {
                if (features[23] <= 0.09502580389380455f) {
                    if (features[7] <= -1.2148626148700714f) {
                        return 0;                    } else {
                        if (features[7] <= 0.15366558730602264f) {
                            if (features[10] <= -0.4126114845275879f) {
                                return 0;                            } else {
                                if (features[26] <= 0.07540398091077805f) {
                                    if (features[5] <= 0.0895652286708355f) {
                                        if (features[6] <= 0.5450443178415298f) {
                                            if (features[8] <= 0.3760054409503937f) {
                                                if (features[19] <= -0.3136308491230011f) {
                                                    if (features[24] <= -0.37945041060447693f) {
                                                        return 0;                                                    } else {
                                                        if (features[10] <= -0.3052825480699539f) {
                                                            if (features[11] <= -0.12544110789895058f) {
                                                                return 0;                                                            } else {
                                                                if (features[27] <= 0.6028508543968201f) {
                                                                    if (features[2] <= 0.8606979250907898f) {
                                                                        if (features[15] <= 0.7553892731666565f) {
                                                                            if (features[25] <= -0.37399013340473175f) {
                                                                                return 0;                                                                            } else {
                                                                                return 1;                                                                            }
                                                                        } else {
                                                                            if (features[0] <= -0.3761644959449768f) {
                                                                                return 0;                                                                            } else {
                                                                                if (features[24] <= -0.1362214982509613f) {
                                                                                    return 1;                                                                                } else {
                                                                                    return 2;                                                                                }
                                                                            }
                                                                        }
                                                                    } else {
                                                                        return 0;                                                                    }
                                                                } else {
                                                                    if (features[14] <= 0.29109427332878113f) {
                                                                        return 2;                                                                    } else {
                                                                        return 1;                                                                    }
                                                                }
                                                            }
                                                        } else {
                                                            if (features[25] <= 0.016782786697149277f) {
                                                                return 1;                                                            } else {
                                                                return 2;                                                            }
                                                        }
                                                    }
                                                } else {
                                                    return 0;                                                }
                                            } else {
                                                return 2;                                            }
                                        } else {
                                            return 0;                                        }
                                    } else {
                                        if (features[9] <= 1.8220404982566833f) {
                                            return 2;                                        } else {
                                            return 2;                                        }
                                    }
                                } else {
                                    if (features[2] <= -0.3516653776168823f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                }
                            }
                        } else {
                            if (features[2] <= 0.0054648995865136385f) {
                                if (features[19] <= -0.40721796452999115f) {
                                    return 0;                                } else {
                                    if (features[26] <= -0.3313148766756058f) {
                                        return 0;                                    } else {
                                        if (features[12] <= -0.016357598826289177f) {
                                            return 0;                                        } else {
                                            if (features[27] <= -0.3860199749469757f) {
                                                return 0;                                            } else {
                                                if (features[30] <= 0.18403255939483643f) {
                                                    if (features[10] <= -0.3509949892759323f) {
                                                        if (features[2] <= -0.2464059218764305f) {
                                                            return 1;                                                        } else {
                                                            return 0;                                                        }
                                                    } else {
                                                        return 1;                                                    }
                                                } else {
                                                    if (features[11] <= 0.05009993351995945f) {
                                                        if (features[27] <= -0.3829466998577118f) {
                                                            return 0;                                                        } else {
                                                            if (features[17] <= -0.3752882033586502f) {
                                                                if (features[12] <= 0.001438564358977601f) {
                                                                    return 1;                                                                } else {
                                                                    if (features[2] <= -0.2567439004778862f) {
                                                                        return 2;                                                                    } else {
                                                                        return 0;                                                                    }
                                                                }
                                                            } else {
                                                                return 1;                                                            }
                                                        }
                                                    } else {
                                                        return 2;                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            } else {
                                if (features[7] <= 0.4203161746263504f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            }
                        }
                    }
                } else {
                    if (features[28] <= 0.034745603799819946f) {
                        if (features[5] <= 0.09032361954450607f) {
                            return 1;                        } else {
                            if (features[0] <= -0.4028644412755966f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[25] <= 0.08962589129805565f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[3] <= 1.8834524750709534f) {
                if (features[18] <= -0.13782230764627457f) {
                    if (features[5] <= 0.1214175671339035f) {
                        return 1;                    } else {
                        if (features[22] <= 1.420204073190689f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[4] <= 0.20107893645763397f) {
                        if (features[7] <= -0.47863733768463135f) {
                            return 1;                        } else {
                            return 2;                        }
                    } else {
                        if (features[22] <= 0.07338361628353596f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[21] <= -0.08857762813568115f) {
                    return 0;                } else {
                    return 0;                }
            }
        }
    }
}

// Tree 8
int predict_tree_8(const float* features) {
    // Max depth: 20
    if (features[1] <= -0.06616747006773949f) {
        if (features[0] <= -0.4262443482875824f) {
            if (features[21] <= 0.14507320523262024f) {
                if (features[9] <= -1.0657048225402832f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[19] <= -0.503117710351944f) {
                    if (features[12] <= -0.00047092000022530556f) {
                        return 0;                    } else {
                        if (features[14] <= -0.12785660475492477f) {
                            return 0;                        } else {
                            if (features[5] <= 0.009555181255564094f) {
                                return 0;                            } else {
                                if (features[6] <= 0.3237733840942383f) {
                                    return 1;                                } else {
                                    if (features[18] <= -0.5605116784572601f) {
                                        return 1;                                    } else {
                                        return 2;                                    }
                                }
                            }
                        }
                    }
                } else {
                    if (features[1] <= -0.47705861926078796f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[22] <= 1.418739676475525f) {
                if (features[3] <= 0.6019358038902283f) {
                    if (features[23] <= 0.1101977489888668f) {
                        if (features[9] <= -0.7655880153179169f) {
                            return 0;                        } else {
                            if (features[9] <= 2.6976022720336914f) {
                                if (features[5] <= 0.0895652286708355f) {
                                    if (features[23] <= -0.38744188845157623f) {
                                        return 0;                                    } else {
                                        if (features[17] <= -0.19416580721735954f) {
                                            if (features[24] <= -0.38893671333789825f) {
                                                return 0;                                            } else {
                                                if (features[6] <= 0.10250241588801146f) {
                                                    if (features[26] <= -0.2674252688884735f) {
                                                        return 1;                                                    } else {
                                                        if (features[20] <= 0.40145932883024216f) {
                                                            if (features[14] <= -0.005662601441144943f) {
                                                                return 0;                                                            } else {
                                                                return 1;                                                            }
                                                        } else {
                                                            if (features[27] <= -0.19636472314596176f) {
                                                                return 2;                                                            } else {
                                                                return 2;                                                            }
                                                        }
                                                    }
                                                } else {
                                                    if (features[21] <= -0.5649789869785309f) {
                                                        if (features[26] <= -0.3313148766756058f) {
                                                            return 0;                                                        } else {
                                                            if (features[19] <= -0.3851314038038254f) {
                                                                if (features[0] <= -0.3697195053100586f) {
                                                                    return 0;                                                                } else {
                                                                    return 1;                                                                }
                                                            } else {
                                                                if (features[26] <= -0.13671719655394554f) {
                                                                    if (features[18] <= -0.38093554973602295f) {
                                                                        return 0;                                                                    } else {
                                                                        if (features[26] <= -0.30939361453056335f) {
                                                                            if (features[4] <= -0.6289442777633667f) {
                                                                                if (features[18] <= -0.37269461154937744f) {
                                                                                    return 0;                                                                                } else {
                                                                                    return 1;                                                                                }
                                                                            } else {
                                                                                return 0;                                                                            }
                                                                        } else {
                                                                            return 1;                                                                        }
                                                                    }
                                                                } else {
                                                                    return 0;                                                                }
                                                            }
                                                        }
                                                    } else {
                                                        if (features[25] <= -0.2810392826795578f) {
                                                            if (features[29] <= -0.5067617737222463f) {
                                                                return 0;                                                            } else {
                                                                return 0;                                                            }
                                                        } else {
                                                            if (features[25] <= -0.21806035190820694f) {
                                                                return 1;                                                            } else {
                                                                return 0;                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        } else {
                                            if (features[7] <= -0.3800409138202667f) {
                                                return 1;                                            } else {
                                                return 2;                                            }
                                        }
                                    }
                                } else {
                                    if (features[24] <= 0.07589232549071312f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                }
                            } else {
                                if (features[9] <= 2.7202953100204468f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        }
                    } else {
                        if (features[5] <= 0.10321623086929321f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[13] <= -0.1470712277223356f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[6] <= -0.7825813936069608f) {
                    return 2;                } else {
                    if (features[25] <= 0.145396389067173f) {
                        return 2;                    } else {
                        return 1;                    }
                }
            }
        }
    } else {
        if (features[2] <= -0.9597266465425491f) {
            return 0;        } else {
            return 2;        }
    }
}

// Tree 9
int predict_tree_9(const float* features) {
    // Max depth: 13
    if (features[1] <= -0.418053463101387f) {
        if (features[27] <= -0.032439662143588066f) {
            if (features[22] <= 0.33451028168201447f) {
                if (features[7] <= -3.5717815160751343f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[4] <= 0.39283591508865356f) {
                    return 1;                } else {
                    if (features[18] <= -0.5353734791278839f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[25] <= 0.8859679698944092f) {
                if (features[26] <= -0.3254833221435547f) {
                    return 0;                } else {
                    if (features[4] <= 0.21936789900064468f) {
                        if (features[33] <= -0.785379022359848f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[27] <= 2.0377508997917175f) {
                            return 1;                        } else {
                            return 0;                        }
                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[5] <= -0.05907903052866459f) {
            if (features[2] <= 0.8512997627258301f) {
                if (features[27] <= -0.3829466998577118f) {
                    return 0;                } else {
                    if (features[10] <= -0.36321739852428436f) {
                        if (features[5] <= -0.4610252380371094f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[26] <= 1.348070740699768f) {
                            if (features[0] <= -0.3722134679555893f) {
                                return 0;                            } else {
                                if (features[28] <= 0.034745603799819946f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        } else {
                            if (features[23] <= -0.06769324839115143f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                if (features[17] <= 0.16297684609889984f) {
                    return 0;                } else {
                    return 2;                }
            }
        } else {
            if (features[3] <= 0.2919042706489563f) {
                if (features[11] <= -5.107746601104736f) {
                    if (features[20] <= 0.3565448373556137f) {
                        return 1;                    } else {
                        return 2;                    }
                } else {
                    if (features[1] <= -0.0606569480150938f) {
                        if (features[27] <= 0.19741668552160263f) {
                            if (features[30] <= 0.18403255939483643f) {
                                return 2;                            } else {
                                return 2;                            }
                        } else {
                            return 1;                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[22] <= 1.4201126098632812f) {
                    if (features[21] <= 1.154955804347992f) {
                        if (features[2] <= -0.9597266465425491f) {
                            return 0;                        } else {
                            if (features[7] <= 0.35323652625083923f) {
                                return 2;                            } else {
                                if (features[3] <= 0.5342780947685242f) {
                                    return 2;                                } else {
                                    return 1;                                }
                            }
                        }
                    } else {
                        if (features[27] <= 0.7678872048854828f) {
                            if (features[23] <= 0.1105770468711853f) {
                                if (features[10] <= -0.36010921001434326f) {
                                    if (features[23] <= 0.089715626090765f) {
                                        if (features[1] <= -0.3647131621837616f) {
                                            return 1;                                        } else {
                                            if (features[7] <= 0.14374062418937683f) {
                                                if (features[20] <= 1.279458999633789f) {
                                                    if (features[19] <= -0.38649123907089233f) {
                                                        return 1;                                                    } else {
                                                        return 2;                                                    }
                                                } else {
                                                    return 2;                                                }
                                            } else {
                                                return 2;                                            }
                                        }
                                    } else {
                                        if (features[18] <= -0.4000476449728012f) {
                                            return 2;                                        } else {
                                            if (features[1] <= -0.35775645077228546f) {
                                                return 2;                                            } else {
                                                return 1;                                            }
                                        }
                                    }
                                } else {
                                    if (features[31] <= 0.1988118588924408f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                }
                            } else {
                                if (features[13] <= -0.8367711007595062f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[15] <= 0.7553892731666565f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[15] <= 0.7553892731666565f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 10
int predict_tree_10(const float* features) {
    // Max depth: 18
    if (features[1] <= -0.4170478880405426f) {
        if (features[16] <= 2.4144846946001053f) {
            if (features[6] <= -1.4463942050933838f) {
                if (features[17] <= -0.5287416875362396f) {
                    if (features[27] <= 0.27854909002780914f) {
                        return 0;                    } else {
                        if (features[24] <= -0.12521738093346357f) {
                            return 0;                        } else {
                            if (features[21] <= 0.5061198025941849f) {
                                if (features[27] <= 0.46436239778995514f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    return 2;                }
            } else {
                if (features[23] <= 0.0017183751915581524f) {
                    if (features[18] <= -0.6049982309341431f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[23] <= 0.0036148675717413425f) {
                        return 1;                    } else {
                        return 0;                    }
                }
            }
        } else {
            if (features[20] <= 1.9726361334323883f) {
                if (features[5] <= 0.011071959510445595f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                if (features[29] <= -0.001376032829284668f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[6] <= -0.1187685402110219f) {
            if (features[18] <= -0.3177034556865692f) {
                if (features[24] <= 0.08651698753237724f) {
                    if (features[9] <= -0.680912435054779f) {
                        return 0;                    } else {
                        if (features[23] <= 0.09161211922764778f) {
                            if (features[13] <= -1.051707148551941f) {
                                return 2;                            } else {
                                if (features[1] <= -0.40207213163375854f) {
                                    return 0;                                } else {
                                    if (features[11] <= 0.23633228987455368f) {
                                        if (features[26] <= -0.3353203237056732f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 2;                                    }
                                }
                            }
                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[11] <= -0.029429213143885136f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[10] <= -0.3164954334497452f) {
                    if (features[4] <= 0.7757956683635712f) {
                        return 1;                    } else {
                        return 2;                    }
                } else {
                    if (features[7] <= 1.9131525754928589f) {
                        if (features[3] <= 1.9033518135547638f) {
                            return 2;                        } else {
                            return 0;                        }
                    } else {
                        if (features[21] <= 0.17981750704348087f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[27] <= 0.6152150630950928f) {
                if (features[1] <= -0.3768407255411148f) {
                    return 0;                } else {
                    if (features[0] <= -0.27848954498767853f) {
                        if (features[20] <= 1.4348613023757935f) {
                            if (features[23] <= 0.1101977489888668f) {
                                if (features[21] <= -0.7017502188682556f) {
                                    return 0;                                } else {
                                    if (features[3] <= -0.4049701690673828f) {
                                        return 0;                                    } else {
                                        if (features[14] <= 0.4831134229898453f) {
                                            if (features[2] <= 0.3062061667442322f) {
                                                if (features[19] <= -0.4048127233982086f) {
                                                    if (features[11] <= 0.04204835928976536f) {
                                                        if (features[2] <= -0.22854941338300705f) {
                                                            return 2;                                                        } else {
                                                            return 0;                                                        }
                                                    } else {
                                                        if (features[7] <= 0.23088838905096054f) {
                                                            return 1;                                                        } else {
                                                            return 0;                                                        }
                                                    }
                                                } else {
                                                    if (features[26] <= -0.3326534330844879f) {
                                                        return 0;                                                    } else {
                                                        if (features[9] <= -0.7587411999702454f) {
                                                            return 0;                                                        } else {
                                                            if (features[0] <= -0.37225593626499176f) {
                                                                if (features[9] <= 2.170461058616638f) {
                                                                    if (features[22] <= 0.28160762786865234f) {
                                                                        return 0;                                                                    } else {
                                                                        return 2;                                                                    }
                                                                } else {
                                                                    if (features[1] <= -0.3688700199127197f) {
                                                                        return 1;                                                                    } else {
                                                                        if (features[5] <= 0.08918603509664536f) {
                                                                            return 1;                                                                        } else {
                                                                            return 2;                                                                        }
                                                                    }
                                                                }
                                                            } else {
                                                                return 1;                                                            }
                                                        }
                                                    }
                                                }
                                            } else {
                                                if (features[8] <= 0.4608888179063797f) {
                                                    if (features[3] <= -0.3970104455947876f) {
                                                        return 0;                                                    } else {
                                                        return 0;                                                    }
                                                } else {
                                                    return 1;                                                }
                                            }
                                        } else {
                                            if (features[12] <= 0.013489787932485342f) {
                                                return 2;                                            } else {
                                                return 2;                                            }
                                        }
                                    }
                                }
                            } else {
                                if (features[24] <= 0.0941060371696949f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[8] <= -0.1514420211315155f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[23] <= -0.0016953113081399351f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[0] <= -0.3965615779161453f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 11
int predict_tree_11(const float* features) {
    // Max depth: 14
    if (features[18] <= -0.4517357349395752f) {
        if (features[23] <= 0.0017183751915581524f) {
            if (features[11] <= 0.1299009993672371f) {
                if (features[23] <= -0.5110931992530823f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[17] <= -0.41570553183555603f) {
                    if (features[18] <= -0.5647321939468384f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    return 1;                }
            }
        } else {
            if (features[3] <= -0.35721178352832794f) {
                return 1;            } else {
                if (features[20] <= 1.4382737278938293f) {
                    if (features[4] <= 0.33843088150024414f) {
                        if (features[26] <= 0.1968189924955368f) {
                            return 0;                        } else {
                            return 2;                        }
                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[0] <= -0.23168553411960602f) {
            if (features[4] <= 1.4548887610435486f) {
                if (features[4] <= -0.6470485031604767f) {
                    return 0;                } else {
                    if (features[5] <= 0.08918603509664536f) {
                        if (features[0] <= -0.42639899253845215f) {
                            return 0;                        } else {
                            if (features[5] <= -0.10989109799265862f) {
                                if (features[24] <= -0.3661695867776871f) {
                                    if (features[8] <= -0.07337940111756325f) {
                                        if (features[3] <= 0.5820364952087402f) {
                                            if (features[12] <= -0.0645377654582262f) {
                                                return 0;                                            } else {
                                                if (features[10] <= -0.3565128445625305f) {
                                                    if (features[31] <= 0.1988118588924408f) {
                                                        return 0;                                                    } else {
                                                        return 0;                                                    }
                                                } else {
                                                    if (features[0] <= -0.37225593626499176f) {
                                                        return 0;                                                    } else {
                                                        if (features[18] <= -0.4456387907266617f) {
                                                            return 1;                                                        } else {
                                                            return 1;                                                        }
                                                    }
                                                }
                                            }
                                        } else {
                                            if (features[27] <= -0.38285112380981445f) {
                                                return 0;                                            } else {
                                                return 0;                                            }
                                        }
                                    } else {
                                        if (features[2] <= -0.03212776035070419f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    }
                                } else {
                                    if (features[8] <= 0.4703059494495392f) {
                                        if (features[11] <= -0.11718078330159187f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                if (features[1] <= -0.3457430303096771f) {
                                    return 1;                                } else {
                                    if (features[3] <= 0.37508346140384674f) {
                                        return 1;                                    } else {
                                        return 2;                                    }
                                }
                            }
                        }
                    } else {
                        if (features[10] <= -0.39593029022216797f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[6] <= -1.888936161994934f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[6] <= -1.0038523077964783f) {
                if (features[3] <= 1.911311537027359f) {
                    return 2;                } else {
                    if (features[26] <= -0.33241698145866394f) {
                        return 0;                    } else {
                        return 0;                    }
                }
            } else {
                return 2;            }
        }
    }
}

// Tree 12
int predict_tree_12(const float* features) {
    // Max depth: 15
    if (features[8] <= -0.3191589266061783f) {
        if (features[18] <= -0.27007855847477913f) {
            if (features[7] <= 0.6673174202442169f) {
                return 0;            } else {
                return 2;            }
        } else {
            if (features[17] <= -0.062276557087898254f) {
                return 2;            } else {
                return 2;            }
        }
    } else {
        if (features[4] <= 0.1257062554359436f) {
            if (features[2] <= -0.12610940635204315f) {
                if (features[13] <= 0.04065772891044617f) {
                    if (features[9] <= -1.061959683895111f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[11] <= 0.10000056400895119f) {
                        if (features[17] <= -0.6048803627490997f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[11] <= 0.10186426341533661f) {
                            return 1;                        } else {
                            return 0;                        }
                    }
                }
            } else {
                if (features[6] <= 1.2088571786880493f) {
                    if (features[10] <= -0.3669240176677704f) {
                        return 0;                    } else {
                        if (features[17] <= -0.16005748719908297f) {
                            if (features[27] <= -0.2602262943983078f) {
                                if (features[11] <= -0.03704584389925003f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            } else {
                                return 1;                            }
                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[0] <= -0.37225593626499176f) {
                        if (features[25] <= -0.3971329927444458f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[17] <= -0.37374623119831085f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            }
        } else {
            if (features[24] <= 0.12673892825841904f) {
                if (features[10] <= -0.2654678225517273f) {
                    if (features[23] <= 0.09730159863829613f) {
                        if (features[5] <= -0.07197164371609688f) {
                            return 0;                        } else {
                            if (features[17] <= -0.5817916691303253f) {
                                return 0;                            } else {
                                if (features[1] <= -0.5211361944675446f) {
                                    if (features[2] <= -0.20129472762346268f) {
                                        if (features[18] <= -0.5826831459999084f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        if (features[19] <= -0.5775381028652191f) {
                                            if (features[5] <= 0.0482330247759819f) {
                                                if (features[24] <= -0.05463926121592522f) {
                                                    return 0;                                                } else {
                                                    return 0;                                                }
                                            } else {
                                                return 1;                                            }
                                        } else {
                                            if (features[10] <= -0.5603733360767365f) {
                                                return 0;                                            } else {
                                                return 0;                                            }
                                        }
                                    }
                                } else {
                                    if (features[24] <= 0.08386082202196121f) {
                                        if (features[25] <= 0.09417858347296715f) {
                                            if (features[21] <= 1.2499052286148071f) {
                                                if (features[5] <= 0.27271618694067f) {
                                                    if (features[22] <= 1.2337635159492493f) {
                                                        return 1;                                                    } else {
                                                        if (features[26] <= -0.2836894541978836f) {
                                                            if (features[5] <= 0.0895652286708355f) {
                                                                return 1;                                                            } else {
                                                                return 2;                                                            }
                                                        } else {
                                                            return 2;                                                        }
                                                    }
                                                } else {
                                                    return 2;                                                }
                                            } else {
                                                return 1;                                            }
                                        } else {
                                            return 2;                                        }
                                    } else {
                                        if (features[11] <= 0.012612348422408104f) {
                                            if (features[10] <= -0.3458152264356613f) {
                                                if (features[12] <= 0.008568734396249056f) {
                                                    if (features[4] <= 1.145916223526001f) {
                                                        return 2;                                                    } else {
                                                        return 1;                                                    }
                                                } else {
                                                    if (features[25] <= 0.1245298758149147f) {
                                                        if (features[14] <= -0.09294403158128262f) {
                                                            return 2;                                                        } else {
                                                            return 2;                                                        }
                                                    } else {
                                                        return 1;                                                    }
                                                }
                                            } else {
                                                return 2;                                            }
                                        } else {
                                            return 2;                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        if (features[17] <= -0.46099384129047394f) {
                            return 1;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[27] <= -0.3806704729795456f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[19] <= -0.5027588903903961f) {
                    if (features[0] <= -0.36451049894094467f) {
                        return 1;                    } else {
                        return 2;                    }
                } else {
                    if (features[13] <= 3.6075079441070557f) {
                        return 2;                    } else {
                        if (features[2] <= -1.061226800084114f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    }
}

// Tree 13
int predict_tree_13(const float* features) {
    // Max depth: 16
    if (features[21] <= 0.1247597336769104f) {
        if (features[1] <= -0.34813080728054047f) {
            if (features[17] <= -0.6049589514732361f) {
                return 0;            } else {
                return 0;            }
        } else {
            if (features[5] <= -0.23464610427618027f) {
                if (features[5] <= -0.4094547778367996f) {
                    return 0;                } else {
                    if (features[10] <= -0.35753123462200165f) {
                        return 0;                    } else {
                        if (features[3] <= -0.3970104455947876f) {
                            return 0;                        } else {
                            if (features[5] <= -0.3700185567140579f) {
                                if (features[5] <= -0.37608565390110016f) {
                                    return 1;                                } else {
                                    if (features[17] <= -0.37135984003543854f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                if (features[14] <= 0.11653140932321548f) {
                                    if (features[3] <= 0.546217679977417f) {
                                        if (features[10] <= -0.3503971993923187f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 0;                                    }
                                } else {
                                    if (features[27] <= -0.29326891899108887f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                if (features[21] <= 0.05986693874001503f) {
                    if (features[6] <= -1.0038523077964783f) {
                        return 0;                    } else {
                        if (features[8] <= 0.1442035660147667f) {
                            return 2;                        } else {
                            if (features[0] <= -0.4582750201225281f) {
                                return 0;                            } else {
                                return 0;                            }
                        }
                    }
                } else {
                    if (features[7] <= -0.45957762002944946f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[22] <= 1.1436094045639038f) {
            if (features[18] <= -0.3177034556865692f) {
                if (features[23] <= -0.07262412831187248f) {
                    return 0;                } else {
                    if (features[2] <= -0.18249839544296265f) {
                        if (features[0] <= -0.5289275050163269f) {
                            return 0;                        } else {
                            if (features[19] <= -0.45236240327358246f) {
                                return 1;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[1] <= -0.5431885719299316f) {
                            return 0;                        } else {
                            if (features[14] <= -0.3024194687604904f) {
                                return 0;                            } else {
                                if (features[26] <= -0.3327478617429733f) {
                                    return 0;                                } else {
                                    if (features[5] <= -0.07197164371609688f) {
                                        return 0;                                    } else {
                                        if (features[9] <= 0.11194571852684021f) {
                                            return 2;                                        } else {
                                            if (features[8] <= -0.23179160803556442f) {
                                                return 0;                                            } else {
                                                if (features[13] <= -0.10762094333767891f) {
                                                    if (features[20] <= 0.18094489723443985f) {
                                                        return 0;                                                    } else {
                                                        if (features[27] <= 0.3204079940915108f) {
                                                            if (features[12] <= -0.002208950463682413f) {
                                                                return 0;                                                            } else {
                                                                return 0;                                                            }
                                                        } else {
                                                            return 1;                                                        }
                                                    }
                                                } else {
                                                    if (features[25] <= -0.04619615152478218f) {
                                                        if (features[24] <= -0.079683106392622f) {
                                                            return 0;                                                        } else {
                                                            if (features[7] <= -0.2363530471920967f) {
                                                                if (features[0] <= -0.5812687277793884f) {
                                                                    return 1;                                                                } else {
                                                                    return 1;                                                                }
                                                            } else {
                                                                if (features[6] <= -0.00813305377960205f) {
                                                                    return 1;                                                                } else {
                                                                    return 0;                                                                }
                                                            }
                                                        }
                                                    } else {
                                                        if (features[0] <= -0.5527611374855042f) {
                                                            return 0;                                                        } else {
                                                            return 1;                                                        }
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
            } else {
                if (features[5] <= -0.043152859434485435f) {
                    if (features[8] <= -0.1618790104985237f) {
                        return 1;                    } else {
                        if (features[1] <= 0.920341283082962f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[23] <= -0.0711069367825985f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[5] <= 0.08880684152245522f) {
                if (features[10] <= -0.3603646159172058f) {
                    return 1;                } else {
                    if (features[18] <= 0.06681793928146362f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[25] <= -0.0021867742761969566f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 14
int predict_tree_14(const float* features) {
    // Max depth: 18
    if (features[1] <= -0.2056017816066742f) {
        if (features[10] <= -0.41013185679912567f) {
            if (features[24] <= -0.061848850920796394f) {
                if (features[20] <= -0.8359484374523163f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[17] <= -0.5030697286128998f) {
                    if (features[21] <= 0.29875698685646057f) {
                        if (features[13] <= 0.3671428821980953f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        if (features[7] <= -0.5432323962450027f) {
                            if (features[4] <= 0.036385923624038696f) {
                                return 0;                            } else {
                                if (features[26] <= -0.18481295555830002f) {
                                    if (features[20] <= 0.4534752815961838f) {
                                        if (features[10] <= -0.5135950893163681f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 2;                                }
                            }
                        } else {
                            return 0;                        }
                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[24] <= 0.12560056895017624f) {
                if (features[2] <= -0.4484664499759674f) {
                    if (features[5] <= -0.15766961127519608f) {
                        if (features[31] <= 0.1988118588924408f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[21] <= 1.4355758428573608f) {
                        if (features[22] <= -0.6420833170413971f) {
                            return 0;                        } else {
                            if (features[23] <= 0.09730159863829613f) {
                                if (features[5] <= 0.0895652286708355f) {
                                    if (features[18] <= -0.46752889454364777f) {
                                        return 0;                                    } else {
                                        if (features[0] <= -0.4263508468866348f) {
                                            return 0;                                        } else {
                                            if (features[1] <= -0.33325743675231934f) {
                                                if (features[20] <= -0.6113760471343994f) {
                                                    if (features[2] <= -0.10731307789683342f) {
                                                        if (features[4] <= -0.6393819153308868f) {
                                                            if (features[10] <= -0.35391396284103394f) {
                                                                if (features[5] <= -0.3753272742033005f) {
                                                                    return 0;                                                                } else {
                                                                    return 0;                                                                }
                                                            } else {
                                                                return 1;                                                            }
                                                        } else {
                                                            if (features[30] <= 0.18403255939483643f) {
                                                                return 0;                                                            } else {
                                                                return 0;                                                            }
                                                        }
                                                    } else {
                                                        return 0;                                                    }
                                                } else {
                                                    if (features[18] <= -0.4441002905368805f) {
                                                        return 0;                                                    } else {
                                                        if (features[19] <= -0.42774730920791626f) {
                                                            if (features[17] <= -0.3949025124311447f) {
                                                                return 0;                                                            } else {
                                                                return 1;                                                            }
                                                        } else {
                                                            if (features[27] <= -0.3470039516687393f) {
                                                                if (features[5] <= -0.14629376865923405f) {
                                                                    return 0;                                                                } else {
                                                                    return 1;                                                                }
                                                            } else {
                                                                if (features[11] <= 0.049110932275652885f) {
                                                                    if (features[20] <= 0.09830963239073753f) {
                                                                        if (features[17] <= -0.37693463265895844f) {
                                                                            return 0;                                                                        } else {
                                                                            return 1;                                                                        }
                                                                    } else {
                                                                        return 1;                                                                    }
                                                                } else {
                                                                    return 2;                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            } else {
                                                if (features[20] <= 0.45799438655376434f) {
                                                    if (features[3] <= -0.3890507221221924f) {
                                                        if (features[20] <= -0.15955666452646255f) {
                                                            return 0;                                                        } else {
                                                            return 1;                                                        }
                                                    } else {
                                                        if (features[10] <= -0.3512568175792694f) {
                                                            return 0;                                                        } else {
                                                            if (features[11] <= -0.06281160376966f) {
                                                                return 1;                                                            } else {
                                                                return 1;                                                            }
                                                        }
                                                    }
                                                } else {
                                                    if (features[20] <= 0.5843451917171478f) {
                                                        return 2;                                                    } else {
                                                        return 2;                                                    }
                                                }
                                            }
                                        }
                                    }
                                } else {
                                    if (features[28] <= 0.034745603799819946f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                }
                            } else {
                                if (features[7] <= 0.3285208195447922f) {
                                    if (features[27] <= -0.2871616631746292f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                } else {
                                    return 1;                                }
                            }
                        }
                    } else {
                        if (features[14] <= -0.2151380330324173f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[1] <= -0.3523509204387665f) {
                    return 2;                } else {
                    if (features[5] <= 0.10738737508654594f) {
                        return 1;                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[22] <= 0.05709180235862732f) {
            if (features[2] <= -0.6524066478013992f) {
                return 0;            } else {
                return 2;            }
        } else {
            if (features[14] <= 1.0242582559585571f) {
                if (features[1] <= -0.16269316524267197f) {
                    return 2;                } else {
                    return 2;                }
            } else {
                if (features[5] <= -0.02760588377714157f) {
                    if (features[17] <= 0.4354051798582077f) {
                        return 1;                    } else {
                        return 2;                    }
                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 15
int predict_tree_15(const float* features) {
    // Max depth: 14
    if (features[0] <= -0.2898711562156677f) {
        if (features[18] <= -0.4262853264808655f) {
            if (features[24] <= -0.05881323479115963f) {
                if (features[18] <= -0.4656197726726532f) {
                    if (features[17] <= -0.4229193329811096f) {
                        if (features[27] <= -0.4003090560436249f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[11] <= 0.0858808308839798f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[10] <= -0.484856441617012f) {
                    if (features[5] <= 0.030031686648726463f) {
                        return 0;                    } else {
                        if (features[22] <= 0.5068557262420654f) {
                            return 1;                        } else {
                            if (features[11] <= 0.0017062677652575076f) {
                                return 2;                            } else {
                                return 0;                            }
                        }
                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[23] <= 0.1101977489888668f) {
                if (features[20] <= -0.6448543965816498f) {
                    return 0;                } else {
                    if (features[0] <= -0.4264049082994461f) {
                        return 0;                    } else {
                        if (features[24] <= -0.11269545927643776f) {
                            if (features[17] <= -0.36997297406196594f) {
                                if (features[21] <= -0.644302636384964f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                if (features[6] <= -0.008133061230182648f) {
                                    if (features[27] <= -0.3536257892847061f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[1] <= -0.33796460926532745f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        } else {
                            if (features[4] <= 1.4608927369117737f) {
                                if (features[2] <= -0.42121177911758423f) {
                                    if (features[31] <= 0.1988118588924408f) {
                                        return 2;                                    } else {
                                        if (features[2] <= -0.4428275525569916f) {
                                            if (features[0] <= -0.40723541378974915f) {
                                                return 2;                                            } else {
                                                return 1;                                            }
                                        } else {
                                            return 2;                                        }
                                    }
                                } else {
                                    if (features[25] <= 0.09493736922740936f) {
                                        if (features[1] <= -0.368840292096138f) {
                                            if (features[23] <= 0.08668123930692673f) {
                                                return 1;                                            } else {
                                                return 2;                                            }
                                        } else {
                                            if (features[3] <= 0.3249371647834778f) {
                                                return 1;                                            } else {
                                                if (features[20] <= 1.1860331892967224f) {
                                                    return 2;                                                } else {
                                                    if (features[4] <= 1.3632592558860779f) {
                                                        if (features[0] <= -0.40109553933143616f) {
                                                            return 2;                                                        } else {
                                                            return 1;                                                        }
                                                    } else {
                                                        return 2;                                                    }
                                                }
                                            }
                                        }
                                    } else {
                                        if (features[10] <= -0.3718092739582062f) {
                                            if (features[20] <= 1.3316594362258911f) {
                                                if (features[8] <= -0.05439861863851547f) {
                                                    return 1;                                                } else {
                                                    return 2;                                                }
                                            } else {
                                                return 2;                                            }
                                        } else {
                                            return 2;                                        }
                                    }
                                }
                            } else {
                                if (features[7] <= -0.07405082695186138f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                }
            } else {
                if (features[27] <= -0.3647567480802536f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[7] <= 1.9131525754928589f) {
            return 2;        } else {
            if (features[4] <= 0.22454053163528442f) {
                return 0;            } else {
                return 2;            }
        }
    }
}

// Tree 16
int predict_tree_16(const float* features) {
    // Max depth: 19
    if (features[19] <= -0.005444669164717197f) {
        if (features[1] <= -0.3977525234222412f) {
            if (features[22] <= 0.30000460147857666f) {
                if (features[25] <= -0.11107204109430313f) {
                    return 0;                } else {
                    if (features[23] <= 0.008545748190954328f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[2] <= 0.04305755998939276f) {
                    if (features[5] <= 0.02661893516778946f) {
                        if (features[11] <= -0.02729961182922125f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[14] <= 7.989316642284393f) {
                            if (features[7] <= -0.5432323962450027f) {
                                return 1;                            } else {
                                if (features[21] <= 0.5314886569976807f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            }
                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[7] <= 0.27002807706594467f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[21] <= 1.4016587734222412f) {
                if (features[17] <= -0.272496834397316f) {
                    if (features[21] <= -0.644302636384964f) {
                        return 0;                    } else {
                        if (features[10] <= -0.4100543260574341f) {
                            return 0;                        } else {
                            if (features[23] <= 0.1105770468711853f) {
                                if (features[8] <= -0.057463232427835464f) {
                                    if (features[11] <= 0.17657774686813354f) {
                                        if (features[14] <= 0.4831134229898453f) {
                                            if (features[23] <= -0.3893383741378784f) {
                                                return 0;                                            } else {
                                                if (features[17] <= -0.4258766770362854f) {
                                                    return 0;                                                } else {
                                                    if (features[7] <= 0.4402111917734146f) {
                                                        if (features[5] <= 0.09146120399236679f) {
                                                            if (features[25] <= -0.3887863755226135f) {
                                                                return 0;                                                            } else {
                                                                if (features[4] <= 0.09513228572905064f) {
                                                                    if (features[20] <= -0.564248114824295f) {
                                                                        if (features[12] <= -0.09389263391494751f) {
                                                                            return 0;                                                                        } else {
                                                                            if (features[10] <= -0.35890598595142365f) {
                                                                                return 0;                                                                            } else {
                                                                                return 1;                                                                            }
                                                                        }
                                                                    } else {
                                                                        if (features[5] <= -0.35750512778759f) {
                                                                            return 0;                                                                        } else {
                                                                            return 0;                                                                        }
                                                                    }
                                                                } else {
                                                                    if (features[12] <= 0.035318825393915176f) {
                                                                        return 1;                                                                    } else {
                                                                        return 2;                                                                    }
                                                                }
                                                            }
                                                        } else {
                                                            if (features[4] <= 1.1508117318153381f) {
                                                                return 2;                                                            } else {
                                                                return 2;                                                            }
                                                        }
                                                    } else {
                                                        if (features[10] <= -0.35214927792549133f) {
                                                            return 0;                                                        } else {
                                                            return 1;                                                        }
                                                    }
                                                }
                                            }
                                        } else {
                                            if (features[12] <= 0.013988487888127565f) {
                                                return 2;                                            } else {
                                                return 2;                                            }
                                        }
                                    } else {
                                        if (features[26] <= -0.01703947875648737f) {
                                            return 2;                                        } else {
                                            return 0;                                        }
                                    }
                                } else {
                                    if (features[28] <= 0.5375470276921988f) {
                                        if (features[7] <= 0.15676970779895782f) {
                                            if (features[22] <= 0.5978335998952389f) {
                                                return 0;                                            } else {
                                                return 2;                                            }
                                        } else {
                                            if (features[8] <= 0.16865324974060059f) {
                                                return 0;                                            } else {
                                                return 0;                                            }
                                        }
                                    } else {
                                        if (features[18] <= -0.4608127623796463f) {
                                            return 0;                                        } else {
                                            if (features[0] <= -0.4158415198326111f) {
                                                return 2;                                            } else {
                                                if (features[23] <= 0.08061246201395988f) {
                                                    return 1;                                                } else {
                                                    return 2;                                                }
                                            }
                                        }
                                    }
                                }
                            } else {
                                if (features[13] <= -0.4218628853559494f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                } else {
                    if (features[14] <= -0.3198757469654083f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[27] <= 0.7735139727592468f) {
                    return 2;                } else {
                    if (features[25] <= 1.9365021735429764f) {
                        return 1;                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[22] <= 0.05709180235862732f) {
            if (features[6] <= -1.0038523077964783f) {
                return 0;            } else {
                return 2;            }
        } else {
            if (features[5] <= -0.03860252536833286f) {
                if (features[9] <= 0.5957176685333252f) {
                    return 1;                } else {
                    return 2;                }
            } else {
                if (features[21] <= 1.293749213218689f) {
                    if (features[5] <= 0.15744104981422424f) {
                        if (features[2] <= -0.45974425971508026f) {
                            return 2;                        } else {
                            return 2;                        }
                    } else {
                        if (features[24] <= 0.18327732384204865f) {
                            if (features[21] <= 0.06887472048401833f) {
                                return 0;                            } else {
                                return 2;                            }
                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[2] <= -0.0716000571846962f) {
                        if (features[23] <= 0.0893363282084465f) {
                            return 2;                        } else {
                            return 1;                        }
                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 17
int predict_tree_17(const float* features) {
    // Max depth: 20
    if (features[19] <= -0.005369451362639666f) {
        if (features[26] <= -0.3291703909635544f) {
            if (features[24] <= -0.06222830340266228f) {
                if (features[19] <= -0.3727397173643112f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                if (features[4] <= 1.3647371530532837f) {
                    if (features[4] <= 0.33843088150024414f) {
                        if (features[31] <= 0.1988118588924408f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[13] <= -0.46947531402111053f) {
                            if (features[17] <= -0.4778246730566025f) {
                                return 0;                            } else {
                                if (features[24] <= 0.10890467464923859f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[13] <= 0.04201808385550976f) {
                                if (features[25] <= 0.009574351832270622f) {
                                    return 0;                                } else {
                                    if (features[18] <= -0.39439401030540466f) {
                                        return 1;                                    } else {
                                        if (features[26] <= -0.33190956711769104f) {
                                            return 2;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            } else {
                                if (features[18] <= -0.5756338536739349f) {
                                    return 1;                                } else {
                                    if (features[0] <= -0.48681823909282684f) {
                                        return 0;                                    } else {
                                        return 2;                                    }
                                }
                            }
                        }
                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[10] <= -0.40957237780094147f) {
                if (features[20] <= 0.4645425081253052f) {
                    return 0;                } else {
                    if (features[7] <= 0.09693555533885956f) {
                        if (features[9] <= 0.9770218729972839f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[24] <= 0.14153756946325302f) {
                    if (features[5] <= 0.08918603509664536f) {
                        if (features[8] <= -0.2896888926625252f) {
                            return 2;                        } else {
                            if (features[23] <= -0.3882004916667938f) {
                                return 0;                            } else {
                                if (features[11] <= 0.1399955376982689f) {
                                    if (features[17] <= -0.4267341047525406f) {
                                        return 0;                                    } else {
                                        if (features[12] <= -0.09389263391494751f) {
                                            return 0;                                        } else {
                                            if (features[18] <= -0.3693135231733322f) {
                                                if (features[2] <= -0.06972042098641396f) {
                                                    if (features[11] <= 0.04547256417572498f) {
                                                        if (features[19] <= -0.3731579929590225f) {
                                                            if (features[25] <= -0.37664586305618286f) {
                                                                return 0;                                                            } else {
                                                                if (features[3] <= 0.559351235628128f) {
                                                                    if (features[21] <= 0.9205697178840637f) {
                                                                        if (features[5] <= -0.14098504558205605f) {
                                                                            if (features[12] <= 0.027830909937620163f) {
                                                                                return 0;                                                                            } else {
                                                                                return 1;                                                                            }
                                                                        } else {
                                                                            return 2;                                                                        }
                                                                    } else {
                                                                        if (features[22] <= 1.14452463388443f) {
                                                                            return 1;                                                                        } else {
                                                                            return 1;                                                                        }
                                                                    }
                                                                } else {
                                                                    if (features[8] <= -0.14287949353456497f) {
                                                                        return 0;                                                                    } else {
                                                                        if (features[10] <= -0.3852892518043518f) {
                                                                            return 0;                                                                        } else {
                                                                            if (features[29] <= -0.5067617737222463f) {
                                                                                return 1;                                                                            } else {
                                                                                if (features[17] <= -0.3950863629579544f) {
                                                                                    return 0;                                                                                } else {
                                                                                    return 0;                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        } else {
                                                            return 0;                                                        }
                                                    } else {
                                                        if (features[27] <= 0.17245277389883995f) {
                                                            return 2;                                                        } else {
                                                            return 2;                                                        }
                                                    }
                                                } else {
                                                    if (features[7] <= 0.3852735459804535f) {
                                                        if (features[0] <= -0.37119583785533905f) {
                                                            return 0;                                                        } else {
                                                            if (features[20] <= -0.6372917890548706f) {
                                                                return 1;                                                            } else {
                                                                return 1;                                                            }
                                                        }
                                                    } else {
                                                        if (features[6] <= 1.4301281571388245f) {
                                                            return 0;                                                        } else {
                                                            return 0;                                                        }
                                                    }
                                                }
                                            } else {
                                                if (features[1] <= -0.3525126725435257f) {
                                                    if (features[20] <= 0.4243316054344177f) {
                                                        return 0;                                                    } else {
                                                        return 1;                                                    }
                                                } else {
                                                    if (features[0] <= -0.3725171834230423f) {
                                                        return 0;                                                    } else {
                                                        return 1;                                                    }
                                                }
                                            }
                                        }
                                    }
                                } else {
                                    if (features[24] <= -0.1696133017539978f) {
                                        return 0;                                    } else {
                                        return 2;                                    }
                                }
                            }
                        }
                    } else {
                        if (features[19] <= -0.5012459605932236f) {
                            return 1;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[13] <= -2.6596463918685913f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[2] <= -0.9597266465425491f) {
            return 0;        } else {
            if (features[26] <= 5.780059814453125f) {
                if (features[23] <= -0.07224483042955399f) {
                    return 2;                } else {
                    return 2;                }
            } else {
                if (features[0] <= 0.4141012132167816f) {
                    return 1;                } else {
                    if (features[26] <= 5.986416339874268f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 18
int predict_tree_18(const float* features) {
    // Max depth: 15
    if (features[20] <= 0.12293420732021332f) {
        if (features[18] <= -0.4125281274318695f) {
            if (features[26] <= -0.03466833382844925f) {
                if (features[2] <= -3.377874493598938f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[17] <= -0.4117504805326462f) {
                    return 0;                } else {
                    return 1;                }
            }
        } else {
            if (features[4] <= -0.5628084540367126f) {
                if (features[8] <= -0.07050308585166931f) {
                    if (features[18] <= -0.38093554973602295f) {
                        if (features[22] <= -0.6256999671459198f) {
                            if (features[10] <= -0.39991115033626556f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            if (features[10] <= -0.35130898654460907f) {
                                if (features[22] <= -0.6253338754177094f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[2] <= -0.23888739198446274f) {
                            return 0;                        } else {
                            if (features[25] <= -0.36602291464805603f) {
                                if (features[19] <= -0.3522559255361557f) {
                                    if (features[17] <= -0.37257441878318787f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[27] <= -0.3847298324108124f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                return 0;                            }
                        }
                    }
                } else {
                    if (features[21] <= -0.7821768224239349f) {
                        return 0;                    } else {
                        return 0;                    }
                }
            } else {
                if (features[10] <= 1.057161808013916f) {
                    if (features[25] <= -0.06668327189981937f) {
                        return 0;                    } else {
                        if (features[10] <= 0.8633590340614319f) {
                            if (features[4] <= -0.029195698909461498f) {
                                return 0;                            } else {
                                return 2;                            }
                        } else {
                            if (features[12] <= 0.44991884380578995f) {
                                return 0;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[3] <= 1.310351848602295f) {
                        return 2;                    } else {
                        return 0;                    }
                }
            }
        }
    } else {
        if (features[10] <= -0.12924597039818764f) {
            if (features[7] <= 0.5380546003580093f) {
                if (features[1] <= -0.4797051250934601f) {
                    if (features[2] <= -0.20129472762346268f) {
                        if (features[2] <= -0.6336103081703186f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[9] <= 0.910124808549881f) {
                            if (features[26] <= -0.28668633103370667f) {
                                return 0;                            } else {
                                return 1;                            }
                        } else {
                            if (features[17] <= -0.5760741531848907f) {
                                return 1;                            } else {
                                if (features[26] <= -0.3330383151769638f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            }
                        }
                    }
                } else {
                    if (features[20] <= 1.4328323006629944f) {
                        if (features[8] <= -0.21741604059934616f) {
                            return 2;                        } else {
                            if (features[24] <= 0.09903891384601593f) {
                                if (features[13] <= -1.202706515789032f) {
                                    if (features[16] <= 2.4144846946001053f) {
                                        return 2;                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[24] <= 0.08613753691315651f) {
                                        if (features[14] <= 0.1514439806342125f) {
                                            if (features[19] <= -0.40014471113681793f) {
                                                return 1;                                            } else {
                                                if (features[17] <= -0.31714729964733124f) {
                                                    if (features[1] <= -0.35927872359752655f) {
                                                        if (features[21] <= 1.2295917868614197f) {
                                                            if (features[9] <= 2.4270668029785156f) {
                                                                return 2;                                                            } else {
                                                                return 1;                                                            }
                                                        } else {
                                                            return 1;                                                        }
                                                    } else {
                                                        return 1;                                                    }
                                                } else {
                                                    return 2;                                                }
                                            }
                                        } else {
                                            if (features[2] <= -0.4155728816986084f) {
                                                return 2;                                            } else {
                                                if (features[3] <= 0.4049324542284012f) {
                                                    return 1;                                                } else {
                                                    if (features[24] <= 0.07133889757096767f) {
                                                        return 1;                                                    } else {
                                                        if (features[13] <= -0.1987647172063589f) {
                                                            return 2;                                                        } else {
                                                            return 2;                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    } else {
                                        if (features[27] <= 0.04359753616154194f) {
                                            return 2;                                        } else {
                                            if (features[8] <= -0.12387661263346672f) {
                                                if (features[10] <= -0.3910863995552063f) {
                                                    return 1;                                                } else {
                                                    return 1;                                                }
                                            } else {
                                                return 2;                                            }
                                        }
                                    }
                                }
                            } else {
                                if (features[14] <= 0.011793687008321285f) {
                                    if (features[4] <= 1.3360105156898499f) {
                                        if (features[13] <= 0.2991251274943352f) {
                                            if (features[26] <= -0.3218380957841873f) {
                                                if (features[6] <= -1.3357587456703186f) {
                                                    return 2;                                                } else {
                                                    if (features[5] <= 0.09714912250638008f) {
                                                        return 1;                                                    } else {
                                                        if (features[27] <= -0.31000371277332306f) {
                                                            return 1;                                                        } else {
                                                            return 2;                                                        }
                                                    }
                                                }
                                            } else {
                                                return 2;                                            }
                                        } else {
                                            return 2;                                        }
                                    } else {
                                        return 2;                                    }
                                } else {
                                    return 2;                                }
                            }
                        }
                    } else {
                        if (features[7] <= -0.07405082695186138f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[13] <= -8.469721794128418f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[17] <= -0.2292896807193756f) {
                return 2;            } else {
                return 2;            }
        }
    }
}

// Tree 19
int predict_tree_19(const float* features) {
    // Max depth: 27
    if (features[10] <= -0.43039026856422424f) {
        if (features[7] <= 0.6708427965641022f) {
            if (features[27] <= 0.217019185423851f) {
                if (features[23] <= -0.5110931992530823f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[19] <= -0.572450190782547f) {
                    if (features[4] <= -0.04877781867980957f) {
                        return 0;                    } else {
                        if (features[22] <= 0.5942640602588654f) {
                            if (features[22] <= 0.45166489481925964f) {
                                if (features[14] <= -0.2325943261384964f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            } else {
                                if (features[24] <= 0.05881697125732899f) {
                                    if (features[23] <= 0.012338733300566673f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    return 1;                                }
                            }
                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[14] <= 8.355898678302765f) {
                        if (features[24] <= 1.8972632586956024f) {
                            return 0;                        } else {
                            return 2;                        }
                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[2] <= -0.12610940262675285f) {
                return 0;            } else {
                return 2;            }
        }
    } else {
        if (features[6] <= -0.1187685402110219f) {
            if (features[17] <= -0.27779386937618256f) {
                if (features[23] <= 0.09085352346301079f) {
                    if (features[24] <= 0.08651698753237724f) {
                        if (features[20] <= -0.6903222501277924f) {
                            return 0;                        } else {
                            if (features[27] <= -0.3846312314271927f) {
                                return 0;                            } else {
                                if (features[1] <= -0.40207213163375854f) {
                                    return 0;                                } else {
                                    if (features[22] <= -0.23982195556163788f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[22] <= 0.47601109743118286f) {
                        return 1;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[6] <= -1.0038523077964783f) {
                    if (features[4] <= 0.07518068887293339f) {
                        if (features[14] <= -0.44206976890563965f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[22] <= 0.02533191628754139f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[23] <= -0.03545287810266018f) {
                        if (features[26] <= 5.968938827514648f) {
                            return 2;                        } else {
                            return 1;                        }
                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[21] <= 1.368844747543335f) {
                if (features[3] <= -0.4033782333135605f) {
                    if (features[8] <= -0.24953154474496841f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    if (features[17] <= -0.4136670380830765f) {
                        if (features[24] <= -0.1085214838385582f) {
                            if (features[4] <= -0.7684206962585449f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 2;                        }
                    } else {
                        if (features[2] <= 0.6031881868839264f) {
                            if (features[0] <= -0.2191919907927513f) {
                                if (features[3] <= 0.6019358038902283f) {
                                    if (features[18] <= -0.3704439550638199f) {
                                        if (features[22] <= -0.6256999671459198f) {
                                            if (features[18] <= -0.37601713836193085f) {
                                                return 0;                                            } else {
                                                if (features[11] <= 4.59012808278203e-05f) {
                                                    if (features[22] <= -0.6381476521492004f) {
                                                        return 0;                                                    } else {
                                                        return 0;                                                    }
                                                } else {
                                                    return 1;                                                }
                                            }
                                        } else {
                                            if (features[14] <= 0.5180260092020035f) {
                                                if (features[13] <= 0.5045387148857117f) {
                                                    if (features[13] <= -0.6123125553131104f) {
                                                        return 2;                                                    } else {
                                                        if (features[4] <= 1.3398900032043457f) {
                                                            if (features[23] <= 0.1101977489888668f) {
                                                                if (features[22] <= -0.6197507381439209f) {
                                                                    if (features[3] <= 0.38702306151390076f) {
                                                                        return 1;                                                                    } else {
                                                                        return 0;                                                                    }
                                                                } else {
                                                                    if (features[1] <= -0.37776343524456024f) {
                                                                        return 0;                                                                    } else {
                                                                        if (features[7] <= -0.17508214712142944f) {
                                                                            return 2;                                                                        } else {
                                                                            if (features[21] <= -0.6238053143024445f) {
                                                                                return 0;                                                                            } else {
                                                                                if (features[4] <= 1.3070068359375f) {
                                                                                    if (features[27] <= -0.39113762974739075f) {
                                                                                        return 0;                                                                                    } else {
                                                                                        if (features[19] <= -0.4079612195491791f) {
                                                                                            if (features[30] <= 0.18403255939483643f) {
                                                                                                return 0;                                                                                            } else {
                                                                                                if (features[27] <= 0.1469567985041067f) {
                                                                                                    if (features[2] <= 0.34379883110523224f) {
                                                                                                        return 1;                                                                                                    } else {
                                                                                                        if (features[21] <= -0.44512033462524414f) {
                                                                                                            if (features[7] <= 0.20046459138393402f) {
                                                                                                                return 0;                                                                                                            } else {
                                                                                                                return 0;                                                                                                            }
                                                                                                        } else {
                                                                                                            return 1;                                                                                                        }
                                                                                                    }
                                                                                                } else {
                                                                                                    return 2;                                                                                                }
                                                                                            }
                                                                                        } else {
                                                                                            return 1;                                                                                        }
                                                                                    }
                                                                                } else {
                                                                                    if (features[8] <= -0.13328152149915695f) {
                                                                                        return 2;                                                                                    } else {
                                                                                        return 1;                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            } else {
                                                                if (features[0] <= -0.4040367156267166f) {
                                                                    return 2;                                                                } else {
                                                                    return 2;                                                                }
                                                            }
                                                        } else {
                                                            if (features[9] <= 2.362074851989746f) {
                                                                return 2;                                                            } else {
                                                                return 2;                                                            }
                                                        }
                                                    }
                                                } else {
                                                    if (features[23] <= 0.09085351973772049f) {
                                                        return 2;                                                    } else {
                                                        return 2;                                                    }
                                                }
                                            } else {
                                                if (features[17] <= -0.395545095205307f) {
                                                    return 2;                                                } else {
                                                    return 2;                                                }
                                            }
                                        }
                                    } else {
                                        if (features[19] <= 0.21494603902101517f) {
                                            if (features[18] <= -0.3693419247865677f) {
                                                if (features[22] <= -0.6334797739982605f) {
                                                    return 0;                                                } else {
                                                    return 1;                                                }
                                            } else {
                                                if (features[3] <= -0.37711112201213837f) {
                                                    return 0;                                                } else {
                                                    if (features[17] <= -0.37087294459342957f) {
                                                        if (features[23] <= -0.14127715677022934f) {
                                                            return 0;                                                        } else {
                                                            return 1;                                                        }
                                                    } else {
                                                        return 1;                                                    }
                                                }
                                            }
                                        } else {
                                            return 2;                                        }
                                    }
                                } else {
                                    if (features[13] <= -0.18108009546995163f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                }
                            } else {
                                if (features[29] <= -0.001376032829284668f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[11] <= -0.09894201532006264f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                if (features[20] <= 1.3309215903282166f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 20
int predict_tree_20(const float* features) {
    // Max depth: 8
    if (features[4] <= 0.12589098513126373f) {
        if (features[7] <= 0.3666609525680542f) {
            if (features[10] <= -0.35766860842704773f) {
                if (features[25] <= -0.5109503269195557f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[5] <= -0.33854539692401886f) {
                    if (features[21] <= -0.699911892414093f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[24] <= -0.1438105497509241f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[0] <= -0.3722134679555893f) {
                return 0;            } else {
                if (features[10] <= 0.3348657190799713f) {
                    return 1;                } else {
                    if (features[5] <= 0.08804845064878464f) {
                        return 0;                    } else {
                        return 0;                    }
                }
            }
        }
    } else {
        if (features[9] <= 2.1802068948745728f) {
            if (features[7] <= -0.3481309562921524f) {
                if (features[0] <= -0.21684617549180984f) {
                    if (features[17] <= -0.5546683073043823f) {
                        if (features[24] <= -0.061848850920796394f) {
                            return 0;                        } else {
                            if (features[5] <= 0.0482330247759819f) {
                                if (features[3] <= -0.7352989912033081f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[20] <= 0.5927378237247467f) {
                            return 1;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[12] <= -8.27011251449585f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[2] <= -0.17216041684150696f) {
                    if (features[22] <= 0.14623914659023285f) {
                        if (features[18] <= -0.5565829277038574f) {
                            return 1;                        } else {
                            if (features[14] <= 0.675132542848587f) {
                                return 2;                            } else {
                                if (features[25] <= -0.08110014349222183f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            }
                        }
                    } else {
                        if (features[4] <= 1.0148452818393707f) {
                            if (features[18] <= -0.45058178901672363f) {
                                return 0;                            } else {
                                return 2;                            }
                        } else {
                            if (features[12] <= 0.013547077309340239f) {
                                return 2;                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    if (features[1] <= -0.4843893498182297f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[2] <= 0.039298295974731445f) {
                if (features[24] <= 0.13053345680236816f) {
                    if (features[14] <= 0.2561816945672035f) {
                        if (features[5] <= 0.08918603509664536f) {
                            return 1;                        } else {
                            if (features[30] <= 0.18403255939483643f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[2] <= -0.3892580270767212f) {
                            if (features[31] <= 0.1988118588924408f) {
                                return 2;                            } else {
                                return 2;                            }
                        } else {
                            if (features[5] <= 0.09108200669288635f) {
                                return 1;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[2] <= -0.4644433557987213f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[14] <= -18.666433334350586f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 21
int predict_tree_21(const float* features) {
    // Max depth: 13
    if (features[0] <= -0.4480029344558716f) {
        if (features[23] <= 0.0017183751915581524f) {
            if (features[13] <= -4.902871340513229f) {
                return 0;            } else {
                return 0;            }
        } else {
            if (features[18] <= -0.5605116784572601f) {
                if (features[14] <= -0.42461346089839935f) {
                    return 0;                } else {
                    if (features[22] <= 0.5942640602588654f) {
                        if (features[20] <= 0.4645425081253052f) {
                            if (features[29] <= -0.001376032829284668f) {
                                return 0;                            } else {
                                return 1;                            }
                        } else {
                            return 1;                        }
                    } else {
                        return 0;                    }
                }
            } else {
                if (features[7] <= -2.2617589831352234f) {
                    return 0;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[20] <= 0.1462676003575325f) {
            if (features[24] <= -0.028457051143050194f) {
                if (features[25] <= -0.3880275934934616f) {
                    return 0;                } else {
                    if (features[17] <= -0.37257441878318787f) {
                        if (features[14] <= -0.12785660475492477f) {
                            if (features[6] <= -0.008133061230182648f) {
                                return 0;                            } else {
                                if (features[19] <= -0.4823193699121475f) {
                                    if (features[20] <= -0.4160395711660385f) {
                                        return 1;                                    } else {
                                        return 0;                                    }
                                } else {
                                    if (features[22] <= -0.6211236417293549f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                }
                            }
                        } else {
                            if (features[20] <= -0.652417004108429f) {
                                return 0;                            } else {
                                return 0;                            }
                        }
                    } else {
                        if (features[10] <= -0.35042904317379f) {
                            return 0;                        } else {
                            if (features[4] <= -0.5111744403839111f) {
                                return 1;                            } else {
                                if (features[22] <= -0.4127165377140045f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            }
                        }
                    }
                }
            } else {
                if (features[7] <= 0.9535867208614945f) {
                    return 2;                } else {
                    return 0;                }
            }
        } else {
            if (features[1] <= -0.06616747006773949f) {
                if (features[25] <= 0.1491902992129326f) {
                    if (features[4] <= 1.4354913234710693f) {
                        if (features[0] <= -0.22930758446455002f) {
                            if (features[24] <= 0.0975211039185524f) {
                                if (features[14] <= 0.32600684463977814f) {
                                    if (features[8] <= -0.18508217483758926f) {
                                        return 2;                                    } else {
                                        if (features[4] <= 1.1650364398956299f) {
                                            if (features[20] <= 0.4599311500787735f) {
                                                return 1;                                            } else {
                                                return 2;                                            }
                                        } else {
                                            if (features[9] <= 2.389039397239685f) {
                                                if (features[23] <= 0.09919809177517891f) {
                                                    return 1;                                                } else {
                                                    return 2;                                                }
                                            } else {
                                                if (features[11] <= 0.010363033507019281f) {
                                                    return 1;                                                } else {
                                                    if (features[0] <= -0.4186195731163025f) {
                                                        return 2;                                                    } else {
                                                        return 1;                                                    }
                                                }
                                            }
                                        }
                                    }
                                } else {
                                    if (features[25] <= 0.06913876533508301f) {
                                        if (features[11] <= 0.010579001624137163f) {
                                            if (features[9] <= 1.9709506034851074f) {
                                                return 2;                                            } else {
                                                return 1;                                            }
                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 2;                                    }
                                }
                            } else {
                                if (features[25] <= 0.12870318442583084f) {
                                    return 2;                                } else {
                                    if (features[8] <= -0.05115953087806702f) {
                                        if (features[0] <= -0.4030204713344574f) {
                                            return 2;                                        } else {
                                            if (features[28] <= 0.034745603799819946f) {
                                                if (features[27] <= 0.09357978217303753f) {
                                                    return 1;                                                } else {
                                                    return 2;                                                }
                                            } else {
                                                return 1;                                            }
                                        }
                                    } else {
                                        return 2;                                    }
                                }
                            }
                        } else {
                            if (features[4] <= 0.21973736584186554f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[23] <= 0.09578440338373184f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[16] <= 2.4144846946001053f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[31] <= 0.1988118588924408f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 22
int predict_tree_22(const float* features) {
    // Max depth: 10
    if (features[4] <= 0.12589098513126373f) {
        if (features[18] <= -0.3925958275794983f) {
            if (features[1] <= -0.35566432774066925f) {
                if (features[31] <= 0.1988118588924408f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[15] <= 0.7553892731666565f) {
                    return 0;                } else {
                    if (features[21] <= -0.40118442475795746f) {
                        return 1;                    } else {
                        if (features[7] <= -0.4035583883523941f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                }
            }
        } else {
            if (features[5] <= -0.3669849932193756f) {
                if (features[0] <= -0.37160593271255493f) {
                    return 0;                } else {
                    if (features[17] <= -0.37374623119831085f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[0] <= 0.8649576306343079f) {
                    if (features[19] <= -0.16646526916883886f) {
                        return 0;                    } else {
                        if (features[3] <= 1.7759960740804672f) {
                            return 2;                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[9] <= -0.31470365822315216f) {
                        return 2;                    } else {
                        if (features[7] <= 0.8725173324346542f) {
                            return 2;                        } else {
                            return 0;                        }
                    }
                }
            }
        }
    } else {
        if (features[1] <= -0.2397419586777687f) {
            if (features[7] <= 0.22139890491962433f) {
                if (features[18] <= -0.5099711418151855f) {
                    if (features[33] <= -0.785379022359848f) {
                        if (features[7] <= -0.7073032855987549f) {
                            return 1;                        } else {
                            if (features[31] <= 0.1988118588924408f) {
                                return 0;                            } else {
                                return 0;                            }
                        }
                    } else {
                        if (features[10] <= -0.5632756948471069f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[4] <= 1.453318476676941f) {
                        if (features[13] <= 0.5140611976385117f) {
                            if (features[5] <= 0.08918603509664536f) {
                                if (features[15] <= 0.7553892731666565f) {
                                    if (features[13] <= -0.2722238600254059f) {
                                        if (features[20] <= 0.9362829029560089f) {
                                            return 2;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[13] <= -0.00015291385352611542f) {
                                        return 2;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                if (features[22] <= 0.7728332877159119f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[11] <= -0.20292006572708488f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[30] <= 0.18403255939483643f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[7] <= 0.23025066405534744f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[14] <= -5.783693313598633f) {
                return 2;            } else {
                return 2;            }
        }
    }
}

// Tree 23
int predict_tree_23(const float* features) {
    // Max depth: 10
    if (features[21] <= 0.1186932697892189f) {
        if (features[1] <= -0.3559093028306961f) {
            if (features[30] <= 0.18403255939483643f) {
                return 0;            } else {
                return 0;            }
        } else {
            if (features[4] <= -0.4263801872730255f) {
                if (features[0] <= -0.37176869809627533f) {
                    return 0;                } else {
                    if (features[11] <= -0.10089294984936714f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[3] <= 1.7242578566074371f) {
                    if (features[0] <= -0.20297699607908726f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    return 0;                }
            }
        }
    } else {
        if (features[22] <= 1.144616186618805f) {
            if (features[17] <= -0.2722918689250946f) {
                if (features[5] <= -0.07197164371609688f) {
                    return 0;                } else {
                    if (features[1] <= -0.5211361944675446f) {
                        if (features[27] <= 0.3653261959552765f) {
                            return 0;                        } else {
                            if (features[19] <= -0.5797303020954132f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[22] <= 0.532666340470314f) {
                            if (features[11] <= 0.5960404574871063f) {
                                if (features[24] <= 0.0018991308752447367f) {
                                    return 1;                                } else {
                                    if (features[13] <= -0.6748888644506223f) {
                                        if (features[12] <= -0.0011612698435783386f) {
                                            return 0;                                        } else {
                                            return 2;                                        }
                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                return 2;                            }
                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[27] <= -0.39540718495845795f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[9] <= 2.1642128229141235f) {
                return 2;            } else {
                if (features[20] <= 1.4329245686531067f) {
                    if (features[24] <= 0.0212511969730258f) {
                        return 2;                    } else {
                        if (features[13] <= 0.5861599743366241f) {
                            if (features[5] <= 0.0895652286708355f) {
                                return 1;                            } else {
                                if (features[26] <= -0.33362625539302826f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[12] <= -0.009808970149606466f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[7] <= -0.05452451668679714f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 24
int predict_tree_24(const float* features) {
    // Max depth: 16
    if (features[0] <= -0.4439397156238556f) {
        if (features[5] <= 0.006900819425936788f) {
            if (features[21] <= -0.8334660530090332f) {
                return 0;            } else {
                return 0;            }
        } else {
            if (features[7] <= 0.5429976731538773f) {
                if (features[14] <= 9.56038236618042f) {
                    if (features[23] <= -0.012315669097006321f) {
                        return 0;                    } else {
                        if (features[19] <= -0.5810368359088898f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                } else {
                    return 2;                }
            } else {
                return 2;            }
        }
    } else {
        if (features[8] <= -0.23893751949071884f) {
            return 2;        } else {
            if (features[3] <= -0.39303058385849f) {
                if (features[21] <= 0.2062893509864807f) {
                    if (features[5] <= -0.0029582390561699867f) {
                        if (features[9] <= 0.44226162135601044f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[5] <= -0.03860252536833286f) {
                        if (features[10] <= 0.18488836288452148f) {
                            return 1;                        } else {
                            return 2;                        }
                    } else {
                        if (features[4] <= 0.14889074116945267f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[24] <= 0.11118138581514359f) {
                    if (features[2] <= -0.6401890367269516f) {
                        return 0;                    } else {
                        if (features[19] <= 0.1608811542391777f) {
                            if (features[17] <= -0.4262520670890808f) {
                                if (features[21] <= -0.08839379996061325f) {
                                    if (features[12] <= -0.05897829495370388f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                if (features[5] <= 0.0895652286708355f) {
                                    if (features[20] <= -0.6448543965816498f) {
                                        return 0;                                    } else {
                                        if (features[9] <= -0.7655880153179169f) {
                                            return 0;                                        } else {
                                            if (features[10] <= -0.22102189809083939f) {
                                                if (features[25] <= -0.38840697705745697f) {
                                                    return 0;                                                } else {
                                                    if (features[0] <= -0.4264049082994461f) {
                                                        return 0;                                                    } else {
                                                        if (features[22] <= 0.995335578918457f) {
                                                            if (features[10] <= -0.35147352516651154f) {
                                                                if (features[2] <= -0.23888739198446274f) {
                                                                    return 0;                                                                } else {
                                                                    return 0;                                                                }
                                                            } else {
                                                                if (features[6] <= -0.8932168707251549f) {
                                                                    return 2;                                                                } else {
                                                                    return 1;                                                                }
                                                            }
                                                        } else {
                                                            return 1;                                                        }
                                                    }
                                                }
                                            } else {
                                                if (features[13] <= -0.03960320074111223f) {
                                                    return 2;                                                } else {
                                                    return 2;                                                }
                                            }
                                        }
                                    }
                                } else {
                                    if (features[33] <= -0.785379022359848f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                }
                            }
                        } else {
                            if (features[25] <= 0.04941042419523001f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[4] <= 0.23303842544555664f) {
                        return 0;                    } else {
                        if (features[23] <= 0.1101977489888668f) {
                            if (features[12] <= 0.0008397124474868178f) {
                                if (features[4] <= 1.329544723033905f) {
                                    return 1;                                } else {
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

// Tree 25
int predict_tree_25(const float* features) {
    // Max depth: 10
    if (features[1] <= -0.4180285185575485f) {
        if (features[5] <= 0.0482330247759819f) {
            if (features[33] <= -0.785379022359848f) {
                return 0;            } else {
                return 0;            }
        } else {
            if (features[5] <= 1.2836488485336304f) {
                return 1;            } else {
                return 2;            }
        }
    } else {
        if (features[10] <= -0.1329411305487156f) {
            if (features[5] <= 0.0895652286708355f) {
                if (features[20] <= -0.6448543965816498f) {
                    return 0;                } else {
                    if (features[25] <= -0.07578866183757782f) {
                        if (features[19] <= -0.3902593106031418f) {
                            if (features[31] <= 0.1988118588924408f) {
                                if (features[30] <= 0.18403255939483643f) {
                                    return 0;                                } else {
                                    if (features[0] <= -0.37212298810482025f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                return 0;                            }
                        } else {
                            if (features[17] <= -0.37257441878318787f) {
                                return 0;                            } else {
                                if (features[8] <= 0.15155236050486565f) {
                                    if (features[0] <= -0.38013291358947754f) {
                                        return 0;                                    } else {
                                        if (features[22] <= -0.6410765051841736f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    return 0;                                }
                            }
                        }
                    } else {
                        if (features[11] <= 0.28968900442123413f) {
                            if (features[0] <= -0.3477412164211273f) {
                                return 1;                            } else {
                                if (features[22] <= 0.5207678228616714f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[15] <= 0.7553892731666565f) {
                    return 2;                } else {
                    if (features[17] <= -0.4719148278236389f) {
                        return 1;                    } else {
                        if (features[33] <= -0.785379022359848f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[2] <= -0.9597266465425491f) {
                return 0;            } else {
                if (features[28] <= -0.4680557791143656f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 26
int predict_tree_26(const float* features) {
    // Max depth: 23
    if (features[18] <= -0.45749323070049286f) {
        if (features[5] <= 0.046716244891285896f) {
            if (features[11] <= 0.17448845505714417f) {
                if (features[12] <= -0.09654275327920914f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[27] <= -0.2773439586162567f) {
                    if (features[12] <= 0.16616404056549072f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    return 1;                }
            }
        } else {
            if (features[10] <= -0.49024684727191925f) {
                return 1;            } else {
                return 2;            }
        }
    } else {
        if (features[10] <= -0.22607501596212387f) {
            if (features[7] <= 0.6655865013599396f) {
                if (features[17] <= -0.42613160610198975f) {
                    return 0;                } else {
                    if (features[21] <= 1.4266599416732788f) {
                        if (features[23] <= 0.1105770468711853f) {
                            if (features[0] <= -0.42640189826488495f) {
                                return 0;                            } else {
                                if (features[21] <= -0.644302636384964f) {
                                    return 0;                                } else {
                                    if (features[3] <= 0.6027317941188812f) {
                                        if (features[20] <= -0.6464222371578217f) {
                                            return 0;                                        } else {
                                            if (features[13] <= 0.824222058057785f) {
                                                if (features[6] <= 0.5450443178415298f) {
                                                    if (features[0] <= -0.3148026764392853f) {
                                                        if (features[23] <= 0.09730159863829613f) {
                                                            if (features[12] <= 0.005007771076634526f) {
                                                                if (features[4] <= -0.5894105732440948f) {
                                                                    return 0;                                                                } else {
                                                                    if (features[19] <= -0.4316776394844055f) {
                                                                        return 0;                                                                    } else {
                                                                        if (features[8] <= -0.048684513196349144f) {
                                                                            if (features[5] <= 0.09146120399236679f) {
                                                                                if (features[2] <= 0.8512997329235077f) {
                                                                                    if (features[19] <= -0.3136308491230011f) {
                                                                                        if (features[12] <= -0.06858630292117596f) {
                                                                                            if (features[4] <= -0.5666879117488861f) {
                                                                                                return 1;                                                                                            } else {
                                                                                                return 0;                                                                                            }
                                                                                        } else {
                                                                                            if (features[18] <= -0.4259587526321411f) {
                                                                                                return 1;                                                                                            } else {
                                                                                                return 1;                                                                                            }
                                                                                        }
                                                                                    } else {
                                                                                        return 0;                                                                                    }
                                                                                } else {
                                                                                    if (features[4] <= 0.1340194158256054f) {
                                                                                        if (features[4] <= 0.060678837820887566f) {
                                                                                            return 0;                                                                                        } else {
                                                                                            return 0;                                                                                        }
                                                                                    } else {
                                                                                        return 1;                                                                                    }
                                                                                }
                                                                            } else {
                                                                                return 2;                                                                            }
                                                                        } else {
                                                                            return 2;                                                                        }
                                                                    }
                                                                }
                                                            } else {
                                                                if (features[20] <= 1.3556383848190308f) {
                                                                    if (features[13] <= -1.051707148551941f) {
                                                                        return 2;                                                                    } else {
                                                                        if (features[10] <= -0.40345682203769684f) {
                                                                            return 0;                                                                        } else {
                                                                            if (features[27] <= 0.012507857638411224f) {
                                                                                if (features[7] <= 0.14374062418937683f) {
                                                                                    if (features[14] <= 0.08161883428692818f) {
                                                                                        return 1;                                                                                    } else {
                                                                                        if (features[24] <= -0.06526392046362162f) {
                                                                                            return 0;                                                                                        } else {
                                                                                            return 1;                                                                                        }
                                                                                    }
                                                                                } else {
                                                                                    return 2;                                                                                }
                                                                            } else {
                                                                                if (features[13] <= -0.11850377917289734f) {
                                                                                    if (features[23] <= 0.06581982411444187f) {
                                                                                        return 1;                                                                                    } else {
                                                                                        return 2;                                                                                    }
                                                                                } else {
                                                                                    return 2;                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                } else {
                                                                    return 2;                                                                }
                                                            }
                                                        } else {
                                                            if (features[1] <= -0.3578486144542694f) {
                                                                return 2;                                                            } else {
                                                                if (features[27] <= -0.03006720170378685f) {
                                                                    return 1;                                                                } else {
                                                                    return 2;                                                                }
                                                            }
                                                        }
                                                    } else {
                                                        if (features[2] <= -0.3695218861103058f) {
                                                            return 2;                                                        } else {
                                                            return 2;                                                        }
                                                    }
                                                } else {
                                                    if (features[10] <= -0.3509949892759323f) {
                                                        if (features[25] <= -0.391442134976387f) {
                                                            return 0;                                                        } else {
                                                            return 0;                                                        }
                                                    } else {
                                                        if (features[7] <= 0.3229679763317108f) {
                                                            return 0;                                                        } else {
                                                            return 1;                                                        }
                                                    }
                                                }
                                            } else {
                                                return 2;                                            }
                                        }
                                    } else {
                                        if (features[26] <= -0.26875801384449005f) {
                                            return 2;                                        } else {
                                            return 2;                                        }
                                    }
                                }
                            }
                        } else {
                            if (features[0] <= -0.40582823753356934f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[20] <= 1.3891167640686035f) {
                            return 1;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[6] <= -1.888936161994934f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[4] <= 0.058369625359773636f) {
                if (features[7] <= 0.9053584411740303f) {
                    return 2;                } else {
                    return 0;                }
            } else {
                if (features[2] <= -0.9691248089075089f) {
                    return 0;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 27
int predict_tree_27(const float* features) {
    // Max depth: 10
    if (features[5] <= -0.07197164371609688f) {
        if (features[26] <= -0.3087146133184433f) {
            if (features[20] <= -0.6293602883815765f) {
                if (features[0] <= -0.3714727461338043f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                if (features[24] <= -0.4022175520658493f) {
                    return 0;                } else {
                    return 0;                }
            }
        } else {
            if (features[0] <= -0.37172622978687286f) {
                if (features[20] <= -0.8060669302940369f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[33] <= -0.785379022359848f) {
                    return 2;                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[0] <= -0.3121277540922165f) {
            if (features[5] <= 0.09752831235527992f) {
                if (features[17] <= -0.5626189708709717f) {
                    if (features[27] <= 0.24733170121908188f) {
                        if (features[18] <= -0.583344966173172f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[13] <= -0.4354664385318756f) {
                            return 0;                        } else {
                            if (features[1] <= -0.5363328754901886f) {
                                if (features[19] <= -0.5808270573616028f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            } else {
                                if (features[27] <= 0.34836821258068085f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            }
                        }
                    }
                } else {
                    if (features[23] <= 0.09654299914836884f) {
                        if (features[17] <= -0.28962014615535736f) {
                            if (features[12] <= 0.027299650013446808f) {
                                if (features[24] <= 0.0986594632267952f) {
                                    if (features[5] <= 0.0895652286708355f) {
                                        return 1;                                    } else {
                                        if (features[10] <= -0.37598006427288055f) {
                                            return 2;                                        } else {
                                            return 2;                                        }
                                    }
                                } else {
                                    if (features[20] <= 1.1722914576530457f) {
                                        return 2;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                if (features[22] <= 0.5730297714471817f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            return 2;                        }
                    } else {
                        if (features[20] <= 0.48999714106321335f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[20] <= 0.49654521048069f) {
                    return 1;                } else {
                    return 2;                }
            }
        } else {
            if (features[6] <= -1.0038523077964783f) {
                if (features[18] <= 1.0408876538276672f) {
                    if (features[20] <= 0.00257815420627594f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    if (features[7] <= 1.249806523323059f) {
                        return 2;                    } else {
                        return 0;                    }
                }
            } else {
                return 2;            }
        }
    }
}

// Tree 28
int predict_tree_28(const float* features) {
    // Max depth: 18
    if (features[5] <= -0.07197164371609688f) {
        if (features[17] <= -0.408745139837265f) {
            if (features[20] <= -0.8359484374523163f) {
                return 0;            } else {
                return 0;            }
        } else {
            if (features[0] <= -0.37172622978687286f) {
                if (features[2] <= -1.112916737794876f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[24] <= -0.17378727719187737f) {
                    return 1;                } else {
                    if (features[18] <= 1.4629683792591095f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[8] <= -0.21919294446706772f) {
            if (features[3] <= 1.8993719220161438f) {
                if (features[25] <= -0.05264580249786377f) {
                    return 0;                } else {
                    if (features[0] <= -0.5379078388214111f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            } else {
                return 0;            }
        } else {
            if (features[0] <= -0.22781988978385925f) {
                if (features[7] <= 0.5648484379053116f) {
                    if (features[23] <= 0.1101977489888668f) {
                        if (features[23] <= 0.09730159863829613f) {
                            if (features[1] <= -0.536533772945404f) {
                                if (features[4] <= 0.5089430809020996f) {
                                    if (features[29] <= -0.5067617737222463f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                if (features[20] <= 1.4409483075141907f) {
                                    if (features[24] <= -0.07475022971630096f) {
                                        return 0;                                    } else {
                                        if (features[6] <= -1.888936161994934f) {
                                            return 0;                                        } else {
                                            if (features[18] <= -0.5816126465797424f) {
                                                return 0;                                            } else {
                                                if (features[5] <= 0.09714911878108978f) {
                                                    if (features[0] <= -0.5783555209636688f) {
                                                        return 0;                                                    } else {
                                                        if (features[1] <= -0.5138073563575745f) {
                                                            if (features[26] <= -0.3254842311143875f) {
                                                                return 0;                                                            } else {
                                                                return 1;                                                            }
                                                        } else {
                                                            if (features[10] <= -0.2854164242744446f) {
                                                                if (features[3] <= 0.6071096360683441f) {
                                                                    if (features[27] <= 0.6567611992359161f) {
                                                                        return 1;                                                                    } else {
                                                                        if (features[3] <= -0.36954934895038605f) {
                                                                            return 1;                                                                        } else {
                                                                            return 2;                                                                        }
                                                                    }
                                                                } else {
                                                                    if (features[12] <= 0.027820606715977192f) {
                                                                        return 1;                                                                    } else {
                                                                        return 2;                                                                    }
                                                                }
                                                            } else {
                                                                if (features[13] <= 0.6609794795513153f) {
                                                                    return 2;                                                                } else {
                                                                    return 1;                                                                }
                                                            }
                                                        }
                                                    }
                                                } else {
                                                    if (features[9] <= 1.0000929832458496f) {
                                                        return 1;                                                    } else {
                                                        if (features[26] <= -0.32076095044612885f) {
                                                            return 2;                                                        } else {
                                                            return 2;                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                } else {
                                    if (features[14] <= 0.39583198726177216f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                }
                            }
                        } else {
                            if (features[14] <= -0.895933210849762f) {
                                return 1;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[4] <= 0.771731436252594f) {
                            return 1;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[34] <= -2.074661783874035f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[4] <= 0.07259437255561352f) {
                    return 0;                } else {
                    if (features[13] <= 3.671444535255432f) {
                        return 2;                    } else {
                        if (features[7] <= 1.9730498790740967f) {
                            return 2;                        } else {
                            if (features[23] <= 0.08023316599428654f) {
                                return 2;                            } else {
                                return 0;                            }
                        }
                    }
                }
            }
        }
    }
}

// Tree 29
int predict_tree_29(const float* features) {
    // Max depth: 14
    if (features[17] <= -0.44520868360996246f) {
        if (features[4] <= 0.29326267540454865f) {
            if (features[8] <= -0.7120418548583984f) {
                return 0;            } else {
                return 0;            }
        } else {
            if (features[2] <= 0.09944654628634453f) {
                if (features[21] <= 1.717942237854004f) {
                    if (features[24] <= -0.10814202949404716f) {
                        return 0;                    } else {
                        if (features[22] <= 0.5942640602588654f) {
                            if (features[7] <= -0.48416395485401154f) {
                                if (features[30] <= 0.18403255939483643f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            } else {
                                if (features[25] <= 0.022853041999042034f) {
                                    return 1;                                } else {
                                    return 0;                                }
                            }
                        } else {
                            return 0;                        }
                    }
                } else {
                    return 2;                }
            } else {
                if (features[5] <= 1.142967672785744f) {
                    return 0;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[8] <= -0.2378905713558197f) {
            if (features[6] <= 0.7663152767345309f) {
                return 2;            } else {
                return 0;            }
        } else {
            if (features[0] <= -0.23168553411960602f) {
                if (features[4] <= 1.453318476676941f) {
                    if (features[5] <= 0.08918603509664536f) {
                        if (features[25] <= -0.3872688114643097f) {
                            return 0;                        } else {
                            if (features[10] <= -0.4102548360824585f) {
                                return 0;                            } else {
                                if (features[17] <= -0.4271029829978943f) {
                                    return 0;                                } else {
                                    if (features[17] <= -0.37086400389671326f) {
                                        if (features[24] <= -0.2952120155096054f) {
                                            if (features[13] <= -0.032801428809762f) {
                                                if (features[0] <= -0.3712332993745804f) {
                                                    return 0;                                                } else {
                                                    return 1;                                                }
                                            } else {
                                                return 0;                                            }
                                        } else {
                                            if (features[17] <= -0.37661758065223694f) {
                                                if (features[5] <= -0.06438775546848774f) {
                                                    if (features[31] <= 0.1988118588924408f) {
                                                        return 1;                                                    } else {
                                                        return 0;                                                    }
                                                } else {
                                                    if (features[17] <= -0.3809918165206909f) {
                                                        return 1;                                                    } else {
                                                        if (features[9] <= 2.5400413274765015f) {
                                                            return 2;                                                        } else {
                                                            return 1;                                                        }
                                                    }
                                                }
                                            } else {
                                                if (features[12] <= 0.021461153402924538f) {
                                                    return 2;                                                } else {
                                                    return 2;                                                }
                                            }
                                        }
                                    } else {
                                        if (features[23] <= 0.02030400186777115f) {
                                            if (features[0] <= -0.37300267815589905f) {
                                                return 0;                                            } else {
                                                if (features[24] <= -0.3881778120994568f) {
                                                    return 1;                                                } else {
                                                    return 1;                                                }
                                            }
                                        } else {
                                            if (features[9] <= 1.8497751355171204f) {
                                                return 2;                                            } else {
                                                return 1;                                            }
                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        if (features[31] <= 0.1988118588924408f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[22] <= 1.0423804819583893f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[22] <= 0.05974608659744263f) {
                    if (features[4] <= 0.20994631201028824f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    if (features[2] <= -0.9672451764345169f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 30
int predict_tree_30(const float* features) {
    // Max depth: 21
    if (features[1] <= -0.4178345948457718f) {
        if (features[4] <= 0.22343210875988007f) {
            if (features[21] <= -0.8337417840957642f) {
                return 0;            } else {
                return 0;            }
        } else {
            if (features[20] <= 0.6245560944080353f) {
                if (features[31] <= 0.1988118588924408f) {
                    if (features[10] <= -0.5135950893163681f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[27] <= 0.19657112658023834f) {
                        return 0;                    } else {
                        if (features[21] <= 0.0174935981631279f) {
                            return 0;                        } else {
                            if (features[30] <= 0.18403255939483643f) {
                                if (features[2] <= 0.06185389310121536f) {
                                    return 1;                                } else {
                                    if (features[4] <= 0.44059041142463684f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                }
                            } else {
                                return 1;                            }
                        }
                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[18] <= -0.14465460181236267f) {
            if (features[4] <= 1.453318476676941f) {
                if (features[4] <= -0.6457553505897522f) {
                    return 0;                } else {
                    if (features[17] <= -0.4262520670890808f) {
                        if (features[25] <= -0.08906735200434923f) {
                            if (features[17] <= -0.5106883943080902f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            if (features[11] <= 0.3180505819618702f) {
                                return 2;                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[25] <= 0.14843151718378067f) {
                            if (features[5] <= 0.0895652286708355f) {
                                if (features[0] <= -0.42671744525432587f) {
                                    return 0;                                } else {
                                    if (features[11] <= 0.22770800441503525f) {
                                        if (features[1] <= -0.07225370407104492f) {
                                            if (features[12] <= -0.16476405411958694f) {
                                                return 0;                                            } else {
                                                if (features[25] <= -0.38840697705745697f) {
                                                    return 0;                                                } else {
                                                    if (features[4] <= -0.44060492515563965f) {
                                                        if (features[20] <= -0.563418060541153f) {
                                                            if (features[2] <= -0.23888739198446274f) {
                                                                return 0;                                                            } else {
                                                                if (features[24] <= -0.3654106706380844f) {
                                                                    if (features[17] <= -0.3752165585756302f) {
                                                                        if (features[26] <= -0.1306365360505879f) {
                                                                            if (features[24] <= -0.3859011083841324f) {
                                                                                return 0;                                                                            } else {
                                                                                return 0;                                                                            }
                                                                        } else {
                                                                            return 1;                                                                        }
                                                                    } else {
                                                                        if (features[17] <= -0.37257441878318787f) {
                                                                            if (features[24] <= -0.377932608127594f) {
                                                                                return 1;                                                                            } else {
                                                                                if (features[19] <= -0.36991944909095764f) {
                                                                                    return 0;                                                                                } else {
                                                                                    return 0;                                                                                }
                                                                            }
                                                                        } else {
                                                                            if (features[5] <= -0.3700185567140579f) {
                                                                                return 1;                                                                            } else {
                                                                                if (features[21] <= -0.6223346590995789f) {
                                                                                    if (features[4] <= -0.6254342794418335f) {
                                                                                        return 0;                                                                                    } else {
                                                                                        return 1;                                                                                    }
                                                                                } else {
                                                                                    return 1;                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                } else {
                                                                    if (features[11] <= 0.007604178186738864f) {
                                                                        return 0;                                                                    } else {
                                                                        return 0;                                                                    }
                                                                }
                                                            }
                                                        } else {
                                                            if (features[3] <= -0.3373124599456787f) {
                                                                return 0;                                                            } else {
                                                                return 0;                                                            }
                                                        }
                                                    } else {
                                                        if (features[11] <= 0.03742038831114769f) {
                                                            if (features[9] <= 0.43817469477653503f) {
                                                                return 0;                                                            } else {
                                                                return 1;                                                            }
                                                        } else {
                                                            if (features[11] <= 0.111064862459898f) {
                                                                return 2;                                                            } else {
                                                                return 1;                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        } else {
                                            return 2;                                        }
                                    } else {
                                        if (features[1] <= -0.23057213425636292f) {
                                            return 2;                                        } else {
                                            return 2;                                        }
                                    }
                                }
                            } else {
                                if (features[15] <= 0.7553892731666565f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[21] <= 1.04851695895195f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                if (features[20] <= 1.4324633479118347f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[2] <= -0.9691248089075089f) {
                return 0;            } else {
                if (features[3] <= -1.3840170502662659f) {
                    if (features[1] <= -0.08918992429971695f) {
                        return 1;                    } else {
                        return 2;                    }
                } else {
                    if (features[29] <= -0.5067617737222463f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 31
int predict_tree_31(const float* features) {
    // Max depth: 15
    if (features[1] <= -0.4180285185575485f) {
        if (features[6] <= -1.888936161994934f) {
            if (features[23] <= 0.9328961968421936f) {
                if (features[5] <= 0.0448202732950449f) {
                    return 0;                } else {
                    if (features[5] <= 0.053162552416324615f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            } else {
                return 2;            }
        } else {
            if (features[13] <= 0.9112847745418549f) {
                if (features[24] <= 2.265331953763962f) {
                    return 0;                } else {
                    if (features[27] <= -0.25795599818229675f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[6] <= 0.766315259039402f) {
                    if (features[13] <= 1.3860486149787903f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[6] <= -0.1187685402110219f) {
            if (features[3] <= 0.31140561401844025f) {
                if (features[5] <= -0.05377030558884144f) {
                    if (features[18] <= 0.19093583524227142f) {
                        if (features[24] <= -0.2178037352859974f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[23] <= -0.03545287810266018f) {
                        if (features[1] <= 0.1352842152118683f) {
                            return 1;                        } else {
                            return 2;                        }
                    } else {
                        if (features[25] <= -0.07427109777927399f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[23] <= 0.08630194142460823f) {
                    if (features[0] <= -0.3559301495552063f) {
                        if (features[10] <= -0.41514594852924347f) {
                            return 0;                        } else {
                            if (features[20] <= 0.2542652487754822f) {
                                if (features[13] <= 0.014810987282544374f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            } else {
                                return 1;                            }
                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[20] <= 0.21599110588431358f) {
                        if (features[18] <= 0.7188884764909744f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[1] <= -0.05353866331279278f) {
                if (features[10] <= -0.3970406651496887f) {
                    return 0;                } else {
                    if (features[20] <= 1.4348613023757935f) {
                        if (features[24] <= 0.11118138581514359f) {
                            if (features[3] <= -0.4049701690673828f) {
                                return 0;                            } else {
                                if (features[26] <= 0.6070203334093094f) {
                                    if (features[17] <= -0.40435223281383514f) {
                                        if (features[9] <= -0.671222984790802f) {
                                            if (features[26] <= -0.33244165778160095f) {
                                                return 0;                                            } else {
                                                return 0;                                            }
                                        } else {
                                            if (features[23] <= 0.08630194142460823f) {
                                                if (features[2] <= 0.34379883110523224f) {
                                                    if (features[17] <= -0.41989243030548096f) {
                                                        return 0;                                                    } else {
                                                        if (features[7] <= 0.07194436714053154f) {
                                                            return 1;                                                        } else {
                                                            return 0;                                                        }
                                                    }
                                                } else {
                                                    if (features[14] <= -0.11040031537413597f) {
                                                        return 0;                                                    } else {
                                                        return 0;                                                    }
                                                }
                                            } else {
                                                return 2;                                            }
                                        }
                                    } else {
                                        if (features[5] <= 0.08918603509664536f) {
                                            if (features[10] <= -0.35121169686317444f) {
                                                if (features[7] <= 0.27379097044467926f) {
                                                    if (features[6] <= 0.5450443178415298f) {
                                                        if (features[24] <= -0.15860918909311295f) {
                                                            if (features[1] <= -0.3487219661474228f) {
                                                                return 0;                                                            } else {
                                                                return 1;                                                            }
                                                        } else {
                                                            return 1;                                                        }
                                                    } else {
                                                        if (features[20] <= -0.5186880826950073f) {
                                                            return 0;                                                        } else {
                                                            return 0;                                                        }
                                                    }
                                                } else {
                                                    if (features[11] <= -0.024283881299197674f) {
                                                        return 0;                                                    } else {
                                                        return 0;                                                    }
                                                }
                                            } else {
                                                if (features[9] <= -0.5033128261566162f) {
                                                    return 1;                                                } else {
                                                    if (features[10] <= -0.27048853039741516f) {
                                                        return 0;                                                    } else {
                                                        return 1;                                                    }
                                                }
                                            }
                                        } else {
                                            if (features[11] <= -0.014605028089135885f) {
                                                return 2;                                            } else {
                                                return 2;                                            }
                                        }
                                    }
                                } else {
                                    if (features[24] <= 0.08234301581978798f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                }
                            }
                        } else {
                            if (features[31] <= 0.1988118588924408f) {
                                if (features[26] <= -0.3223493695259094f) {
                                    if (features[0] <= -0.38832612335681915f) {
                                        if (features[14] <= -0.2151380330324173f) {
                                            if (features[18] <= -0.39206846058368683f) {
                                                return 1;                                            } else {
                                                if (features[25] <= 0.13970552384853363f) {
                                                    return 2;                                                } else {
                                                    return 1;                                                }
                                            }
                                        } else {
                                            return 2;                                        }
                                    } else {
                                        return 2;                                    }
                                } else {
                                    return 2;                                }
                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[19] <= -0.40435853600502014f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[31] <= 0.1988118588924408f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 32
int predict_tree_32(const float* features) {
    // Max depth: 16
    if (features[19] <= -0.44408486783504486f) {
        if (features[5] <= 0.009555181255564094f) {
            if (features[10] <= -0.362265482544899f) {
                if (features[11] <= -0.08169526234269142f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[14] <= -0.2325943186879158f) {
                    return 0;                } else {
                    return 1;                }
            }
        } else {
            if (features[25] <= 1.3302350342273712f) {
                if (features[11] <= -0.03384602768346667f) {
                    if (features[3] <= 0.37110360711812973f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    if (features[13] <= -0.8898249119520187f) {
                        return 2;                    } else {
                        if (features[11] <= 0.7371421158313751f) {
                            return 1;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[1] <= -0.27291586995124817f) {
            if (features[20] <= 1.4326478838920593f) {
                if (features[5] <= 0.0895652286708355f) {
                    if (features[1] <= -0.397040531039238f) {
                        return 0;                    } else {
                        if (features[10] <= -0.41013185679912567f) {
                            return 0;                        } else {
                            if (features[5] <= -0.388219878077507f) {
                                return 0;                            } else {
                                if (features[18] <= -0.4259158670902252f) {
                                    return 0;                                } else {
                                    if (features[2] <= -0.3432070314884186f) {
                                        if (features[11] <= 0.049110932275652885f) {
                                            return 1;                                        } else {
                                            return 2;                                        }
                                    } else {
                                        if (features[10] <= -0.36036621034145355f) {
                                            if (features[5] <= -0.05680386163294315f) {
                                                return 0;                                            } else {
                                                return 1;                                            }
                                        } else {
                                            if (features[9] <= -0.7664791643619537f) {
                                                return 0;                                            } else {
                                                if (features[23] <= 0.07113000005483627f) {
                                                    if (features[17] <= -0.37135984003543854f) {
                                                        if (features[5] <= -0.3707769364118576f) {
                                                            return 0;                                                        } else {
                                                            if (features[13] <= -0.02463930007070303f) {
                                                                return 1;                                                            } else {
                                                                if (features[26] <= -0.31475184857845306f) {
                                                                    return 0;                                                                } else {
                                                                    return 0;                                                                }
                                                            }
                                                        }
                                                    } else {
                                                        return 1;                                                    }
                                                } else {
                                                    if (features[17] <= -0.37310804426670074f) {
                                                        return 2;                                                    } else {
                                                        return 2;                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                } else {
                    if (features[13] <= -0.9673651456832886f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[15] <= 0.7553892731666565f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[3] <= 1.9033518135547638f) {
                if (features[17] <= -0.27779386937618256f) {
                    if (features[12] <= 0.36841070652008057f) {
                        return 2;                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            } else {
                if (features[28] <= 0.034745603799819946f) {
                    return 0;                } else {
                    return 0;                }
            }
        }
    }
}

// Tree 33
int predict_tree_33(const float* features) {
    // Max depth: 11
    if (features[4] <= 0.12829256802797318f) {
        if (features[23] <= -0.36544257402420044f) {
            if (features[24] <= -0.38893671333789825f) {
                return 0;            } else {
                if (features[0] <= -0.3722134679555893f) {
                    if (features[10] <= -0.5727896988391876f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[26] <= -0.3310762792825699f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            }
        } else {
            if (features[21] <= 0.125311229377985f) {
                if (features[25] <= 0.3369889259338379f) {
                    if (features[12] <= 0.23235303908586502f) {
                        if (features[26] <= 1.0023295283317566f) {
                            if (features[22] <= 0.12985581159591675f) {
                                if (features[4] <= 0.11452966183423996f) {
                                    return 0;                                } else {
                                    if (features[0] <= -0.08396436274051666f) {
                                        return 0;                                    } else {
                                        return 2;                                    }
                                }
                            } else {
                                if (features[12] <= 0.004089916008524597f) {
                                    return 0;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[29] <= -0.001376032829284668f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[2] <= -0.5960176587104797f) {
                            return 0;                        } else {
                            if (features[4] <= -0.43035203218460083f) {
                                return 1;                            } else {
                                if (features[4] <= -0.1666399985551834f) {
                                    return 0;                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                } else {
                    if (features[17] <= -0.27806897670961916f) {
                        return 0;                    } else {
                        if (features[30] <= 0.18403255939483643f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[26] <= -0.3179287612438202f) {
                    return 0;                } else {
                    if (features[28] <= 0.034745603799819946f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[10] <= -0.1329411305487156f) {
            if (features[22] <= 1.5564878582954407f) {
                if (features[23] <= 0.1105770468711853f) {
                    if (features[19] <= -0.47045037150382996f) {
                        if (features[20] <= 0.1812215819954872f) {
                            return 0;                        } else {
                            if (features[14] <= 0.44820085167884827f) {
                                if (features[9] <= 0.910124808549881f) {
                                    return 0;                                } else {
                                    if (features[6] <= -0.11876857280731201f) {
                                        return 1;                                    } else {
                                        return 0;                                    }
                                }
                            } else {
                                if (features[8] <= -0.051362818107008934f) {
                                    return 2;                                } else {
                                    if (features[5] <= 0.0027296794578433037f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        }
                    } else {
                        if (features[11] <= 0.23633228987455368f) {
                            if (features[12] <= -0.1730952300131321f) {
                                return 2;                            } else {
                                if (features[27] <= 1.6312401294708252f) {
                                    if (features[5] <= 0.08918603509664536f) {
                                        if (features[21] <= 0.9205697178840637f) {
                                            if (features[2] <= 0.1934281885623932f) {
                                                return 2;                                            } else {
                                                return 1;                                            }
                                        } else {
                                            if (features[28] <= 0.034745603799819946f) {
                                                return 1;                                            } else {
                                                return 1;                                            }
                                        }
                                    } else {
                                        if (features[17] <= -0.4101293385028839f) {
                                            return 2;                                        } else {
                                            return 2;                                        }
                                    }
                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[13] <= -0.2028457708656788f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[3] <= 0.285536490380764f) {
                        return 1;                    } else {
                        return 2;                    }
                }
            } else {
                return 2;            }
        } else {
            if (features[9] <= 0.20272327959537506f) {
                if (features[21] <= 0.026409463956952095f) {
                    return 0;                } else {
                    return 2;                }
            } else {
                return 2;            }
        }
    }
}

// Tree 34
int predict_tree_34(const float* features) {
    // Max depth: 16
    if (features[17] <= -0.27497029304504395f) {
        if (features[25] <= -0.0769268348813057f) {
            if (features[10] <= -0.35102444887161255f) {
                if (features[9] <= 0.9952497780323029f) {
                    if (features[24] <= -0.06108994968235493f) {
                        if (features[6] <= -1.888936161994934f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[13] <= 0.5208629667758942f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[3] <= -0.36517152190208435f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[0] <= -0.37300267815589905f) {
                    return 0;                } else {
                    return 1;                }
            }
        } else {
            if (features[1] <= -0.39770661294460297f) {
                if (features[21] <= 1.1427310109138489f) {
                    if (features[20] <= 0.21497660875320435f) {
                        return 0;                    } else {
                        if (features[20] <= 0.6252939105033875f) {
                            if (features[23] <= 0.010062942281365395f) {
                                if (features[28] <= 0.034745603799819946f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                if (features[19] <= -0.5807915925979614f) {
                                    return 0;                                } else {
                                    if (features[29] <= -0.5067617737222463f) {
                                        if (features[1] <= -0.5390697717666626f) {
                                            return 1;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        return 1;                                    }
                                }
                            }
                        } else {
                            return 2;                        }
                    }
                } else {
                    return 2;                }
            } else {
                if (features[7] <= 0.22766803205013275f) {
                    if (features[25] <= 0.14956969022750854f) {
                        if (features[21] <= 1.4266599416732788f) {
                            if (features[9] <= 2.6896005868911743f) {
                                if (features[11] <= 0.3022049218416214f) {
                                    if (features[23] <= 0.09730159863829613f) {
                                        if (features[25] <= 0.0964549332857132f) {
                                            if (features[3] <= 0.598353922367096f) {
                                                if (features[27] <= 0.08163631893694401f) {
                                                    if (features[5] <= 0.09032361954450607f) {
                                                        return 1;                                                    } else {
                                                        if (features[9] <= 2.547857403755188f) {
                                                            return 2;                                                        } else {
                                                            return 2;                                                        }
                                                    }
                                                } else {
                                                    if (features[22] <= 1.1993493437767029f) {
                                                        return 1;                                                    } else {
                                                        if (features[7] <= 0.019222834147512913f) {
                                                            if (features[7] <= -0.052334632724523544f) {
                                                                return 1;                                                            } else {
                                                                if (features[18] <= -0.39873427152633667f) {
                                                                    return 2;                                                                } else {
                                                                    return 2;                                                                }
                                                            }
                                                        } else {
                                                            if (features[0] <= -0.3879760205745697f) {
                                                                return 1;                                                            } else {
                                                                return 2;                                                            }
                                                        }
                                                    }
                                                }
                                            } else {
                                                return 2;                                            }
                                        } else {
                                            if (features[12] <= 0.013180676847696304f) {
                                                if (features[5] <= 0.08804845064878464f) {
                                                    return 1;                                                } else {
                                                    return 2;                                                }
                                            } else {
                                                return 2;                                            }
                                        }
                                    } else {
                                        if (features[26] <= -0.325815811753273f) {
                                            if (features[28] <= 0.034745603799819946f) {
                                                if (features[24] <= 0.1320512630045414f) {
                                                    return 2;                                                } else {
                                                    return 1;                                                }
                                            } else {
                                                if (features[26] <= -0.3316180408000946f) {
                                                    return 2;                                                } else {
                                                    return 2;                                                }
                                            }
                                        } else {
                                            return 2;                                        }
                                    }
                                } else {
                                    return 2;                                }
                            } else {
                                if (features[7] <= -0.031522220466285944f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[3] <= 0.6198451817035675f) {
                                return 2;                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[4] <= 1.3010952472686768f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[3] <= -0.030862816609442234f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[21] <= 0.05802861601114273f) {
            if (features[7] <= 0.8931276276707649f) {
                return 2;            } else {
                return 0;            }
        } else {
            return 2;        }
    }
}

// Tree 35
int predict_tree_35(const float* features) {
    // Max depth: 11
    if (features[23] <= -0.07186553254723549f) {
        if (features[17] <= -0.408745139837265f) {
            if (features[20] <= -0.8359484374523163f) {
                return 0;            } else {
                return 0;            }
        } else {
            if (features[3] <= 0.5740767419338226f) {
                if (features[1] <= -0.3559093028306961f) {
                    return 0;                } else {
                    if (features[17] <= -0.37257441878318787f) {
                        if (features[15] <= 0.7553892731666565f) {
                            if (features[22] <= -0.7942927777767181f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            if (features[19] <= -0.4111960530281067f) {
                                return 1;                            } else {
                                if (features[31] <= 0.1988118588924408f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            }
                        }
                    } else {
                        if (features[0] <= -0.37300267815589905f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                return 0;            }
        }
    } else {
        if (features[21] <= 1.1390543580055237f) {
            if (features[1] <= -0.0606569480150938f) {
                if (features[7] <= -0.293033242225647f) {
                    if (features[26] <= -0.3302069455385208f) {
                        return 0;                    } else {
                        if (features[18] <= -0.5703784227371216f) {
                            if (features[2] <= -0.20129472762346268f) {
                                return 0;                            } else {
                                if (features[18] <= -0.5776118040084839f) {
                                    if (features[20] <= 0.1765180081129074f) {
                                        return 0;                                    } else {
                                        if (features[23] <= -0.0035918038338422775f) {
                                            return 0;                                        } else {
                                            if (features[29] <= -0.001376032829284668f) {
                                                return 1;                                            } else {
                                                return 1;                                            }
                                        }
                                    }
                                } else {
                                    if (features[30] <= 0.18403255939483643f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                }
                            }
                        } else {
                            if (features[20] <= 0.5927378237247467f) {
                                if (features[27] <= 2.8229252696037292f) {
                                    if (features[27] <= -0.34180180728435516f) {
                                        if (features[27] <= -0.3601665198802948f) {
                                            return 1;                                        } else {
                                            return 2;                                        }
                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 0;                                }
                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[10] <= -0.4445176422595978f) {
                        if (features[19] <= -0.5765452086925507f) {
                            return 1;                        } else {
                            if (features[17] <= -0.5737632215023041f) {
                                return 0;                            } else {
                                return 0;                            }
                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[27] <= -0.23305700719356537f) {
                    if (features[20] <= 0.06224893592298031f) {
                        if (features[6] <= -1.0038523077964783f) {
                            return 0;                        } else {
                            return 2;                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[17] <= 1.272385835647583f) {
                        if (features[17] <= -0.2292896807193756f) {
                            return 2;                        } else {
                            return 2;                        }
                    } else {
                        if (features[27] <= -0.13477497547864914f) {
                            if (features[18] <= 2.338351011276245f) {
                                if (features[2] <= -0.6054158210754395f) {
                                    if (features[0] <= 1.2686222791671753f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    return 2;                                }
                            } else {
                                if (features[7] <= 1.0933215785771608f) {
                                    if (features[31] <= 0.1988118588924408f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                } else {
                                    return 0;                                }
                            }
                        } else {
                            if (features[6] <= -1.0038523077964783f) {
                                return 0;                            } else {
                                if (features[25] <= -0.07389170676469803f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                }
            }
        } else {
            if (features[5] <= 0.08880684152245522f) {
                if (features[10] <= 0.013948634266853333f) {
                    return 1;                } else {
                    if (features[2] <= -0.07347968965768814f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[15] <= 0.7553892731666565f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 36
int predict_tree_36(const float* features) {
    // Max depth: 12
    if (features[17] <= -0.28981177508831024f) {
        if (features[20] <= 0.1339092031121254f) {
            if (features[1] <= -0.3405788540840149f) {
                if (features[26] <= -0.33586014807224274f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[17] <= -0.4195549488067627f) {
                    return 0;                } else {
                    if (features[0] <= -0.37225593626499176f) {
                        return 0;                    } else {
                        if (features[15] <= 0.7553892731666565f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            }
        } else {
            if (features[23] <= 0.1101977489888668f) {
                if (features[0] <= -0.5468661487102509f) {
                    if (features[23] <= 0.015373121248558164f) {
                        if (features[8] <= -0.39761942625045776f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[13] <= -0.3728901147842407f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[27] <= 0.6278706192970276f) {
                        if (features[4] <= 1.451932966709137f) {
                            if (features[22] <= 1.451140284538269f) {
                                if (features[3] <= 0.598353922367096f) {
                                    if (features[25] <= -0.07920318469405174f) {
                                        return 0;                                    } else {
                                        if (features[26] <= -0.2696283906698227f) {
                                            if (features[5] <= 0.08918603509664536f) {
                                                return 1;                                            } else {
                                                if (features[26] <= -0.31793051958084106f) {
                                                    return 2;                                                } else {
                                                    return 2;                                                }
                                            }
                                        } else {
                                            if (features[29] <= -0.001376032829284668f) {
                                                return 2;                                            } else {
                                                return 1;                                            }
                                        }
                                    }
                                } else {
                                    if (features[33] <= -0.785379022359848f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                }
                            } else {
                                return 2;                            }
                        } else {
                            return 2;                        }
                    } else {
                        if (features[5] <= 0.06112563796341419f) {
                            if (features[22] <= 0.026704832911491394f) {
                                return 0;                            } else {
                                return 1;                            }
                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[20] <= 0.7672310620546341f) {
                    if (features[8] <= -0.21741604059934616f) {
                        return 2;                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[20] <= 0.05828317999839783f) {
            if (features[12] <= -0.7339013516902924f) {
                return 2;            } else {
                if (features[25] <= 0.06837998330593109f) {
                    return 2;                } else {
                    if (features[2] <= -0.5960176587104797f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[10] <= -0.32772138714790344f) {
                return 1;            } else {
                if (features[31] <= 0.1988118588924408f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 37
int predict_tree_37(const float* features) {
    // Max depth: 10
    if (features[17] <= -0.44405877590179443f) {
        if (features[20] <= 0.1812215819954872f) {
            if (features[6] <= -1.888936161994934f) {
                return 0;            } else {
                return 0;            }
        } else {
            if (features[17] <= -0.5030697286128998f) {
                if (features[23] <= 0.0017183751915581524f) {
                    if (features[20] <= 0.18380393087863922f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[14] <= -0.1976817548274994f) {
                        return 0;                    } else {
                        if (features[2] <= 0.16523369774222374f) {
                            if (features[0] <= -0.5046067833900452f) {
                                return 1;                            } else {
                                if (features[29] <= -0.001376032829284668f) {
                                    return 2;                                } else {
                                    return 1;                                }
                            }
                        } else {
                            return 0;                        }
                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[18] <= -0.25920821726322174f) {
            if (features[5] <= 0.0895652286708355f) {
                if (features[17] <= -0.42624905705451965f) {
                    return 0;                } else {
                    if (features[23] <= -0.3882004916667938f) {
                        return 0;                    } else {
                        if (features[21] <= 0.09194567427039146f) {
                            if (features[0] <= -0.3722134679555893f) {
                                if (features[21] <= -0.644302636384964f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        } else {
                            if (features[27] <= 0.621798574924469f) {
                                if (features[10] <= -0.09261323139071465f) {
                                    if (features[22] <= 0.9544229805469513f) {
                                        if (features[3] <= -0.44078898429870605f) {
                                            return 1;                                        } else {
                                            return 2;                                        }
                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 2;                                }
                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                if (features[31] <= 0.1988118588924408f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[20] <= 0.057084230706095695f) {
                if (features[12] <= -1.0061875879764557f) {
                    return 2;                } else {
                    return 0;                }
            } else {
                if (features[25] <= -0.01850059535354376f) {
                    if (features[1] <= -0.03055073320865631f) {
                        return 1;                    } else {
                        if (features[5] <= -0.07197164371609688f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[17] <= -0.3061832934617996f) {
                        if (features[21] <= 0.5717479288578033f) {
                            return 1;                        } else {
                            return 2;                        }
                    } else {
                        if (features[22] <= -0.03663189383223653f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    }
}

// Tree 38
int predict_tree_38(const float* features) {
    // Max depth: 19
    if (features[0] <= -0.44524042308330536f) {
        if (features[20] <= 0.21894236654043198f) {
            if (features[17] <= -0.6049589514732361f) {
                return 0;            } else {
                return 0;            }
        } else {
            if (features[0] <= -0.5046067833900452f) {
                if (features[0] <= -0.5588176846504211f) {
                    if (features[4] <= 0.4712567627429962f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[11] <= -0.0069144027947913855f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[8] <= -0.23873991519212723f) {
            return 2;        } else {
            if (features[18] <= -0.14465460181236267f) {
                if (features[7] <= 0.7079880833625793f) {
                    if (features[17] <= -0.42624905705451965f) {
                        if (features[22] <= 0.18934838473796844f) {
                            return 0;                        } else {
                            return 2;                        }
                    } else {
                        if (features[0] <= -0.2572661265730858f) {
                            if (features[5] <= 0.08918603509664536f) {
                                if (features[5] <= -0.388219878077507f) {
                                    return 0;                                } else {
                                    if (features[25] <= -0.3887863755226135f) {
                                        return 0;                                    } else {
                                        if (features[27] <= -0.3884178400039673f) {
                                            return 0;                                        } else {
                                            if (features[8] <= -0.14780541509389877f) {
                                                if (features[17] <= -0.42446523904800415f) {
                                                    return 0;                                                } else {
                                                    if (features[19] <= -0.5379298627376556f) {
                                                        return 0;                                                    } else {
                                                        if (features[1] <= -0.39788690209388733f) {
                                                            return 0;                                                        } else {
                                                            if (features[10] <= -0.406169056892395f) {
                                                                if (features[25] <= -0.1380088161677122f) {
                                                                    return 0;                                                                } else {
                                                                    return 1;                                                                }
                                                            } else {
                                                                if (features[27] <= -0.3845291882753372f) {
                                                                    return 0;                                                                } else {
                                                                    if (features[4] <= -0.6292213797569275f) {
                                                                        if (features[0] <= -0.34848088026046753f) {
                                                                            return 0;                                                                        } else {
                                                                            return 1;                                                                        }
                                                                    } else {
                                                                        if (features[25] <= -0.37133438885211945f) {
                                                                            if (features[14] <= -0.04057517368346453f) {
                                                                                return 0;                                                                            } else {
                                                                                return 1;                                                                            }
                                                                        } else {
                                                                            if (features[22] <= -0.6244186162948608f) {
                                                                                return 1;                                                                            } else {
                                                                                return 1;                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            } else {
                                                if (features[3] <= 0.07301166653633118f) {
                                                    if (features[0] <= -0.3571026474237442f) {
                                                        return 0;                                                    } else {
                                                        return 1;                                                    }
                                                } else {
                                                    if (features[4] <= -0.6234945356845856f) {
                                                        if (features[26] <= -0.30888962745666504f) {
                                                            if (features[12] <= -0.0002990540269820485f) {
                                                                return 0;                                                            } else {
                                                                if (features[17] <= -0.3729749619960785f) {
                                                                    return 0;                                                                } else {
                                                                    return 1;                                                                }
                                                            }
                                                        } else {
                                                            if (features[11] <= 0.011620941804721951f) {
                                                                return 1;                                                            } else {
                                                                if (features[2] <= -0.0979149155318737f) {
                                                                    return 0;                                                                } else {
                                                                    if (features[10] <= -0.35148437321186066f) {
                                                                        return 0;                                                                    } else {
                                                                        return 1;                                                                    }
                                                                }
                                                            }
                                                        }
                                                    } else {
                                                        if (features[25] <= -0.37209317088127136f) {
                                                            return 0;                                                        } else {
                                                            return 1;                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            } else {
                                if (features[25] <= 0.04713407903909683f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[3] <= -0.4961090683937073f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[25] <= 3.5587788820266724f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[21] <= 0.05986693874001503f) {
                    if (features[4] <= 0.1088951900601387f) {
                        return 0;                    } else {
                        if (features[25] <= 0.1590544730424881f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[10] <= -0.32754819095134735f) {
                        if (features[19] <= 0.7027000859379768f) {
                            return 2;                        } else {
                            return 1;                        }
                    } else {
                        if (features[4] <= 0.08515648543834686f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    }
}

// Tree 39
int predict_tree_39(const float* features) {
    // Max depth: 14
    if (features[20] <= 0.12293420732021332f) {
        if (features[17] <= -0.4088541120290756f) {
            if (features[17] <= -0.6049589514732361f) {
                return 0;            } else {
                return 0;            }
        } else {
            if (features[19] <= -0.14711483311839402f) {
                if (features[12] <= -0.04247957468032837f) {
                    return 0;                } else {
                    if (features[0] <= -0.3722134679555893f) {
                        if (features[12] <= -0.0353362150490284f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                }
            } else {
                if (features[7] <= 0.941732554929331f) {
                    return 2;                } else {
                    return 0;                }
            }
        }
    } else {
        if (features[0] <= -0.22930758446455002f) {
            if (features[20] <= 1.4326478838920593f) {
                if (features[10] <= -0.5387349128723145f) {
                    if (features[0] <= -0.5802113115787506f) {
                        if (features[20] <= 0.3812616392970085f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        if (features[12] <= -0.022159826010465622f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[8] <= -0.21313730627298355f) {
                        return 0;                    } else {
                        if (features[17] <= -0.3972339481115341f) {
                            if (features[18] <= -0.28341227769851685f) {
                                if (features[24] <= -0.051224189810454845f) {
                                    return 0;                                } else {
                                    if (features[8] <= -0.10696674138307571f) {
                                        if (features[5] <= 0.09335717186331749f) {
                                            return 1;                                        } else {
                                            if (features[21] <= 0.7365535870194435f) {
                                                return 1;                                            } else {
                                                return 2;                                            }
                                        }
                                    } else {
                                        if (features[3] <= 0.5903941988945007f) {
                                            if (features[1] <= -0.34979090094566345f) {
                                                if (features[1] <= -0.36966775357723236f) {
                                                    if (features[3] <= 0.4805499017238617f) {
                                                        return 1;                                                    } else {
                                                        if (features[17] <= -0.4163478910923004f) {
                                                            return 2;                                                        } else {
                                                            return 1;                                                        }
                                                    }
                                                } else {
                                                    if (features[21] <= 1.3219674825668335f) {
                                                        if (features[5] <= 0.09525314718484879f) {
                                                            return 1;                                                        } else {
                                                            return 2;                                                        }
                                                    } else {
                                                        return 2;                                                    }
                                                }
                                            } else {
                                                return 2;                                            }
                                        } else {
                                            return 2;                                        }
                                    }
                                }
                            } else {
                                if (features[8] <= -0.09661291167140007f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[6] <= -1.0038523524999619f) {
                                if (features[24] <= 0.04287997726351023f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            } else {
                                if (features[5] <= 0.08918603509664536f) {
                                    return 1;                                } else {
                                    if (features[21] <= 1.156610369682312f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                if (features[0] <= -0.5010775327682495f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[3] <= -2.176010251045227f) {
                return 2;            } else {
                return 2;            }
        }
    }
}

// Tree 40
int predict_tree_40(const float* features) {
    // Max depth: 15
    if (features[21] <= 0.1271495595574379f) {
        if (features[0] <= -0.37225593626499176f) {
            if (features[8] <= -0.7293393909931183f) {
                return 0;            } else {
                return 0;            }
        } else {
            if (features[18] <= -0.11868366412818432f) {
                return 1;            } else {
                if (features[2] <= -0.9531479179859161f) {
                    return 0;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[9] <= 2.1984755992889404f) {
            if (features[22] <= 0.20435882359743118f) {
                if (features[17] <= -0.13362284936010838f) {
                    if (features[3] <= -0.6517218351364136f) {
                        if (features[0] <= -0.5680030286312103f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        if (features[3] <= 0.3591640070080757f) {
                            if (features[1] <= -0.5462048649787903f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    }
                } else {
                    return 2;                }
            } else {
                if (features[0] <= -0.5032685995101929f) {
                    if (features[17] <= -0.512719452381134f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[17] <= -0.34054215252399445f) {
                        if (features[5] <= 0.07288067042827606f) {
                            return 1;                        } else {
                            if (features[20] <= 0.6539764702320099f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[7] <= -1.6020681262016296f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[20] <= 1.4311721920967102f) {
                if (features[10] <= -0.3699805289506912f) {
                    if (features[26] <= -0.33552761375904083f) {
                        return 2;                    } else {
                        if (features[17] <= -0.38884496688842773f) {
                            if (features[3] <= 0.6286008954048157f) {
                                if (features[14] <= 0.4831134229898453f) {
                                    if (features[13] <= 0.6378534734249115f) {
                                        if (features[8] <= -0.027210216969251633f) {
                                            if (features[25] <= 0.10062823444604874f) {
                                                if (features[17] <= -0.3890548050403595f) {
                                                    if (features[5] <= 0.09411556273698807f) {
                                                        return 1;                                                    } else {
                                                        if (features[20] <= 1.2600913643836975f) {
                                                            return 2;                                                        } else {
                                                            return 2;                                                        }
                                                    }
                                                } else {
                                                    return 2;                                                }
                                            } else {
                                                if (features[1] <= -0.3679278790950775f) {
                                                    return 2;                                                } else {
                                                    if (features[0] <= -0.4030204713344574f) {
                                                        return 2;                                                    } else {
                                                        if (features[4] <= 1.3731426000595093f) {
                                                            if (features[5] <= 0.09525314718484879f) {
                                                                return 1;                                                            } else {
                                                                return 2;                                                            }
                                                        } else {
                                                            return 2;                                                        }
                                                    }
                                                }
                                            }
                                        } else {
                                            if (features[10] <= -0.37369176745414734f) {
                                                return 2;                                            } else {
                                                return 2;                                            }
                                        }
                                    } else {
                                        if (features[26] <= -0.3278045207262039f) {
                                            return 2;                                        } else {
                                            return 2;                                        }
                                    }
                                } else {
                                    if (features[4] <= 1.3214162588119507f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                }
                            } else {
                                if (features[5] <= 0.12217595800757408f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[11] <= -0.008109746733680367f) {
                                if (features[24] <= 0.08765534684062004f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[8] <= -0.377962589263916f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[23] <= 0.006269956938922405f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 41
int predict_tree_41(const float* features) {
    // Max depth: 9
    if (features[23] <= -0.07338272780179977f) {
        if (features[12] <= 0.016785328276455402f) {
            if (features[10] <= -0.357530876994133f) {
                if (features[11] <= -0.13699088245630264f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[9] <= -0.8923689424991608f) {
                    return 0;                } else {
                    if (features[0] <= -0.3725171834230423f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            }
        } else {
            if (features[0] <= -0.37140268087387085f) {
                return 0;            } else {
                return 1;            }
        }
    } else {
        if (features[8] <= -0.18389088660478592f) {
            if (features[25] <= 0.09379919618368149f) {
                if (features[22] <= 0.1649106666445732f) {
                    if (features[25] <= -0.04050528351217508f) {
                        return 0;                    } else {
                        if (features[14] <= 2.6476929783821106f) {
                            if (features[7] <= 1.0620848536491394f) {
                                if (features[0] <= 0.3291887491941452f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            } else {
                                if (features[7] <= 2.183772325515747f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            }
                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[6] <= -1.888936161994934f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[7] <= 1.5873299837112427f) {
                    return 2;                } else {
                    if (features[25] <= 0.0945579782128334f) {
                        return 0;                    } else {
                        return 0;                    }
                }
            }
        } else {
            if (features[2] <= 0.04305755998939276f) {
                if (features[5] <= 0.0895652286708355f) {
                    if (features[22] <= 0.282339870929718f) {
                        return 0;                    } else {
                        if (features[5] <= 0.013347126310691237f) {
                            return 0;                        } else {
                            if (features[21] <= 0.9205697178840637f) {
                                if (features[24] <= 0.05691971257328987f) {
                                    return 1;                                } else {
                                    if (features[19] <= -0.479804128408432f) {
                                        return 0;                                    } else {
                                        return 2;                                    }
                                }
                            } else {
                                if (features[22] <= 1.2523435354232788f) {
                                    if (features[0] <= -0.37370719015598297f) {
                                        return 1;                                    } else {
                                        return 2;                                    }
                                } else {
                                    return 1;                                }
                            }
                        }
                    }
                } else {
                    if (features[17] <= -0.45991475880146027f) {
                        return 1;                    } else {
                        if (features[1] <= 1.310099296271801f) {
                            return 2;                        } else {
                            if (features[13] <= -0.05728781409561634f) {
                                return 0;                            } else {
                                return 0;                            }
                        }
                    }
                }
            } else {
                if (features[7] <= -0.359801709651947f) {
                    if (features[0] <= -0.25706253200769424f) {
                        if (features[10] <= -0.5291832089424133f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[21] <= 0.446741983294487f) {
                        if (features[17] <= 0.046432316303253174f) {
                            return 0;                        } else {
                            return 2;                        }
                    } else {
                        if (features[31] <= 0.1988118588924408f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    }
}

// Tree 42
int predict_tree_42(const float* features) {
    // Max depth: 11
    if (features[0] <= -0.44404713809490204f) {
        if (features[14] <= 0.5005697160959244f) {
            if (features[14] <= -0.7911954820156097f) {
                if (features[19] <= -0.5031110942363739f) {
                    return 0;                } else {
                    return 2;                }
            } else {
                if (features[5] <= 0.058471277356147766f) {
                    if (features[31] <= 0.1988118588924408f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[8] <= -0.13207023218274117f) {
                        return 2;                    } else {
                        return 1;                    }
                }
            }
        } else {
            if (features[0] <= -0.5056865811347961f) {
                if (features[20] <= 0.16425183415412903f) {
                    return 0;                } else {
                    if (features[5] <= 0.0027296794578433037f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[21] <= -0.07368721067905426f) {
                    return 0;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[0] <= -0.22930758446455002f) {
            if (features[33] <= -0.785379022359848f) {
                if (features[24] <= 0.12673892825841904f) {
                    if (features[5] <= 0.09032361954450607f) {
                        if (features[12] <= 0.02617860585451126f) {
                            if (features[18] <= -0.41486282646656036f) {
                                return 0;                            } else {
                                if (features[25] <= -0.25144678354263306f) {
                                    return 0;                                } else {
                                    if (features[8] <= -0.057463232427835464f) {
                                        return 1;                                    } else {
                                        if (features[4] <= 0.9379947185516357f) {
                                            return 2;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        } else {
                            if (features[21] <= 0.5956461429595947f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[7] <= 0.3281586393713951f) {
                            if (features[15] <= 0.7553892731666565f) {
                                return 2;                            } else {
                                return 2;                            }
                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[12] <= -0.459493950009346f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[5] <= 0.08918603509664536f) {
                    if (features[18] <= -0.4263527989387512f) {
                        if (features[0] <= -0.37823234498500824f) {
                            if (features[17] <= -0.4560178220272064f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[25] <= -0.38688941299915314f) {
                            return 0;                        } else {
                            if (features[6] <= 0.10250241588801146f) {
                                if (features[25] <= -0.2184397503733635f) {
                                    if (features[29] <= 0.5040097392629832f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                if (features[1] <= -0.34821756184101105f) {
                                    if (features[13] <= -0.05592745915055275f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    if (features[23] <= -0.36620116233825684f) {
                                        if (features[0] <= -0.3722134679555893f) {
                                            return 0;                                        } else {
                                            if (features[3] <= -0.37313126027584076f) {
                                                return 1;                                            } else {
                                                return 1;                                            }
                                        }
                                    } else {
                                        if (features[8] <= -0.11509760096669197f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    }
                                }
                            }
                        }
                    }
                } else {
                    if (features[3] <= 0.3778693675994873f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[22] <= 0.05709180235862732f) {
                if (features[10] <= 0.8329218924045563f) {
                    if (features[7] <= 1.054432313889265f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    return 0;                }
            } else {
                if (features[6] <= -1.4463942646980286f) {
                    if (features[18] <= 1.0948428511619568f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    if (features[29] <= -0.5067617737222463f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 43
int predict_tree_43(const float* features) {
    // Max depth: 20
    if (features[0] <= -0.22930758446455002f) {
        if (features[0] <= -0.4260692894458771f) {
            if (features[22] <= 0.2865501195192337f) {
                if (features[27] <= 0.37579192221164703f) {
                    if (features[0] <= -0.6052342653274536f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[6] <= -1.4463942050933838f) {
                        if (features[25] <= -0.18277697265148163f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        if (features[5] <= -0.38480713963508606f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                }
            } else {
                if (features[5] <= 0.21621619910001755f) {
                    if (features[26] <= -0.33092865347862244f) {
                        return 0;                    } else {
                        if (features[12] <= 0.0019009949755854905f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[23] <= 0.09730159863829613f) {
                if (features[25] <= -0.38764820992946625f) {
                    return 0;                } else {
                    if (features[7] <= 0.4402111917734146f) {
                        if (features[10] <= -0.4101376533508301f) {
                            return 0;                        } else {
                            if (features[4] <= -0.6475103497505188f) {
                                return 0;                            } else {
                                if (features[18] <= -0.49274976551532745f) {
                                    return 0;                                } else {
                                    if (features[27] <= -0.39259468019008636f) {
                                        return 0;                                    } else {
                                        if (features[23] <= -0.3893383741378784f) {
                                            return 0;                                        } else {
                                            if (features[14] <= 0.1863565519452095f) {
                                                if (features[12] <= 0.2837780490517616f) {
                                                    if (features[0] <= -0.28031691908836365f) {
                                                        if (features[13] <= 0.5222233086824417f) {
                                                            if (features[5] <= 0.0895652286708355f) {
                                                                if (features[11] <= 0.044772323220968246f) {
                                                                    if (features[25] <= -0.11145143210887909f) {
                                                                        if (features[1] <= -0.34763216972351074f) {
                                                                            return 0;                                                                        } else {
                                                                            if (features[4] <= -0.507479727268219f) {
                                                                                return 1;                                                                            } else {
                                                                                return 0;                                                                            }
                                                                        }
                                                                    } else {
                                                                        if (features[12] <= 0.013692153617739677f) {
                                                                            return 1;                                                                        } else {
                                                                            if (features[12] <= 0.014398164115846157f) {
                                                                                return 2;                                                                            } else {
                                                                                return 1;                                                                            }
                                                                        }
                                                                    }
                                                                } else {
                                                                    if (features[5] <= 0.009934373199939728f) {
                                                                        if (features[9] <= -0.6506964266300201f) {
                                                                            return 0;                                                                        } else {
                                                                            if (features[14] <= 0.08161883428692818f) {
                                                                                if (features[1] <= -0.36812858283519745f) {
                                                                                    return 0;                                                                                } else {
                                                                                    return 1;                                                                                }
                                                                            } else {
                                                                                return 0;                                                                            }
                                                                        }
                                                                    } else {
                                                                        return 2;                                                                    }
                                                                }
                                                            } else {
                                                                if (features[0] <= -0.40078847110271454f) {
                                                                    return 2;                                                                } else {
                                                                    return 2;                                                                }
                                                            }
                                                        } else {
                                                            return 2;                                                        }
                                                    } else {
                                                        if (features[28] <= 0.034745603799819946f) {
                                                            return 2;                                                        } else {
                                                            return 2;                                                        }
                                                    }
                                                } else {
                                                    return 0;                                                }
                                            } else {
                                                if (features[33] <= -0.785379022359848f) {
                                                    return 2;                                                } else {
                                                    if (features[11] <= -0.013003014959394932f) {
                                                        return 2;                                                    } else {
                                                        if (features[2] <= 0.24981719255447388f) {
                                                            return 1;                                                        } else {
                                                            return 1;                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        if (features[27] <= -0.3831588923931122f) {
                            return 0;                        } else {
                            if (features[4] <= -0.6252495348453522f) {
                                if (features[17] <= -0.3726990520954132f) {
                                    if (features[0] <= -0.4176681786775589f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    if (features[8] <= -0.08758009225130081f) {
                                        if (features[21] <= -0.6400744915008545f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 0;                                    }
                                }
                            } else {
                                if (features[10] <= -0.3575489968061447f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            }
                        }
                    }
                }
            } else {
                if (features[3] <= 0.1171881826594472f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[6] <= -1.0038523077964783f) {
            if (features[20] <= 0.07525292225182056f) {
                return 0;            } else {
                if (features[12] <= 0.8450110554695129f) {
                    if (features[16] <= 2.4144846946001053f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    if (features[24] <= 0.1851745881140232f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            }
        } else {
            return 2;        }
    }
}

// Tree 44
int predict_tree_44(const float* features) {
    // Max depth: 15
    if (features[18] <= -0.28418077528476715f) {
        if (features[18] <= -0.4262853264808655f) {
            if (features[5] <= 0.02661893516778946f) {
                if (features[14] <= -0.2325943186879158f) {
                    if (features[17] <= -0.4195549488067627f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[10] <= -0.362265482544899f) {
                        if (features[23] <= -0.5110931992530823f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                }
            } else {
                if (features[10] <= -0.48964767158031464f) {
                    if (features[13] <= -0.3728901147842407f) {
                        return 0;                    } else {
                        if (features[14] <= 0.04670625925064087f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[9] <= -0.7655824720859528f) {
                if (features[24] <= 1.6297494173049927f) {
                    return 0;                } else {
                    return 2;                }
            } else {
                if (features[21] <= 1.4127806425094604f) {
                    if (features[23] <= 0.09806019440293312f) {
                        if (features[10] <= -0.4102548360824585f) {
                            return 0;                        } else {
                            if (features[20] <= -0.6466067135334015f) {
                                return 0;                            } else {
                                if (features[5] <= 0.0895652286708355f) {
                                    if (features[25] <= -0.38840697705745697f) {
                                        return 0;                                    } else {
                                        if (features[25] <= -0.11296899616718292f) {
                                            if (features[18] <= -0.3928169012069702f) {
                                                if (features[26] <= -0.1210068752989173f) {
                                                    if (features[15] <= 0.7553892731666565f) {
                                                        return 0;                                                    } else {
                                                        return 0;                                                    }
                                                } else {
                                                    return 1;                                                }
                                            } else {
                                                if (features[18] <= -0.3702254295349121f) {
                                                    if (features[11] <= 0.006032244069501758f) {
                                                        return 0;                                                    } else {
                                                        if (features[10] <= -0.3517681658267975f) {
                                                            if (features[2] <= -0.0979149155318737f) {
                                                                return 0;                                                            } else {
                                                                return 0;                                                            }
                                                        } else {
                                                            return 1;                                                        }
                                                    }
                                                } else {
                                                    if (features[10] <= -0.35076048970222473f) {
                                                        return 0;                                                    } else {
                                                        if (features[5] <= -0.33664941787719727f) {
                                                            return 1;                                                        } else {
                                                            return 0;                                                        }
                                                    }
                                                }
                                            }
                                        } else {
                                            if (features[24] <= 0.08537863194942474f) {
                                                return 1;                                            } else {
                                                if (features[12] <= 0.02647906308993697f) {
                                                    return 1;                                                } else {
                                                    return 2;                                                }
                                            }
                                        }
                                    }
                                } else {
                                    if (features[4] <= 0.9984960854053497f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                }
                            }
                        }
                    } else {
                        if (features[13] <= -0.7551498115062714f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[4] <= 1.3373960256576538f) {
                        return 1;                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[2] <= -0.9597266465425491f) {
            return 0;        } else {
            if (features[26] <= 5.780059814453125f) {
                return 2;            } else {
                if (features[25] <= 0.024370608385652304f) {
                    return 1;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 45
int predict_tree_45(const float* features) {
    // Max depth: 18
    if (features[10] <= -0.4322226345539093f) {
        if (features[6] <= -1.4463942050933838f) {
            if (features[27] <= -0.15244993567466736f) {
                if (features[10] <= -0.5159150063991547f) {
                    if (features[7] <= -1.514247715473175f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    return 2;                }
            } else {
                if (features[1] <= -0.47571562230587006f) {
                    if (features[27] <= 0.3653261959552765f) {
                        if (features[22] <= 2.4964706003665924f) {
                            if (features[23] <= -0.22699862718582153f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 2;                        }
                    } else {
                        if (features[5] <= 0.03647799231112003f) {
                            return 0;                        } else {
                            if (features[10] <= -0.49029552936553955f) {
                                return 1;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[23] <= 0.009683643700554967f) {
                if (features[30] <= 0.18403255939483643f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[5] <= 0.030031686648726463f) {
                    return 0;                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[0] <= -0.22930758446455002f) {
            if (features[22] <= 1.5320501923561096f) {
                if (features[0] <= -0.4262443482875824f) {
                    return 0;                } else {
                    if (features[9] <= -0.7635334730148315f) {
                        return 0;                    } else {
                        if (features[9] <= 2.685706853866577f) {
                            if (features[20] <= 1.432555615901947f) {
                                if (features[25] <= 0.09304041042923927f) {
                                    if (features[12] <= -0.16476405411958694f) {
                                        if (features[4] <= 0.4506586045026779f) {
                                            return 0;                                        } else {
                                            return 2;                                        }
                                    } else {
                                        if (features[27] <= -0.38414251804351807f) {
                                            return 0;                                        } else {
                                            if (features[6] <= 0.5450443178415298f) {
                                                if (features[3] <= 0.39936064183712006f) {
                                                    if (features[17] <= -0.41579779982566833f) {
                                                        return 0;                                                    } else {
                                                        if (features[0] <= -0.4153473228216171f) {
                                                            return 0;                                                        } else {
                                                            if (features[20] <= 1.3586819171905518f) {
                                                                if (features[23] <= 0.0893363282084465f) {
                                                                    return 1;                                                                } else {
                                                                    return 2;                                                                }
                                                            } else {
                                                                if (features[18] <= -0.2843283414840698f) {
                                                                    return 2;                                                                } else {
                                                                    return 1;                                                                }
                                                            }
                                                        }
                                                    }
                                                } else {
                                                    if (features[27] <= 1.0314407050609589f) {
                                                        if (features[1] <= -0.2936762273311615f) {
                                                            if (features[23] <= 0.089715626090765f) {
                                                                if (features[13] <= 0.3902689069509506f) {
                                                                    if (features[8] <= -0.07726146094501019f) {
                                                                        return 1;                                                                    } else {
                                                                        if (features[21] <= 1.3575390577316284f) {
                                                                            return 1;                                                                        } else {
                                                                            return 2;                                                                        }
                                                                    }
                                                                } else {
                                                                    if (features[1] <= -0.361908420920372f) {
                                                                        return 1;                                                                    } else {
                                                                        return 2;                                                                    }
                                                                }
                                                            } else {
                                                                if (features[12] <= 0.2215007496997714f) {
                                                                    if (features[17] <= -0.41335344314575195f) {
                                                                        return 2;                                                                    } else {
                                                                        return 2;                                                                    }
                                                                } else {
                                                                    return 1;                                                                }
                                                            }
                                                        } else {
                                                            return 2;                                                        }
                                                    } else {
                                                        return 2;                                                    }
                                                }
                                            } else {
                                                if (features[1] <= -0.3336902856826782f) {
                                                    if (features[25] <= -0.3933390825986862f) {
                                                        return 0;                                                    } else {
                                                        return 0;                                                    }
                                                } else {
                                                    if (features[10] <= -0.35002031922340393f) {
                                                        return 1;                                                    } else {
                                                        return 1;                                                    }
                                                }
                                            }
                                        }
                                    }
                                } else {
                                    if (features[4] <= 1.3360105156898499f) {
                                        if (features[17] <= -0.38605664670467377f) {
                                            if (features[5] <= 0.0895652286708355f) {
                                                return 1;                                            } else {
                                                return 2;                                            }
                                        } else {
                                            return 2;                                        }
                                    } else {
                                        return 2;                                    }
                                }
                            } else {
                                if (features[20] <= 1.433754563331604f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[27] <= -0.12551852874457836f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                if (features[7] <= 0.3525222148746252f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[23] <= 0.09123282134532928f) {
                if (features[20] <= -0.03892393340356648f) {
                    return 0;                } else {
                    return 2;                }
            } else {
                if (features[3] <= 1.8834524750709534f) {
                    return 2;                } else {
                    if (features[31] <= 0.1988118588924408f) {
                        return 0;                    } else {
                        return 0;                    }
                }
            }
        }
    }
}

// Tree 46
int predict_tree_46(const float* features) {
    // Max depth: 17
    if (features[27] <= -0.23759402334690094f) {
        if (features[19] <= -0.4260518550872803f) {
            if (features[17] <= -0.39031797647476196f) {
                if (features[34] <= -2.074661783874035f) {
                    return 2;                } else {
                    if (features[23] <= 0.37077581137418747f) {
                        if (features[23] <= -0.5110931992530823f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                }
            } else {
                return 1;            }
        } else {
            if (features[23] <= 0.08288825303316116f) {
                if (features[17] <= -0.27823300659656525f) {
                    if (features[1] <= -0.39788690209388733f) {
                        return 0;                    } else {
                        if (features[20] <= -0.6448543965816498f) {
                            return 0;                        } else {
                            if (features[26] <= -0.17254909873008728f) {
                                if (features[19] <= -0.3856833130121231f) {
                                    if (features[23] <= -0.057072896510362625f) {
                                        if (features[0] <= -0.3660125732421875f) {
                                            if (features[11] <= -0.1073184497654438f) {
                                                return 0;                                            } else {
                                                return 0;                                            }
                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[28] <= 0.034745603799819946f) {
                                        if (features[17] <= -0.37087294459342957f) {
                                            return 0;                                        } else {
                                            if (features[1] <= -0.25828467309474945f) {
                                                return 1;                                            } else {
                                                return 0;                                            }
                                        }
                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                if (features[17] <= -0.35335487127304077f) {
                                    return 0;                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                } else {
                    if (features[29] <= -0.5067617737222463f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[6] <= -1.0038523077964783f) {
                    if (features[20] <= 0.4362288471311331f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[17] <= -0.3304222375154495f) {
            if (features[4] <= 1.4561819434165955f) {
                if (features[23] <= -0.05783149041235447f) {
                    if (features[5] <= -0.2949380427598953f) {
                        if (features[10] <= -0.3554396778345108f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        if (features[24] <= -0.31418462097644806f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[0] <= -0.32427558302879333f) {
                        if (features[23] <= 0.09730159863829613f) {
                            if (features[11] <= 0.12566345185041428f) {
                                if (features[14] <= 9.508013486862183f) {
                                    if (features[20] <= 0.17162998765707016f) {
                                        return 0;                                    } else {
                                        if (features[26] <= -0.3330404460430145f) {
                                            if (features[17] <= -0.49317625164985657f) {
                                                return 0;                                            } else {
                                                return 2;                                            }
                                        } else {
                                            if (features[11] <= 0.022312257438898087f) {
                                                if (features[1] <= -0.46519148349761963f) {
                                                    if (features[9] <= 1.0039059519767761f) {
                                                        if (features[0] <= -0.5791363716125488f) {
                                                            return 0;                                                        } else {
                                                            return 0;                                                        }
                                                    } else {
                                                        return 1;                                                    }
                                                } else {
                                                    if (features[14] <= 0.5180260092020035f) {
                                                        if (features[4] <= 1.1577393412590027f) {
                                                            if (features[1] <= -0.3318420648574829f) {
                                                                return 2;                                                            } else {
                                                                return 1;                                                            }
                                                        } else {
                                                            if (features[21] <= 1.2498133182525635f) {
                                                                if (features[20] <= 1.2968899011611938f) {
                                                                    if (features[22] <= 1.2774219512939453f) {
                                                                        return 1;                                                                    } else {
                                                                        return 2;                                                                    }
                                                                } else {
                                                                    if (features[9] <= 2.4621299505233765f) {
                                                                        return 2;                                                                    } else {
                                                                        return 1;                                                                    }
                                                                }
                                                            } else {
                                                                return 1;                                                            }
                                                        }
                                                    } else {
                                                        if (features[8] <= -0.14127888530492783f) {
                                                            return 2;                                                        } else {
                                                            return 1;                                                        }
                                                    }
                                                }
                                            } else {
                                                if (features[19] <= -0.4125926196575165f) {
                                                    return 1;                                                } else {
                                                    if (features[12] <= 0.012291260529309511f) {
                                                        return 2;                                                    } else {
                                                        return 2;                                                    }
                                                }
                                            }
                                        }
                                    }
                                } else {
                                    return 2;                                }
                            } else {
                                return 2;                            }
                        } else {
                            if (features[26] <= -0.20649850368499756f) {
                                if (features[2] <= -0.475721150636673f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[17] <= -0.37379735708236694f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[3] <= -0.20597689598798752f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[20] <= 0.04740040935575962f) {
                if (features[11] <= -0.19461341947317123f) {
                    if (features[0] <= 1.5543015599250793f) {
                        return 2;                    } else {
                        if (features[13] <= 0.07058553397655487f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                } else {
                    return 0;                }
            } else {
                return 2;            }
        }
    }
}

// Tree 47
int predict_tree_47(const float* features) {
    // Max depth: 14
    if (features[1] <= -0.41790489852428436f) {
        if (features[21] <= 0.43286263942718506f) {
            if (features[5] <= 0.03989074379205704f) {
                if (features[8] <= -0.7293393909931183f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[21] <= 0.12246183305978775f) {
                    return 1;                } else {
                    return 1;                }
            }
        } else {
            if (features[10] <= -0.4918682128190994f) {
                if (features[3] <= -0.22985609620809555f) {
                    if (features[2] <= 0.1464373730123043f) {
                        return 1;                    } else {
                        return 0;                    }
                } else {
                    if (features[27] <= 0.3345029652118683f) {
                        return 0;                    } else {
                        return 0;                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[19] <= -0.005369451362639666f) {
            if (features[5] <= 0.0895652286708355f) {
                if (features[5] <= -0.388219878077507f) {
                    return 0;                } else {
                    if (features[20] <= 0.8656370937824249f) {
                        if (features[24] <= -0.01631457917392254f) {
                            if (features[27] <= -0.3833763897418976f) {
                                return 0;                            } else {
                                if (features[2] <= 0.841901570558548f) {
                                    if (features[1] <= -0.34817807376384735f) {
                                        if (features[29] <= -0.5067617737222463f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        if (features[3] <= 0.5740767419338226f) {
                                            if (features[12] <= -0.12784378230571747f) {
                                                return 0;                                            } else {
                                                if (features[26] <= -0.32869789004325867f) {
                                                    return 0;                                                } else {
                                                    if (features[0] <= -0.37368980050086975f) {
                                                        return 0;                                                    } else {
                                                        if (features[0] <= -0.37125639617443085f) {
                                                            return 1;                                                        } else {
                                                            return 1;                                                        }
                                                    }
                                                }
                                            }
                                        } else {
                                            if (features[27] <= -0.3719078153371811f) {
                                                return 0;                                            } else {
                                                return 0;                                            }
                                        }
                                    }
                                } else {
                                    return 0;                                }
                            }
                        } else {
                            if (features[1] <= -0.3229091614484787f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        return 1;                    }
                }
            } else {
                if (features[17] <= -0.47955629229545593f) {
                    return 1;                } else {
                    return 2;                }
            }
        } else {
            if (features[22] <= 0.035216838121414185f) {
                if (features[6] <= -1.0038523077964783f) {
                    return 0;                } else {
                    return 2;                }
            } else {
                if (features[5] <= -0.03860252536833286f) {
                    if (features[6] <= -0.5613104552030563f) {
                        return 2;                    } else {
                        if (features[21] <= 0.5893958508968353f) {
                            if (features[27] <= 2.4720489978790283f) {
                                return 1;                            } else {
                                return 2;                            }
                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[18] <= -0.08157750032842159f) {
                        return 1;                    } else {
                        if (features[2] <= -0.9606664478778839f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    }
}

// Tree 48
int predict_tree_48(const float* features) {
    // Max depth: 9
    if (features[20] <= 0.1280066817998886f) {
        if (features[0] <= -0.37160593271255493f) {
            if (features[21] <= -0.8335579633712769f) {
                return 0;            } else {
                return 0;            }
        } else {
            if (features[17] <= -0.13645882718265057f) {
                return 1;            } else {
                if (features[22] <= 0.03347782511264086f) {
                    if (features[1] <= 0.29258108139038086f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    if (features[0] <= 1.288953959941864f) {
                        if (features[7] <= 0.9879938438534737f) {
                            return 2;                        } else {
                            return 0;                        }
                    } else {
                        if (features[4] <= 0.059847522526979446f) {
                            return 0;                        } else {
                            if (features[26] <= 0.3126397654414177f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                }
            }
        }
    } else {
        if (features[0] <= -0.22930758446455002f) {
            if (features[4] <= 1.4548887610435486f) {
                if (features[0] <= -0.5451856553554535f) {
                    if (features[6] <= -1.888936161994934f) {
                        if (features[5] <= 0.0482330247759819f) {
                            if (features[20] <= 0.13068126887083054f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[7] <= -1.5023735165596008f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[21] <= 1.438241422176361f) {
                        if (features[5] <= 0.08918603509664536f) {
                            if (features[25] <= -0.08185892179608345f) {
                                return 0;                            } else {
                                if (features[24] <= 0.08234301581978798f) {
                                    return 1;                                } else {
                                    if (features[9] <= 1.6706598997116089f) {
                                        return 2;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        } else {
                            if (features[25] <= -0.01243033620994538f) {
                                return 1;                            } else {
                                return 2;                            }
                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[13] <= -8.632964134216309f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[3] <= -2.1799901723861694f) {
                return 2;            } else {
                return 2;            }
        }
    }
}

// Tree 49
int predict_tree_49(const float* features) {
    // Max depth: 11
    if (features[18] <= -0.4452478736639023f) {
        if (features[33] <= -0.785379022359848f) {
            if (features[21] <= 1.2758256196975708f) {
                if (features[23] <= 0.009683643700554967f) {
                    return 0;                } else {
                    if (features[3] <= -0.22985609620809555f) {
                        return 1;                    } else {
                        if (features[13] <= -0.49940311908721924f) {
                            if (features[0] <= -0.26119174994528294f) {
                                return 0;                            } else {
                                return 2;                            }
                        } else {
                            return 0;                        }
                    }
                }
            } else {
                return 2;            }
        } else {
            if (features[26] <= -0.03702409565448761f) {
                return 0;            } else {
                if (features[29] <= -0.001376032829284668f) {
                    if (features[11] <= 0.21533948183059692f) {
                        return 1;                    } else {
                        return 0;                    }
                } else {
                    return 0;                }
            }
        }
    } else {
        if (features[22] <= 0.14440860599279404f) {
            if (features[19] <= -0.14719005092047155f) {
                if (features[0] <= -0.37225593626499176f) {
                    if (features[14] <= -0.1976817473769188f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    return 1;                }
            } else {
                if (features[33] <= -0.785379022359848f) {
                    if (features[6] <= -1.2251232862472534f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    if (features[3] <= 1.7680363804101944f) {
                        return 2;                    } else {
                        return 0;                    }
                }
            }
        } else {
            if (features[10] <= -0.30563631653785706f) {
                if (features[34] <= -2.074661783874035f) {
                    return 2;                } else {
                    if (features[23] <= 0.09578440338373184f) {
                        if (features[9] <= 2.713264226913452f) {
                            if (features[27] <= 0.922523707151413f) {
                                if (features[8] <= -0.048684513196349144f) {
                                    if (features[9] <= 2.3181328773498535f) {
                                        if (features[11] <= 0.022107720375061035f) {
                                            if (features[23] <= 0.08554334565997124f) {
                                                return 1;                                            } else {
                                                return 2;                                            }
                                        } else {
                                            return 2;                                        }
                                    } else {
                                        if (features[5] <= 0.08918603509664536f) {
                                            if (features[0] <= -0.37370719015598297f) {
                                                return 1;                                            } else {
                                                return 2;                                            }
                                        } else {
                                            if (features[20] <= 1.293477475643158f) {
                                                return 2;                                            } else {
                                                return 2;                                            }
                                        }
                                    }
                                } else {
                                    return 2;                                }
                            } else {
                                if (features[4] <= 0.6256968900561333f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            return 2;                        }
                    } else {
                        if (features[23] <= 0.09692230075597763f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[13] <= -9.563446998596191f) {
                    return 2;                } else {
                    return 2;                }
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
