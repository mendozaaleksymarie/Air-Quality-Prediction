/*
 * ════════════════════════════════════════════════════════════════════════
 * RANDOM FOREST MODEL - C++ EMBEDDED VERSION FOR ESP32
 * ════════════════════════════════════════════════════════════════════════
 * 
 * GENERATED: Automated conversion from Python sklearn model (200 trees)
 * Model Type: Random Forest Classifier
 * Features: 35 (Core: PM2.5, PM10, Temp, Humidity, Gas, CO, TimeOfDay, WetBulb + Engineered: ratios, deltas, lags, volatility, trends, anomalies)
 * Classes: 3 (0=Safe, 1=Caution, 2=Hazardous)
 * Trees: 200
 * Training Data: 20,568 samples from 8 MILES Protocol scenarios
 * Training Target: Safety-critical minority class (Caution) detection
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
    132.1752144959205f,  // feature_0
    159.66049259183424f,  // feature_1
    31.423558926487743f,  // feature_2
    58.1755257357709f,  // feature_3
    31.760376492789916f,  // feature_4
    7.64884323303675f,  // feature_5
    9.026059898872035f,  // feature_6
    28.844712224609317f,  // feature_7
    1.3884552076302081f,  // feature_8
    4.033891345680228f,  // feature_9
    291.8357070877554f,  // feature_10
    -0.01203950709263556f,  // feature_11
    -0.031222455602866694f,  // feature_12
    0.0014065658748336886f,  // feature_13
    -0.00014526756130966105f,  // feature_14
    0.200959419162453f,  // feature_15
    0.02320757163230909f,  // feature_16
    132.18725400301358f,  // feature_17
    132.26720111250435f,  // feature_18
    132.26170659637467f,  // feature_19
    31.75896992691509f,  // feature_20
    31.75564813014092f,  // feature_21
    31.74977306831653f,  // feature_22
    7.648988500598028f,  // feature_23
    7.6469995475266535f,  // feature_24
    7.64627133354048f,  // feature_25
    6.75887232423971f,  // feature_26
    0.3425395024137648f,  // feature_27
    -0.033774147543109034f,  // feature_28
    0.0025930247633864905f,  // feature_29
    0.41280954233112926f,  // feature_30
    0.41955140671593416f,  // feature_31
    0.0f,  // feature_32
    0.7950862180733826f,  // feature_33
    0.8978348243225723f,  // feature_34
};

const float SCALER_SCALE[] = {
    216.04218493908522f,  // feature_0
    276.42468266487685f,  // feature_1
    5.327753462460191f,  // feature_2
    12.567591142591118f,  // feature_3
    18.38205524269758f,  // feature_4
    3.585933601027247f,  // feature_5
    4.534349103149055f,  // feature_6
    3.4574315723233267f,  // feature_7
    1.012267186913389f,  // feature_8
    1.1999112725752432f,  // feature_9
    491.6620433730285f,  // feature_10
    18.907686261280805f,  // feature_11
    27.687921990732136f,  // feature_12
    0.8621135931395214f,  // feature_13
    0.22445447785688244f,  // feature_14
    0.4007177697736195f,  // feature_15
    0.15056221388928176f,  // feature_16
    216.08907222177302f,  // feature_17
    216.33941029856365f,  // feature_18
    216.44992687474135f,  // feature_19
    18.365181216849827f,  // feature_20
    18.335799172538795f,  // feature_21
    18.324487159237798f,  // feature_22
    3.587471997667802f,  // feature_23
    3.582296621522661f,  // feature_24
    3.5866882292353384f,  // feature_25
    18.56510426651965f,  // feature_26
    1.0579620916975285f,  // feature_27
    0.9955626842578799f,  // feature_28
    0.9988939909587554f,  // feature_29
    0.4923391352427357f,  // feature_30
    0.4934855862520801f,  // feature_31
    1.0f,  // feature_32
    0.4036386055658796f,  // feature_33
    0.4403324065222899f,  // feature_34
};

const int NUM_FEATURES = 35;
const int NUM_CLASSES = 3;
const int NUM_TREES = 200;

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
    if (features[21] <= 0.11983741819858551f) {
        if (features[0] <= -0.3756202161312103f) {
            return 0;        } else {
            if (features[0] <= -0.17111074924468994f) {
                return 1;            } else {
                if (features[0] <= 0.9993243217468262f) {
                    if (features[22] <= -0.057924664579331875f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    if (features[23] <= 0.3752908259630203f) {
                        if (features[22] <= 0.0479142852127552f) {
                            return 0;                        } else {
                            return 2;                        }
                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[2] <= -0.3084900379180908f) {
            if (features[24] <= -0.00047181162517517805f) {
                if (features[25] <= -0.04811277240514755f) {
                    if (features[22] <= 0.12095963209867477f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    return 2;                }
            } else {
                if (features[10] <= -0.34496551752090454f) {
                    if (features[12] <= -0.3007810339331627f) {
                        return 1;                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[22] <= 0.18039234727621078f) {
                if (features[18] <= -0.12195268273353577f) {
                    if (features[18] <= -0.5845630168914795f) {
                        return 0;                    } else {
                        if (features[24] <= -0.09189333394169807f) {
                            return 0;                        } else {
                            if (features[1] <= -0.5505309402942657f) {
                                return 0;                            } else {
                                if (features[13] <= -0.1391058936715126f) {
                                    return 0;                                } else {
                                    if (features[2] <= -0.18273348361253738f) {
                                        return 0;                                    } else {
                                        if (features[17] <= -0.45147131383419037f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        }
                    }
                } else {
                    return 2;                }
            } else {
                if (features[1] <= -0.4876805394887924f) {
                    if (features[9] <= 0.8998923599720001f) {
                        if (features[8] <= -0.20019826292991638f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[12] <= -1.063732624053955f) {
                        if (features[26] <= 8.413588047027588f) {
                            return 2;                        } else {
                            return 1;                        }
                    } else {
                        if (features[3] <= -2.166328191757202f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    }
}

// Tree 1
int predict_tree_1(const float* features) {
    // Max depth: 10
    if (features[17] <= -0.45113205909729004f) {
        if (features[4] <= 0.4632433205842972f) {
            return 0;        } else {
            if (features[22] <= 1.467083901166916f) {
                return 1;            } else {
                if (features[34] <= -2.0389932096004486f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[10] <= -0.2071150615811348f) {
            if (features[22] <= 1.53965425491333f) {
                if (features[0] <= -0.43021006882190704f) {
                    return 0;                } else {
                    if (features[23] <= -0.395358145236969f) {
                        return 0;                    } else {
                        if (features[22] <= 0.0897324439138174f) {
                            if (features[1] <= -0.35448597371578217f) {
                                if (features[7] <= -0.10166335478425026f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                if (features[17] <= -0.3792797327041626f) {
                                    return 0;                                } else {
                                    if (features[21] <= -0.5642624795436859f) {
                                        if (features[13] <= 0.07440897449851036f) {
                                            return 1;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        return 1;                                    }
                                }
                            }
                        } else {
                            if (features[11] <= 0.11159082874655724f) {
                                if (features[18] <= -0.16881216317415237f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            } else {
                                if (features[14] <= -0.4681316763162613f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                }
            } else {
                if (features[12] <= -0.9144937694072723f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[2] <= -0.958857998251915f) {
                return 0;            } else {
                return 2;            }
        }
    }
}

// Tree 2
int predict_tree_2(const float* features) {
    // Max depth: 9
    if (features[4] <= 0.12307662516832352f) {
        if (features[6] <= 1.2072162628173828f) {
            if (features[17] <= -0.38406287133693695f) {
                return 0;            } else {
                if (features[10] <= -0.1526372004300356f) {
                    if (features[19] <= -0.3460773527622223f) {
                        return 1;                    } else {
                        return 1;                    }
                } else {
                    if (features[2] <= -0.9429038017988205f) {
                        if (features[2] <= -1.665534794330597f) {
                            return 2;                        } else {
                            return 0;                        }
                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[24] <= -0.34895624220371246f) {
                if (features[1] <= -0.3395637720823288f) {
                    if (features[18] <= -0.6085299253463745f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[18] <= -0.3875793069601059f) {
                        return 1;                    } else {
                        if (features[17] <= -0.37341780960559845f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[2] <= -0.12642456963658333f) {
                    return 0;                } else {
                    return 0;                }
            }
        }
    } else {
        if (features[2] <= -0.31036700308322906f) {
            if (features[8] <= -0.1839715614914894f) {
                if (features[24] <= -0.04449554719030857f) {
                    return 0;                } else {
                    if (features[23] <= 0.10524795576930046f) {
                        if (features[17] <= -0.2715313956141472f) {
                            return 2;                        } else {
                            return 2;                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[4] <= 0.5986914336681366f) {
                    if (features[5] <= -0.02278979681432247f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    if (features[13] <= 1.72624933719635f) {
                        if (features[2] <= -0.3244442343711853f) {
                            if (features[12] <= 0.11467945016920567f) {
                                if (features[0] <= -0.37859775125980377f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            } else {
                                return 2;                            }
                        } else {
                            return 1;                        }
                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[23] <= -0.05297181010246277f) {
                if (features[17] <= 0.06462651491165161f) {
                    if (features[17] <= -0.4408375173807144f) {
                        if (features[20] <= 0.12133026495575905f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            } else {
                if (features[22] <= 0.0013059377670288086f) {
                    return 1;                } else {
                    if (features[0] <= -0.5167755782604218f) {
                        if (features[22] <= 0.4265212267637253f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        if (features[4] <= 0.1339970976114273f) {
                            if (features[19] <= 0.11182234063744545f) {
                                return 1;                            } else {
                                return 2;                            }
                        } else {
                            if (features[25] <= -0.07537524402141571f) {
                                if (features[4] <= 0.42160649597644806f) {
                                    return 1;                                } else {
                                    if (features[18] <= 1.2602145075798035f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                }
                            } else {
                                if (features[14] <= 2.9841467142105103f) {
                                    if (features[0] <= -0.5051935315132141f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                } else {
                                    if (features[22] <= 0.7254533171653748f) {
                                        return 1;                                    } else {
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

// Tree 3
int predict_tree_3(const float* features) {
    // Max depth: 9
    if (features[18] <= -0.44847212731838226f) {
        if (features[33] <= -0.7310653924942017f) {
            if (features[24] <= 0.22491830587387085f) {
                if (features[25] <= -0.05910938233137131f) {
                    if (features[2] <= -0.12642456963658333f) {
                        if (features[29] <= -0.5031495066359639f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[24] <= -0.04121887031942606f) {
                            if (features[18] <= -0.5847773849964142f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[4] <= 0.2922734469175339f) {
                        if (features[0] <= -0.5883448421955109f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[8] <= 0.09188399836421013f) {
                            if (features[9] <= 0.9006536304950714f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            return 0;                        }
                    }
                }
            } else {
                return 2;            }
        } else {
            if (features[0] <= -0.37770046293735504f) {
                return 0;            } else {
                return 1;            }
        }
    } else {
        if (features[10] <= -0.20674120634794235f) {
            if (features[20] <= 1.5383434891700745f) {
                if (features[20] <= 0.08821607194840908f) {
                    if (features[27] <= -0.3095593601465225f) {
                        return 0;                    } else {
                        if (features[17] <= -0.379781037569046f) {
                            if (features[23] <= -0.42158345878124237f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            if (features[11] <= -0.17938543856143951f) {
                                return 1;                            } else {
                                if (features[0] <= -0.37586139142513275f) {
                                    return 0;                                } else {
                                    if (features[19] <= -0.4627783000469208f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        }
                    }
                } else {
                    if (features[15] <= 0.7462623417377472f) {
                        return 1;                    } else {
                        if (features[23] <= 0.050549428910017014f) {
                            if (features[31] <= 0.16302114725112915f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[7] <= 0.7331040799617767f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[17] <= 1.1593074202537537f) {
                if (features[18] <= 1.0693566799163818f) {
                    if (features[2] <= -0.4577086716890335f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    if (features[20] <= -0.00608475913759321f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[6] <= -0.9981719255447388f) {
                    if (features[4] <= 1.1347718089818954f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 4
int predict_tree_4(const float* features) {
    // Max depth: 10
    if (features[0] <= -0.4505611062049866f) {
        if (features[4] <= 0.46065424382686615f) {
            return 0;        } else {
            if (features[21] <= 1.087798148393631f) {
                return 1;            } else {
                if (features[20] <= 2.481855869293213f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[3] <= 0.28521569073200226f) {
            if (features[10] <= -0.22114674746990204f) {
                if (features[2] <= 0.26773782074451447f) {
                    return 0;                } else {
                    if (features[0] <= -0.3745678663253784f) {
                        if (features[23] <= -0.13235614076256752f) {
                            if (features[4] <= -0.5617700219154358f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 2;                        }
                    } else {
                        return 1;                    }
                }
            } else {
                if (features[3] <= -2.1822421550750732f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[4] <= 1.5315960049629211f) {
                if (features[19] <= 0.0057551562786102295f) {
                    if (features[17] <= -0.43032942712306976f) {
                        if (features[6] <= -0.8879024907946587f) {
                            return 1;                        } else {
                            if (features[13] <= -0.06134696118533611f) {
                                return 0;                            } else {
                                return 0;                            }
                        }
                    } else {
                        if (features[12] <= 0.08114364370703697f) {
                            if (features[20] <= -0.6217929422855377f) {
                                if (features[1] <= -0.3376671075820923f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            } else {
                                if (features[27] <= -0.3026234209537506f) {
                                    if (features[20] <= 0.10852420330047607f) {
                                        return 0;                                    } else {
                                        return 2;                                    }
                                } else {
                                    if (features[22] <= 0.5357456207275391f) {
                                        if (features[21] <= -0.5985608994960785f) {
                                            return 1;                                        } else {
                                            return 2;                                        }
                                    } else {
                                        return 1;                                    }
                                }
                            }
                        } else {
                            if (features[2] <= -0.257812038064003f) {
                                if (features[1] <= -0.32033471763134f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            } else {
                                if (features[8] <= -0.09458248317241669f) {
                                    return 1;                                } else {
                                    return 0;                                }
                            }
                        }
                    }
                } else {
                    if (features[2] <= -0.9569810330867767f) {
                        return 0;                    } else {
                        if (features[31] <= 0.16302114725112915f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[2] <= 0.08004144579172134f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 5
int predict_tree_5(const float* features) {
    // Max depth: 10
    if (features[0] <= -0.4491826593875885f) {
        if (features[20] <= 0.43952497839927673f) {
            return 0;        } else {
            if (features[5] <= 0.8384912088513374f) {
                return 1;            } else {
                if (features[2] <= 0.08004144579172134f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[18] <= -0.18709474802017212f) {
            if (features[20] <= 1.550292432308197f) {
                if (features[1] <= -0.4018087685108185f) {
                    return 0;                } else {
                    if (features[23] <= -0.3907252103090286f) {
                        return 0;                    } else {
                        if (features[24] <= -0.11450402438640594f) {
                            if (features[24] <= -0.3489517420530319f) {
                                if (features[10] <= -0.3634177893400192f) {
                                    if (features[2] <= -0.10765492916107178f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    if (features[11] <= -0.13061608746647835f) {
                                        return 1;                                    } else {
                                        if (features[10] <= -0.36021170020103455f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            } else {
                                if (features[10] <= -0.29787833988666534f) {
                                    return 0;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[20] <= 0.9080948531627655f) {
                                if (features[25] <= 0.03865793440490961f) {
                                    return 1;                                } else {
                                    if (features[26] <= -0.217155821621418f) {
                                        return 2;                                    } else {
                                        return 2;                                    }
                                }
                            } else {
                                if (features[1] <= -0.33981746435165405f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                }
            } else {
                if (features[17] <= -0.4494752734899521f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[8] <= -0.2365313246846199f) {
                return 2;            } else {
                if (features[22] <= 0.05428099445998669f) {
                    if (features[20] <= 0.0482955202460289f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    if (features[14] <= -0.4334942549467087f) {
                        if (features[14] <= -0.43504075706005096f) {
                            if (features[17] <= -0.13445647805929184f) {
                                return 2;                            } else {
                                return 2;                            }
                        } else {
                            return 1;                        }
                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 6
int predict_tree_6(const float* features) {
    // Max depth: 7
    if (features[21] <= 0.11981721967458725f) {
        if (features[18] <= -0.4176875054836273f) {
            if (features[0] <= -0.3768584728240967f) {
                return 0;            } else {
                return 1;            }
        } else {
            if (features[21] <= -0.27335212379693985f) {
                if (features[26] <= -0.314845010638237f) {
                    if (features[0] <= -0.37597908079624176f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[12] <= -0.19050254672765732f) {
                        return 0;                    } else {
                        if (features[17] <= -0.3832317739725113f) {
                            return 0;                        } else {
                            if (features[0] <= -0.37586139142513275f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    }
                }
            } else {
                if (features[20] <= 0.055777473375201225f) {
                    if (features[17] <= 0.9991490244865417f) {
                        if (features[25] <= 0.0034881962928920984f) {
                            return 0;                        } else {
                            return 2;                        }
                    } else {
                        if (features[26] <= 6.265743255615234f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[4] <= 0.19933859258890152f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[17] <= -0.23100721091032028f) {
            if (features[23] <= 1.0926437377929688f) {
                if (features[0] <= -0.47524282336235046f) {
                    if (features[20] <= 0.38452962040901184f) {
                        return 0;                    } else {
                        if (features[2] <= 0.11758071696385741f) {
                            return 1;                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[0] <= -0.32476580142974854f) {
                        if (features[12] <= 0.0783008374273777f) {
                            if (features[8] <= -0.1794201210141182f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            if (features[13] <= 0.07806063815951347f) {
                                return 2;                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[7] <= 0.12688055634498596f) {
                            return 2;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                return 2;            }
        } else {
            if (features[23] <= -0.15862611681222916f) {
                return 2;            } else {
                return 2;            }
        }
    }
}

// Tree 7
int predict_tree_7(const float* features) {
    // Max depth: 10
    if (features[0] <= -0.4496677815914154f) {
        if (features[4] <= 0.4343201816082001f) {
            return 0;        } else {
            if (features[8] <= -0.07042740471661091f) {
                if (features[26] <= -0.3630975931882858f) {
                    return 2;                } else {
                    return 2;                }
            } else {
                return 1;            }
        }
    } else {
        if (features[17] <= -0.24509385973215103f) {
            if (features[21] <= 1.5381214022636414f) {
                if (features[20] <= -0.6398020684719086f) {
                    return 0;                } else {
                    if (features[25] <= -0.11548442021012306f) {
                        if (features[4] <= -0.5591708719730377f) {
                            if (features[11] <= -0.029406779445707798f) {
                                if (features[1] <= -0.3566775619983673f) {
                                    return 0;                                } else {
                                    if (features[25] <= -0.3843156546354294f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                if (features[10] <= -0.36021170020103455f) {
                                    return 0;                                } else {
                                    if (features[30] <= 0.17709434032440186f) {
                                        if (features[10] <= -0.35496382415294647f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[10] <= -0.35514219105243683f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        } else {
                            if (features[8] <= 0.4780513346195221f) {
                                if (features[7] <= -1.8138136863708496f) {
                                    return 2;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[15] <= 0.7462623417377472f) {
                            return 1;                        } else {
                            if (features[22] <= 1.2341331243515015f) {
                                if (features[31] <= 0.16302114725112915f) {
                                    return 1;                                } else {
                                    if (features[27] <= 0.662050724029541f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                return 1;                            }
                        }
                    }
                }
            } else {
                if (features[13] <= -2.372849464416504f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[22] <= 0.04020349495112896f) {
                if (features[3] <= 1.3029126971960068f) {
                    return 2;                } else {
                    return 0;                }
            } else {
                if (features[2] <= -0.9757506549358368f) {
                    return 0;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 8
int predict_tree_8(const float* features) {
    // Max depth: 10
    if (features[1] <= -0.423549547791481f) {
        if (features[9] <= 0.8882248103618622f) {
            if (features[21] <= 1.165939137339592f) {
                return 0;            } else {
                if (features[9] <= -1.0810186266899109f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[20] <= 2.513830691576004f) {
                if (features[27] <= 0.19188746809959412f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                if (features[21] <= 4.536617040634155f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[19] <= -0.12862157076597214f) {
            if (features[6] <= -1.6597883701324463f) {
                if (features[18] <= -0.4677160233259201f) {
                    return 1;                } else {
                    return 2;                }
            } else {
                if (features[18] <= -0.43003541231155396f) {
                    if (features[6] <= -0.5570942685008049f) {
                        if (features[3] <= 0.5271077156066895f) {
                            return 2;                        } else {
                            return 2;                        }
                    } else {
                        if (features[26] <= -0.35730065405368805f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[7] <= 0.6962836384773254f) {
                        if (features[18] <= -0.22722812741994858f) {
                            if (features[11] <= 0.4913231134414673f) {
                                if (features[33] <= -0.7310653924942017f) {
                                    if (features[5] <= -0.2029301959555596f) {
                                        return 0;                                    } else {
                                        if (features[21] <= 1.0391380190849304f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    if (features[24] <= -0.3953741043806076f) {
                                        return 0;                                    } else {
                                        if (features[21] <= 0.08664996176958084f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            } else {
                                if (features[18] <= -0.35892699658870697f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            return 2;                        }
                    } else {
                        if (features[18] <= -0.4281897395849228f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[23] <= 0.05901874601840973f) {
                if (features[0] <= -0.07536549121141434f) {
                    return 1;                } else {
                    if (features[20] <= -0.0353168083820492f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[22] <= 0.05498840659856796f) {
                    if (features[1] <= 0.8659382462501526f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 9
int predict_tree_9(const float* features) {
    // Max depth: 10
    if (features[1] <= -0.15344125032424927f) {
        if (features[1] <= -0.40174736082553864f) {
            if (features[22] <= 0.4331102520227432f) {
                if (features[5] <= 0.04834745544940233f) {
                    return 0;                } else {
                    if (features[27] <= 1.2203131020069122f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[18] <= -0.5368474721908569f) {
                    return 1;                } else {
                    return 2;                }
            }
        } else {
            if (features[25] <= 1.5124974697828293f) {
                if (features[4] <= -0.6392812132835388f) {
                    return 0;                } else {
                    if (features[0] <= -0.43021006882190704f) {
                        return 0;                    } else {
                        if (features[9] <= 0.44187258183956146f) {
                            if (features[1] <= -0.35435670614242554f) {
                                if (features[11] <= -0.20998801290988922f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                if (features[11] <= -0.18052831292152405f) {
                                    return 0;                                } else {
                                    if (features[13] <= -0.1577938124537468f) {
                                        return 0;                                    } else {
                                        if (features[2] <= -0.09827011078596115f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        } else {
                            if (features[5] <= 1.0476103350520134f) {
                                if (features[14] <= -1.1700255870819092f) {
                                    return 1;                                } else {
                                    if (features[27] <= 0.48866795003414154f) {
                                        return 1;                                    } else {
                                        if (features[18] <= -0.38412103056907654f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                if (features[23] <= 3.342664361000061f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[6] <= -0.9981719255447388f) {
            if (features[3] <= 1.8797933459281921f) {
                return 2;            } else {
                if (features[18] <= 1.079232931137085f) {
                    return 0;                } else {
                    return 0;                }
            }
        } else {
            return 2;        }
    }
}

// Tree 10
int predict_tree_10(const float* features) {
    // Max depth: 10
    if (features[1] <= -0.4235561043024063f) {
        if (features[1] <= -0.4779521971940994f) {
            if (features[6] <= 1.648293912410736f) {
                if (features[17] <= -0.4971368759870529f) {
                    if (features[27] <= 0.7469317615032196f) {
                        if (features[34] <= -2.0389932096004486f) {
                            return 2;                        } else {
                            return 0;                        }
                    } else {
                        if (features[21] <= 0.27767477184534073f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[33] <= -0.7310653924942017f) {
                        return 2;                    } else {
                        if (features[13] <= -0.05318441800773144f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                }
            } else {
                if (features[20] <= 0.44134001433849335f) {
                    if (features[23] <= -0.17648673057556152f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    return 1;                }
            }
        } else {
            if (features[23] <= 0.7630100026726723f) {
                if (features[5] <= -0.47845450043678284f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                return 2;            }
        }
    } else {
        if (features[8] <= -0.18651193380355835f) {
            if (features[6] <= 0.10452218819409609f) {
                if (features[1] <= 1.164219319820404f) {
                    if (features[18] <= 1.06706303358078f) {
                        if (features[3] <= 1.9394706785678864f) {
                            if (features[23] <= -0.22326499223709106f) {
                                return 0;                            } else {
                                if (features[26] <= -0.3623422831296921f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            return 0;                        }
                    } else {
                        if (features[21] <= 0.008498857961967587f) {
                            return 0;                        } else {
                            if (features[1] <= 0.49561460316181183f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[7] <= 1.2536694705486298f) {
                        return 2;                    } else {
                        return 0;                    }
                }
            } else {
                if (features[1] <= -0.37631115317344666f) {
                    if (features[5] <= -0.36188100278377533f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    return 1;                }
            }
        } else {
            if (features[2] <= 0.004962893668562174f) {
                if (features[24] <= -0.3953741043806076f) {
                    return 0;                } else {
                    if (features[19] <= -0.46475499868392944f) {
                        return 0;                    } else {
                        if (features[0] <= -0.4289495497941971f) {
                            return 0;                        } else {
                            if (features[9] <= 1.1784300804138184f) {
                                if (features[18] <= -0.38736048340797424f) {
                                    if (features[0] <= -0.37508928775787354f) {
                                        if (features[3] <= 0.3003339469432831f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[9] <= -0.7125549018383026f) {
                                        if (features[17] <= -0.379781037569046f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[13] <= -0.11590709537267685f) {
                                            return 2;                                        } else {
                                            return 0;                                        }
                                    }
                                }
                            } else {
                                if (features[10] <= -0.3518057316541672f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                }
            } else {
                if (features[27] <= -0.13569897413253784f) {
                    if (features[33] <= -0.7310653924942017f) {
                        return 2;                    } else {
                        if (features[10] <= -0.36010049283504486f) {
                            if (features[15] <= 0.7462623417377472f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            if (features[21] <= 0.22418702393770218f) {
                                if (features[18] <= -0.4630401134490967f) {
                                    return 0;                                } else {
                                    if (features[7] <= 0.13672164548188448f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[6] <= -0.33655544370412827f) {
                        return 2;                    } else {
                        return 1;                    }
                }
            }
        }
    }
}

// Tree 11
int predict_tree_11(const float* features) {
    // Max depth: 10
    if (features[18] <= -0.4485054761171341f) {
        if (features[23] <= -0.02270204108208418f) {
            if (features[11] <= 1.1076053977012634f) {
                return 0;            } else {
                return 2;            }
        } else {
            if (features[23] <= 1.0670694708824158f) {
                if (features[8] <= 0.0955120101571083f) {
                    if (features[5] <= -0.019847903749905527f) {
                        return 0;                    } else {
                        if (features[25] <= -0.001153571531176567f) {
                            if (features[14] <= 0.6017177999019623f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[4] <= 0.28963398933410645f) {
                        return 0;                    } else {
                        return 0;                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[4] <= 1.0516996383666992f) {
            if (features[17] <= -0.23004907369613647f) {
                if (features[2] <= -0.5768958628177643f) {
                    return 0;                } else {
                    if (features[24] <= -0.3896516263484955f) {
                        return 0;                    } else {
                        if (features[27] <= -0.31009896099567413f) {
                            return 0;                        } else {
                            if (features[1] <= -0.35150931775569916f) {
                                if (features[27] <= -0.3082491010427475f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                if (features[17] <= -0.3868100792169571f) {
                                    return 0;                                } else {
                                    if (features[5] <= 0.010262371972203255f) {
                                        if (features[17] <= -0.379781037569046f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[12] <= 0.05956655740737915f) {
                                            return 1;                                        } else {
                                            return 2;                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                if (features[22] <= 0.05498840659856796f) {
                    if (features[2] <= -0.5862806886434555f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    if (features[2] <= -0.4530162662267685f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[0] <= -0.37395015358924866f) {
                if (features[4] <= 1.5431914925575256f) {
                    return 1;                } else {
                    return 2;                }
            } else {
                return 2;            }
        }
    }
}

// Tree 12
int predict_tree_12(const float* features) {
    // Max depth: 10
    if (features[3] <= 0.2887963354587555f) {
        if (features[18] <= -0.3157816231250763f) {
            if (features[17] <= -0.3743685930967331f) {
                if (features[21] <= 0.27114030718803406f) {
                    if (features[4] <= 0.30100780725479126f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[5] <= 0.9388452246785164f) {
                        if (features[5] <= -0.004704053630121052f) {
                            return 0;                        } else {
                            if (features[9] <= 0.9006536304950714f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[3] <= -0.2089124098420143f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[21] <= 0.16292253881692886f) {
                    if (features[2] <= 0.6431305706501007f) {
                        if (features[14] <= -0.25950510054826736f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        return 1;                    }
                } else {
                    return 1;                }
            }
        } else {
            if (features[1] <= -0.27031224966049194f) {
                return 1;            } else {
                if (features[15] <= 0.7462623417377472f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[1] <= -0.40162132680416107f) {
            if (features[4] <= 0.4643238000571728f) {
                if (features[10] <= -0.593331903219223f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                return 2;            }
        } else {
            if (features[18] <= -0.20689783245325089f) {
                if (features[21] <= 1.538383960723877f) {
                    if (features[21] <= 0.7160400450229645f) {
                        if (features[20] <= 0.30459776520729065f) {
                            if (features[18] <= -0.39643295109272003f) {
                                if (features[0] <= -0.36849601566791534f) {
                                    if (features[4] <= -0.6944678723812103f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                if (features[3] <= 0.5708710551261902f) {
                                    if (features[7] <= -0.03400217927992344f) {
                                        return 0;                                    } else {
                                        if (features[26] <= -0.31534330546855927f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    if (features[11] <= 0.005323505960404873f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        } else {
                            return 2;                        }
                    } else {
                        if (features[11] <= 0.31238871440291405f) {
                            if (features[24] <= 0.25404342263936996f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[8] <= -0.1541091427206993f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[3] <= 1.8797933459281921f) {
                    return 2;                } else {
                    return 0;                }
            }
        }
    }
}

// Tree 13
int predict_tree_13(const float* features) {
    // Max depth: 9
    if (features[21] <= 0.11981721967458725f) {
        if (features[1] <= -0.35448597371578217f) {
            return 0;        } else {
            if (features[6] <= -0.33655544370412827f) {
                if (features[1] <= 0.8976576328277588f) {
                    if (features[5] <= 0.015687193983467296f) {
                        if (features[22] <= 0.07560441642999649f) {
                            return 2;                        } else {
                            return 2;                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[6] <= -0.9981719255447388f) {
                        return 0;                    } else {
                        if (features[27] <= -0.21834202110767365f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[4] <= -0.4252137243747711f) {
                    if (features[24] <= -0.40676796436309814f) {
                        return 0;                    } else {
                        if (features[17] <= -0.37529483437538147f) {
                            if (features[18] <= -0.38554343581199646f) {
                                return 1;                            } else {
                                if (features[27] <= -0.3006049245595932f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            }
                        } else {
                            if (features[24] <= -0.39187461137771606f) {
                                return 1;                            } else {
                                if (features[14] <= -0.22290381789207458f) {
                                    if (features[5] <= -0.3782097101211548f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 1;                                }
                            }
                        }
                    }
                } else {
                    return 0;                }
            }
        }
    } else {
        if (features[4] <= 1.0517802834510803f) {
            if (features[19] <= -0.2591739520430565f) {
                if (features[10] <= -0.3948909789323807f) {
                    if (features[17] <= -0.58474400639534f) {
                        if (features[21] <= 0.2609497532248497f) {
                            if (features[5] <= -0.017280020751059055f) {
                                if (features[31] <= 0.16302114725112915f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        } else {
                            if (features[2] <= -0.16396384686231613f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[4] <= 0.39997710287570953f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[6] <= -0.9981718957424164f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[0] <= -0.1420585922896862f) {
                    return 1;                } else {
                    return 2;                }
            }
        } else {
            if (features[7] <= 0.34343916177749634f) {
                if (features[17] <= -0.3807973861694336f) {
                    return 1;                } else {
                    return 2;                }
            } else {
                return 2;            }
        }
    }
}

// Tree 14
int predict_tree_14(const float* features) {
    // Max depth: 10
    if (features[1] <= -0.4232726991176605f) {
        if (features[22] <= 0.5337446928024292f) {
            if (features[24] <= -0.022179621271789074f) {
                return 0;            } else {
                if (features[20] <= 0.48105888068675995f) {
                    if (features[17] <= -0.5851553678512573f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    return 1;                }
            }
        } else {
            if (features[21] <= 1.955630898475647f) {
                return 1;            } else {
                if (features[5] <= 1.7115232944488525f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[1] <= -0.15766572952270508f) {
            if (features[4] <= 1.53406423330307f) {
                if (features[4] <= -0.639331579208374f) {
                    return 0;                } else {
                    if (features[20] <= 0.09763405472040176f) {
                        if (features[20] <= -0.5688647031784058f) {
                            if (features[17] <= -0.37916359305381775f) {
                                if (features[12] <= 0.1618916653096676f) {
                                    if (features[5] <= -0.39088742434978485f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                if (features[24] <= -0.3918043524026871f) {
                                    return 1;                                } else {
                                    if (features[1] <= -0.3375915288925171f) {
                                        if (features[22] <= -0.6137079894542694f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[17] <= -0.3747432380914688f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        } else {
                            if (features[18] <= -0.40614575147628784f) {
                                if (features[2] <= -0.09827011357992887f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                if (features[17] <= -0.3571365177631378f) {
                                    if (features[9] <= -0.5815591216087341f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    return 1;                                }
                            }
                        }
                    } else {
                        if (features[11] <= 0.5366389006376266f) {
                            if (features[24] <= 0.2756664752960205f) {
                                if (features[12] <= -0.3007810339331627f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            } else {
                                return 1;                            }
                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[15] <= 0.7462623417377472f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[3] <= 1.8758148550987244f) {
                if (features[18] <= -0.32387498021125793f) {
                    return 1;                } else {
                    if (features[6] <= -1.6597883701324463f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                return 0;            }
        }
    }
}

// Tree 15
int predict_tree_15(const float* features) {
    // Max depth: 10
    if (features[0] <= -0.4495891183614731f) {
        if (features[21] <= 0.4146563410758972f) {
            if (features[13] <= 1.8211926221847534f) {
                return 0;            } else {
                if (features[8] <= -0.04440611135214567f) {
                    return 1;                } else {
                    return 0;                }
            }
        } else {
            if (features[17] <= -0.5370994508266449f) {
                return 1;            } else {
                return 2;            }
        }
    } else {
        if (features[2] <= -0.0034834432881325483f) {
            if (features[18] <= -0.19727405905723572f) {
                if (features[11] <= 0.10871243104338646f) {
                    if (features[17] <= -0.43032942712306976f) {
                        return 0;                    } else {
                        if (features[25] <= -0.38774916529655457f) {
                            return 0;                        } else {
                            if (features[17] <= -0.25057460367679596f) {
                                if (features[23] <= -0.3536574989557266f) {
                                    if (features[13] <= 0.05765428766608238f) {
                                        if (features[27] <= -0.3096165806055069f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 0;                                    }
                                } else {
                                    if (features[24] <= -0.18594586243852973f) {
                                        if (features[17] <= -0.3504778891801834f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[21] <= -0.5403162240982056f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[21] <= 0.0711268000304699f) {
                    if (features[8] <= -0.23669619113206863f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[27] <= -0.1126142106950283f) {
                if (features[24] <= -0.04037108086049557f) {
                    if (features[6] <= 1.2072162628173828f) {
                        if (features[0] <= -0.3745678663253784f) {
                            if (features[30] <= 0.17709434032440186f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            if (features[1] <= 0.08753085881471634f) {
                                return 1;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[28] <= 0.03392469882965088f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                } else {
                    return 2;                }
            } else {
                if (features[22] <= 0.19234761595726013f) {
                    if (features[23] <= -0.03663978073745966f) {
                        return 1;                    } else {
                        if (features[20] <= 0.02250194427324459f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 16
int predict_tree_16(const float* features) {
    // Max depth: 10
    if (features[19] <= -0.4547262042760849f) {
        if (features[1] <= -0.3529857248067856f) {
            if (features[22] <= 0.2767115533351898f) {
                if (features[25] <= -0.030040491372346878f) {
                    if (features[23] <= -0.013237688690423965f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[23] <= -0.021354446187615395f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[8] <= -0.1353985071182251f) {
                    if (features[10] <= -0.4907737970352173f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    if (features[5] <= 0.02815077919512987f) {
                        if (features[1] <= -0.541656106710434f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                }
            }
        } else {
            if (features[0] <= -0.2990276366472244f) {
                if (features[7] <= -0.20901187509298325f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                return 2;            }
        }
    } else {
        if (features[0] <= -0.23959659039974213f) {
            if (features[34] <= -2.0389932096004486f) {
                return 2;            } else {
                if (features[1] <= -0.40189267694950104f) {
                    if (features[20] <= 0.061998991295695305f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    if (features[4] <= -0.6392812132835388f) {
                        return 0;                    } else {
                        if (features[0] <= -0.43021006882190704f) {
                            return 0;                        } else {
                            if (features[18] <= -0.43146465718746185f) {
                                return 0;                            } else {
                                if (features[20] <= 0.08603803627192974f) {
                                    if (features[1] <= -0.3546426594257355f) {
                                        if (features[20] <= -0.6363635957241058f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        if (features[3] <= 0.5708710551261902f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    if (features[19] <= -0.036624975502491f) {
                                        if (features[1] <= -0.3073882609605789f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[22] <= 0.8275328874588013f) {
                                            return 1;                                        } else {
                                            return 2;                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else {
            if (features[22] <= 0.05568571202456951f) {
                if (features[17] <= 0.7010888159275055f) {
                    if (features[31] <= 0.16302114725112915f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    return 0;                }
            } else {
                if (features[5] <= -0.15864861011505127f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 17
int predict_tree_17(const float* features) {
    // Max depth: 9
    if (features[21] <= 0.11981721967458725f) {
        if (features[26] <= -0.31182242929935455f) {
            if (features[21] <= -0.6250118911266327f) {
                if (features[0] <= -0.37661218643188477f) {
                    return 0;                } else {
                    if (features[4] <= -0.6301539540290833f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[4] <= 0.11975212395191193f) {
                    return 0;                } else {
                    if (features[25] <= -0.0521923191845417f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[18] <= -0.39929020404815674f) {
                if (features[17] <= -0.5913839638233185f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[1] <= -0.10399451851844788f) {
                    if (features[9] <= -0.7578341066837311f) {
                        return 0;                    } else {
                        if (features[21] <= -0.5642624795436859f) {
                            if (features[2] <= -0.2202727533876896f) {
                                return 0;                            } else {
                                if (features[23] <= -0.38147303462028503f) {
                                    if (features[3] <= 0.2963554561138153f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[1] <= -0.3452359586954117f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        } else {
                            if (features[10] <= -0.3051108568906784f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    if (features[20] <= 0.04360669665038586f) {
                        if (features[7] <= 0.8492511436343193f) {
                            return 2;                        } else {
                            return 0;                        }
                    } else {
                        if (features[26] <= -0.2263348251581192f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    } else {
        if (features[10] <= -0.14820684492588043f) {
            if (features[25] <= 0.47414152324199677f) {
                if (features[9] <= 0.8893032371997833f) {
                    if (features[9] <= 0.5470653176307678f) {
                        if (features[10] <= -0.4060208797454834f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        return 0;                    }
                } else {
                    if (features[12] <= -0.5758653581142426f) {
                        return 2;                    } else {
                        if (features[10] <= -0.34698256850242615f) {
                            if (features[9] <= 0.93425452709198f) {
                                return 1;                            } else {
                                if (features[2] <= 0.014347713440656662f) {
                                    if (features[33] <= -0.7310653924942017f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 1;                                }
                            }
                        } else {
                            if (features[3] <= 0.34767794609069824f) {
                                return 1;                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                if (features[26] <= -0.3633280247449875f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[10] <= -0.13598725944757462f) {
                return 2;            } else {
                return 2;            }
        }
    }
}

// Tree 18
int predict_tree_18(const float* features) {
    // Max depth: 9
    if (features[20] <= 0.12298395484685898f) {
        if (features[18] <= -0.3947704881429672f) {
            if (features[26] <= -0.029687145724892616f) {
                return 0;            } else {
                if (features[22] <= -0.5764980912208557f) {
                    if (features[17] <= -0.4110521525144577f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[4] <= -0.3520244061946869f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[9] <= -0.572336733341217f) {
                if (features[3] <= -0.4038582742214203f) {
                    if (features[23] <= 0.13157597184181213f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    if (features[10] <= -0.364113450050354f) {
                        return 0;                    } else {
                        if (features[10] <= -0.35785675048828125f) {
                            if (features[18] <= -0.3915596008300781f) {
                                return 1;                            } else {
                                return 0;                            }
                        } else {
                            if (features[13] <= 0.052069392055273056f) {
                                if (features[18] <= -0.3736105114221573f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            } else {
                                return 1;                            }
                        }
                    }
                }
            } else {
                if (features[22] <= 0.06013230420649052f) {
                    if (features[17] <= 0.3732427954673767f) {
                        if (features[10] <= -0.08471555262804031f) {
                            return 0;                        } else {
                            return 2;                        }
                    } else {
                        return 0;                    }
                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[1] <= -0.15344125032424927f) {
            if (features[24] <= 0.2756664752960205f) {
                if (features[17] <= -0.49785609543323517f) {
                    if (features[9] <= 0.8893032371997833f) {
                        if (features[17] <= -0.5892621278762817f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[27] <= 0.19188746809959412f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[10] <= -0.31426680088043213f) {
                        if (features[20] <= 0.6230344772338867f) {
                            if (features[7] <= -0.1362416110932827f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            if (features[11] <= 0.07409276440739632f) {
                                if (features[7] <= -0.12350008636713028f) {
                                    if (features[31] <= 0.16302114725112915f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[9] <= 0.8500505685806274f) {
                            return 1;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                return 2;            }
        } else {
            if (features[31] <= 0.16302114725112915f) {
                return 2;            } else {
                return 2;            }
        }
    }
}

// Tree 19
int predict_tree_19(const float* features) {
    // Max depth: 10
    if (features[10] <= -0.4372512549161911f) {
        if (features[7] <= 0.6593850255012512f) {
            if (features[20] <= 0.4011371284723282f) {
                return 0;            } else {
                if (features[23] <= 1.7594083435833454f) {
                    if (features[4] <= 0.46065424382686615f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[4] <= 0.1584397256374359f) {
                return 0;            } else {
                if (features[9] <= -1.184430181980133f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[10] <= -0.14820684492588043f) {
            if (features[23] <= 0.5896455645561218f) {
                if (features[0] <= -0.43032296001911163f) {
                    return 0;                } else {
                    if (features[9] <= -0.7603023648262024f) {
                        return 0;                    } else {
                        if (features[33] <= -0.7310653924942017f) {
                            if (features[4] <= 0.5986914336681366f) {
                                if (features[22] <= 0.3882199078798294f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            } else {
                                if (features[7] <= 0.26537445187568665f) {
                                    if (features[17] <= -0.3787992149591446f) {
                                        if (features[5] <= 0.01515510119497776f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 2;                                    }
                                } else {
                                    return 1;                                }
                            }
                        } else {
                            if (features[4] <= -0.6393819451332092f) {
                                return 0;                            } else {
                                if (features[18] <= -0.4323759377002716f) {
                                    return 0;                                } else {
                                    if (features[25] <= -0.2980111837387085f) {
                                        if (features[5] <= -0.34911197423934937f) {
                                            return 1;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        if (features[27] <= -0.2231755256652832f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                if (features[29] <= -0.0025959014892578125f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[10] <= 1.0246679186820984f) {
                if (features[12] <= 2.9950283765792847f) {
                    if (features[17] <= 1.0695335268974304f) {
                        if (features[25] <= 0.0012271503219380975f) {
                            if (features[20] <= 0.0016492828726768494f) {
                                return 2;                            } else {
                                return 2;                            }
                        } else {
                            return 2;                        }
                    } else {
                        if (features[22] <= 0.1490641012787819f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    return 2;                }
            } else {
                if (features[3] <= 1.4182888194918633f) {
                    if (features[1] <= 0.9691635370254517f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    return 0;                }
            }
        }
    }
}

// Tree 20
int predict_tree_20(const float* features) {
    // Max depth: 10
    if (features[4] <= 0.12252254039049149f) {
        if (features[7] <= 0.36101575195789337f) {
            if (features[17] <= -0.3714224249124527f) {
                if (features[26] <= 0.2995850667357445f) {
                    return 0;                } else {
                    return 2;                }
            } else {
                if (features[5] <= -0.16142281237989664f) {
                    if (features[19] <= -0.3460773527622223f) {
                        if (features[25] <= -0.29564523696899414f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[17] <= 0.06945679616183043f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[10] <= -0.35469114780426025f) {
                if (features[5] <= -0.47842974960803986f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[5] <= -0.32396553456783295f) {
                    return 1;                } else {
                    if (features[6] <= -1.4392495155334473f) {
                        return 0;                    } else {
                        return 0;                    }
                }
            }
        }
    } else {
        if (features[0] <= -0.23959659039974213f) {
            if (features[22] <= 1.53965425491333f) {
                if (features[17] <= -0.5702398717403412f) {
                    if (features[5] <= 0.043608540669083595f) {
                        if (features[3] <= -0.698266327381134f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[20] <= 0.4602263867855072f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[24] <= -0.10062121599912643f) {
                        return 0;                    } else {
                        if (features[1] <= -0.5193114280700684f) {
                            return 0;                        } else {
                            if (features[12] <= 0.1761169210076332f) {
                                if (features[23] <= -0.09101997688412666f) {
                                    return 0;                                } else {
                                    if (features[17] <= -0.24509385973215103f) {
                                        if (features[14] <= -0.45926283299922943f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                if (features[0] <= -0.35826869308948517f) {
                                    return 2;                                } else {
                                    if (features[2] <= 0.33343154191970825f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                if (features[11] <= -0.6154389306902885f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[17] <= -0.26298747956752777f) {
                return 2;            } else {
                return 2;            }
        }
    }
}

// Tree 21
int predict_tree_21(const float* features) {
    // Max depth: 8
    if (features[0] <= -0.44880789518356323f) {
        if (features[21] <= 0.2762204259634018f) {
            return 0;        } else {
            if (features[22] <= 1.280266523361206f) {
                if (features[26] <= -0.3568793088197708f) {
                    return 0;                } else {
                    if (features[14] <= 0.0023817960172891617f) {
                        return 1;                    } else {
                        if (features[24] <= -0.005332419648766518f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[16] <= 3.1667469069361687f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[33] <= -0.7310653924942017f) {
            if (features[2] <= -0.3113054931163788f) {
                if (features[0] <= -0.3681335598230362f) {
                    if (features[4] <= 0.03660944104194641f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[22] <= 0.08551828749477863f) {
                        return 0;                    } else {
                        if (features[29] <= -0.0025959014892578125f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[15] <= 0.7462623417377472f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[6] <= -0.33655544370412827f) {
                if (features[0] <= -0.20041532441973686f) {
                    if (features[21] <= 0.12548312544822693f) {
                        return 1;                    } else {
                        return 1;                    }
                } else {
                    if (features[3] <= 1.808180570602417f) {
                        if (features[1] <= -0.1404702588915825f) {
                            return 2;                        } else {
                            return 2;                        }
                    } else {
                        return 0;                    }
                }
            } else {
                if (features[10] <= -0.3892125189304352f) {
                    if (features[4] <= -0.6450436413288116f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[17] <= -0.40486258268356323f) {
                        return 0;                    } else {
                        if (features[1] <= 0.09978034347295761f) {
                            if (features[0] <= -0.3758653551340103f) {
                                if (features[25] <= -0.11852660216391087f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            } else {
                                return 1;                            }
                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    }
}

// Tree 22
int predict_tree_22(const float* features) {
    // Max depth: 7
    if (features[4] <= 0.12223038822412491f) {
        if (features[18] <= -0.3978624641895294f) {
            if (features[1] <= -0.3512137532234192f) {
                return 0;            } else {
                if (features[12] <= 0.0630481205880642f) {
                    return 0;                } else {
                    return 1;                }
            }
        } else {
            if (features[5] <= -0.3180304169654846f) {
                if (features[0] <= -0.3758691996335983f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                if (features[7] <= 0.1425341907888651f) {
                    return 2;                } else {
                    if (features[31] <= 0.16302114725112915f) {
                        return 0;                    } else {
                        return 0;                    }
                }
            }
        }
    } else {
        if (features[17] <= -0.23100721091032028f) {
            if (features[22] <= 1.5393915176391602f) {
                if (features[0] <= -0.4531653821468353f) {
                    if (features[4] <= 0.46065424382686615f) {
                        if (features[26] <= -0.3615015149116516f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[1] <= -0.29966413974761963f) {
                        if (features[10] <= -0.3557049334049225f) {
                            return 1;                        } else {
                            if (features[21] <= 0.4753754734992981f) {
                                return 1;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[8] <= -0.03486538678407669f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[27] <= -0.2943497598171234f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[2] <= -0.4530162662267685f) {
                return 2;            } else {
                return 2;            }
        }
    }
}

// Tree 23
int predict_tree_23(const float* features) {
    // Max depth: 10
    if (features[21] <= 0.11982731893658638f) {
        if (features[1] <= -0.3493572473526001f) {
            return 0;        } else {
            if (features[23] <= -0.29870347678661346f) {
                if (features[2] <= -0.9898279048502445f) {
                    return 0;                } else {
                    if (features[0] <= -0.3758653551340103f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[3] <= 1.8042020797729492f) {
                    if (features[8] <= 0.11184482276439667f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    return 0;                }
            }
        }
    } else {
        if (features[2] <= -0.3113054931163788f) {
            if (features[17] <= -0.37945929169654846f) {
                if (features[22] <= 0.5510560423135757f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                return 2;            }
        } else {
            if (features[20] <= 0.1530025228857994f) {
                if (features[9] <= 0.21694714576005936f) {
                    if (features[28] <= 0.03392469882965088f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    if (features[19] <= -0.43881407380104065f) {
                        if (features[7] <= -1.026792973279953f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                }
            } else {
                if (features[21] <= 0.28046227991580963f) {
                    if (features[10] <= -0.18635578453540802f) {
                        if (features[26] <= -0.35274699330329895f) {
                            return 0;                        } else {
                            if (features[12] <= -0.0028613691683858633f) {
                                return 0;                            } else {
                                if (features[27] <= -0.07958366256207228f) {
                                    if (features[30] <= 0.17709434032440186f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    if (features[13] <= -0.2881796658039093f) {
                                        return 0;                                    } else {
                                        if (features[21] <= 0.19857429713010788f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[6] <= 0.8764080302789807f) {
                        if (features[13] <= -0.6245622336864471f) {
                            if (features[18] <= -0.5055416226387024f) {
                                return 1;                            } else {
                                return 2;                            }
                        } else {
                            if (features[10] <= -0.5263391882181168f) {
                                return 0;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[25] <= -0.001153571531176567f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                }
            }
        }
    }
}

// Tree 24
int predict_tree_24(const float* features) {
    // Max depth: 9
    if (features[0] <= -0.4495891183614731f) {
        if (features[20] <= 0.469775453209877f) {
            return 0;        } else {
            if (features[21] <= 1.087798148393631f) {
                return 1;            } else {
                if (features[27] <= -0.27131715416908264f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[9] <= 2.0291956663131714f) {
            if (features[23] <= -0.29867100715637207f) {
                if (features[17] <= -0.3802667409181595f) {
                    if (features[8] <= -0.2382049486041069f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[3] <= 0.5549571514129639f) {
                        if (features[14] <= 0.22327853739261627f) {
                            if (features[17] <= -0.3724249601364136f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            if (features[10] <= -0.3528010994195938f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[30] <= 0.17709434032440186f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[10] <= -0.14820684492588043f) {
                    if (features[5] <= 1.6161034405231476f) {
                        if (features[5] <= -0.13885965943336487f) {
                            return 0;                        } else {
                            if (features[2] <= -0.38919949531555176f) {
                                return 1;                            } else {
                                if (features[10] <= -0.20661623775959015f) {
                                    if (features[11] <= 0.16159724444150925f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 1;                                }
                            }
                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[21] <= 0.05533094331622124f) {
                        if (features[17] <= 0.9990517497062683f) {
                            if (features[21] <= -0.06515789881814271f) {
                                return 0;                            } else {
                                return 2;                            }
                        } else {
                            return 0;                        }
                    } else {
                        if (features[17] <= -0.14773625135421753f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[19] <= 0.06809551903279498f) {
                if (features[11] <= 0.15431782230734825f) {
                    return 1;                } else {
                    return 2;                }
            } else {
                return 2;            }
        }
    }
}

// Tree 25
int predict_tree_25(const float* features) {
    // Max depth: 10
    if (features[1] <= -0.4233284592628479f) {
        if (features[5] <= -0.004704053630121052f) {
            return 0;        } else {
            if (features[9] <= 0.8916953206062317f) {
                if (features[23] <= 1.8412025920115411f) {
                    return 0;                } else {
                    return 2;                }
            } else {
                if (features[8] <= -0.07990042865276337f) {
                    if (features[23] <= 1.9829274415969849f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    if (features[27] <= 0.18769938126206398f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            }
        }
    } else {
        if (features[8] <= -0.24036648869514465f) {
            return 2;        } else {
            if (features[19] <= 0.00714016129495576f) {
                if (features[21] <= 1.5400201082229614f) {
                    if (features[18] <= -0.43015874922275543f) {
                        if (features[7] <= 0.40844370424747467f) {
                            if (features[8] <= -0.19948329031467438f) {
                                return 2;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[24] <= -0.3907344788312912f) {
                            return 0;                        } else {
                            if (features[0] <= -0.2271149605512619f) {
                                if (features[0] <= -0.43021006882190704f) {
                                    return 0;                                } else {
                                    if (features[22] <= -0.42345456779003143f) {
                                        if (features[5] <= -0.3526346981525421f) {
                                            return 1;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        if (features[12] <= 0.261271096765995f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            } else {
                                if (features[5] <= 0.14019320905208588f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                } else {
                    if (features[4] <= 1.3969488143920898f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[26] <= 0.37463369965553284f) {
                    if (features[20] <= 0.06846250593662262f) {
                        return 0;                    } else {
                        if (features[7] <= -0.6641383767127991f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[17] <= -0.061661574989557266f) {
                        if (features[20] <= 0.7590809911489487f) {
                            return 1;                        } else {
                            return 2;                        }
                    } else {
                        if (features[21] <= 0.0028632525354623795f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    }
}

// Tree 26
int predict_tree_26(const float* features) {
    // Max depth: 10
    if (features[18] <= -0.20689783245325089f) {
        if (features[18] <= -0.43003541231155396f) {
            if (features[33] <= -0.7310653924942017f) {
                if (features[24] <= 0.26234759390354156f) {
                    if (features[4] <= 0.2794993072748184f) {
                        return 0;                    } else {
                        if (features[27] <= 0.19188746809959412f) {
                            return 1;                        } else {
                            if (features[5] <= 0.04275062680244446f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    return 2;                }
            } else {
                if (features[16] <= 3.1667469069361687f) {
                    return 0;                } else {
                    return 2;                }
            }
        } else {
            if (features[4] <= 1.53406423330307f) {
                if (features[17] <= -0.43021655082702637f) {
                    if (features[21] <= -0.19593828916549683f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    if (features[22] <= -0.6403774321079254f) {
                        return 0;                    } else {
                        if (features[10] <= -0.1354660429060459f) {
                            if (features[11] <= 0.47158950567245483f) {
                                if (features[6] <= 0.5455998182296753f) {
                                    if (features[17] <= -0.23004907369613647f) {
                                        if (features[10] <= -0.41532109677791595f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 2;                                    }
                                } else {
                                    if (features[2] <= -0.08888529241085052f) {
                                        return 0;                                    } else {
                                        if (features[26] <= -0.3562765121459961f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            } else {
                                return 2;                            }
                        } else {
                            if (features[2] <= -0.3525986969470978f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                if (features[13] <= -2.8920300006866455f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[3] <= 1.8758148550987244f) {
            if (features[10] <= -0.32082274556159973f) {
                return 1;            } else {
                if (features[9] <= -0.7127779126167297f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            return 0;        }
    }
}

// Tree 27
int predict_tree_27(const float* features) {
    // Max depth: 9
    if (features[5] <= -0.13076816499233246f) {
        if (features[26] <= -0.3167443722486496f) {
            if (features[20] <= -0.6242029368877411f) {
                if (features[0] <= -0.37597908079624176f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                return 0;            }
        } else {
            if (features[0] <= -0.37561240792274475f) {
                if (features[0] <= -0.5962145626544952f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[1] <= -0.11337940394878387f) {
                    if (features[21] <= -0.6390100121498108f) {
                        return 1;                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[0] <= -0.2316778227686882f) {
            if (features[25] <= 1.0899469703435898f) {
                if (features[17] <= -0.4432007074356079f) {
                    if (features[27] <= 0.3373500257730484f) {
                        return 0;                    } else {
                        if (features[14] <= 0.6302593052387238f) {
                            if (features[23] <= -0.0475153848528862f) {
                                return 0;                            } else {
                                if (features[5] <= 0.019561262102797627f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        } else {
                            if (features[19] <= -0.581810474395752f) {
                                return 0;                            } else {
                                return 0;                            }
                        }
                    }
                } else {
                    if (features[14] <= 2.134594440460205f) {
                        if (features[10] <= -0.31340712308883667f) {
                            if (features[15] <= 0.7462623417377472f) {
                                if (features[12] <= -0.06337831914424896f) {
                                    return 1;                                } else {
                                    if (features[23] <= -0.08005394041538239f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                return 1;                            }
                        } else {
                            if (features[7] <= -0.2228861302137375f) {
                                return 1;                            } else {
                                return 2;                            }
                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[21] <= 1.5768131613731384f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[9] <= -0.14302415400743484f) {
                if (features[2] <= -0.6425895914435387f) {
                    if (features[9] <= -0.28634798526763916f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    return 2;                }
            } else {
                if (features[9] <= -0.10544820502400398f) {
                    if (features[6] <= -0.9981719255447388f) {
                        return 0;                    } else {
                        if (features[29] <= -0.0025959014892578125f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[21] <= 0.062188608571887016f) {
                        if (features[7] <= 0.9682264849543571f) {
                            return 2;                        } else {
                            return 0;                        }
                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 28
int predict_tree_28(const float* features) {
    // Max depth: 9
    if (features[5] <= -0.1309334635734558f) {
        if (features[17] <= -0.3803262859582901f) {
            if (features[10] <= -0.36049826443195343f) {
                return 0;            } else {
                return 1;            }
        } else {
            if (features[0] <= -0.1706392616033554f) {
                if (features[1] <= -0.3375915288925171f) {
                    if (features[24] <= -0.3524377793073654f) {
                        if (features[18] <= -0.3784315288066864f) {
                            return 1;                        } else {
                            if (features[31] <= 0.16302114725112915f) {
                                return 0;                            } else {
                                return 0;                            }
                        }
                    } else {
                        return 0;                    }
                } else {
                    if (features[4] <= -0.5044979751110077f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[4] <= 1.073973834514618f) {
            if (features[21] <= 0.15943815559148788f) {
                if (features[4] <= 0.12252254039049149f) {
                    if (features[25] <= 0.24216776341199875f) {
                        if (features[19] <= 3.0283578634262085f) {
                            if (features[13] <= 0.21102412790060043f) {
                                if (features[22] <= 0.139999121427536f) {
                                    if (features[17] <= -0.600971132516861f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    if (features[21] <= 0.12937148660421371f) {
                                        return 2;                                    } else {
                                        return 0;                                    }
                                }
                            } else {
                                if (features[7] <= 0.0649530477821827f) {
                                    if (features[0] <= -0.2021785005927086f) {
                                        return 0;                                    } else {
                                        return 2;                                    }
                                } else {
                                    return 0;                                }
                            }
                        } else {
                            return 2;                        }
                    } else {
                        if (features[22] <= 0.046519672498106956f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[0] <= -0.09973900020122528f) {
                        if (features[10] <= -0.4275110512971878f) {
                            if (features[22] <= -0.13458791747689247f) {
                                return 1;                            } else {
                                if (features[19] <= -0.588163286447525f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[31] <= 0.16302114725112915f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[17] <= -0.22465001046657562f) {
                    if (features[0] <= -0.5286632180213928f) {
                        if (features[25] <= -0.09964114427566528f) {
                            return 1;                        } else {
                            if (features[20] <= 0.15607798099517822f) {
                                return 0;                            } else {
                                return 0;                            }
                        }
                    } else {
                        if (features[27] <= 0.4043697416782379f) {
                            if (features[22] <= 0.44204385578632355f) {
                                return 0;                            } else {
                                return 2;                            }
                        } else {
                            if (features[23] <= 0.05398196820169687f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    if (features[31] <= 0.16302114725112915f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[21] <= 1.5285267233848572f) {
                if (features[23] <= -0.00019629720191005617f) {
                    return 2;                } else {
                    if (features[1] <= -0.3477524369955063f) {
                        return 1;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[33] <= -0.7310653924942017f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 29
int predict_tree_29(const float* features) {
    // Max depth: 10
    if (features[17] <= -0.4506124407052994f) {
        if (features[4] <= 0.4589315503835678f) {
            return 0;        } else {
            if (features[19] <= -0.5421547889709473f) {
                return 1;            } else {
                return 2;            }
        }
    } else {
        if (features[2] <= -0.0016064795199781656f) {
            if (features[3] <= 0.30232319235801697f) {
                if (features[0] <= -0.29020924866199493f) {
                    return 0;                } else {
                    return 2;                }
            } else {
                if (features[10] <= -0.21241428703069687f) {
                    if (features[0] <= -0.4316937178373337f) {
                        return 0;                    } else {
                        if (features[6] <= 0.6558692352846265f) {
                            if (features[13] <= 2.7106947898864746f) {
                                if (features[4] <= -0.5951157510280609f) {
                                    return 0;                                } else {
                                    if (features[4] <= 0.5986914336681366f) {
                                        if (features[19] <= -0.411087304353714f) {
                                            return 1;                                        } else {
                                            return 2;                                        }
                                    } else {
                                        if (features[0] <= -0.367722287774086f) {
                                            return 1;                                        } else {
                                            return 2;                                        }
                                    }
                                }
                            } else {
                                return 1;                            }
                        } else {
                            if (features[13] <= 0.06860927492380142f) {
                                if (features[1] <= -0.3429037630558014f) {
                                    if (features[9] <= -0.764171689748764f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    if (features[10] <= -0.35785675048828125f) {
                                        return 0;                                    } else {
                                        if (features[17] <= -0.3774107098579407f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            } else {
                                return 0;                            }
                        }
                    }
                } else {
                    if (features[1] <= 0.5908983796834946f) {
                        if (features[3] <= 0.6711289584636688f) {
                            return 2;                        } else {
                            return 2;                        }
                    } else {
                        return 0;                    }
                }
            }
        } else {
            if (features[21] <= 0.16705328971147537f) {
                if (features[25] <= -0.030388778541237116f) {
                    if (features[2] <= 0.26773782074451447f) {
                        return 0;                    } else {
                        if (features[17] <= -0.3613695800304413f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                } else {
                    return 2;                }
            } else {
                if (features[11] <= -10.64769172668457f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 30
int predict_tree_30(const float* features) {
    // Max depth: 10
    if (features[1] <= -0.42361240088939667f) {
        if (features[4] <= 0.46065424382686615f) {
            return 0;        } else {
            if (features[21] <= 1.2562401592731476f) {
                return 1;            } else {
                return 2;            }
        }
    } else {
        if (features[3] <= 0.3035167455673218f) {
            if (features[4] <= 0.16720178723335266f) {
                if (features[27] <= -0.13709302246570587f) {
                    if (features[1] <= -0.10399451851844788f) {
                        if (features[19] <= -0.4144052118062973f) {
                            if (features[10] <= -0.3429689258337021f) {
                                if (features[28] <= -0.4683038666844368f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        } else {
                            if (features[17] <= -0.3611677289009094f) {
                                return 0;                            } else {
                                if (features[9] <= 0.005499526858329773f) {
                                    if (features[13] <= 0.004812578903511167f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 1;                                }
                            }
                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[27] <= -0.13659577071666718f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[17] <= -0.26600807905197144f) {
                    return 1;                } else {
                    if (features[5] <= -0.1547539010643959f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[17] <= -0.29182904958724976f) {
                if (features[21] <= 1.537333607673645f) {
                    if (features[10] <= -0.41872814297676086f) {
                        return 0;                    } else {
                        if (features[2] <= -1.139984980225563f) {
                            return 2;                        } else {
                            if (features[24] <= -0.35942788422107697f) {
                                if (features[25] <= -0.3576107770204544f) {
                                    if (features[17] <= -0.3812497556209564f) {
                                        return 0;                                    } else {
                                        if (features[17] <= -0.3735552728176117f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    if (features[24] <= -0.3629719316959381f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                }
                            } else {
                                if (features[9] <= -0.7430879175662994f) {
                                    return 0;                                } else {
                                    if (features[26] <= -0.21383657306432724f) {
                                        if (features[19] <= -0.3868201673030853f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[29] <= -0.0025959014892578125f) {
                                            return 2;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        }
                    }
                } else {
                    if (features[19] <= -0.45796050131320953f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[7] <= 1.5305007100105286f) {
                    return 2;                } else {
                    return 0;                }
            }
        }
    }
}

// Tree 31
int predict_tree_31(const float* features) {
    // Max depth: 10
    if (features[1] <= -0.4236069470643997f) {
        if (features[6] <= -1.439249575138092f) {
            if (features[23] <= 0.8726251274347305f) {
                if (features[5] <= 0.0338671812787652f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                return 2;            }
        } else {
            if (features[5] <= -0.04046553838998079f) {
                return 0;            } else {
                if (features[8] <= 0.07166363298892975f) {
                    return 1;                } else {
                    return 0;                }
            }
        }
    } else {
        if (features[1] <= -0.1487656682729721f) {
            if (features[23] <= 0.5896455645561218f) {
                if (features[20] <= -0.6398020684719086f) {
                    return 0;                } else {
                    if (features[19] <= -0.4300471842288971f) {
                        if (features[26] <= -0.14487962424755096f) {
                            if (features[31] <= 0.16302114725112915f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            if (features[3] <= 0.2963554635643959f) {
                                if (features[18] <= -0.5432332456111908f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                if (features[10] <= -0.36594298481941223f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            }
                        }
                    } else {
                        if (features[11] <= 0.4791518300771713f) {
                            if (features[1] <= -0.4015910476446152f) {
                                return 0;                            } else {
                                if (features[9] <= 0.009067714214324951f) {
                                    if (features[0] <= -0.37574799358844757f) {
                                        if (features[26] <= -0.35848699510097504f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[26] <= -0.22560621052980423f) {
                                        if (features[26] <= -0.36318765580654144f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[26] <= -0.07307934202253819f) {
                                            return 2;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[17] <= -0.4510813504457474f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[7] <= 1.917330026626587f) {
                if (features[10] <= -0.13042651116847992f) {
                    return 1;                } else {
                    if (features[2] <= -1.01516692340374f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[12] <= -1.1127097010612488f) {
                    return 2;                } else {
                    if (features[9] <= 0.3353401683270931f) {
                        return 0;                    } else {
                        if (features[23] <= -0.13225582987070084f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    }
}

// Tree 32
int predict_tree_32(const float* features) {
    // Max depth: 8
    if (features[20] <= 0.1218646913766861f) {
        if (features[10] <= -0.3602023273706436f) {
            return 0;        } else {
            if (features[23] <= -0.29870347678661346f) {
                if (features[10] <= -0.35496382415294647f) {
                    if (features[4] <= -0.6071645319461823f) {
                        if (features[25] <= -0.3808597922325134f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[11] <= -0.17938543856143951f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[3] <= 1.8042020797729492f) {
                    if (features[17] <= -0.17243972001597285f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    return 0;                }
            }
        }
    } else {
        if (features[10] <= -0.2071150615811348f) {
            if (features[5] <= 1.2099989354610443f) {
                if (features[6] <= -1.6597883701324463f) {
                    if (features[4] <= 0.2804664373397827f) {
                        if (features[5] <= -0.09380777552723885f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[23] <= 0.045210414566099644f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[18] <= -0.47449998557567596f) {
                        if (features[3] <= -0.8414918482303619f) {
                            return 1;                        } else {
                            if (features[2] <= -0.16396384686231613f) {
                                return 0;                            } else {
                                return 0;                            }
                        }
                    } else {
                        if (features[17] <= -0.24509385973215103f) {
                            if (features[10] <= -0.34609441459178925f) {
                                return 1;                            } else {
                                if (features[18] <= -0.3690183013677597f) {
                                    return 2;                                } else {
                                    return 1;                                }
                            }
                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[23] <= 1.8654807806015015f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[0] <= -0.21337823569774628f) {
                return 2;            } else {
                return 2;            }
        }
    }
}

// Tree 33
int predict_tree_33(const float* features) {
    // Max depth: 10
    if (features[4] <= 0.12167630344629288f) {
        if (features[23] <= -0.35942813754081726f) {
            if (features[9] <= -0.7627576887607574f) {
                return 0;            } else {
                if (features[0] <= -0.3759319484233856f) {
                    if (features[10] <= -0.580145925283432f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    return 1;                }
            }
        } else {
            if (features[25] <= 0.33463168144226074f) {
                if (features[21] <= -0.6212447285652161f) {
                    if (features[12] <= -0.033270563930273056f) {
                        return 1;                    } else {
                        if (features[23] <= -0.3571787327528f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[26] <= -0.05254790000617504f) {
                        if (features[22] <= 0.139999121427536f) {
                            return 0;                        } else {
                            if (features[22] <= 0.14222241193056107f) {
                                return 2;                            } else {
                                return 0;                            }
                        }
                    } else {
                        if (features[1] <= 0.9021007716655731f) {
                            if (features[13] <= -0.08454575762152672f) {
                                return 1;                            } else {
                                if (features[24] <= -0.08303502481430769f) {
                                    return 0;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[26] <= -0.0464668907225132f) {
                                return 0;                            } else {
                                return 0;                            }
                        }
                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[22] <= 1.0556631684303284f) {
            if (features[6] <= -1.6597883701324463f) {
                if (features[4] <= 0.2927066385746002f) {
                    if (features[30] <= 0.17709434032440186f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[5] <= 0.0338671812787652f) {
                        return 0;                    } else {
                        if (features[19] <= -0.5838122367858887f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[10] <= -0.13132085651159286f) {
                    if (features[10] <= -0.5417011380195618f) {
                        return 0;                    } else {
                        if (features[8] <= -0.1922936588525772f) {
                            if (features[0] <= -0.36411112546920776f) {
                                return 0;                            } else {
                                return 2;                            }
                        } else {
                            if (features[13] <= -0.20999111980199814f) {
                                if (features[4] <= 0.4081674739718437f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            } else {
                                if (features[11] <= 0.02323321718722582f) {
                                    if (features[3] <= -0.7738575637340546f) {
                                        return 1;                                    } else {
                                        if (features[14] <= -0.19288787990808487f) {
                                            return 2;                                        } else {
                                            return 0;                                        }
                                    }
                                } else {
                                    return 1;                                }
                            }
                        }
                    }
                } else {
                    if (features[33] <= -0.7310653924942017f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[7] <= 0.3482196033000946f) {
                if (features[18] <= 0.1259337216615677f) {
                    if (features[10] <= -0.3286314904689789f) {
                        return 1;                    } else {
                        return 2;                    }
                } else {
                    return 2;                }
            } else {
                if (features[13] <= -10.190200328826904f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 34
int predict_tree_34(const float* features) {
    // Max depth: 10
    if (features[17] <= -0.4498710483312607f) {
        if (features[25] <= 0.07900022342801094f) {
            if (features[4] <= 0.49707262217998505f) {
                return 0;            } else {
                return 1;            }
        } else {
            if (features[19] <= -0.5052581429481506f) {
                return 1;            } else {
                if (features[29] <= -0.0025959014892578125f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[10] <= -0.14812666922807693f) {
            if (features[10] <= -0.4145937114953995f) {
                if (features[26] <= -0.32279661297798157f) {
                    if (features[3] <= 0.4714089035987854f) {
                        return 0;                    } else {
                        if (features[1] <= -0.4235561043024063f) {
                            if (features[2] <= -0.2671968415379524f) {
                                return 0;                            } else {
                                return 2;                            }
                        } else {
                            if (features[14] <= -6.7835373878479f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[20] <= -0.43214261531829834f) {
                        if (features[1] <= -0.4334830641746521f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[4] <= 1.5368548035621643f) {
                    if (features[24] <= -0.40112724900245667f) {
                        return 0;                    } else {
                        if (features[4] <= -0.6389487683773041f) {
                            return 0;                        } else {
                            if (features[23] <= -0.11616252362728119f) {
                                if (features[0] <= -0.37574799358844757f) {
                                    if (features[24] <= -0.3884277790784836f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                if (features[12] <= -0.3007810339331627f) {
                                    return 1;                                } else {
                                    if (features[15] <= 0.7462623417377472f) {
                                        if (features[19] <= -0.2621280178427696f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[29] <= -0.0025959014892578125f) {
                                            return 2;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        }
                    }
                } else {
                    if (features[15] <= 0.7462623417377472f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[4] <= 0.05423935875296593f) {
                if (features[5] <= 0.01512462506070733f) {
                    return 2;                } else {
                    return 0;                }
            } else {
                if (features[20] <= 0.051451653242111206f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 35
int predict_tree_35(const float* features) {
    // Max depth: 10
    if (features[23] <= -0.12822941690683365f) {
        if (features[17] <= -0.39827775955200195f) {
            return 0;        } else {
            if (features[20] <= -0.5620180070400238f) {
                if (features[19] <= -0.36411765217781067f) {
                    if (features[1] <= -0.35395754873752594f) {
                        return 0;                    } else {
                        if (features[17] <= -0.37529483437538147f) {
                            if (features[7] <= 0.42499858140945435f) {
                                if (features[22] <= -0.6273711323738098f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[19] <= -0.358862042427063f) {
                        return 1;                    } else {
                        if (features[4] <= -0.567532479763031f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[9] <= -0.32604750990867615f) {
                    return 0;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[0] <= -0.32047267258167267f) {
            if (features[5] <= 0.9093040153384209f) {
                if (features[4] <= 0.12307662516832352f) {
                    return 0;                } else {
                    if (features[5] <= -0.09103783220052719f) {
                        return 0;                    } else {
                        if (features[10] <= -0.5403608679771423f) {
                            if (features[33] <= -0.7310653924942017f) {
                                if (features[9] <= 0.8893032371997833f) {
                                    return 0;                                } else {
                                    if (features[2] <= 0.05188698694109917f) {
                                        return 1;                                    } else {
                                        return 0;                                    }
                                }
                            } else {
                                if (features[9] <= 0.399714395403862f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            }
                        } else {
                            if (features[21] <= 0.1068795658648014f) {
                                return 0;                            } else {
                                if (features[17] <= -0.3245689421892166f) {
                                    if (features[22] <= 0.1115308403968811f) {
                                        return 0;                                    } else {
                                        if (features[12] <= 0.14147628843784332f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    return 1;                                }
                            }
                        }
                    }
                }
            } else {
                if (features[27] <= -0.2791447341442108f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[27] <= -0.17603368312120438f) {
                if (features[21] <= 0.05533094331622124f) {
                    return 0;                } else {
                    return 2;                }
            } else {
                if (features[18] <= -0.3802875578403473f) {
                    return 1;                } else {
                    if (features[2] <= -0.968242809176445f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 36
int predict_tree_36(const float* features) {
    // Max depth: 10
    if (features[17] <= -0.45113205909729004f) {
        if (features[20] <= 0.3998766988515854f) {
            return 0;        } else {
            if (features[8] <= -0.11186705902218819f) {
                if (features[26] <= -0.3630220293998718f) {
                    return 2;                } else {
                    return 2;                }
            } else {
                return 1;            }
        }
    } else {
        if (features[17] <= -0.22705212235450745f) {
            if (features[7] <= 0.6562289595603943f) {
                if (features[5] <= -0.13885965943336487f) {
                    if (features[18] <= -0.3947704881429672f) {
                        if (features[0] <= -0.3745678663253784f) {
                            if (features[6] <= -1.1084413453936577f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[1] <= -0.3546426594257355f) {
                            return 0;                        } else {
                            if (features[21] <= -0.5642624795436859f) {
                                if (features[9] <= -0.763979434967041f) {
                                    return 0;                                } else {
                                    if (features[17] <= -0.3807806670665741f) {
                                        return 0;                                    } else {
                                        if (features[10] <= -0.35785675048828125f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    if (features[8] <= -0.19878696650266647f) {
                        return 2;                    } else {
                        if (features[18] <= -0.38945381343364716f) {
                            return 1;                        } else {
                            if (features[21] <= 1.2372527718544006f) {
                                if (features[26] <= -0.2684931606054306f) {
                                    return 1;                                } else {
                                    if (features[25] <= 0.06288823299109936f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                if (features[10] <= -0.3652622699737549f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                }
            } else {
                if (features[7] <= 0.7752752900123596f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[22] <= 0.05498840659856796f) {
                if (features[8] <= -0.2419508844614029f) {
                    return 2;                } else {
                    if (features[0] <= 0.9620674252510071f) {
                        return 2;                    } else {
                        return 0;                    }
                }
            } else {
                if (features[8] <= -0.3903472125530243f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 37
int predict_tree_37(const float* features) {
    // Max depth: 6
    if (features[17] <= -0.4491848349571228f) {
        if (features[20] <= 0.4011371284723282f) {
            return 0;        } else {
            if (features[8] <= -0.09179993718862534f) {
                if (features[24] <= 1.713775634765625f) {
                    return 2;                } else {
                    return 2;                }
            } else {
                if (features[4] <= 0.46065424382686615f) {
                    return 0;                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[20] <= 1.0608497262001038f) {
            if (features[24] <= -0.2986769825220108f) {
                if (features[24] <= -0.3524780571460724f) {
                    if (features[0] <= -0.3758653551340103f) {
                        if (features[5] <= -0.42732861638069153f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[18] <= -0.3777129650115967f) {
                        if (features[29] <= -0.5031495066359639f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                }
            } else {
                if (features[0] <= -0.2124960944056511f) {
                    if (features[23] <= -0.10315441712737083f) {
                        return 0;                    } else {
                        if (features[14] <= 0.47182078659534454f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[3] <= 1.8996857702732086f) {
                        if (features[21] <= 0.008195868460461497f) {
                            return 2;                        } else {
                            return 2;                        }
                    } else {
                        return 0;                    }
                }
            }
        } else {
            if (features[7] <= 0.3482196033000946f) {
                if (features[19] <= 0.07130791881354526f) {
                    if (features[13] <= 1.8364436626434326f) {
                        if (features[12] <= 0.2496650032699108f) {
                            return 1;                        } else {
                            return 2;                        }
                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            } else {
                if (features[31] <= 0.16302114725112915f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 38
int predict_tree_38(const float* features) {
    // Max depth: 10
    if (features[0] <= -0.4511675536632538f) {
        if (features[20] <= 0.3998766988515854f) {
            return 0;        } else {
            if (features[17] <= -0.5424358546733856f) {
                if (features[23] <= 0.03949646418914199f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                return 2;            }
        }
    } else {
        if (features[0] <= -0.21553847193717957f) {
            if (features[7] <= 0.701331615447998f) {
                if (features[19] <= -0.42991192638874054f) {
                    if (features[1] <= -0.356849804520607f) {
                        if (features[27] <= -0.31845274567604065f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[9] <= -0.6337976455688477f) {
                            return 1;                        } else {
                            if (features[1] <= -0.2221548780798912f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    if (features[1] <= -0.40189267694950104f) {
                        return 0;                    } else {
                        if (features[11] <= 0.47158950567245483f) {
                            if (features[21] <= -0.6407673358917236f) {
                                return 0;                            } else {
                                if (features[22] <= -0.42345456779003143f) {
                                    if (features[1] <= -0.3546426594257355f) {
                                        if (features[21] <= -0.6366870999336243f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        if (features[27] <= -0.25330276042222977f) {
                                            return 1;                                        } else {
                                            return 0;                                        }
                                    }
                                } else {
                                    if (features[12] <= 0.0783008374273777f) {
                                        if (features[19] <= -0.06398009619442746f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 1;                                    }
                                }
                            }
                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[28] <= 0.03392469882965088f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[3] <= 1.8758148550987244f) {
                if (features[28] <= -0.4683038666844368f) {
                    return 2;                } else {
                    return 2;                }
            } else {
                return 0;            }
        }
    }
}

// Tree 39
int predict_tree_39(const float* features) {
    // Max depth: 10
    if (features[20] <= 0.12241927906870842f) {
        if (features[17] <= -0.3802667409181595f) {
            return 0;        } else {
            if (features[20] <= -0.28114229440689087f) {
                if (features[13] <= 0.07440897449851036f) {
                    if (features[23] <= -0.35829006135463715f) {
                        if (features[0] <= -0.3758653551340103f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        if (features[4] <= -0.6192334592342377f) {
                            if (features[18] <= -0.37097637355327606f) {
                                return 0;                            } else {
                                return 1;                            }
                        } else {
                            return 1;                        }
                    }
                } else {
                    return 0;                }
            } else {
                if (features[21] <= 0.05462396703660488f) {
                    if (features[6] <= -0.9981719255447388f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    if (features[9] <= -0.5967603921890259f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[10] <= -0.2071150615811348f) {
            if (features[20] <= 1.544685959815979f) {
                if (features[1] <= -0.40620122849941254f) {
                    if (features[23] <= -0.02270204108208418f) {
                        if (features[11] <= -0.03259775880724192f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[14] <= -0.47282084822654724f) {
                            return 0;                        } else {
                            if (features[19] <= -0.5777615904808044f) {
                                if (features[27] <= 0.025372730568051338f) {
                                    return 0;                                } else {
                                    if (features[4] <= 0.41772791743278503f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[26] <= 1.348282814025879f) {
                        if (features[13] <= 1.1892401576042175f) {
                            if (features[3] <= 0.6615805923938751f) {
                                if (features[26] <= -0.2646472454071045f) {
                                    return 1;                                } else {
                                    if (features[30] <= 0.17709434032440186f) {
                                        return 1;                                    } else {
                                        if (features[13] <= -0.16574155539274216f) {
                                            return 2;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            } else {
                                return 1;                            }
                        } else {
                            return 1;                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[16] <= 3.1667469069361687f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[13] <= -6.300750017166138f) {
                return 2;            } else {
                return 2;            }
        }
    }
}

// Tree 40
int predict_tree_40(const float* features) {
    // Max depth: 7
    if (features[21] <= 0.11981721967458725f) {
        if (features[0] <= -0.3758653551340103f) {
            return 0;        } else {
            if (features[10] <= -0.14931774325668812f) {
                return 1;            } else {
                if (features[4] <= 0.06160362996160984f) {
                    if (features[2] <= -1.4590688347816467f) {
                        if (features[14] <= 1.095971792936325f) {
                            return 0;                        } else {
                            return 2;                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[33] <= -0.7310653924942017f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[17] <= -0.3084181547164917f) {
            if (features[7] <= 0.5319443792104721f) {
                if (features[0] <= -0.4531653821468353f) {
                    if (features[20] <= 0.4011371284723282f) {
                        if (features[1] <= -0.5534392893314362f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[27] <= 0.5716331303119659f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[17] <= -0.32056528329849243f) {
                        if (features[15] <= 0.7462623417377472f) {
                            return 1;                        } else {
                            if (features[19] <= -0.3694869875907898f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    } else {
                        return 1;                    }
                }
            } else {
                if (features[20] <= 1.5979369282722473f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[7] <= -1.4296380877494812f) {
                return 2;            } else {
                return 2;            }
        }
    }
}

// Tree 41
int predict_tree_41(const float* features) {
    // Max depth: 10
    if (features[23] <= -0.12822941690683365f) {
        if (features[24] <= -0.3942602127790451f) {
            return 0;        } else {
            if (features[1] <= -0.3487269729375839f) {
                return 0;            } else {
                if (features[26] <= 0.35370853543281555f) {
                    if (features[12] <= -0.371526762843132f) {
                        return 2;                    } else {
                        if (features[18] <= -0.4630401134490967f) {
                            return 0;                        } else {
                            if (features[10] <= -0.3599660098552704f) {
                                return 0;                            } else {
                                if (features[14] <= 0.29641103744506836f) {
                                    if (features[24] <= -0.36176103353500366f) {
                                        return 1;                                    } else {
                                        if (features[17] <= -0.3733074367046356f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    if (features[1] <= -0.33753548562526703f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        }
                    }
                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[20] <= 1.061827838420868f) {
            if (features[0] <= -0.2124960944056511f) {
                if (features[17] <= -0.5686517059803009f) {
                    if (features[33] <= -0.7310653924942017f) {
                        if (features[0] <= -0.5856801569461823f) {
                            if (features[5] <= 0.00037258490920066833f) {
                                if (features[18] <= -0.5883428752422333f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        } else {
                            if (features[3] <= -0.47149255871772766f) {
                                return 0;                            } else {
                                return 0;                            }
                        }
                    } else {
                        return 0;                    }
                } else {
                    if (features[0] <= -0.4111148864030838f) {
                        if (features[20] <= 0.3659154772758484f) {
                            if (features[6] <= -0.6673636958003044f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[25] <= 0.021579109132289886f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[21] <= 0.04397893324494362f) {
                    if (features[17] <= 0.9990517497062683f) {
                        if (features[21] <= -0.06515789881814271f) {
                            return 0;                        } else {
                            return 2;                        }
                    } else {
                        return 0;                    }
                } else {
                    if (features[2] <= -0.45958563685417175f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[2] <= -0.2587505131959915f) {
                if (features[12] <= 0.12798143550753593f) {
                    if (features[10] <= -0.3379157483577728f) {
                        if (features[13] <= -0.9169100821018219f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        return 2;                    }
                } else {
                    return 2;                }
            } else {
                if (features[26] <= -0.363810196518898f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 42
int predict_tree_42(const float* features) {
    // Max depth: 10
    if (features[0] <= -0.4512583017349243f) {
        if (features[14] <= -0.736262708902359f) {
            if (features[19] <= -0.5263532400131226f) {
                return 0;            } else {
                if (features[19] <= -0.5050492882728577f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[4] <= 0.46065424382686615f) {
                return 0;            } else {
                if (features[25] <= 1.1397939324378967f) {
                    return 1;                } else {
                    if (features[34] <= -2.0389932096004486f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[0] <= -0.23959659039974213f) {
            if (features[7] <= 0.6561440229415894f) {
                if (features[24] <= -0.11189107969403267f) {
                    if (features[19] <= -0.39547955989837646f) {
                        if (features[0] <= -0.37592414021492004f) {
                            if (features[1] <= -0.43259958922863007f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[18] <= -0.38736048340797424f) {
                            return 0;                        } else {
                            if (features[12] <= -0.19050254672765732f) {
                                return 0;                            } else {
                                if (features[5] <= -0.389695942401886f) {
                                    return 0;                                } else {
                                    if (features[1] <= -0.33857356011867523f) {
                                        if (features[21] <= -0.6193157136440277f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[1] <= -0.3375915288925171f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        }
                    }
                } else {
                    if (features[15] <= 0.7462623417377472f) {
                        return 1;                    } else {
                        if (features[2] <= -0.257812038064003f) {
                            if (features[28] <= 0.03392469882965088f) {
                                return 1;                            } else {
                                return 2;                            }
                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[28] <= 0.03392469882965088f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[9] <= -0.10662208124995232f) {
                if (features[2] <= -0.6238199695944786f) {
                    if (features[5] <= 0.021212062129052356f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    return 2;                }
            } else {
                if (features[3] <= 1.8487611413002014f) {
                    return 2;                } else {
                    return 0;                }
            }
        }
    }
}

// Tree 43
int predict_tree_43(const float* features) {
    // Max depth: 10
    if (features[17] <= -0.4506124407052994f) {
        if (features[34] <= -2.0389932096004486f) {
            return 2;        } else {
            if (features[22] <= 0.12020169198513031f) {
                if (features[27] <= 2.441583037376404f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                if (features[25] <= 0.9393647909164429f) {
                    if (features[20] <= 0.44134001433849335f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[25] <= 2.086934804916382f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[3] <= 0.2887963354587555f) {
            if (features[4] <= 0.1909669041633606f) {
                if (features[24] <= -0.004102624050574377f) {
                    if (features[1] <= -0.3555963486433029f) {
                        if (features[33] <= -0.7310653924942017f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[25] <= 7.77647364884615e-05f) {
                            if (features[0] <= -0.37533751130104065f) {
                                return 0;                            } else {
                                if (features[26] <= -0.33663901686668396f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        } else {
                            return 2;                        }
                    }
                } else {
                    return 2;                }
            } else {
                if (features[0] <= -0.17122778668999672f) {
                    return 1;                } else {
                    return 2;                }
            }
        } else {
            if (features[7] <= 0.701331615447998f) {
                if (features[10] <= -0.26714205741882324f) {
                    if (features[2] <= -0.623819962143898f) {
                        return 0;                    } else {
                        if (features[12] <= 0.08380856737494469f) {
                            if (features[0] <= -0.4303356260061264f) {
                                return 0;                            } else {
                                if (features[20] <= -0.6208451092243195f) {
                                    if (features[4] <= -0.6238575577735901f) {
                                        if (features[0] <= -0.3759319484233856f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[12] <= 0.04676560824736953f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    if (features[25] <= -0.3635074496269226f) {
                                        if (features[17] <= -0.38205505907535553f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[5] <= 0.1929066851735115f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[12] <= -0.3317207247018814f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[18] <= 0.9748136699199677f) {
                    if (features[34] <= -2.0389932096004486f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    return 0;                }
            }
        }
    }
}

// Tree 44
int predict_tree_44(const float* features) {
    // Max depth: 9
    if (features[18] <= -0.4504038095474243f) {
        if (features[14] <= 0.7223928570747375f) {
            if (features[20] <= 0.2963595539331436f) {
                return 0;            } else {
                if (features[18] <= -0.523480623960495f) {
                    if (features[9] <= 0.8893032371997833f) {
                        if (features[10] <= -0.5575650334358215f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        if (features[23] <= 0.01652532583102584f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[30] <= 0.17709434032440186f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[15] <= 0.7462623417377472f) {
                if (features[21] <= 1.4066441655158997f) {
                    return 0;                } else {
                    return 2;                }
            } else {
                return 1;            }
        }
    } else {
        if (features[17] <= -0.23100721091032028f) {
            if (features[22] <= 1.53965425491333f) {
                if (features[10] <= -0.4139540195465088f) {
                    return 0;                } else {
                    if (features[25] <= -0.39004001021385193f) {
                        return 0;                    } else {
                        if (features[2] <= -0.22121122851967812f) {
                            if (features[8] <= -0.19683266431093216f) {
                                return 2;                            } else {
                                if (features[11] <= 0.15431782230734825f) {
                                    if (features[26] <= 0.537603884935379f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[10] <= -0.35785675048828125f) {
                                if (features[28] <= 0.03392469882965088f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                if (features[0] <= -0.3757518380880356f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            }
                        }
                    }
                }
            } else {
                if (features[9] <= -1.248924970626831f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[5] <= 0.07344064489006996f) {
                if (features[7] <= 2.153159737586975f) {
                    return 2;                } else {
                    if (features[9] <= 0.3946273773908615f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[2] <= -0.9457192420959473f) {
                    return 0;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 45
int predict_tree_45(const float* features) {
    // Max depth: 10
    if (features[10] <= -0.4366036206483841f) {
        if (features[6] <= -1.8803272247314453f) {
            if (features[8] <= -0.1773812547326088f) {
                if (features[10] <= -0.5277519673109055f) {
                    return 0;                } else {
                    return 2;                }
            } else {
                if (features[24] <= -0.03310329373925924f) {
                    if (features[1] <= -0.5515033900737762f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[27] <= 0.6579424440860748f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            }
        } else {
            if (features[22] <= 0.4331102520227432f) {
                return 0;            } else {
                if (features[17] <= -0.46448130905628204f) {
                    return 1;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[1] <= -0.15766572952270508f) {
            if (features[21] <= 1.537333607673645f) {
                if (features[23] <= -0.39533182978630066f) {
                    return 0;                } else {
                    if (features[9] <= -0.26283467561006546f) {
                        if (features[18] <= -0.39643295109272003f) {
                            if (features[10] <= -0.36250805854797363f) {
                                if (features[8] <= -0.23760001361370087f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                if (features[5] <= -0.2987911105155945f) {
                                    return 1;                                } else {
                                    return 0;                                }
                            }
                        } else {
                            if (features[0] <= -0.3758691996335983f) {
                                return 0;                            } else {
                                if (features[6] <= 0.6558692157268524f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        }
                    } else {
                        if (features[25] <= -0.11416078731417656f) {
                            return 0;                        } else {
                            if (features[1] <= -0.21131204068660736f) {
                                if (features[11] <= 0.2016637995839119f) {
                                    if (features[0] <= -0.3721648156642914f) {
                                        return 1;                                    } else {
                                        if (features[33] <= -0.7310653924942017f) {
                                            return 2;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    if (features[2] <= -0.257812038064003f) {
                                        return 2;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                if (features[17] <= -0.4494752734899521f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[25] <= 0.06555371731519699f) {
                if (features[22] <= 0.15511752665042877f) {
                    if (features[16] <= 3.1667469069361687f) {
                        if (features[10] <= 0.3389202505350113f) {
                            return 2;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            } else {
                if (features[21] <= 0.05592682212591171f) {
                    if (features[3] <= 1.3347405940294266f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 46
int predict_tree_46(const float* features) {
    // Max depth: 8
    if (features[9] <= 1.995823621749878f) {
        if (features[19] <= -0.44943320751190186f) {
            if (features[27] <= 0.0065391360549256206f) {
                if (features[12] <= 0.07301074638962746f) {
                    if (features[23] <= 2.1060508242808282f) {
                        return 0;                    } else {
                        if (features[23] <= 4.406655311584473f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[5] <= -0.3642522692680359f) {
                        return 0;                    } else {
                        if (features[17] <= -0.40198753774166107f) {
                            if (features[22] <= 0.0547256525605917f) {
                                return 0;                            } else {
                                return 2;                            }
                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[17] <= -0.5167222619056702f) {
                    if (features[24] <= -0.03992524463683367f) {
                        if (features[14] <= -0.9496728330850601f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[10] <= -0.5651594996452332f) {
                            return 1;                        } else {
                            if (features[11] <= 0.07288151700049639f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    if (features[24] <= -0.3213256448507309f) {
                        return 0;                    } else {
                        if (features[15] <= 0.7462623417377472f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[20] <= 0.1447138860821724f) {
                if (features[5] <= -0.049010489135980606f) {
                    if (features[0] <= -0.3758653551340103f) {
                        if (features[24] <= -0.4250103831291199f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[24] <= 0.26825861632823944f) {
                        if (features[2] <= -0.9522886127233505f) {
                            return 0;                        } else {
                            if (features[22] <= 0.053957606200128794f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[4] <= 0.03819110197946429f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[18] <= -0.0075117365922778845f) {
                    if (features[5] <= 0.17542587965726852f) {
                        if (features[9] <= 0.4655214995145798f) {
                            return 2;                        } else {
                            if (features[6] <= -0.8879024684429169f) {
                                if (features[0] <= -0.3681335598230362f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            } else {
                                return 1;                            }
                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[23] <= -0.05297314375638962f) {
                        if (features[17] <= 0.5010808706283569f) {
                            return 1;                        } else {
                            return 2;                        }
                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[22] <= 1.5206653475761414f) {
            if (features[17] <= -0.3623146712779999f) {
                return 1;            } else {
                if (features[10] <= -0.2533028945326805f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[17] <= -0.49484647810459137f) {
                return 2;            } else {
                return 2;            }
        }
    }
}

// Tree 47
int predict_tree_47(const float* features) {
    // Max depth: 9
    if (features[1] <= -0.4231262058019638f) {
        if (features[21] <= 0.2762204259634018f) {
            return 0;        } else {
            if (features[5] <= 0.8384912088513374f) {
                if (features[9] <= 0.9134634137153625f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                return 2;            }
        }
    } else {
        if (features[3] <= 0.2887963354587555f) {
            if (features[10] <= -0.13132085651159286f) {
                if (features[3] <= -0.2884821593761444f) {
                    if (features[0] <= -0.368623748421669f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[20] <= 0.31711137294769287f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[4] <= 0.005741981993196532f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[24] <= 0.2046792209148407f) {
                if (features[4] <= 0.9125442206859589f) {
                    if (features[7] <= 1.243214726448059f) {
                        if (features[24] <= -0.04150437191128731f) {
                            if (features[27] <= -0.3096165806055069f) {
                                return 0;                            } else {
                                if (features[0] <= -0.3758691996335983f) {
                                    return 0;                                } else {
                                    if (features[27] <= 0.9988662600517273f) {
                                        return 1;                                    } else {
                                        return 2;                                    }
                                }
                            }
                        } else {
                            if (features[7] <= 0.04138706438243389f) {
                                if (features[6] <= -1.218710720539093f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[21] <= -0.08912437409162521f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[0] <= -0.37421369552612305f) {
                        return 1;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[1] <= 1.0777825117111206f) {
                    if (features[1] <= -0.4226010590791702f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    return 0;                }
            }
        }
    }
}

// Tree 48
int predict_tree_48(const float* features) {
    // Max depth: 8
    if (features[20] <= 0.11958581954240799f) {
        if (features[0] <= -0.3756202161312103f) {
            return 0;        } else {
            if (features[6] <= -0.11601662635803223f) {
                if (features[22] <= 0.05257309786975384f) {
                    if (features[25] <= 0.02721690246835351f) {
                        if (features[1] <= 0.43835482001304626f) {
                            return 2;                        } else {
                            return 0;                        }
                    } else {
                        if (features[8] <= -0.2409549579024315f) {
                            return 2;                        } else {
                            if (features[7] <= 1.9126811623573303f) {
                                return 2;                            } else {
                                return 0;                            }
                        }
                    }
                } else {
                    if (features[4] <= 0.04044772870838642f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                return 1;            }
        }
    } else {
        if (features[21] <= 1.0627307891845703f) {
            if (features[0] <= -0.2124960944056511f) {
                if (features[10] <= -0.5060524940490723f) {
                    if (features[9] <= 0.8893032371997833f) {
                        if (features[6] <= -1.8803272247314453f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[4] <= 0.46065424382686615f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[20] <= 0.5607487559318542f) {
                        if (features[26] <= -0.3443284183740616f) {
                            return 0;                        } else {
                            if (features[13] <= 0.5671686381101608f) {
                                if (features[6] <= -1.108441323041916f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            } else {
                                return 1;                            }
                        }
                    } else {
                        return 1;                    }
                }
            } else {
                if (features[5] <= -0.15606216341257095f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[4] <= 1.5124952793121338f) {
                if (features[8] <= -0.1966995745897293f) {
                    return 2;                } else {
                    if (features[11] <= 0.15431782230734825f) {
                        if (features[3] <= -0.28132085502147675f) {
                            return 2;                        } else {
                            if (features[22] <= 1.6214816570281982f) {
                                return 1;                            } else {
                                return 2;                            }
                        }
                    } else {
                        return 2;                    }
                }
            } else {
                return 2;            }
        }
    }
}

// Tree 49
int predict_tree_49(const float* features) {
    // Max depth: 10
    if (features[18] <= -0.44834041595458984f) {
        if (features[7] <= 0.6562467813491821f) {
            if (features[21] <= 0.25509195029735565f) {
                if (features[23] <= 0.02816949924454093f) {
                    if (features[26] <= 0.18460490554571152f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    return 1;                }
            } else {
                if (features[18] <= -0.5302750468254089f) {
                    if (features[20] <= 0.2858727127313614f) {
                        return 0;                    } else {
                        if (features[2] <= 0.10819589858874679f) {
                            if (features[9] <= 0.808246523141861f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[8] <= -0.16165941208600998f) {
                        return 2;                    } else {
                        return 0;                    }
                }
            }
        } else {
            if (features[22] <= 0.7354379445314407f) {
                return 0;            } else {
                if (features[7] <= 0.6653272807598114f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[26] <= -0.21320253610610962f) {
            if (features[1] <= -0.26992420852184296f) {
                if (features[21] <= 1.5383031964302063f) {
                    if (features[19] <= -0.42991192638874054f) {
                        return 0;                    } else {
                        if (features[22] <= -0.6407109200954437f) {
                            return 0;                        } else {
                            if (features[10] <= -0.41459906101226807f) {
                                return 0;                            } else {
                                if (features[6] <= 0.10452218819409609f) {
                                    if (features[30] <= 0.17709434032440186f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[0] <= -0.3757518380880356f) {
                                        if (features[31] <= 0.16302114725112915f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        return 1;                                    }
                                }
                            }
                        }
                    }
                } else {
                    if (features[14] <= -5.802745342254639f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[22] <= 0.06260824389755726f) {
                    return 0;                } else {
                    if (features[19] <= -0.23770007491111755f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[4] <= 0.06160362996160984f) {
                if (features[23] <= -0.29867100715637207f) {
                    if (features[18] <= -0.40338996052742004f) {
                        if (features[22] <= -0.593051552772522f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[10] <= -0.33549486100673676f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[12] <= -1.6263622045516968f) {
                        return 2;                    } else {
                        return 0;                    }
                }
            } else {
                if (features[17] <= -0.2740820497274399f) {
                    if (features[19] <= -0.3688044995069504f) {
                        return 2;                    } else {
                        if (features[13] <= 11.546429634094238f) {
                            if (features[24] <= 0.10927443578839302f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            return 2;                        }
                    }
                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 50
int predict_tree_50(const float* features) {
    // Max depth: 10
    if (features[19] <= -0.12862157076597214f) {
        if (features[0] <= -0.4301111698150635f) {
            if (features[5] <= -0.004704053630121052f) {
                if (features[24] <= -0.022179621271789074f) {
                    return 0;                } else {
                    if (features[24] <= -0.016578936018049717f) {
                        return 1;                    } else {
                        if (features[23] <= -0.010154854040592909f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                }
            } else {
                if (features[19] <= -0.5422951877117157f) {
                    if (features[4] <= 0.4572390764951706f) {
                        if (features[31] <= 0.16302114725112915f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[25] <= 1.5124974697828293f) {
                if (features[23] <= -0.11483398824930191f) {
                    if (features[18] <= -0.3947704881429672f) {
                        if (features[26] <= 0.20619072765111923f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        if (features[7] <= -0.10174174979329109f) {
                            return 0;                        } else {
                            if (features[26] <= -0.31498125195503235f) {
                                if (features[17] <= -0.3746878206729889f) {
                                    if (features[8] <= -0.12709801644086838f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                if (features[11] <= -0.15943120419979095f) {
                                    if (features[0] <= -0.3741089701652527f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[17] <= -0.38164205849170685f) {
                                        return 0;                                    } else {
                                        if (features[1] <= -0.3371053487062454f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        }
                    }
                } else {
                    if (features[10] <= -0.13474924862384796f) {
                        if (features[0] <= -0.214971661567688f) {
                            if (features[24] <= 0.2756664752960205f) {
                                if (features[0] <= -0.36037294566631317f) {
                                    return 1;                                } else {
                                    if (features[24] <= 0.003573637455701828f) {
                                        if (features[15] <= 0.7462623417377472f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                return 1;                            }
                        } else {
                            return 2;                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[29] <= -0.0025959014892578125f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[5] <= 0.06468716263771057f) {
            if (features[21] <= -0.003267236053943634f) {
                return 0;            } else {
                if (features[3] <= 0.4439573436975479f) {
                    if (features[7] <= -0.363553911447525f) {
                        if (features[25] <= -0.005658911075443029f) {
                            return 2;                        } else {
                            if (features[18] <= 0.40969862043857574f) {
                                return 1;                            } else {
                                return 2;                            }
                        }
                    } else {
                        return 2;                    }
                } else {
                    return 1;                }
            }
        } else {
            if (features[4] <= 0.05423935875296593f) {
                if (features[8] <= -0.2409549579024315f) {
                    return 2;                } else {
                    return 0;                }
            } else {
                if (features[3] <= 0.6743117570877075f) {
                    return 2;                } else {
                    if (features[9] <= -0.47743771970272064f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 51
int predict_tree_51(const float* features) {
    // Max depth: 10
    if (features[0] <= -0.45059768855571747f) {
        if (features[20] <= 0.44134001433849335f) {
            return 0;        } else {
            if (features[0] <= -0.5166175067424774f) {
                return 1;            } else {
                return 2;            }
        }
    } else {
        if (features[17] <= -0.22001521289348602f) {
            if (features[4] <= 1.53406423330307f) {
                if (features[12] <= 0.08148667216300964f) {
                    if (features[6] <= 0.10452218819409609f) {
                        if (features[2] <= -0.6266353875398636f) {
                            return 0;                        } else {
                            if (features[5] <= -0.3619125634431839f) {
                                return 0;                            } else {
                                if (features[17] <= -0.32180117070674896f) {
                                    if (features[25] <= -0.11818541958928108f) {
                                        return 1;                                    } else {
                                        if (features[11] <= 0.07451522350311279f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    return 1;                                }
                            }
                        }
                    } else {
                        if (features[5] <= -0.318118155002594f) {
                            if (features[17] <= -0.379781037569046f) {
                                return 0;                            } else {
                                if (features[10] <= -0.35469114780426025f) {
                                    if (features[25] <= -0.36581969261169434f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 1;                                }
                            }
                        } else {
                            if (features[21] <= -0.4858487993478775f) {
                                return 0;                            } else {
                                return 0;                            }
                        }
                    }
                } else {
                    if (features[2] <= -0.257812038064003f) {
                        if (features[23] <= -0.12416975200176239f) {
                            if (features[21] <= -0.7919692397117615f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 2;                        }
                    } else {
                        if (features[12] <= 0.16096461564302444f) {
                            if (features[9] <= -0.7307577431201935f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            if (features[8] <= 0.3850049078464508f) {
                                if (features[29] <= -0.0025959014892578125f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            } else {
                                return 1;                            }
                        }
                    }
                }
            } else {
                if (features[11] <= -0.07772261649370193f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[4] <= 0.05423935875296593f) {
                return 0;            } else {
                if (features[18] <= 2.3506535291671753f) {
                    if (features[12] <= -10.438920497894287f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    if (features[22] <= 0.03273524343967438f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 52
int predict_tree_52(const float* features) {
    // Max depth: 8
    if (features[21] <= 0.11952432990074158f) {
        if (features[17] <= -0.39827775955200195f) {
            return 0;        } else {
            if (features[18] <= -0.13631319347769022f) {
                if (features[0] <= -0.3758653551340103f) {
                    return 0;                } else {
                    if (features[9] <= -0.7592896521091461f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[7] <= 0.939143480209168f) {
                    return 2;                } else {
                    return 0;                }
            }
        }
    } else {
        if (features[8] <= -0.1863780841231346f) {
            if (features[22] <= 0.1457999050617218f) {
                if (features[0] <= -0.1373702809214592f) {
                    if (features[22] <= 0.1438191458582878f) {
                        if (features[14] <= -0.30270761251449585f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            } else {
                if (features[17] <= -0.5130833089351654f) {
                    return 0;                } else {
                    if (features[12] <= 1.2179502248764038f) {
                        return 2;                    } else {
                        if (features[25] <= 0.11495498195290565f) {
                            return 1;                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[0] <= -0.23959659039974213f) {
                if (features[20] <= 1.530478298664093f) {
                    if (features[18] <= -0.584480494260788f) {
                        return 0;                    } else {
                        if (features[1] <= -0.4117836654186249f) {
                            if (features[4] <= 0.47661183774471283f) {
                                if (features[24] <= -0.11403396353125572f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        } else {
                            if (features[12] <= 0.0783008374273777f) {
                                if (features[10] <= -0.3179440200328827f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            } else {
                                if (features[20] <= 0.415233850479126f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                } else {
                    if (features[20] <= 1.5990057587623596f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[26] <= -0.29032571613788605f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 53
int predict_tree_53(const float* features) {
    // Max depth: 8
    if (features[20] <= 0.12193527445197105f) {
        if (features[1] <= -0.35448597371578217f) {
            return 0;        } else {
            if (features[23] <= -0.29870347678661346f) {
                if (features[5] <= -0.3897176533937454f) {
                    return 0;                } else {
                    if (features[17] <= -0.3783881664276123f) {
                        if (features[27] <= -0.2717393785715103f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        if (features[1] <= -0.3375915288925171f) {
                            if (features[14] <= 0.14980114623904228f) {
                                if (features[0] <= -0.37586139142513275f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            } else {
                                if (features[24] <= -0.3837921470403671f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            }
                        } else {
                            if (features[4] <= -0.44567452371120453f) {
                                if (features[12] <= -0.10569362714886665f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            } else {
                                return 1;                            }
                        }
                    }
                }
            } else {
                if (features[7] <= 0.10904210666194558f) {
                    if (features[24] <= -0.08711356949061155f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    return 0;                }
            }
        }
    } else {
        if (features[8] <= -0.186538465321064f) {
            if (features[18] <= -0.5127813816070557f) {
                if (features[26] <= 0.1899019181728363f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                return 2;            }
        } else {
            if (features[1] <= -0.05457092449069023f) {
                if (features[9] <= 0.34708748757839203f) {
                    if (features[23] <= 3.183402419090271f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    if (features[6] <= -1.6597883701324463f) {
                        if (features[4] <= 0.44213777780532837f) {
                            if (features[1] <= -0.5518527328968048f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[17] <= -0.47403839230537415f) {
                            if (features[13] <= 0.718605250120163f) {
                                if (features[3] <= -0.5112774223089218f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        } else {
                            if (features[10] <= -0.3557049334049225f) {
                                return 1;                            } else {
                                if (features[22] <= 0.6083665192127228f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                }
            } else {
                if (features[20] <= 0.13504381477832794f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 54
int predict_tree_54(const float* features) {
    // Max depth: 10
    if (features[10] <= -0.43731772899627686f) {
        if (features[13] <= -0.22502737492322922f) {
            if (features[4] <= 0.7420604526996613f) {
                if (features[17] <= -0.5868752896785736f) {
                    return 1;                } else {
                    if (features[14] <= -1.0197201520204544f) {
                        return 0;                    } else {
                        return 0;                    }
                }
            } else {
                if (features[20] <= 1.9747973680496216f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[33] <= -0.7310653924942017f) {
                if (features[23] <= 0.8726251274347305f) {
                    if (features[27] <= 3.301996350288391f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[20] <= 2.484235644340515f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                return 0;            }
        }
    } else {
        if (features[1] <= -0.15344125032424927f) {
            if (features[34] <= -2.0389932096004486f) {
                return 2;            } else {
                if (features[2] <= -0.6425895839929581f) {
                    return 0;                } else {
                    if (features[17] <= -0.4265347719192505f) {
                        if (features[23] <= -0.13479040935635567f) {
                            if (features[23] <= -0.3941933363676071f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[1] <= -0.4002765715122223f) {
                            return 0;                        } else {
                            if (features[11] <= 0.4594182223081589f) {
                                if (features[13] <= 4.785053968429565f) {
                                    if (features[25] <= -0.11416078731417656f) {
                                        if (features[19] <= -0.38985390961170197f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[5] <= 0.211422860622406f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    return 2;                                }
                            } else {
                                return 2;                            }
                        }
                    }
                }
            }
        } else {
            if (features[7] <= 1.917330026626587f) {
                if (features[25] <= 0.17380639165639877f) {
                    return 2;                } else {
                    if (features[2] <= -0.9757506847381592f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[2] <= 0.2771226763725281f) {
                    return 0;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 55
int predict_tree_55(const float* features) {
    // Max depth: 9
    if (features[1] <= -0.42361240088939667f) {
        if (features[21] <= 0.2762204259634018f) {
            if (features[23] <= 0.02816949924454093f) {
                return 0;            } else {
                return 1;            }
        } else {
            if (features[8] <= -0.1325678750872612f) {
                if (features[22] <= 2.002352237701416f) {
                    return 2;                } else {
                    return 2;                }
            } else {
                if (features[24] <= -0.045531297102570534f) {
                    return 0;                } else {
                    if (features[4] <= 0.4545391798019409f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            }
        }
    } else {
        if (features[9] <= 2.0418550968170166f) {
            if (features[1] <= -0.15035637468099594f) {
                if (features[17] <= -0.38548967242240906f) {
                    if (features[22] <= 1.4415159821510315f) {
                        if (features[27] <= 0.1797175332903862f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[25] <= 0.05578978359699249f) {
                        if (features[1] <= -0.33894018828868866f) {
                            if (features[1] <= -0.3427797108888626f) {
                                if (features[20] <= -0.6198065280914307f) {
                                    return 0;                                } else {
                                    if (features[11] <= -0.10758776031434536f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                if (features[14] <= 0.01785341650247574f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            }
                        } else {
                            if (features[14] <= 0.3027558922767639f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[2] <= -0.958857998251915f) {
                    if (features[10] <= 0.6836339831352234f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    if (features[8] <= 0.14970267564058304f) {
                        if (features[19] <= -0.49586667120456696f) {
                            return 2;                        } else {
                            return 2;                        }
                    } else {
                        return 1;                    }
                }
            }
        } else {
            if (features[0] <= -0.3721648156642914f) {
                if (features[21] <= 1.50393408536911f) {
                    return 1;                } else {
                    return 1;                }
            } else {
                return 2;            }
        }
    }
}

// Tree 56
int predict_tree_56(const float* features) {
    // Max depth: 7
    if (features[5] <= -0.1309334635734558f) {
        if (features[17] <= -0.379781037569046f) {
            return 0;        } else {
            if (features[1] <= 0.4644355848431587f) {
                if (features[0] <= -0.3758653551340103f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                return 2;            }
        }
    } else {
        if (features[3] <= 0.3078930675983429f) {
            if (features[1] <= -0.05862759053707123f) {
                if (features[10] <= -0.39968255162239075f) {
                    if (features[24] <= 0.0017290213145315647f) {
                        return 0;                    } else {
                        if (features[21] <= 2.2657104432582855f) {
                            if (features[26] <= -0.352356418967247f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            if (features[18] <= -0.49656812846660614f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[6] <= -0.8879024684429169f) {
                        return 2;                    } else {
                        if (features[21] <= 0.7774661481380463f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[17] <= 0.05185310449451208f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[6] <= -1.6597883701324463f) {
                if (features[7] <= 0.6719996631145477f) {
                    return 1;                } else {
                    return 2;                }
            } else {
                if (features[22] <= 0.8055626749992371f) {
                    if (features[21] <= 0.0713287927210331f) {
                        return 0;                    } else {
                        if (features[7] <= -0.19350407272577286f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[22] <= 1.53965425491333f) {
                        if (features[12] <= 0.12798143550753593f) {
                            if (features[0] <= -0.35355837643146515f) {
                                return 1;                            } else {
                                return 2;                            }
                        } else {
                            return 2;                        }
                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 57
int predict_tree_57(const float* features) {
    // Max depth: 8
    if (features[17] <= -0.45023810863494873f) {
        if (features[23] <= -0.02813013829290867f) {
            return 0;        } else {
            if (features[2] <= -0.013806741684675217f) {
                if (features[1] <= -0.5480098724365234f) {
                    return 1;                } else {
                    return 0;                }
            } else {
                if (features[24] <= 0.9146785791963339f) {
                    if (features[23] <= -0.0033318456262350082f) {
                        return 1;                    } else {
                        return 0;                    }
                } else {
                    if (features[19] <= -0.5044876933097839f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[9] <= 1.9700989127159119f) {
            if (features[25] <= -0.16543389856815338f) {
                if (features[23] <= -0.35712504386901855f) {
                    if (features[1] <= -0.35435670614242554f) {
                        return 0;                    } else {
                        if (features[9] <= -0.7676421999931335f) {
                            return 0;                        } else {
                            if (features[0] <= -0.3758653551340103f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    if (features[12] <= -0.3020833134651184f) {
                        return 1;                    } else {
                        if (features[23] <= -0.3570983558893204f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                }
            } else {
                if (features[20] <= 0.05647323466837406f) {
                    if (features[14] <= 2.1806885600090027f) {
                        if (features[3] <= 1.326783612370491f) {
                            if (features[8] <= -0.15989357233047485f) {
                                return 2;                            } else {
                                if (features[31] <= 0.16302114725112915f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            }
                        } else {
                            return 0;                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[0] <= -0.2124960944056511f) {
                        if (features[20] <= 1.1720554828643799f) {
                            if (features[25] <= 0.10463486611843109f) {
                                if (features[25] <= 0.04143438953906298f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            } else {
                                return 2;                            }
                        } else {
                            return 2;                        }
                    } else {
                        if (features[2] <= -0.4530162662267685f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[20] <= 1.517057180404663f) {
                if (features[19] <= 0.136730476107914f) {
                    if (features[13] <= 1.8364436626434326f) {
                        if (features[17] <= -0.3757111579179764f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            } else {
                if (features[4] <= 1.5352126955986023f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 58
int predict_tree_58(const float* features) {
    // Max depth: 9
    if (features[1] <= -0.42217056453227997f) {
        if (features[23] <= -0.026626940816640854f) {
            if (features[6] <= 1.648293912410736f) {
                return 0;            } else {
                if (features[10] <= -0.5212896168231964f) {
                    if (features[14] <= -0.5164046883583069f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    return 1;                }
            }
        } else {
            if (features[19] <= -0.5402398109436035f) {
                if (features[14] <= 0.6166249364614487f) {
                    if (features[9] <= 0.8893032371997833f) {
                        if (features[21] <= 0.26076795160770416f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                } else {
                    return 0;                }
            } else {
                return 2;            }
        }
    } else {
        if (features[4] <= 1.0517802834510803f) {
            if (features[20] <= 0.1530025228857994f) {
                if (features[0] <= -0.13607700914144516f) {
                    if (features[10] <= -0.364113450050354f) {
                        if (features[7] <= -2.6198980808258057f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[24] <= -0.40681934356689453f) {
                            return 0;                        } else {
                            if (features[9] <= -0.7624001801013947f) {
                                return 0;                            } else {
                                if (features[10] <= -0.3602023273706436f) {
                                    if (features[19] <= -0.3936948776245117f) {
                                        return 1;                                    } else {
                                        return 0;                                    }
                                } else {
                                    if (features[0] <= -0.3758145868778229f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        }
                    }
                } else {
                    if (features[3] <= 1.7524817436933517f) {
                        return 2;                    } else {
                        return 0;                    }
                }
            } else {
                if (features[0] <= -0.2124960944056511f) {
                    if (features[25] <= 0.04143438953906298f) {
                        return 1;                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[4] <= 1.515285849571228f) {
                if (features[2] <= -0.05509994179010391f) {
                    if (features[0] <= -0.3721648156642914f) {
                        return 1;                    } else {
                        return 2;                    }
                } else {
                    return 2;                }
            } else {
                if (features[23] <= 0.037485165521502495f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 59
int predict_tree_59(const float* features) {
    // Max depth: 10
    if (features[0] <= -0.2891186326742172f) {
        if (features[0] <= -0.4296617656946182f) {
            if (features[27] <= -0.07706740871071815f) {
                if (features[24] <= 1.4423709884285927f) {
                    return 0;                } else {
                    if (features[12] <= -0.010924437548965216f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[21] <= 1.0627308189868927f) {
                    if (features[19] <= -0.5770379900932312f) {
                        if (features[33] <= -0.7310653924942017f) {
                            if (features[20] <= 0.3998766988515854f) {
                                if (features[6] <= -1.8803272247314453f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        } else {
                            if (features[4] <= -0.5851724743843079f) {
                                return 0;                            } else {
                                return 0;                            }
                        }
                    } else {
                        return 0;                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[6] <= -1.6597883701324463f) {
                return 2;            } else {
                if (features[22] <= 1.5412914156913757f) {
                    if (features[18] <= -0.4302481859922409f) {
                        return 0;                    } else {
                        if (features[22] <= -0.6407210230827332f) {
                            return 0;                        } else {
                            if (features[7] <= 0.4375799894332886f) {
                                if (features[11] <= 0.2016637995839119f) {
                                    if (features[27] <= -0.3113083839416504f) {
                                        return 0;                                    } else {
                                        if (features[20] <= -0.6398020684719086f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    return 2;                                }
                            } else {
                                if (features[19] <= -0.38926564157009125f) {
                                    return 0;                                } else {
                                    if (features[0] <= -0.3758691996335983f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        }
                    }
                } else {
                    if (features[3] <= 0.4435594826936722f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[21] <= 0.054876457899808884f) {
            if (features[6] <= -0.9981719255447388f) {
                return 0;            } else {
                return 2;            }
        } else {
            if (features[0] <= -0.27645033597946167f) {
                return 2;            } else {
                return 2;            }
        }
    }
}

// Tree 60
int predict_tree_60(const float* features) {
    // Max depth: 10
    if (features[19] <= -0.454338937997818f) {
        if (features[14] <= -0.9249779880046844f) {
            if (features[5] <= 1.3070129305124283f) {
                return 2;            } else {
                if (features[0] <= -0.5048849880695343f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[20] <= 0.2736918479204178f) {
                if (features[17] <= -0.38727158308029175f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                if (features[19] <= -0.5734698474407196f) {
                    if (features[27] <= 0.30187438428401947f) {
                        return 0;                    } else {
                        if (features[24] <= 0.0444147065281868f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[4] <= 0.34017643332481384f) {
                        return 0;                    } else {
                        if (features[29] <= -0.0025959014892578125f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    } else {
        if (features[6] <= -0.11601662915199995f) {
            if (features[10] <= -0.14820684492588043f) {
                if (features[25] <= 0.47414152324199677f) {
                    if (features[0] <= -0.43235036730766296f) {
                        return 0;                    } else {
                        if (features[13] <= 4.019923210144043f) {
                            if (features[5] <= -0.3619125634431839f) {
                                return 0;                            } else {
                                if (features[20] <= 0.6230344772338867f) {
                                    if (features[20] <= 0.5541239082813263f) {
                                        return 1;                                    } else {
                                        return 2;                                    }
                                } else {
                                    return 1;                                }
                            }
                        } else {
                            return 2;                        }
                    }
                } else {
                    return 2;                }
            } else {
                if (features[3] <= 1.8797933459281921f) {
                    if (features[7] <= -1.632675290107727f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    return 0;                }
            }
        } else {
            if (features[1] <= -0.013357289135456085f) {
                if (features[18] <= -0.4216734319925308f) {
                    return 0;                } else {
                    if (features[10] <= -0.3994221091270447f) {
                        return 0;                    } else {
                        if (features[11] <= -0.4107060581445694f) {
                            return 2;                        } else {
                            if (features[24] <= -0.3895769268274307f) {
                                return 0;                            } else {
                                if (features[20] <= -0.442962184548378f) {
                                    if (features[19] <= -0.38985390961170197f) {
                                        if (features[6] <= 0.5455998182296753f) {
                                            return 1;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        if (features[1] <= -0.3429037630558014f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    if (features[1] <= -0.27527521550655365f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                return 2;            }
        }
    }
}

// Tree 61
int predict_tree_61(const float* features) {
    // Max depth: 10
    if (features[18] <= -0.4494751989841461f) {
        if (features[23] <= 0.01652532583102584f) {
            if (features[14] <= 1.7907890677452087f) {
                return 0;            } else {
                return 2;            }
        } else {
            if (features[19] <= -0.5772186815738678f) {
                return 1;            } else {
                if (features[16] <= 3.1667469069361687f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[9] <= 1.9910786747932434f) {
            if (features[0] <= -0.23563377559185028f) {
                if (features[21] <= 1.4049474000930786f) {
                    if (features[27] <= -0.3095593601465225f) {
                        if (features[14] <= -0.7555253058671951f) {
                            return 2;                        } else {
                            return 0;                        }
                    } else {
                        if (features[17] <= -0.4001740366220474f) {
                            if (features[3] <= -1.0443947315216064f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            if (features[0] <= -0.3846000134944916f) {
                                if (features[17] <= -0.3991789370775223f) {
                                    return 1;                                } else {
                                    if (features[17] <= -0.3981543183326721f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                }
                            } else {
                                if (features[2] <= -0.09827011078596115f) {
                                    if (features[12] <= 0.0766604132950306f) {
                                        if (features[13] <= 0.07440897449851036f) {
                                            return 1;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        return 2;                                    }
                                } else {
                                    if (features[10] <= -0.35866618156433105f) {
                                        if (features[7] <= 0.18035993026569486f) {
                                            return 1;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        if (features[21] <= -0.6200125813484192f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        }
                    }
                } else {
                    return 2;                }
            } else {
                if (features[22] <= 0.05568571202456951f) {
                    if (features[2] <= -0.6613592356443405f) {
                        return 0;                    } else {
                        if (features[2] <= 0.25835300236940384f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[5] <= -0.15606216341257095f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[1] <= -0.3477524369955063f) {
                if (features[6] <= -1.7700577974319458f) {
                    return 2;                } else {
                    return 1;                }
            } else {
                return 2;            }
        }
    }
}

// Tree 62
int predict_tree_62(const float* features) {
    // Max depth: 10
    if (features[19] <= -0.20676681399345398f) {
        if (features[17] <= -0.43032942712306976f) {
            if (features[17] <= -0.5029101669788361f) {
                if (features[4] <= 0.4632433205842972f) {
                    return 0;                } else {
                    if (features[3] <= 0.10936656594276428f) {
                        return 1;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[24] <= -0.07693136110901833f) {
                    if (features[2] <= -1.834461510181427f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[24] <= 1.6881644129753113f) {
                        return 1;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[25] <= 1.5124974697828293f) {
                if (features[0] <= -0.214971661567688f) {
                    if (features[22] <= -0.6407210230827332f) {
                        return 0;                    } else {
                        if (features[6] <= 0.5455998182296753f) {
                            if (features[19] <= -0.4300471842288971f) {
                                if (features[12] <= 0.0649429876357317f) {
                                    return 0;                                } else {
                                    if (features[24] <= -0.3745259940624237f) {
                                        return 1;                                    } else {
                                        if (features[23] <= -0.36169610917568207f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            } else {
                                if (features[11] <= 0.39624856412410736f) {
                                    if (features[27] <= -0.30840063095092773f) {
                                        return 1;                                    } else {
                                        if (features[10] <= -0.4150698184967041f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    return 1;                                }
                            }
                        } else {
                            if (features[17] <= -0.379781037569046f) {
                                if (features[2] <= -0.10765492916107178f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                if (features[2] <= -0.09827011078596115f) {
                                    if (features[23] <= -0.36172711849212646f) {
                                        if (features[12] <= -0.011759634595364332f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[18] <= -0.3777812421321869f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    }
                                } else {
                                    if (features[4] <= -0.44567452371120453f) {
                                        if (features[22] <= -0.6212469935417175f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 1;                                    }
                                }
                            }
                        }
                    }
                } else {
                    if (features[25] <= 0.04708176851272583f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[20] <= 1.6255152225494385f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[4] <= 0.05423935875296593f) {
            if (features[7] <= 0.8859101459383965f) {
                return 2;            } else {
                if (features[2] <= -1.6467651724815369f) {
                    return 0;                } else {
                    return 0;                }
            }
        } else {
            if (features[17] <= -0.23100721091032028f) {
                if (features[29] <= -0.0025959014892578125f) {
                    return 1;                } else {
                    return 2;                }
            } else {
                if (features[21] <= 0.027900289744138718f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 63
int predict_tree_63(const float* features) {
    // Max depth: 10
    if (features[0] <= -0.4491826593875885f) {
        if (features[9] <= 0.8891274631023407f) {
            if (features[34] <= -2.0389932096004486f) {
                return 2;            } else {
                return 0;            }
        } else {
            if (features[1] <= -0.483899861574173f) {
                if (features[14] <= 0.06979059055447578f) {
                    return 1;                } else {
                    return 1;                }
            } else {
                if (features[18] <= -0.496758833527565f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[15] <= 0.7462623417377472f) {
            if (features[0] <= -0.2918366491794586f) {
                if (features[7] <= 0.7013479471206665f) {
                    if (features[7] <= -1.179312139749527f) {
                        return 0;                    } else {
                        if (features[0] <= -0.4301111698150635f) {
                            return 0;                        } else {
                            if (features[25] <= -0.3888484388589859f) {
                                return 0;                            } else {
                                if (features[4] <= 0.08157076686620712f) {
                                    if (features[4] <= -0.5384683012962341f) {
                                        if (features[3] <= 0.3401188254356384f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[12] <= -0.09270236268639565f) {
                                            return 1;                                        } else {
                                            return 0;                                        }
                                    }
                                } else {
                                    if (features[22] <= 0.12718486040830612f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        }
                    }
                } else {
                    if (features[9] <= -1.1640693545341492f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[9] <= -0.05940765794366598f) {
                    if (features[20] <= 0.05675557442009449f) {
                        return 0;                    } else {
                        if (features[3] <= -1.000631332397461f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[20] <= 0.09481067582964897f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[10] <= -0.14820684492588043f) {
                if (features[10] <= -0.3894369453191757f) {
                    if (features[22] <= 0.8963236827403307f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    if (features[21] <= 1.967336356639862f) {
                        if (features[2] <= -0.3535371720790863f) {
                            if (features[6] <= -0.11601662915199995f) {
                                return 0;                            } else {
                                return 2;                            }
                        } else {
                            if (features[24] <= 0.007790708914399147f) {
                                if (features[10] <= -0.36010049283504486f) {
                                    return 1;                                } else {
                                    if (features[0] <= -0.3745678663253784f) {
                                        return 0;                                    } else {
                                        if (features[28] <= 0.03392469882965088f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            } else {
                                return 1;                            }
                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[21] <= 0.014336456544697285f) {
                    if (features[10] <= 0.4467097297310829f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    if (features[22] <= 0.05329061672091484f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 64
int predict_tree_64(const float* features) {
    // Max depth: 10
    if (features[18] <= -0.4494751989841461f) {
        if (features[24] <= -0.044267792254686356f) {
            return 0;        } else {
            if (features[23] <= 0.4434542804956436f) {
                if (features[20] <= 0.2678736746311188f) {
                    if (features[3] <= -0.3242885321378708f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[3] <= -0.2248263582587242f) {
                        if (features[4] <= 0.47060759365558624f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        return 1;                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[1] <= -0.15344125032424927f) {
            if (features[34] <= -2.0389932096004486f) {
                return 2;            } else {
                if (features[10] <= -0.41455593705177307f) {
                    if (features[19] <= -0.34049542248249054f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    if (features[25] <= -0.39004001021385193f) {
                        return 0;                    } else {
                        if (features[25] <= -0.11548442021012306f) {
                            if (features[7] <= -0.08459492772817612f) {
                                return 0;                            } else {
                                if (features[10] <= -0.364113450050354f) {
                                    if (features[7] <= -0.04983827844262123f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    if (features[0] <= -0.37586139142513275f) {
                                        return 0;                                    } else {
                                        if (features[23] <= -0.39179354906082153f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        } else {
                            if (features[8] <= -0.192680224776268f) {
                                return 2;                            } else {
                                if (features[23] <= 0.259522020816803f) {
                                    if (features[17] <= -0.32056528329849243f) {
                                        if (features[21] <= 0.7160400450229645f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                }
            }
        } else {
            if (features[23] <= 0.0708882063627243f) {
                if (features[21] <= -0.02244647452607751f) {
                    return 0;                } else {
                    if (features[0] <= -0.07391617819666862f) {
                        return 1;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[21] <= 0.05462396703660488f) {
                    if (features[6] <= -0.9981719255447388f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 65
int predict_tree_65(const float* features) {
    // Max depth: 10
    if (features[17] <= -0.45116911828517914f) {
        if (features[34] <= -2.0389932096004486f) {
            return 2;        } else {
            if (features[24] <= -0.044267792254686356f) {
                return 0;            } else {
                if (features[9] <= 1.2908761501312256f) {
                    if (features[8] <= 0.07240886241197586f) {
                        if (features[24] <= 0.00016413722187280655f) {
                            if (features[14] <= 0.3736451268196106f) {
                                return 0;                            } else {
                                return 1;                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[3] <= -0.5629977583885193f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[7] <= 0.6653272807598114f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[4] <= 1.073973834514618f) {
            if (features[21] <= 0.16788145899772644f) {
                if (features[19] <= -0.14021283108741045f) {
                    if (features[10] <= -0.3606000989675522f) {
                        if (features[10] <= -0.44405481219291687f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[3] <= 0.5549571514129639f) {
                            if (features[17] <= -0.3714115619659424f) {
                                if (features[30] <= 0.17709434032440186f) {
                                    return 0;                                } else {
                                    if (features[4] <= -0.4930133521556854f) {
                                        if (features[14] <= -0.09173344043665566f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 2;                                    }
                                }
                            } else {
                                if (features[14] <= -0.33926835656166077f) {
                                    if (features[19] <= -0.36827634274959564f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 1;                                }
                            }
                        } else {
                            if (features[20] <= -0.6314630210399628f) {
                                return 1;                            } else {
                                return 0;                            }
                        }
                    }
                } else {
                    if (features[7] <= 0.9678555894643068f) {
                        return 2;                    } else {
                        return 0;                    }
                }
            } else {
                if (features[26] <= 8.486588478088379f) {
                    if (features[19] <= -0.2591739520430565f) {
                        if (features[12] <= 0.05956655740737915f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        if (features[0] <= -0.26905810832977295f) {
                            return 1;                        } else {
                            return 2;                        }
                    }
                } else {
                    return 1;                }
            }
        } else {
            if (features[22] <= 1.5255464911460876f) {
                if (features[1] <= -0.3477524369955063f) {
                    if (features[14] <= -1.0166731774806976f) {
                        return 1;                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            } else {
                if (features[22] <= 1.5491335988044739f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 66
int predict_tree_66(const float* features) {
    // Max depth: 9
    if (features[10] <= -0.437801793217659f) {
        if (features[20] <= 0.4714795649051666f) {
            return 0;        } else {
            if (features[5] <= 0.8399765491485596f) {
                return 1;            } else {
                return 2;            }
        }
    } else {
        if (features[17] <= -0.23100721091032028f) {
            if (features[23] <= 1.5812974572181702f) {
                if (features[4] <= -0.6390192806720734f) {
                    return 0;                } else {
                    if (features[18] <= -0.4302481859922409f) {
                        if (features[26] <= 0.20619072765111923f) {
                            if (features[11] <= -0.07573750801384449f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[4] <= 0.08805857598781586f) {
                            if (features[0] <= -0.3758653551340103f) {
                                if (features[7] <= -0.09934277087450027f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                if (features[6] <= -0.005747221410274506f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        } else {
                            if (features[26] <= -0.22421710938215256f) {
                                if (features[20] <= 0.7178798019886017f) {
                                    if (features[21] <= 0.15782221406698227f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                if (features[23] <= 0.06072591617703438f) {
                                    if (features[7] <= 0.14741219580173492f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[0] <= -0.3623375743627548f) {
                                        return 1;                                    } else {
                                        return 2;                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                if (features[19] <= -0.4624405652284622f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[6] <= -0.9981719255447388f) {
                if (features[21] <= 0.0711268000304699f) {
                    return 0;                } else {
                    return 2;                }
            } else {
                if (features[4] <= 0.0009869421774055809f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 67
int predict_tree_67(const float* features) {
    // Max depth: 10
    if (features[18] <= -0.45106351375579834f) {
        if (features[34] <= -2.0389932096004486f) {
            return 2;        } else {
            if (features[27] <= 0.027112158946692944f) {
                if (features[26] <= 0.20619072765111923f) {
                    if (features[4] <= 0.4390449970960617f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    return 1;                }
            } else {
                if (features[24] <= 0.26234759390354156f) {
                    if (features[23] <= -0.0503070168197155f) {
                        return 0;                    } else {
                        if (features[14] <= 0.6462006568908691f) {
                            if (features[20] <= 0.3854270428419113f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[26] <= -0.3627614676952362f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[2] <= -0.0034834432881325483f) {
            if (features[1] <= -0.23837194591760635f) {
                if (features[8] <= -0.009545262437313795f) {
                    if (features[1] <= -0.4022371470928192f) {
                        return 0;                    } else {
                        if (features[19] <= -0.2228880301117897f) {
                            if (features[11] <= 0.11915373429656029f) {
                                if (features[22] <= -0.6205799877643585f) {
                                    if (features[0] <= -0.3759319484233856f) {
                                        if (features[0] <= -0.4254056066274643f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[6] <= 0.6558692352846265f) {
                                        return 1;                                    } else {
                                        if (features[1] <= -0.3328115940093994f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            } else {
                                return 2;                            }
                        } else {
                            return 2;                        }
                    }
                } else {
                    return 0;                }
            } else {
                if (features[22] <= 0.0716934371739626f) {
                    if (features[18] <= 0.5993080139160156f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[10] <= -0.14820684492588043f) {
                if (features[3] <= -0.292460635304451f) {
                    if (features[0] <= -0.3741089701652527f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[6] <= -0.6673636734485626f) {
                        if (features[25] <= 0.4183567389845848f) {
                            return 2;                        } else {
                            return 2;                        }
                    } else {
                        return 0;                    }
                }
            } else {
                if (features[16] <= 3.1667469069361687f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 68
int predict_tree_68(const float* features) {
    // Max depth: 10
    if (features[22] <= 0.1199793629348278f) {
        if (features[18] <= -0.4176875054836273f) {
            if (features[5] <= 0.06380521692335606f) {
                if (features[26] <= 0.20619072765111923f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                return 1;            }
        } else {
            if (features[23] <= -0.29867100715637207f) {
                if (features[26] <= -0.31087030470371246f) {
                    if (features[19] <= -0.3841238170862198f) {
                        if (features[25] <= -0.3842668980360031f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[5] <= -0.3584032505750656f) {
                            if (features[12] <= -0.01604989357292652f) {
                                return 0;                            } else {
                                if (features[0] <= -0.37597908079624176f) {
                                    return 0;                                } else {
                                    if (features[8] <= -0.1723278984427452f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[9] <= -0.761487603187561f) {
                        return 0;                    } else {
                        if (features[27] <= -0.3112141638994217f) {
                            return 0;                        } else {
                            if (features[10] <= -0.36440782248973846f) {
                                return 0;                            } else {
                                if (features[17] <= -0.38164205849170685f) {
                                    return 0;                                } else {
                                    if (features[10] <= -0.3376063257455826f) {
                                        if (features[11] <= -0.22025152295827866f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 1;                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                if (features[21] <= 0.05462396703660488f) {
                    if (features[0] <= 0.7316393107175827f) {
                        if (features[25] <= 0.0034881962928920984f) {
                            return 0;                        } else {
                            return 2;                        }
                    } else {
                        return 0;                    }
                } else {
                    if (features[33] <= -0.7310653924942017f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[17] <= -0.24500302970409393f) {
            if (features[7] <= 0.5318563878536224f) {
                if (features[6] <= -1.6597883701324463f) {
                    if (features[9] <= 0.8088836073875427f) {
                        if (features[10] <= -0.5594021677970886f) {
                            if (features[9] <= 0.3808000683784485f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[19] <= -0.4742763936519623f) {
                        return 0;                    } else {
                        if (features[8] <= -0.19525185972452164f) {
                            return 2;                        } else {
                            if (features[12] <= -0.3007810339331627f) {
                                return 1;                            } else {
                                if (features[9] <= 1.111545979976654f) {
                                    if (features[2] <= 0.19265927374362946f) {
                                        return 2;                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[26] <= 0.446509450674057f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                return 2;            }
        } else {
            if (features[14] <= -5.380370378494263f) {
                return 2;            } else {
                return 2;            }
        }
    }
}

// Tree 69
int predict_tree_69(const float* features) {
    // Max depth: 10
    if (features[0] <= -0.4502800852060318f) {
        if (features[25] <= -0.030040491372346878f) {
            return 0;        } else {
            if (features[0] <= -0.5168267488479614f) {
                if (features[31] <= 0.16302114725112915f) {
                    if (features[20] <= 0.1872359737753868f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    return 1;                }
            } else {
                return 2;            }
        }
    } else {
        if (features[10] <= -0.14820684492588043f) {
            if (features[6] <= -1.6597883701324463f) {
                if (features[24] <= 1.4582952558994293f) {
                    return 1;                } else {
                    if (features[0] <= -0.4495141804218292f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[24] <= 1.8324272185564041f) {
                    if (features[10] <= -0.41455593705177307f) {
                        return 0;                    } else {
                        if (features[20] <= -0.6394592225551605f) {
                            return 0;                        } else {
                            if (features[23] <= -0.11616252362728119f) {
                                if (features[0] <= -0.3756202161312103f) {
                                    if (features[22] <= -0.6392759084701538f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    if (features[29] <= -0.0025959014892578125f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                if (features[18] <= -0.26228731125593185f) {
                                    if (features[4] <= 0.589402973651886f) {
                                        if (features[11] <= 0.4913231134414673f) {
                                            return 1;                                        } else {
                                            return 2;                                        }
                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 1;                                }
                            }
                        }
                    }
                } else {
                    if (features[2] <= 0.2114289030432701f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[6] <= -0.9981719255447388f) {
                if (features[7] <= 1.5305007100105286f) {
                    return 2;                } else {
                    if (features[4] <= -0.0886838436126709f) {
                        return 0;                    } else {
                        return 0;                    }
                }
            } else {
                return 2;            }
        }
    }
}

// Tree 70
int predict_tree_70(const float* features) {
    // Max depth: 9
    if (features[10] <= -0.4378472715616226f) {
        if (features[5] <= -0.00588306353893131f) {
            return 0;        } else {
            if (features[19] <= -0.5421291589736938f) {
                return 1;            } else {
                return 2;            }
        }
    } else {
        if (features[19] <= -0.20676681399345398f) {
            if (features[5] <= 1.959548443555832f) {
                if (features[20] <= -0.6395297944545746f) {
                    return 0;                } else {
                    if (features[1] <= -0.40162132680416107f) {
                        return 0;                    } else {
                        if (features[22] <= 0.09805969521403313f) {
                            if (features[20] <= -0.4340988099575043f) {
                                if (features[0] <= -0.3758653551340103f) {
                                    if (features[21] <= -0.6402219533920288f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                if (features[24] <= -0.27299830317497253f) {
                                    return 2;                                } else {
                                    if (features[22] <= -0.18687577079981565f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                }
                            }
                        } else {
                            if (features[24] <= 0.34053969383239746f) {
                                if (features[17] <= -0.23004907369613647f) {
                                    if (features[11] <= 0.5838972479104996f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 2;                                }
                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                if (features[1] <= -0.427156925201416f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[9] <= -0.13085877150297165f) {
                if (features[22] <= 0.05414961650967598f) {
                    return 0;                } else {
                    return 2;                }
            } else {
                if (features[10] <= -0.32082274556159973f) {
                    if (features[0] <= -0.40151838958263397f) {
                        return 2;                    } else {
                        return 1;                    }
                } else {
                    if (features[20] <= 0.039502715691924095f) {
                        if (features[2] <= -0.5956654995679855f) {
                            if (features[21] <= -0.04500909708440304f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 2;                        }
                    } else {
                        if (features[4] <= 0.05423935875296593f) {
                            return 2;                        } else {
                            if (features[18] <= 2.3506535291671753f) {
                                if (features[26] <= -0.363572895526886f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            } else {
                                if (features[18] <= 2.3599095344543457f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

// Tree 71
int predict_tree_71(const float* features) {
    // Max depth: 9
    if (features[21] <= 0.11982731893658638f) {
        if (features[7] <= 0.3610851764678955f) {
            if (features[5] <= -0.035377844236791134f) {
                if (features[7] <= 0.009511605370789766f) {
                    if (features[17] <= -0.4020666927099228f) {
                        return 0;                    } else {
                        if (features[0] <= -0.37585754692554474f) {
                            return 0;                        } else {
                            if (features[0] <= -0.3235051929950714f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    return 0;                }
            } else {
                if (features[4] <= 0.21878187358379364f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[25] <= -0.3518434464931488f) {
                if (features[9] <= -0.7627458870410919f) {
                    return 0;                } else {
                    if (features[22] <= -0.640367329120636f) {
                        return 0;                    } else {
                        if (features[27] <= -0.3096165806055069f) {
                            return 0;                        } else {
                            if (features[0] <= -0.37561923265457153f) {
                                if (features[19] <= -0.5970085859298706f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                if (features[17] <= -0.3747115880250931f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        }
                    }
                }
            } else {
                if (features[0] <= -0.6052828133106232f) {
                    return 0;                } else {
                    return 0;                }
            }
        }
    } else {
        if (features[18] <= -0.20689783245325089f) {
            if (features[34] <= -2.0389932096004486f) {
                return 2;            } else {
                if (features[19] <= -0.4517471641302109f) {
                    if (features[9] <= 1.2972140312194824f) {
                        if (features[23] <= -0.02270204108208418f) {
                            if (features[11] <= -0.03432297334074974f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            if (features[12] <= 0.0017495938809588552f) {
                                if (features[8] <= -0.0843141246587038f) {
                                    return 2;                                } else {
                                    return 0;                                }
                            } else {
                                if (features[20] <= 0.2707878053188324f) {
                                    return 0;                                } else {
                                    if (features[10] <= -0.5466106832027435f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        }
                    } else {
                        if (features[19] <= -0.4960475414991379f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[26] <= 0.16826480627059937f) {
                        if (features[23] <= 0.259522020816803f) {
                            if (features[15] <= 0.7462623417377472f) {
                                return 1;                            } else {
                                if (features[6] <= -0.11601662915199995f) {
                                    if (features[2] <= 0.23019854724407196f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 2;                                }
                            }
                        } else {
                            return 2;                        }
                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[17] <= -0.22705212235450745f) {
                return 1;            } else {
                if (features[7] <= -1.5758530497550964f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 72
int predict_tree_72(const float* features) {
    // Max depth: 10
    if (features[10] <= -0.4356302320957184f) {
        if (features[33] <= -0.7310653924942017f) {
            if (features[21] <= 1.087798148393631f) {
                if (features[20] <= 0.4011371284723282f) {
                    if (features[25] <= -0.49291299283504486f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[6] <= -0.116016685962677f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            } else {
                return 2;            }
        } else {
            return 0;        }
    } else {
        if (features[2] <= -0.0034834432881325483f) {
            if (features[3] <= 0.3035167455673218f) {
                if (features[25] <= -0.2019820585846901f) {
                    return 0;                } else {
                    return 2;                }
            } else {
                if (features[0] <= -0.214971661567688f) {
                    if (features[0] <= -0.43150752782821655f) {
                        return 0;                    } else {
                        if (features[21] <= 0.7331589758396149f) {
                            if (features[17] <= -0.3793257921934128f) {
                                if (features[11] <= 0.8178799748420715f) {
                                    if (features[24] <= -0.3884277790784836f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                if (features[14] <= 0.3158061057329178f) {
                                    if (features[0] <= -0.3758691996335983f) {
                                        return 0;                                    } else {
                                        if (features[33] <= -0.7310653924942017f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[0] <= -0.36945921182632446f) {
                                return 1;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[22] <= 0.0716934371739626f) {
                        if (features[12] <= 2.1279468536376953f) {
                            return 0;                        } else {
                            return 2;                        }
                    } else {
                        if (features[26] <= -0.36161142587661743f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[20] <= 0.20463000237941742f) {
                if (features[1] <= -0.07461999938823283f) {
                    if (features[1] <= -0.35580986738204956f) {
                        return 0;                    } else {
                        if (features[6] <= 0.6558692157268524f) {
                            if (features[20] <= 0.07923167757689953f) {
                                if (features[0] <= -0.3748130053281784f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            } else {
                                return 1;                            }
                        } else {
                            if (features[0] <= -0.3668886721134186f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    if (features[31] <= 0.16302114725112915f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[5] <= -0.13365476578474045f) {
                    if (features[14] <= -1.1782144904136658f) {
                        return 1;                    } else {
                        return 2;                    }
                } else {
                    if (features[20] <= 0.24910829216241837f) {
                        if (features[18] <= -0.07340225204825401f) {
                            return 1;                        } else {
                            if (features[20] <= 0.20756430178880692f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 73
int predict_tree_73(const float* features) {
    // Max depth: 10
    if (features[17] <= -0.45023810863494873f) {
        if (features[21] <= 0.4146563410758972f) {
            if (features[23] <= 0.03949646418914199f) {
                return 0;            } else {
                return 1;            }
        } else {
            if (features[21] <= 1.5235274732112885f) {
                if (features[9] <= 0.8998923599720001f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                if (features[0] <= -0.5052848756313324f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[18] <= -0.20689783245325089f) {
            if (features[34] <= -2.0389932096004486f) {
                return 2;            } else {
                if (features[10] <= -0.41455593705177307f) {
                    return 0;                } else {
                    if (features[21] <= -0.6406461298465729f) {
                        return 0;                    } else {
                        if (features[27] <= -0.30868759751319885f) {
                            if (features[22] <= 0.16296979784965515f) {
                                return 0;                            } else {
                                return 1;                            }
                        } else {
                            if (features[0] <= -0.16644833609461784f) {
                                if (features[7] <= 0.2642535865306854f) {
                                    if (features[2] <= 0.8495965600013733f) {
                                        if (features[18] <= -0.4326374679803848f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 0;                                    }
                                } else {
                                    if (features[14] <= 0.2786415070295334f) {
                                        if (features[11] <= -0.02818373776972294f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 0;                                    }
                                }
                            } else {
                                if (features[21] <= 0.4325024336576462f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                }
            }
        } else {
            if (features[23] <= 0.07059157267212868f) {
                if (features[27] <= -0.30653467774391174f) {
                    if (features[9] <= 0.12323823571205139f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    if (features[22] <= 0.0320379389449954f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[25] <= 0.2182801216840744f) {
                    if (features[4] <= 0.07050925306975842f) {
                        if (features[6] <= -0.9981719255447388f) {
                            return 0;                        } else {
                            return 2;                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[21] <= 0.04494850058108568f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 74
int predict_tree_74(const float* features) {
    // Max depth: 10
    if (features[18] <= -0.44939664006233215f) {
        if (features[23] <= 0.01652532583102584f) {
            if (features[10] <= -0.36394138634204865f) {
                if (features[4] <= 0.434844046831131f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                return 1;            }
        } else {
            if (features[21] <= 1.2551696002483368f) {
                if (features[0] <= -0.5858339369297028f) {
                    return 1;                } else {
                    return 1;                }
            } else {
                return 2;            }
        }
    } else {
        if (features[6] <= -0.11601662915199995f) {
            if (features[0] <= -0.23959659039974213f) {
                if (features[7] <= 0.307846836745739f) {
                    if (features[25] <= -0.36808352172374725f) {
                        return 0;                    } else {
                        if (features[27] <= -0.3049663305282593f) {
                            return 0;                        } else {
                            if (features[11] <= 0.10983680188655853f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    if (features[25] <= -0.04918179661035538f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[20] <= 0.06173681654036045f) {
                    if (features[3] <= 1.3665684908628464f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    if (features[21] <= 0.06782421097159386f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[3] <= -0.4062453657388687f) {
                if (features[21] <= 0.21439036168158054f) {
                    return 0;                } else {
                    return 2;                }
            } else {
                if (features[7] <= -0.1783243790268898f) {
                    if (features[20] <= -0.20126086473464966f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    if (features[1] <= -0.3797040432691574f) {
                        return 0;                    } else {
                        if (features[17] <= -0.2656193897128105f) {
                            if (features[22] <= -0.6408422887325287f) {
                                return 0;                            } else {
                                if (features[11] <= 0.17462912946939468f) {
                                    if (features[22] <= -0.620701253414154f) {
                                        if (features[14] <= 0.26044492423534393f) {
                                            return 1;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        if (features[3] <= 0.299538254737854f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    return 1;                                }
                            }
                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    }
}

// Tree 75
int predict_tree_75(const float* features) {
    // Max depth: 9
    if (features[17] <= -0.44983918964862823f) {
        if (features[20] <= 0.2736918479204178f) {
            return 0;        } else {
            if (features[20] <= 1.5268986523151398f) {
                if (features[8] <= 0.09188399836421013f) {
                    if (features[9] <= 0.9134634137153625f) {
                        return 1;                    } else {
                        return 1;                    }
                } else {
                    if (features[9] <= 0.7992545366287231f) {
                        return 0;                    } else {
                        return 0;                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[8] <= -0.24035866558551788f) {
            if (features[2] <= -0.022253080271184444f) {
                if (features[9] <= 0.20246414840221405f) {
                    return 2;                } else {
                    return 2;                }
            } else {
                return 2;            }
        } else {
            if (features[17] <= -0.22465001046657562f) {
                if (features[20] <= 1.535479724407196f) {
                    if (features[9] <= 0.4055638760328293f) {
                        if (features[19] <= -0.39783112704753876f) {
                            if (features[0] <= -0.37561240792274475f) {
                                if (features[25] <= 1.833142340183258f) {
                                    return 0;                                } else {
                                    return 2;                                }
                            } else {
                                if (features[23] <= -0.2951138764619827f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        } else {
                            if (features[9] <= -0.7636584639549255f) {
                                return 0;                            } else {
                                if (features[0] <= -0.3758653551340103f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            }
                        }
                    } else {
                        if (features[22] <= 1.2450575828552246f) {
                            if (features[12] <= 0.0783008374273777f) {
                                if (features[4] <= 1.3676579594612122f) {
                                    if (features[8] <= -0.046445345506072044f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                if (features[20] <= 0.415233850479126f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[6] <= -1.8803272247314453f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[25] <= 0.04692086763679981f) {
                    if (features[3] <= 1.8400084972381592f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    if (features[23] <= 0.2159610614180565f) {
                        if (features[7] <= 1.2764073610305786f) {
                            return 2;                        } else {
                            return 0;                        }
                    } else {
                        if (features[3] <= 1.8996857702732086f) {
                            return 2;                        } else {
                            return 0;                        }
                    }
                }
            }
        }
    }
}

// Tree 76
int predict_tree_76(const float* features) {
    // Max depth: 9
    if (features[21] <= 0.11960512772202492f) {
        if (features[19] <= -0.44183431565761566f) {
            if (features[10] <= -0.3480091691017151f) {
                return 0;            } else {
                return 1;            }
        } else {
            if (features[4] <= -0.4443044066429138f) {
                if (features[10] <= -0.36409255862236023f) {
                    if (features[13] <= -0.09292310103774071f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[2] <= -0.09827011078596115f) {
                        if (features[0] <= -0.3759319484233856f) {
                            if (features[28] <= 0.03392469882965088f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[14] <= 0.22327853739261627f) {
                            if (features[5] <= -0.389695942401886f) {
                                return 1;                            } else {
                                if (features[21] <= -0.621012419462204f) {
                                    return 1;                                } else {
                                    if (features[2] <= -0.07011565566062927f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        } else {
                            if (features[4] <= -0.6242000758647919f) {
                                if (features[8] <= -0.12013007327914238f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            } else {
                                return 0;                            }
                        }
                    }
                }
            } else {
                if (features[7] <= 0.1138220815337263f) {
                    if (features[25] <= -0.06273923255503178f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    return 0;                }
            }
        }
    } else {
        if (features[2] <= -0.31036700308322906f) {
            if (features[9] <= 1.73026704788208f) {
                if (features[23] <= 0.09881074726581573f) {
                    if (features[10] <= -0.4186355918645859f) {
                        return 0;                    } else {
                        if (features[5] <= -0.031271565705537796f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    return 1;                }
            } else {
                if (features[1] <= -0.3415951430797577f) {
                    return 1;                } else {
                    return 2;                }
            }
        } else {
            if (features[8] <= 0.06623148918151855f) {
                if (features[4] <= 0.1827765554189682f) {
                    if (features[1] <= -0.14737635804340243f) {
                        if (features[23] <= -0.08307367190718651f) {
                            return 0;                        } else {
                            if (features[6] <= -1.108441323041916f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[14] <= -1.249569058418274f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[17] <= -0.5185289084911346f) {
                        if (features[7] <= -0.6544800102710724f) {
                            return 1;                        } else {
                            if (features[20] <= 0.1891820952296257f) {
                                return 0;                            } else {
                                return 0;                            }
                        }
                    } else {
                        if (features[2] <= -0.17241018265485764f) {
                            if (features[12] <= 0.4676162004470825f) {
                                return 2;                            } else {
                                return 1;                            }
                        } else {
                            if (features[11] <= -8.734731197357178f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                if (features[19] <= -0.11301854252815247f) {
                    if (features[15] <= 0.7462623417377472f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[28] <= 0.03392469882965088f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 77
int predict_tree_77(const float* features) {
    // Max depth: 10
    if (features[0] <= -0.44996821880340576f) {
        if (features[20] <= 0.4011371284723282f) {
            return 0;        } else {
            if (features[20] <= 0.8733218908309937f) {
                if (features[5] <= 0.04834745544940233f) {
                    return 1;                } else {
                    return 1;                }
            } else {
                if (features[7] <= 0.6653272807598114f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[1] <= -0.20337379723787308f) {
            if (features[22] <= 1.5412914156913757f) {
                if (features[1] <= -0.4018087685108185f) {
                    return 0;                } else {
                    if (features[5] <= -0.3942515701055527f) {
                        return 0;                    } else {
                        if (features[10] <= -0.3992402106523514f) {
                            if (features[9] <= 1.430221438407898f) {
                                if (features[18] <= -0.4613676071166992f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        } else {
                            if (features[17] <= -0.4220186024904251f) {
                                return 0;                            } else {
                                if (features[27] <= -0.3096165806055069f) {
                                    if (features[2] <= -0.27658166363835335f) {
                                        return 1;                                    } else {
                                        return 0;                                    }
                                } else {
                                    if (features[22] <= -0.6372546851634979f) {
                                        return 0;                                    } else {
                                        if (features[4] <= -0.6199588179588318f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                if (features[11] <= -0.7462258785963058f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[3] <= 1.8996857702732086f) {
                if (features[25] <= -0.052310314029455185f) {
                    if (features[25] <= -0.052481066435575485f) {
                        return 2;                    } else {
                        return 1;                    }
                } else {
                    if (features[15] <= 0.7462623417377472f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                return 0;            }
        }
    }
}

// Tree 78
int predict_tree_78(const float* features) {
    // Max depth: 7
    if (features[21] <= 0.11980712041258812f) {
        if (features[10] <= -0.36440782248973846f) {
            return 0;        } else {
            if (features[21] <= -0.5654845535755157f) {
                if (features[25] <= -0.39126643538475037f) {
                    return 0;                } else {
                    if (features[0] <= -0.37586139142513275f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[2] <= -0.9522886127233505f) {
                    if (features[21] <= -0.10993975400924683f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    if (features[8] <= -0.15945672243833542f) {
                        return 2;                    } else {
                        return 0;                    }
                }
            }
        }
    } else {
        if (features[2] <= -0.3113054931163788f) {
            if (features[18] <= -0.19727405905723572f) {
                if (features[21] <= 0.7090006172657013f) {
                    if (features[26] <= -0.2987017333507538f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    if (features[1] <= -0.31957322359085083f) {
                        if (features[0] <= -0.37754952907562256f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        return 2;                    }
                }
            } else {
                return 2;            }
        } else {
            if (features[21] <= 0.16788145899772644f) {
                if (features[0] <= -0.08189471811056137f) {
                    if (features[0] <= -0.4398674964904785f) {
                        if (features[22] <= -0.01207425631582737f) {
                            return 1;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[14] <= -0.8475682735443115f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[10] <= -0.5003955811262131f) {
                    if (features[4] <= 0.46065424382686615f) {
                        if (features[6] <= -1.1084413453936577f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[22] <= 0.14589085429906845f) {
                        if (features[10] <= 0.4681452065706253f) {
                            return 1;                        } else {
                            return 2;                        }
                    } else {
                        if (features[1] <= -0.31842534244060516f) {
                            if (features[25] <= 0.10010660253465176f) {
                                return 1;                            } else {
                                return 2;                            }
                        } else {
                            if (features[29] <= -0.5031495066359639f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                }
            }
        }
    }
}

// Tree 79
int predict_tree_79(const float* features) {
    // Max depth: 8
    if (features[5] <= -0.1309334635734558f) {
        if (features[18] <= -0.4176875054836273f) {
            return 0;        } else {
            if (features[19] <= 0.494363397359848f) {
                if (features[27] <= -0.31103286147117615f) {
                    return 0;                } else {
                    if (features[2] <= -1.1212153732776642f) {
                        return 0;                    } else {
                        if (features[1] <= -0.35448597371578217f) {
                            if (features[10] <= -0.4220094531774521f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            if (features[0] <= -0.3758653551340103f) {
                                return 0;                            } else {
                                if (features[14] <= -0.3502027541399002f) {
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
        if (features[21] <= 1.0637104511260986f) {
            if (features[18] <= -0.00637977896258235f) {
                if (features[19] <= -0.4043816924095154f) {
                    if (features[23] <= -0.026626940816640854f) {
                        return 0;                    } else {
                        if (features[7] <= -0.4567919820547104f) {
                            if (features[3] <= -0.3083745837211609f) {
                                if (features[27] <= 0.9049859680235386f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            } else {
                                return 0;                            }
                        } else {
                            if (features[8] <= 0.058735307306051254f) {
                                return 2;                            } else {
                                return 0;                            }
                        }
                    }
                } else {
                    if (features[10] <= -0.1354660429060459f) {
                        if (features[33] <= -0.7310653924942017f) {
                            if (features[12] <= 0.05441255774348974f) {
                                return 1;                            } else {
                                return 2;                            }
                        } else {
                            return 1;                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[2] <= -0.9569810330867767f) {
                    return 0;                } else {
                    if (features[17] <= -0.008142275619320571f) {
                        return 1;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[2] <= -0.24467327445745468f) {
                if (features[12] <= -0.23490172252058983f) {
                    return 2;                } else {
                    if (features[3] <= 0.3003339469432831f) {
                        return 1;                    } else {
                        if (features[17] <= -0.34760455787181854f) {
                            if (features[7] <= -0.12464063614606857f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[0] <= -0.5049962103366852f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 80
int predict_tree_80(const float* features) {
    // Max depth: 10
    if (features[4] <= 0.1193995252251625f) {
        if (features[18] <= -0.4060193598270416f) {
            if (features[28] <= 0.5361532494425774f) {
                if (features[22] <= -0.8271139860153198f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[18] <= -0.4619574695825577f) {
                    return 0;                } else {
                    if (features[17] <= -0.39912475645542145f) {
                        if (features[8] <= -0.2898324728012085f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                }
            }
        } else {
            if (features[25] <= -0.1331214988604188f) {
                if (features[17] <= -0.379781037569046f) {
                    if (features[7] <= -0.0698906233010348f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[11] <= -0.21372312307357788f) {
                        return 1;                    } else {
                        if (features[17] <= -0.37482111155986786f) {
                            if (features[18] <= -0.37769417464733124f) {
                                return 1;                            } else {
                                if (features[20] <= -0.6223172843456268f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            }
                        } else {
                            if (features[25] <= -0.3843068480491638f) {
                                return 1;                            } else {
                                if (features[0] <= -0.374878391623497f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        }
                    }
                }
            } else {
                if (features[1] <= 0.8971215784549713f) {
                    if (features[2] <= -0.9429038017988205f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    if (features[6] <= -0.9981719255447388f) {
                        return 0;                    } else {
                        if (features[19] <= 1.2923613786697388f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    } else {
        if (features[18] <= -0.20689783245325089f) {
            if (features[21] <= 1.538383960723877f) {
                if (features[22] <= 0.4331102520227432f) {
                    if (features[2] <= -0.18273348361253738f) {
                        return 0;                    } else {
                        if (features[14] <= 0.45150771737098694f) {
                            if (features[7] <= -0.8199246227741241f) {
                                return 0;                            } else {
                                if (features[8] <= -0.23492753505706787f) {
                                    return 0;                                } else {
                                    if (features[8] <= 0.3502674251794815f) {
                                        if (features[6] <= 0.7661386206746101f) {
                                            return 1;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        return 0;                                    }
                                }
                            }
                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[23] <= 0.259522020816803f) {
                        if (features[22] <= 0.7906160950660706f) {
                            if (features[7] <= -0.504954382777214f) {
                                return 1;                            } else {
                                if (features[19] <= -0.37848323583602905f) {
                                    return 0;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[0] <= -0.36841098964214325f) {
                                return 1;                            } else {
                                return 2;                            }
                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[25] <= 1.8245776891708374f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[26] <= 8.874895095825195f) {
                if (features[1] <= -0.27031224966049194f) {
                    return 1;                } else {
                    if (features[20] <= 0.10847381129860878f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                return 1;            }
        }
    }
}

// Tree 81
int predict_tree_81(const float* features) {
    // Max depth: 10
    if (features[18] <= -0.45106351375579834f) {
        if (features[9] <= 0.8882248103618622f) {
            if (features[25] <= 2.0524044521152973f) {
                if (features[20] <= 0.2787638455629349f) {
                    if (features[1] <= -0.2539321184158325f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    if (features[12] <= 1.0128891468048096f) {
                        if (features[21] <= 0.2867038697004318f) {
                            return 2;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                }
            } else {
                if (features[9] <= -1.1682846546173096f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[3] <= -0.26461122930049896f) {
                if (features[2] <= 0.1738896295428276f) {
                    return 1;                } else {
                    return 0;                }
            } else {
                return 2;            }
        }
    } else {
        if (features[10] <= -0.14820684492588043f) {
            if (features[21] <= 1.5458981394767761f) {
                if (features[1] <= -0.4018087685108185f) {
                    return 0;                } else {
                    if (features[21] <= -0.6406461298465729f) {
                        return 0;                    } else {
                        if (features[0] <= -0.4295244663953781f) {
                            return 0;                        } else {
                            if (features[2] <= -0.21745731309056282f) {
                                if (features[0] <= -0.3686157912015915f) {
                                    if (features[19] <= -0.41710013151168823f) {
                                        if (features[11] <= -0.012362435925751925f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[2] <= -0.47647830843925476f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    return 2;                                }
                            } else {
                                if (features[2] <= -0.08888529241085052f) {
                                    if (features[0] <= -0.37685489654541016f) {
                                        if (features[5] <= -0.37468697130680084f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[10] <= -0.35530905425548553f) {
                                        if (features[4] <= -0.6362287104129791f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        if (features[17] <= -0.3762465715408325f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                if (features[10] <= -0.4400971680879593f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[21] <= 0.05533094331622124f) {
                if (features[9] <= -0.36027762293815613f) {
                    return 2;                } else {
                    if (features[17] <= 0.8307374715805054f) {
                        if (features[5] <= 0.06518731825053692f) {
                            return 2;                        } else {
                            return 2;                        }
                    } else {
                        return 0;                    }
                }
            } else {
                if (features[18] <= -0.30847686529159546f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 82
int predict_tree_82(const float* features) {
    // Max depth: 10
    if (features[1] <= -0.4233284592628479f) {
        if (features[24] <= 0.06352587603032589f) {
            if (features[13] <= 1.8211926221847534f) {
                return 0;            } else {
                return 1;            }
        } else {
            if (features[10] <= -0.49483244121074677f) {
                return 1;            } else {
                return 2;            }
        }
    } else {
        if (features[10] <= -0.14812666922807693f) {
            if (features[20] <= 1.535741925239563f) {
                if (features[17] <= -0.4301724284887314f) {
                    if (features[18] <= -0.5467813313007355f) {
                        return 1;                    } else {
                        if (features[5] <= -0.4530643969774246f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[5] <= -0.3000112920999527f) {
                        if (features[10] <= -0.3627457320690155f) {
                            if (features[8] <= -0.18724092841148376f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            if (features[5] <= -0.34911197423934937f) {
                                if (features[25] <= -0.3854149281978607f) {
                                    return 1;                                } else {
                                    if (features[13] <= 0.07440897449851036f) {
                                        if (features[12] <= 0.08692314848303795f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 0;                                    }
                                }
                            } else {
                                return 0;                            }
                        }
                    } else {
                        if (features[10] <= -0.2069772630929947f) {
                            if (features[0] <= -0.4300238788127899f) {
                                return 0;                            } else {
                                if (features[13] <= 0.6023964583873749f) {
                                    if (features[17] <= -0.3148306906223297f) {
                                        if (features[26] <= -0.189268060028553f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[11] <= -0.8209632933139801f) {
                                        return 2;                                    } else {
                                        if (features[8] <= -0.1460522934794426f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[3] <= 0.4435594826936722f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[20] <= 0.0383935309946537f) {
                if (features[27] <= -0.02160521224141121f) {
                    if (features[6] <= -0.9981719255447388f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    if (features[4] <= 0.007585567771457136f) {
                        return 2;                    } else {
                        return 0;                    }
                }
            } else {
                if (features[2] <= -0.9757506549358368f) {
                    return 0;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 83
int predict_tree_83(const float* features) {
    // Max depth: 10
    if (features[19] <= -0.454338937997818f) {
        if (features[4] <= 0.2928275316953659f) {
            if (features[18] <= -0.419345885515213f) {
                if (features[3] <= -0.29643912613391876f) {
                    if (features[11] <= 0.2585940510034561f) {
                        if (features[13] <= -0.22438295930624008f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[24] <= -0.31098972260951996f) {
                            return 1;                        } else {
                            return 0;                        }
                    }
                } else {
                    return 0;                }
            } else {
                return 1;            }
        } else {
            if (features[12] <= 0.10221266373991966f) {
                if (features[21] <= 1.5246081054210663f) {
                    if (features[8] <= 0.09188399836421013f) {
                        if (features[0] <= -0.5828909277915955f) {
                            return 1;                        } else {
                            return 0;                        }
                    } else {
                        return 0;                    }
                } else {
                    return 2;                }
            } else {
                if (features[23] <= 2.599723756313324f) {
                    return 1;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[10] <= -0.2402692660689354f) {
            if (features[25] <= 0.20455151796340942f) {
                if (features[4] <= 0.0870007798075676f) {
                    if (features[17] <= -0.379781037569046f) {
                        if (features[11] <= -0.27480198442935944f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[23] <= -0.3179345279932022f) {
                            if (features[9] <= -0.7510297298431396f) {
                                if (features[0] <= -0.33870692551136017f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            } else {
                                if (features[21] <= -0.5642624795436859f) {
                                    if (features[10] <= -0.35943278670310974f) {
                                        return 0;                                    } else {
                                        if (features[2] <= -0.09827011078596115f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    return 1;                                }
                            }
                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[26] <= -0.05620685196481645f) {
                        if (features[10] <= -0.34042903780937195f) {
                            return 1;                        } else {
                            if (features[24] <= 0.0036489516496658325f) {
                                return 1;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[0] <= -0.32964804768562317f) {
                            return 1;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[0] <= -0.4622834622859955f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[3] <= 1.9036642611026764f) {
                return 2;            } else {
                return 0;            }
        }
    }
}

// Tree 84
int predict_tree_84(const float* features) {
    // Max depth: 10
    if (features[18] <= -0.2254994511604309f) {
        if (features[20] <= 0.12407297268509865f) {
            if (features[1] <= -0.35448597371578217f) {
                return 0;            } else {
                if (features[9] <= -0.3999810218811035f) {
                    if (features[7] <= -1.3219659179449081f) {
                        return 0;                    } else {
                        if (features[2] <= -0.09827011078596115f) {
                            if (features[25] <= -0.3610485941171646f) {
                                if (features[27] <= -0.2612495422363281f) {
                                    if (features[17] <= -0.37846729159355164f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 0;                                }
                            } else {
                                return 0;                            }
                        } else {
                            if (features[5] <= -0.38626159727573395f) {
                                return 1;                            } else {
                                if (features[17] <= -0.3714115619659424f) {
                                    if (features[0] <= -0.3763091266155243f) {
                                        if (features[25] <= -0.37160123884677887f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[7] <= 0.014156778808683157f) {
                                        if (features[0] <= -0.36668506264686584f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[26] <= -0.35413308441638947f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        }
                    }
                } else {
                    if (features[23] <= -0.2963055819272995f) {
                        return 0;                    } else {
                        return 0;                    }
                }
            }
        } else {
            if (features[7] <= 0.4264164865016937f) {
                if (features[17] <= -0.47472384572029114f) {
                    if (features[4] <= 0.4545391798019409f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[10] <= -0.1354660429060459f) {
                        if (features[4] <= 0.6722736656665802f) {
                            if (features[24] <= 0.0036544334143400192f) {
                                return 1;                            } else {
                                if (features[21] <= 0.5788666009902954f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[0] <= -0.36841098964214325f) {
                                return 1;                            } else {
                                return 2;                            }
                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[21] <= 1.5861250162124634f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[2] <= -0.958857998251915f) {
            return 0;        } else {
            return 2;        }
    }
}

// Tree 85
int predict_tree_85(const float* features) {
    // Max depth: 10
    if (features[24] <= -0.1278594508767128f) {
        if (features[0] <= -0.37585754692554474f) {
            return 0;        } else {
            if (features[23] <= -0.2951138764619827f) {
                return 1;            } else {
                return 2;            }
        }
    } else {
        if (features[1] <= -0.06946076825261116f) {
            if (features[5] <= 0.2748727425932884f) {
                if (features[1] <= -0.517544150352478f) {
                    if (features[23] <= 0.05218023248016834f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[0] <= -0.2271149605512619f) {
                        if (features[22] <= 0.1132185235619545f) {
                            return 0;                        } else {
                            if (features[25] <= -0.09879738464951515f) {
                                return 0;                            } else {
                                if (features[23] <= -0.10019267722964287f) {
                                    return 0;                                } else {
                                    if (features[14] <= -1.2053719758987427f) {
                                        return 1;                                    } else {
                                        if (features[18] <= -0.004372505587525666f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[5] <= 0.4560951143503189f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[7] <= 1.9035120010375977f) {
                if (features[9] <= -0.15619825571775436f) {
                    if (features[24] <= 0.27259358763694763f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    return 2;                }
            } else {
                if (features[5] <= 0.03516018111258745f) {
                    return 2;                } else {
                    return 0;                }
            }
        }
    }
}

// Tree 86
int predict_tree_86(const float* features) {
    // Max depth: 10
    if (features[4] <= 0.12252254039049149f) {
        if (features[10] <= -0.364113450050354f) {
            return 0;        } else {
            if (features[20] <= -0.42260362207889557f) {
                if (features[17] <= -0.37572602927684784f) {
                    if (features[0] <= -0.3758145868778229f) {
                        if (features[11] <= -0.026415382511913776f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                } else {
                    return 1;                }
            } else {
                if (features[22] <= 0.05568571202456951f) {
                    if (features[6] <= -0.9981719255447388f) {
                        return 0;                    } else {
                        if (features[7] <= -0.08109098672866821f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[1] <= -0.07243609055876732f) {
            if (features[5] <= 0.5371413230895996f) {
                if (features[1] <= -0.4887845516204834f) {
                    if (features[10] <= -0.565994530916214f) {
                        if (features[25] <= -0.016246885992586613f) {
                            if (features[1] <= -0.5523462295532227f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[1] <= -0.5517595410346985f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[17] <= -0.24509385973215103f) {
                        if (features[10] <= -0.2069772630929947f) {
                            if (features[19] <= 0.07130791881354526f) {
                                if (features[9] <= 1.111545979976654f) {
                                    if (features[9] <= 0.8500505685806274f) {
                                        if (features[23] <= 0.05914177559316158f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                return 1;                            }
                        } else {
                            return 1;                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[8] <= -0.30789199471473694f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[21] <= 0.08983135223388672f) {
                return 2;            } else {
                return 2;            }
        }
    }
}

// Tree 87
int predict_tree_87(const float* features) {
    // Max depth: 9
    if (features[18] <= -0.22779415547847748f) {
        if (features[5] <= -0.06248665042221546f) {
            if (features[19] <= -0.40977220237255096f) {
                if (features[12] <= 0.07301074638962746f) {
                    if (features[19] <= -0.44183431565761566f) {
                        return 0;                    } else {
                        if (features[1] <= -0.356849804520607f) {
                            if (features[11] <= -0.34018590301275253f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[0] <= -0.3745678663253784f) {
                        if (features[25] <= -0.48742708563804626f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                }
            } else {
                if (features[19] <= -0.39547955989837646f) {
                    if (features[26] <= -0.2273440957069397f) {
                        if (features[7] <= -1.2675382047891617f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[17] <= -0.4068557769060135f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[10] <= -0.35496382415294647f) {
                        return 0;                    } else {
                        if (features[12] <= -0.28515908867120743f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            }
        } else {
            if (features[4] <= 1.5417509078979492f) {
                if (features[0] <= -0.5314852893352509f) {
                    if (features[22] <= 0.1210809014737606f) {
                        if (features[19] <= -0.5837863087654114f) {
                            if (features[9] <= 0.710263580083847f) {
                                return 0;                            } else {
                                return 1;                            }
                        } else {
                            if (features[12] <= -0.013524016831070185f) {
                                return 0;                            } else {
                                return 0;                            }
                        }
                    } else {
                        if (features[21] <= 0.442925289273262f) {
                            if (features[2] <= -0.5393565893173218f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[17] <= -0.26600807905197144f) {
                        if (features[7] <= 0.6118143796920776f) {
                            if (features[17] <= -0.37945929169654846f) {
                                return 1;                            } else {
                                if (features[11] <= 0.4913231134414673f) {
                                    if (features[4] <= 0.4703758805990219f) {
                                        return 1;                                    } else {
                                        return 2;                                    }
                                } else {
                                    return 2;                                }
                            }
                        } else {
                            return 2;                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[17] <= -0.5053368806838989f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[20] <= 0.06350143067538738f) {
            if (features[6] <= -0.9981719255447388f) {
                return 0;            } else {
                return 2;            }
        } else {
            if (features[4] <= 0.18305863440036774f) {
                if (features[9] <= 0.44269825518131256f) {
                    return 2;                } else {
                    return 1;                }
            } else {
                return 2;            }
        }
    }
}

// Tree 88
int predict_tree_88(const float* features) {
    // Max depth: 9
    if (features[5] <= -0.1309334635734558f) {
        if (features[19] <= -0.38985390961170197f) {
            if (features[17] <= -0.3808556944131851f) {
                return 0;            } else {
                if (features[17] <= -0.37325596809387207f) {
                    return 1;                } else {
                    return 1;                }
            }
        } else {
            if (features[26] <= -0.19638514518737793f) {
                if (features[17] <= -0.379781037569046f) {
                    return 0;                } else {
                    if (features[5] <= -0.34911197423934937f) {
                        if (features[24] <= -0.35013167560100555f) {
                            if (features[0] <= -0.37597908079624176f) {
                                return 0;                            } else {
                                return 1;                            }
                        } else {
                            return 0;                        }
                    } else {
                        return 0;                    }
                }
            } else {
                if (features[6] <= -0.4468248710036278f) {
                    return 2;                } else {
                    if (features[10] <= -0.44291120767593384f) {
                        return 0;                    } else {
                        return 0;                    }
                }
            }
        }
    } else {
        if (features[20] <= 1.061827838420868f) {
            if (features[2] <= -0.47084741294384f) {
                return 0;            } else {
                if (features[10] <= -0.1354660429060459f) {
                    if (features[21] <= 0.11980712041258812f) {
                        return 0;                    } else {
                        if (features[19] <= -0.4545436352491379f) {
                            if (features[20] <= 0.2963595539331436f) {
                                if (features[31] <= 0.16302114725112915f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                if (features[2] <= 0.11758071696385741f) {
                                    if (features[8] <= 0.037332458421587944f) {
                                        return 1;                                    } else {
                                        return 0;                                    }
                                } else {
                                    if (features[28] <= 0.03392469882965088f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                }
                            }
                        } else {
                            if (features[27] <= -0.3062521070241928f) {
                                return 2;                            } else {
                                if (features[1] <= -0.2535259425640106f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        }
                    }
                } else {
                    if (features[17] <= -0.14776424318552017f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[24] <= 0.18854912370443344f) {
                if (features[18] <= -0.3622649759054184f) {
                    if (features[8] <= -0.16137079149484634f) {
                        if (features[10] <= -0.361130952835083f) {
                            return 1;                        } else {
                            return 2;                        }
                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            } else {
                if (features[11] <= -1.919951856136322f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 89
int predict_tree_89(const float* features) {
    // Max depth: 8
    if (features[22] <= 0.12021179869771004f) {
        if (features[17] <= -0.39827775955200195f) {
            if (features[22] <= -0.18619868159294128f) {
                return 0;            } else {
                if (features[13] <= 0.9031216502189636f) {
                    if (features[21] <= -0.24267948418855667f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    return 1;                }
            }
        } else {
            if (features[20] <= -0.26408102735877037f) {
                if (features[19] <= -0.36411765217781067f) {
                    if (features[19] <= -0.3681091219186783f) {
                        if (features[18] <= -0.3832859694957733f) {
                            if (features[0] <= -0.37829655408859253f) {
                                if (features[18] <= -0.4002903997898102f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        } else {
                            if (features[0] <= -0.37597908079624176f) {
                                if (features[14] <= -0.2041439265012741f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        }
                    } else {
                        return 0;                    }
                } else {
                    if (features[0] <= -0.3741089701652527f) {
                        return 0;                    } else {
                        if (features[18] <= -0.3574451506137848f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[21] <= 0.058532532304525375f) {
                    if (features[10] <= 0.778236597776413f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    if (features[19] <= 0.1088857538998127f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[10] <= -0.14812666922807693f) {
            if (features[24] <= 0.4745195060968399f) {
                if (features[1] <= -0.4421270489692688f) {
                    if (features[8] <= 0.034180013462901115f) {
                        if (features[7] <= -3.359168767929077f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[27] <= -0.013283776119351387f) {
                            if (features[8] <= 0.07652056589722633f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            if (features[5] <= -0.004704053630121052f) {
                                return 0;                            } else {
                                if (features[7] <= -0.504954382777214f) {
                                    return 1;                                } else {
                                    return 0;                                }
                            }
                        }
                    }
                } else {
                    if (features[18] <= -0.004372505587525666f) {
                        if (features[11] <= 0.11159082874655724f) {
                            if (features[19] <= 0.07130791881354526f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            if (features[20] <= 0.44092659652233124f) {
                                return 1;                            } else {
                                return 2;                            }
                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[20] <= 1.581420123577118f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[2] <= -0.45020081102848053f) {
                return 2;            } else {
                return 2;            }
        }
    }
}

// Tree 90
int predict_tree_90(const float* features) {
    // Max depth: 10
    if (features[1] <= -0.423549547791481f) {
        if (features[20] <= 0.3744259476661682f) {
            return 0;        } else {
            if (features[21] <= 1.2562401592731476f) {
                return 1;            } else {
                return 2;            }
        }
    } else {
        if (features[15] <= 0.7462623417377472f) {
            if (features[0] <= -0.2918366491794586f) {
                if (features[5] <= 1.4486486986279488f) {
                    if (features[1] <= -0.40174736082553864f) {
                        return 0;                    } else {
                        if (features[20] <= -0.6398020684719086f) {
                            return 0;                        } else {
                            if (features[12] <= 0.08148667216300964f) {
                                if (features[20] <= 0.08781273104250431f) {
                                    if (features[10] <= -0.36021170020103455f) {
                                        if (features[6] <= 0.5455998182296753f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        if (features[8] <= -0.08803584054112434f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                return 0;                            }
                        }
                    }
                } else {
                    if (features[19] <= -0.45000796020030975f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[2] <= -0.9494731724262238f) {
                    return 0;                } else {
                    if (features[12] <= -0.2211659774184227f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[6] <= -0.9981719255447388f) {
                if (features[7] <= 1.5623512268066406f) {
                    if (features[0] <= -0.20697776973247528f) {
                        if (features[18] <= -0.48333731293678284f) {
                            return 1;                        } else {
                            return 2;                        }
                    } else {
                        return 2;                    }
                } else {
                    return 0;                }
            } else {
                if (features[1] <= -0.10915492475032806f) {
                    if (features[17] <= -0.39456191658973694f) {
                        if (features[9] <= -1.0217601656913757f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[26] <= 0.446509450674057f) {
                            if (features[31] <= 0.16302114725112915f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[6] <= -0.7776331007480621f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 91
int predict_tree_91(const float* features) {
    // Max depth: 10
    if (features[1] <= -0.42356155812740326f) {
        if (features[25] <= 0.0031086986418813467f) {
            if (features[4] <= 0.43915581703186035f) {
                return 0;            } else {
                return 1;            }
        } else {
            if (features[25] <= 0.9517059829086065f) {
                return 1;            } else {
                if (features[9] <= -1.1017342805862427f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[1] <= -0.15766572952270508f) {
            if (features[5] <= 1.2058740556240082f) {
                if (features[27] <= -0.3109426945447922f) {
                    if (features[9] <= 0.28826312720775604f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    if (features[3] <= 0.299538254737854f) {
                        if (features[4] <= -0.5774959325790405f) {
                            return 0;                        } else {
                            if (features[2] <= 0.26773782074451447f) {
                                if (features[24] <= -0.11463867872953415f) {
                                    return 0;                                } else {
                                    return 2;                                }
                            } else {
                                if (features[17] <= -0.4011343717575073f) {
                                    if (features[25] <= -0.34821414947509766f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    if (features[11] <= -0.18052831292152405f) {
                                        if (features[0] <= -0.38488832116127014f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[9] <= -0.5961942970752716f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        if (features[10] <= -0.4144674390554428f) {
                            return 0;                        } else {
                            if (features[23] <= -0.14651466261420865f) {
                                if (features[17] <= -0.379781037569046f) {
                                    if (features[15] <= 0.7462623417377472f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    if (features[24] <= -0.3489517420530319f) {
                                        if (features[10] <= -0.3550563454627991f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 0;                                    }
                                }
                            } else {
                                if (features[8] <= -0.16823969036340714f) {
                                    if (features[17] <= -0.37397433817386627f) {
                                        return 1;                                    } else {
                                        return 2;                                    }
                                } else {
                                    return 1;                                }
                            }
                        }
                    }
                }
            } else {
                if (features[12] <= -0.3510131202638149f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[3] <= 1.8797933459281921f) {
                if (features[26] <= -0.36343546211719513f) {
                    return 2;                } else {
                    return 2;                }
            } else {
                return 0;            }
        }
    }
}

// Tree 92
int predict_tree_92(const float* features) {
    // Max depth: 10
    if (features[17] <= -0.44954729080200195f) {
        if (features[5] <= -0.030889268033206463f) {
            return 0;        } else {
            if (features[22] <= 1.2913020849227905f) {
                if (features[4] <= 0.2922734469175339f) {
                    return 0;                } else {
                    if (features[11] <= 0.00929222907871008f) {
                        if (features[1] <= -0.5474299788475037f) {
                            return 1;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[18] <= -0.2300560474395752f) {
            if (features[23] <= 0.3559298515319824f) {
                if (features[18] <= -0.4302047789096832f) {
                    if (features[1] <= -0.3567028194665909f) {
                        if (features[20] <= -0.6952511966228485f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[21] <= -0.6406461298465729f) {
                        return 0;                    } else {
                        if (features[9] <= -0.3855763077735901f) {
                            if (features[0] <= -0.37586139142513275f) {
                                if (features[21] <= -0.6371213793754578f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        } else {
                            if (features[8] <= -0.21766730397939682f) {
                                return 2;                            } else {
                                if (features[11] <= 0.47158950567245483f) {
                                    if (features[10] <= -0.34722933173179626f) {
                                        return 1;                                    } else {
                                        if (features[22] <= 0.4471271187067032f) {
                                            return 1;                                        } else {
                                            return 2;                                        }
                                    }
                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                }
            } else {
                if (features[17] <= -0.44913771748542786f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[1] <= -0.2709690108895302f) {
                return 1;            } else {
                if (features[7] <= 1.9035120010375977f) {
                    if (features[25] <= 0.21395162492990494f) {
                        return 2;                    } else {
                        if (features[9] <= -0.15619825571775436f) {
                            if (features[4] <= 0.06462590023875237f) {
                                return 2;                            } else {
                                return 2;                            }
                        } else {
                            if (features[7] <= -0.47990424931049347f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[2] <= 0.2771226763725281f) {
                        return 0;                    } else {
                        if (features[30] <= 0.17709434032440186f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    }
}

// Tree 93
int predict_tree_93(const float* features) {
    // Max depth: 10
    if (features[1] <= -0.42356155812740326f) {
        if (features[25] <= 0.0003669685684144497f) {
            if (features[4] <= 0.42289599776268005f) {
                return 0;            } else {
                return 1;            }
        } else {
            if (features[23] <= 0.8651501424610615f) {
                if (features[7] <= -0.6034747362136841f) {
                    return 1;                } else {
                    return 0;                }
            } else {
                return 2;            }
        }
    } else {
        if (features[17] <= -0.23100721091032028f) {
            if (features[21] <= 1.5400201082229614f) {
                if (features[1] <= -0.39716899394989014f) {
                    if (features[5] <= -0.1358840987086296f) {
                        if (features[30] <= 0.17709434032440186f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[24] <= -0.3895987272262573f) {
                        return 0;                    } else {
                        if (features[0] <= -0.4303678572177887f) {
                            return 0;                        } else {
                            if (features[5] <= -0.11617184430360794f) {
                                if (features[18] <= -0.39643295109272003f) {
                                    if (features[0] <= -0.3745678663253784f) {
                                        if (features[1] <= -0.3957200050354004f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[3] <= 0.5708710551261902f) {
                                        if (features[5] <= -0.34911197423934937f) {
                                            return 1;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        if (features[22] <= -0.635152667760849f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    }
                                }
                            } else {
                                if (features[19] <= 0.07130791881354526f) {
                                    if (features[9] <= 1.0754674673080444f) {
                                        if (features[4] <= 0.427499920129776f) {
                                            return 1;                                        } else {
                                            return 2;                                        }
                                    } else {
                                        if (features[8] <= -0.16159772127866745f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    return 1;                                }
                            }
                        }
                    }
                }
            } else {
                if (features[30] <= 0.17709434032440186f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[2] <= -0.9569810330867767f) {
                return 0;            } else {
                return 2;            }
        }
    }
}

// Tree 94
int predict_tree_94(const float* features) {
    // Max depth: 10
    if (features[18] <= -0.451093852519989f) {
        if (features[20] <= 0.3231816440820694f) {
            if (features[17] <= -0.40198753774166107f) {
                return 0;            } else {
                return 1;            }
        } else {
            if (features[23] <= 0.30937691405415535f) {
                if (features[4] <= 0.46065424382686615f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                if (features[16] <= 3.1667469069361687f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[19] <= -0.20676681399345398f) {
            if (features[25] <= 1.0899469703435898f) {
                if (features[25] <= -0.3889715075492859f) {
                    return 0;                } else {
                    if (features[19] <= -0.42979924380779266f) {
                        if (features[17] <= -0.3897888511419296f) {
                            if (features[11] <= -0.338212288916111f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[26] <= 0.6967830657958984f) {
                            if (features[23] <= 0.259522020816803f) {
                                if (features[11] <= 0.47158950567245483f) {
                                    if (features[0] <= -0.43021006882190704f) {
                                        return 0;                                    } else {
                                        if (features[22] <= -0.42345456779003143f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    return 2;                                }
                            } else {
                                return 2;                            }
                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[0] <= -0.45210716128349304f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[3] <= 1.8797933459281921f) {
                if (features[18] <= -0.2300560474395752f) {
                    return 1;                } else {
                    if (features[4] <= 0.18270603567361832f) {
                        if (features[9] <= 0.49291183054447174f) {
                            return 2;                        } else {
                            return 1;                        }
                    } else {
                        if (features[5] <= -0.15606216341257095f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                return 0;            }
        }
    }
}

// Tree 95
int predict_tree_95(const float* features) {
    // Max depth: 10
    if (features[0] <= -0.4502800852060318f) {
        if (features[16] <= 3.1667469069361687f) {
            if (features[20] <= 0.4011371284723282f) {
                return 0;            } else {
                if (features[21] <= 1.2921342551708221f) {
                    if (features[28] <= 0.03392469882965088f) {
                        return 1;                    } else {
                        if (features[17] <= -0.5770770907402039f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[20] <= 1.7900577411055565f) {
                return 0;            } else {
                return 2;            }
        }
    } else {
        if (features[0] <= -0.21553847193717957f) {
            if (features[7] <= 0.666158139705658f) {
                if (features[9] <= 0.44187258183956146f) {
                    if (features[22] <= -0.5631482601165771f) {
                        if (features[22] <= -0.6424592435359955f) {
                            return 0;                        } else {
                            if (features[10] <= -0.36339689791202545f) {
                                if (features[20] <= -0.641334742307663f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                if (features[17] <= -0.3799618184566498f) {
                                    return 0;                                } else {
                                    if (features[2] <= -0.09827011078596115f) {
                                        if (features[5] <= -0.36301155388355255f) {
                                            return 1;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        if (features[17] <= -0.3714115619659424f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        if (features[1] <= -0.23358701169490814f) {
                            if (features[18] <= -0.48413702845573425f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[15] <= 0.7462623417377472f) {
                        return 1;                    } else {
                        if (features[3] <= 0.5362582206726074f) {
                            if (features[18] <= -0.35913461446762085f) {
                                return 2;                            } else {
                                return 1;                            }
                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[24] <= 3.1885567903518677f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[22] <= 0.05463469959795475f) {
                if (features[1] <= 0.30708347260951996f) {
                    return 2;                } else {
                    if (features[20] <= -0.11039849743247032f) {
                        return 0;                    } else {
                        return 0;                    }
                }
            } else {
                return 2;            }
        }
    }
}

// Tree 96
int predict_tree_96(const float* features) {
    // Max depth: 9
    if (features[21] <= 0.11983741819858551f) {
        if (features[0] <= -0.3756202161312103f) {
            return 0;        } else {
            if (features[6] <= -0.11601662635803223f) {
                if (features[4] <= 0.05639524757862091f) {
                    if (features[7] <= 0.8859101459383965f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    if (features[6] <= -0.9981719255447388f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                return 1;            }
        }
    } else {
        if (features[17] <= -0.22705212235450745f) {
            if (features[24] <= 0.4745195060968399f) {
                if (features[17] <= -0.5686802864074707f) {
                    if (features[5] <= 0.0338671812787652f) {
                        if (features[10] <= -0.569230705499649f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[23] <= -0.0963713526725769f) {
                        return 0;                    } else {
                        if (features[12] <= -0.3007810339331627f) {
                            if (features[7] <= 0.05198014248162508f) {
                                return 1;                            } else {
                                return 2;                            }
                        } else {
                            if (features[1] <= -0.30674920976161957f) {
                                if (features[10] <= -0.34881940484046936f) {
                                    if (features[12] <= 0.35876771807670593f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[7] <= -0.16070537827908993f) {
                                        return 1;                                    } else {
                                        return 2;                                    }
                                }
                            } else {
                                if (features[22] <= 0.3751327842473984f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                }
            } else {
                if (features[16] <= 3.1667469069361687f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[3] <= -2.1822421550750732f) {
                return 2;            } else {
                return 2;            }
        }
    }
}

// Tree 97
int predict_tree_97(const float* features) {
    // Max depth: 10
    if (features[25] <= -0.13018885254859924f) {
        if (features[11] <= 0.04113292507827282f) {
            if (features[18] <= -0.3763810694217682f) {
                if (features[5] <= 0.027590757235884666f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                if (features[6] <= -0.005747221410274506f) {
                    if (features[22] <= -0.1325768530368805f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    if (features[1] <= -0.3375915288925171f) {
                        return 0;                    } else {
                        if (features[8] <= 0.07315976545214653f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            }
        } else {
            if (features[10] <= -0.3606458306312561f) {
                if (features[17] <= -0.5913306772708893f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[5] <= -0.2354905754327774f) {
                    if (features[14] <= -0.14779894053936005f) {
                        if (features[19] <= -0.4011861979961395f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[18] <= -0.0075117365922778845f) {
            if (features[6] <= -1.6597883701324463f) {
                if (features[21] <= 1.1254092752933502f) {
                    if (features[17] <= -0.5089624375104904f) {
                        if (features[25] <= 0.03286611661314964f) {
                            if (features[31] <= 0.16302114725112915f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            } else {
                if (features[9] <= 0.401488333940506f) {
                    if (features[24] <= 1.6635342985391617f) {
                        if (features[24] <= -0.16194388270378113f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[5] <= 3.4288620948791504f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[6] <= 0.2147916005924344f) {
                        if (features[25] <= -0.0996272936463356f) {
                            return 0;                        } else {
                            if (features[1] <= -0.1487656682729721f) {
                                if (features[12] <= -0.3007810339331627f) {
                                    return 1;                                } else {
                                    if (features[19] <= -0.4820723235607147f) {
                                        return 0;                                    } else {
                                        if (features[11] <= 0.4594182223081589f) {
                                            return 1;                                        } else {
                                            return 2;                                        }
                                    }
                                }
                            } else {
                                if (features[13] <= 0.016197174787521362f) {
                                    return 2;                                } else {
                                    return 1;                                }
                            }
                        }
                    } else {
                        if (features[24] <= -0.03728098422288895f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                }
            }
        } else {
            if (features[24] <= 0.06545727699995041f) {
                if (features[21] <= -0.025435972143895924f) {
                    return 0;                } else {
                    if (features[0] <= -0.016082310117781162f) {
                        return 1;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[23] <= 0.2159610614180565f) {
                    if (features[2] <= -0.9579195082187653f) {
                        if (features[20] <= -0.09039284661412239f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[3] <= 1.8797933459281921f) {
                        return 2;                    } else {
                        if (features[22] <= 0.025448900647461414f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                }
            }
        }
    }
}

// Tree 98
int predict_tree_98(const float* features) {
    // Max depth: 10
    if (features[0] <= -0.45059768855571747f) {
        if (features[21] <= 0.43252262473106384f) {
            if (features[23] <= 0.045210414566099644f) {
                return 0;            } else {
                return 1;            }
        } else {
            if (features[21] <= 1.5246081054210663f) {
                if (features[9] <= 0.9958835244178772f) {
                    return 1;                } else {
                    return 1;                }
            } else {
                return 2;            }
        }
    } else {
        if (features[1] <= -0.1598765328526497f) {
            if (features[23] <= 1.8244200199842453f) {
                if (features[0] <= -0.4301111698150635f) {
                    return 0;                } else {
                    if (features[9] <= -0.7597196102142334f) {
                        return 0;                    } else {
                        if (features[22] <= -0.42345456779003143f) {
                            if (features[0] <= -0.3758653551340103f) {
                                if (features[29] <= -0.0025959014892578125f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        } else {
                            if (features[11] <= 0.15761509165167809f) {
                                if (features[0] <= -0.3205791115760803f) {
                                    if (features[20] <= 0.08111729100346565f) {
                                        return 1;                                    } else {
                                        if (features[8] <= -0.17914968729019165f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    return 2;                                }
                            } else {
                                if (features[4] <= 0.427499920129776f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                }
            } else {
                if (features[4] <= 1.5847880244255066f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[3] <= 1.8758148550987244f) {
                if (features[8] <= 0.15209679305553436f) {
                    if (features[15] <= 0.7462623417377472f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    return 1;                }
            } else {
                return 0;            }
        }
    }
}

// Tree 99
int predict_tree_99(const float* features) {
    // Max depth: 10
    if (features[10] <= -0.4366086274385452f) {
        if (features[4] <= 0.46065424382686615f) {
            return 0;        } else {
            if (features[0] <= -0.53178271651268f) {
                return 1;            } else {
                if (features[19] <= -0.5048018097877502f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[1] <= -0.07243609055876732f) {
            if (features[34] <= -2.0389932096004486f) {
                return 2;            } else {
                if (features[1] <= -0.40191370248794556f) {
                    if (features[12] <= -0.23699016869068146f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    if (features[17] <= -0.26600807905197144f) {
                        if (features[7] <= -1.277982771396637f) {
                            return 0;                        } else {
                            if (features[25] <= -0.11155104264616966f) {
                                if (features[18] <= -0.39818641543388367f) {
                                    if (features[9] <= -0.6808435320854187f) {
                                        if (features[20] <= -0.6456000804901123f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        if (features[26] <= -0.02915639989078045f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    if (features[3] <= -0.40783676505088806f) {
                                        return 0;                                    } else {
                                        if (features[17] <= -0.37916359305381775f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            } else {
                                if (features[15] <= 0.7462623417377472f) {
                                    if (features[31] <= 0.16302114725112915f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[31] <= 0.16302114725112915f) {
                                        return 2;                                    } else {
                                        if (features[22] <= 0.9991207420825958f) {
                                            return 1;                                        } else {
                                            return 2;                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        if (features[4] <= 0.21260636299848557f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[2] <= -0.9504116624593735f) {
                if (features[7] <= 1.8921182751655579f) {
                    return 2;                } else {
                    return 0;                }
            } else {
                if (features[24] <= -0.15829500555992126f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 100
int predict_tree_100(const float* features) {
    // Max depth: 10
    if (features[0] <= -0.4496677815914154f) {
        if (features[21] <= 0.2743822932243347f) {
            return 0;        } else {
            if (features[1] <= -0.48609672486782074f) {
                if (features[26] <= -0.35761915147304535f) {
                    return 0;                } else {
                    if (features[8] <= 0.0955120101571083f) {
                        return 1;                    } else {
                        return 0;                    }
                }
            } else {
                if (features[0] <= -0.5058113634586334f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[22] <= 1.0526920557022095f) {
            if (features[10] <= -0.16542113199830055f) {
                if (features[10] <= -0.3835560083389282f) {
                    if (features[33] <= -0.7310653924942017f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[5] <= -0.39662186801433563f) {
                        return 0;                    } else {
                        if (features[3] <= 0.5708710551261902f) {
                            if (features[10] <= -0.3583320379257202f) {
                                if (features[19] <= -0.33430027961730957f) {
                                    if (features[28] <= -0.4683038666844368f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                if (features[21] <= 0.47575923800468445f) {
                                    if (features[5] <= -0.3665432631969452f) {
                                        if (features[17] <= -0.3733074367046356f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[20] <= -0.6267136931419373f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[24] <= -0.37337277829647064f) {
                                return 0;                            } else {
                                return 0;                            }
                        }
                    }
                }
            } else {
                if (features[3] <= 1.8042020797729492f) {
                    if (features[17] <= -0.2017674222588539f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    return 0;                }
            }
        } else {
            if (features[5] <= 0.2149413377046585f) {
                if (features[18] <= -0.2254994511604309f) {
                    if (features[3] <= 0.6106559336185455f) {
                        if (features[12] <= 0.05918886698782444f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        if (features[12] <= 0.10010535456240177f) {
                            return 1;                        } else {
                            return 2;                        }
                    }
                } else {
                    return 2;                }
            } else {
                return 2;            }
        }
    }
}

// Tree 101
int predict_tree_101(const float* features) {
    // Max depth: 10
    if (features[17] <= -0.4512464851140976f) {
        if (features[7] <= 0.6562467813491821f) {
            if (features[13] <= 0.24066703766584396f) {
                if (features[33] <= -0.7310653924942017f) {
                    if (features[24] <= 0.0489112064242363f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    return 0;                }
            } else {
                if (features[11] <= 0.11209135502576828f) {
                    if (features[26] <= -0.3577331304550171f) {
                        return 1;                    } else {
                        if (features[18] <= -0.4911089986562729f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[17] <= -0.5702398717403412f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            }
        } else {
            if (features[4] <= 1.1968593709170818f) {
                return 0;            } else {
                if (features[21] <= 2.5046075582504272f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[10] <= -0.1354660429060459f) {
            if (features[23] <= 0.253122515976429f) {
                if (features[18] <= -0.4300442039966583f) {
                    return 0;                } else {
                    if (features[1] <= -0.40189267694950104f) {
                        return 0;                    } else {
                        if (features[6] <= 0.5455998182296753f) {
                            if (features[11] <= 0.47158950567245483f) {
                                if (features[27] <= -0.2945447564125061f) {
                                    if (features[20] <= -0.5844235122203827f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[20] <= -0.6749228835105896f) {
                                        return 0;                                    } else {
                                        if (features[11] <= -0.08843844011425972f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            } else {
                                return 2;                            }
                        } else {
                            if (features[17] <= -0.379781037569046f) {
                                return 0;                            } else {
                                if (features[1] <= -0.3429037630558014f) {
                                    return 0;                                } else {
                                    if (features[0] <= -0.3759319484233856f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                if (features[16] <= 3.1667469069361687f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[3] <= 1.8758148550987244f) {
                if (features[6] <= -1.6597883701324463f) {
                    return 2;                } else {
                    return 2;                }
            } else {
                return 0;            }
        }
    }
}

// Tree 102
int predict_tree_102(const float* features) {
    // Max depth: 10
    if (features[17] <= -0.4506490230560303f) {
        if (features[22] <= 0.2708299309015274f) {
            return 0;        } else {
            if (features[4] <= 1.5194363594055176f) {
                if (features[12] <= 0.003567392996046692f) {
                    return 0;                } else {
                    if (features[8] <= 0.09188399836421013f) {
                        return 1;                    } else {
                        return 0;                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[4] <= 1.0517802834510803f) {
            if (features[18] <= -0.2744351625442505f) {
                if (features[0] <= -0.3846000134944916f) {
                    if (features[20] <= 0.061998991295695305f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    if (features[10] <= -0.1354660429060459f) {
                        if (features[6] <= -0.9981718957424164f) {
                            if (features[27] <= 0.3034534677863121f) {
                                return 2;                            } else {
                                if (features[17] <= -0.3751832842826843f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        } else {
                            if (features[8] <= -0.08803584054112434f) {
                                if (features[18] <= -0.3730659484863281f) {
                                    if (features[3] <= 0.5708710551261902f) {
                                        if (features[17] <= -0.37529483437538147f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 0;                                    }
                                } else {
                                    if (features[10] <= -0.35747258365154266f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                if (features[7] <= 0.42499858140945435f) {
                                    return 1;                                } else {
                                    return 0;                                }
                            }
                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[20] <= 0.053659938275814056f) {
                    if (features[10] <= 0.9457392394542694f) {
                        if (features[20] <= -0.06523452908731997f) {
                            return 0;                        } else {
                            return 2;                        }
                    } else {
                        return 0;                    }
                } else {
                    if (features[4] <= 0.20141388475894928f) {
                        if (features[27] <= 1.2069505155086517f) {
                            return 2;                        } else {
                            return 2;                        }
                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[34] <= -2.0389932096004486f) {
                return 2;            } else {
                if (features[25] <= 0.007752417819574475f) {
                    return 2;                } else {
                    if (features[0] <= -0.37436486780643463f) {
                        if (features[3] <= 0.6774945259094238f) {
                            if (features[20] <= 1.493552565574646f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            return 1;                        }
                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 103
int predict_tree_103(const float* features) {
    // Max depth: 10
    if (features[19] <= -0.46442821621894836f) {
        if (features[4] <= 0.46065424382686615f) {
            if (features[0] <= -0.3513966202735901f) {
                return 0;            } else {
                return 1;            }
        } else {
            if (features[22] <= 1.7980921268463135f) {
                return 1;            } else {
                if (features[17] <= -0.5055481493473053f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[15] <= 0.7462623417377472f) {
            if (features[1] <= -0.1578988879919052f) {
                if (features[21] <= 1.5409896969795227f) {
                    if (features[8] <= -0.18637104332447052f) {
                        if (features[18] <= -0.4034825265407562f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        if (features[17] <= -0.43034209311008453f) {
                            return 0;                        } else {
                            if (features[20] <= -0.6398020684719086f) {
                                return 0;                            } else {
                                if (features[25] <= -0.3017030209302902f) {
                                    if (features[0] <= -0.37592414021492004f) {
                                        if (features[4] <= -0.6363798081874847f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 1;                                }
                            }
                        }
                    }
                } else {
                    if (features[0] <= -0.47378115355968475f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[4] <= 0.056465767323970795f) {
                    return 0;                } else {
                    if (features[22] <= 0.11014633253216743f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[10] <= -0.14820684492588043f) {
                if (features[17] <= -0.39456191658973694f) {
                    if (features[27] <= -0.0911267795599997f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    if (features[11] <= 0.47158950567245483f) {
                        if (features[5] <= 1.0476103350520134f) {
                            if (features[23] <= -0.3698723018169403f) {
                                return 0;                            } else {
                                if (features[5] <= 0.06278865598142147f) {
                                    if (features[26] <= -0.03280855529010296f) {
                                        if (features[0] <= -0.38100431859493256f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[28] <= 0.03392469882965088f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    if (features[10] <= -0.3379233777523041f) {
                                        return 1;                                    } else {
                                        return 2;                                    }
                                }
                            }
                        } else {
                            return 2;                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[21] <= -0.0038833151338621974f) {
                    return 0;                } else {
                    if (features[3] <= 1.8877503275871277f) {
                        return 2;                    } else {
                        return 0;                    }
                }
            }
        }
    }
}

// Tree 104
int predict_tree_104(const float* features) {
    // Max depth: 10
    if (features[0] <= -0.4514061063528061f) {
        if (features[21] <= 0.2762204259634018f) {
            if (features[9] <= 0.7642013132572174f) {
                return 0;            } else {
                return 1;            }
        } else {
            if (features[11] <= 0.08077940531075001f) {
                if (features[10] <= -0.5094908028841019f) {
                    if (features[20] <= 0.469775453209877f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[19] <= -0.5046845972537994f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                return 1;            }
        }
    } else {
        if (features[19] <= 0.007266389031428844f) {
            if (features[4] <= 1.53406423330307f) {
                if (features[1] <= -0.4018087685108185f) {
                    if (features[20] <= -0.43889854848384857f) {
                        if (features[18] <= -0.47500626742839813f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[17] <= -0.27409590780735016f) {
                        if (features[17] <= -0.43032942712306976f) {
                            return 0;                        } else {
                            if (features[17] <= -0.40741224586963654f) {
                                if (features[5] <= -0.056029936764389277f) {
                                    if (features[26] <= -0.3596872091293335f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                if (features[0] <= -0.4128025472164154f) {
                                    return 0;                                } else {
                                    if (features[20] <= -0.7043969333171844f) {
                                        return 0;                                    } else {
                                        if (features[7] <= 0.44054149091243744f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        if (features[13] <= -0.6529163122177124f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[1] <= -0.43102702498435974f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[7] <= 1.9039512872695923f) {
                if (features[26] <= 8.862410545349121f) {
                    if (features[21] <= 0.0012473079841583967f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    return 1;                }
            } else {
                if (features[20] <= 0.1760029587894678f) {
                    return 0;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 105
int predict_tree_105(const float* features) {
    // Max depth: 10
    if (features[15] <= 0.7462623417377472f) {
        if (features[21] <= 0.11983741819858551f) {
            if (features[9] <= -0.674631804227829f) {
                if (features[22] <= -0.6396599113941193f) {
                    return 0;                } else {
                    if (features[10] <= -0.3606458306312561f) {
                        if (features[25] <= -0.41063471138477325f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[8] <= -0.09316607192158699f) {
                            if (features[13] <= 0.052069392055273056f) {
                                if (features[1] <= -0.34411729872226715f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            } else {
                                return 1;                            }
                        } else {
                            if (features[12] <= 0.017971962224692106f) {
                                return 0;                            } else {
                                if (features[13] <= -0.04502187855541706f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        }
                    }
                }
            } else {
                if (features[17] <= -0.37040458619594574f) {
                    return 0;                } else {
                    if (features[7] <= 1.0890628099441528f) {
                        if (features[24] <= -0.15039441036060452f) {
                            return 1;                        } else {
                            return 2;                        }
                    } else {
                        if (features[33] <= -0.7310653924942017f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                }
            }
        } else {
            if (features[8] <= -0.18750125169754028f) {
                if (features[17] <= -0.5130833089351654f) {
                    return 0;                } else {
                    return 2;                }
            } else {
                if (features[7] <= 0.3339008390903473f) {
                    if (features[3] <= -1.4024585485458374f) {
                        return 2;                    } else {
                        if (features[2] <= 0.8308269381523132f) {
                            if (features[18] <= -0.476426437497139f) {
                                if (features[4] <= 0.46065424382686615f) {
                                    if (features[1] <= -0.5518527328968048f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                if (features[9] <= 1.4061627388000488f) {
                                    if (features[17] <= 0.6958363950252533f) {
                                        if (features[31] <= 0.16302114725112915f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 2;                                    }
                                } else {
                                    return 1;                                }
                            }
                        } else {
                            return 2;                        }
                    }
                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[22] <= 0.058030277490615845f) {
            if (features[3] <= -0.29643912613391876f) {
                if (features[1] <= -0.354820653796196f) {
                    if (features[24] <= -0.3815299868583679f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[22] <= -0.4036066085100174f) {
                        if (features[12] <= -0.3446945548057556f) {
                            return 0;                        } else {
                            if (features[4] <= -0.4433876574039459f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    } else {
                        return 2;                    }
                }
            } else {
                return 0;            }
        } else {
            if (features[0] <= -0.29086486995220184f) {
                if (features[19] <= 0.06809551903279498f) {
                    if (features[5] <= 1.0931529700756073f) {
                        if (features[22] <= 0.12953953444957733f) {
                            return 0;                        } else {
                            if (features[14] <= 0.648509681224823f) {
                                if (features[2] <= -0.4070306420326233f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            } else {
                                return 1;                            }
                        }
                    } else {
                        return 2;                    }
                } else {
                    return 2;                }
            } else {
                return 2;            }
        }
    }
}

// Tree 106
int predict_tree_106(const float* features) {
    // Max depth: 10
    if (features[18] <= -0.449688196182251f) {
        if (features[20] <= 0.2787638455629349f) {
            if (features[10] <= -0.31455983221530914f) {
                if (features[16] <= 3.1667469069361687f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                return 2;            }
        } else {
            if (features[19] <= -0.5734698474407196f) {
                if (features[14] <= -0.4681146591901779f) {
                    return 0;                } else {
                    if (features[2] <= 0.11758071696385741f) {
                        if (features[13] <= -0.426942840218544f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        return 0;                    }
                }
            } else {
                if (features[27] <= -0.29550477862358093f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[10] <= -0.14820684492588043f) {
            if (features[4] <= 1.53406423330307f) {
                if (features[19] <= -0.4262035936117172f) {
                    if (features[17] <= -0.4265347719192505f) {
                        if (features[17] <= -0.4960055351257324f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[25] <= -0.37043145298957825f) {
                            return 0;                        } else {
                            if (features[11] <= -0.03231577202677727f) {
                                return 0;                            } else {
                                if (features[25] <= -0.30529801547527313f) {
                                    if (features[9] <= -0.49862438440322876f) {
                                        return 1;                                    } else {
                                        return 0;                                    }
                                } else {
                                    return 1;                                }
                            }
                        }
                    }
                } else {
                    if (features[0] <= -0.4296617656946182f) {
                        if (features[21] <= 0.05095779336988926f) {
                            return 0;                        } else {
                            return 2;                        }
                    } else {
                        if (features[7] <= 0.4375799894332886f) {
                            if (features[22] <= -0.6407210230827332f) {
                                return 0;                            } else {
                                if (features[6] <= 0.10452218819409609f) {
                                    if (features[10] <= -0.2069772630929947f) {
                                        if (features[24] <= -0.22497094422578812f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[15] <= 0.7462623417377472f) {
                                        if (features[17] <= -0.38577260076999664f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[0] <= -0.3741089701652527f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        } else {
                            if (features[22] <= -0.6355468034744263f) {
                                return 0;                            } else {
                                if (features[27] <= -0.30905529856681824f) {
                                    return 0;                                } else {
                                    if (features[10] <= -0.35896992683410645f) {
                                        if (features[23] <= -0.3838900476694107f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        if (features[22] <= -0.6336469054222107f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                if (features[26] <= -0.3633464425802231f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[0] <= 1.1592113971710205f) {
                if (features[1] <= 0.9608294367790222f) {
                    if (features[11] <= 3.3648617267608643f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    if (features[9] <= 0.3597274087369442f) {
                        if (features[12] <= -0.7482969611883163f) {
                            return 2;                        } else {
                            if (features[24] <= 2.1409000009298325f) {
                                if (features[28] <= 0.03392469882965088f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 2;                            }
                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[12] <= -0.4872279763221741f) {
                    if (features[26] <= 0.6527452766895294f) {
                        if (features[20] <= 0.03087124601006508f) {
                            return 0;                        } else {
                            return 2;                        }
                    } else {
                        if (features[4] <= 0.07372293435037136f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[2] <= -0.6519744172692299f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 107
int predict_tree_107(const float* features) {
    // Max depth: 10
    if (features[18] <= -0.44959574937820435f) {
        if (features[21] <= 0.4146563410758972f) {
            if (features[11] <= 0.2708526700735092f) {
                return 0;            } else {
                if (features[10] <= -0.3655068278312683f) {
                    return 0;                } else {
                    return 1;                }
            }
        } else {
            if (features[10] <= -0.5003955811262131f) {
                if (features[9] <= 0.8998923599720001f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                return 2;            }
        }
    } else {
        if (features[19] <= -0.12862157076597214f) {
            if (features[1] <= -0.4018087685108185f) {
                if (features[21] <= 0.8323173522949219f) {
                    return 0;                } else {
                    if (features[5] <= 3.5617090463638306f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[4] <= 1.5368548035621643f) {
                    if (features[22] <= -0.6407210230827332f) {
                        return 0;                    } else {
                        if (features[17] <= -0.27409590780735016f) {
                            if (features[18] <= -0.4302481859922409f) {
                                return 0;                            } else {
                                if (features[0] <= -0.4296617656946182f) {
                                    return 0;                                } else {
                                    if (features[11] <= 0.4791518300771713f) {
                                        if (features[21] <= -0.43961258232593536f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 2;                                    }
                                }
                            }
                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[15] <= 0.7462623417377472f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[0] <= -0.2643798142671585f) {
                if (features[9] <= 3.862707257270813f) {
                    return 1;                } else {
                    return 2;                }
            } else {
                if (features[21] <= 0.05592682212591171f) {
                    if (features[11] <= -0.6697232127189636f) {
                        if (features[4] <= -0.014416566700674593f) {
                            return 0;                        } else {
                            return 2;                        }
                    } else {
                        if (features[4] <= 0.08665825612843037f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[27] <= -0.316541463136673f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 108
int predict_tree_108(const float* features) {
    // Max depth: 8
    if (features[24] <= -0.1278594508767128f) {
        if (features[0] <= -0.3758653551340103f) {
            return 0;        } else {
            if (features[19] <= 0.40351423621177673f) {
                if (features[0] <= -0.3753127455711365f) {
                    return 1;                } else {
                    return 1;                }
            } else {
                return 2;            }
        }
    } else {
        if (features[1] <= -0.22000815719366074f) {
            if (features[5] <= 1.0807428658008575f) {
                if (features[4] <= 0.1238422654569149f) {
                    return 0;                } else {
                    if (features[17] <= -0.47472384572029114f) {
                        if (features[0] <= -0.5865699350833893f) {
                            if (features[5] <= 0.011320664547383785f) {
                                if (features[18] <= -0.5885810256004333f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        } else {
                            if (features[13] <= 0.22283832728862762f) {
                                return 0;                            } else {
                                if (features[7] <= -0.9062038660049438f) {
                                    return 1;                                } else {
                                    return 0;                                }
                            }
                        }
                    } else {
                        if (features[11] <= -0.317173857241869f) {
                            return 1;                        } else {
                            if (features[11] <= 0.2016637995839119f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    }
                }
            } else {
                if (features[25] <= 0.4183567389845848f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[2] <= -0.958857998251915f) {
                return 0;            } else {
                return 2;            }
        }
    }
}

// Tree 109
int predict_tree_109(const float* features) {
    // Max depth: 10
    if (features[18] <= -0.44959574937820435f) {
        if (features[23] <= 0.05400018114596605f) {
            if (features[4] <= 0.434844046831131f) {
                if (features[15] <= 0.7462623417377472f) {
                    return 0;                } else {
                    if (features[11] <= 0.2713642567396164f) {
                        if (features[16] <= 3.1667469069361687f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[7] <= 0.001459099119529128f) {
                            if (features[19] <= -0.5797945559024811f) {
                                return 2;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    }
                }
            } else {
                return 1;            }
        } else {
            if (features[22] <= 0.1990175023674965f) {
                return 1;            } else {
                return 2;            }
        }
    } else {
        if (features[18] <= -0.22779415547847748f) {
            if (features[5] <= 0.29560237377882004f) {
                if (features[10] <= -0.41459985077381134f) {
                    return 0;                } else {
                    if (features[0] <= -0.2740996479988098f) {
                        if (features[5] <= -0.39662623405456543f) {
                            return 0;                        } else {
                            if (features[18] <= -0.4302481859922409f) {
                                return 0;                            } else {
                                if (features[9] <= -0.7603023648262024f) {
                                    return 0;                                } else {
                                    if (features[22] <= -0.6408321857452393f) {
                                        return 0;                                    } else {
                                        if (features[25] <= -0.11659238114953041f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        if (features[13] <= -0.5397148132324219f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[26] <= -0.3620576560497284f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[3] <= 1.8758148550987244f) {
                if (features[7] <= -0.494261234998703f) {
                    if (features[21] <= 0.32759736478328705f) {
                        if (features[4] <= 0.2320295050740242f) {
                            return 1;                        } else {
                            return 2;                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[10] <= -0.29588329792022705f) {
                        return 1;                    } else {
                        if (features[15] <= 0.7462623417377472f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                return 0;            }
        }
    }
}

// Tree 110
int predict_tree_110(const float* features) {
    // Max depth: 10
    if (features[9] <= 2.0318864583969116f) {
        if (features[22] <= 0.13500681519508362f) {
            if (features[8] <= -0.1834072545170784f) {
                if (features[4] <= 0.0742165744304657f) {
                    if (features[26] <= 1.2901250123977661f) {
                        if (features[9] <= -0.5724726617336273f) {
                            if (features[0] <= -0.37470582127571106f) {
                                if (features[4] <= -0.8249493837356567f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        } else {
                            if (features[27] <= -0.005430252407677472f) {
                                return 0;                            } else {
                                return 0;                            }
                        }
                    } else {
                        if (features[1] <= 0.66962930560112f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[19] <= -0.21425480768084526f) {
                        if (features[19] <= -0.6008143723011017f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[22] <= -0.6404582858085632f) {
                    return 0;                } else {
                    if (features[22] <= -0.6042892932891846f) {
                        if (features[0] <= -0.3758691996335983f) {
                            if (features[18] <= -0.5976490676403046f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[9] <= 0.4490005224943161f) {
                            if (features[4] <= 0.13504482060670853f) {
                                if (features[17] <= -0.39832252264022827f) {
                                    if (features[9] <= -0.7015835046768188f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    if (features[11] <= -0.15943120419979095f) {
                                        return 0;                                    } else {
                                        if (features[26] <= 0.14895502850413322f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            } else {
                                if (features[5] <= -0.05706857144832611f) {
                                    return 1;                                } else {
                                    if (features[19] <= 0.5255157351493835f) {
                                        return 0;                                    } else {
                                        return 2;                                    }
                                }
                            }
                        } else {
                            if (features[21] <= 0.11937283724546432f) {
                                if (features[6] <= -1.8803272247314453f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                if (features[23] <= -0.06269669719040394f) {
                                    return 0;                                } else {
                                    if (features[7] <= -0.5898622870445251f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else {
            if (features[7] <= -0.3174111098051071f) {
                if (features[3] <= -1.0085883438587189f) {
                    if (features[1] <= 0.19562865048646927f) {
                        return 1;                    } else {
                        if (features[23] <= -0.1257946789264679f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[23] <= -0.03626006096601486f) {
                        if (features[10] <= -0.06680966913700104f) {
                            return 0;                        } else {
                            return 2;                        }
                    } else {
                        if (features[1] <= -0.247568529099226f) {
                            if (features[5] <= 0.0338671812787652f) {
                                if (features[26] <= -0.3572794795036316f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[17] <= -0.32585929334163666f) {
                    if (features[7] <= 0.526928722858429f) {
                        if (features[5] <= 0.04971696436405182f) {
                            if (features[25] <= -0.13532625883817673f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            if (features[18] <= -0.37997640669345856f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[24] <= -0.15308170765638351f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[0] <= -0.3721648156642914f) {
            if (features[17] <= -0.4371313601732254f) {
                return 2;            } else {
                if (features[6] <= -1.7700577974319458f) {
                    return 2;                } else {
                    return 1;                }
            }
        } else {
            return 2;        }
    }
}

// Tree 111
int predict_tree_111(const float* features) {
    // Max depth: 10
    if (features[1] <= -0.42245733737945557f) {
        if (features[7] <= 0.6593850255012512f) {
            if (features[15] <= 0.7462623417377472f) {
                if (features[19] <= -0.5837446749210358f) {
                    if (features[9] <= 0.8002252578735352f) {
                        if (features[0] <= -0.6118026375770569f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[20] <= 2.62633216381073f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[20] <= 0.2517804205417633f) {
                    return 0;                } else {
                    return 1;                }
            }
        } else {
            if (features[6] <= -0.9981719180941582f) {
                if (features[6] <= -1.8803272247314453f) {
                    return 2;                } else {
                    return 2;                }
            } else {
                return 0;            }
        }
    } else {
        if (features[0] <= -0.21553847193717957f) {
            if (features[24] <= 0.4745195060968399f) {
                if (features[18] <= -0.4299728125333786f) {
                    if (features[20] <= 0.17853392660617828f) {
                        if (features[19] <= -0.5666339695453644f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[0] <= -0.43021006882190704f) {
                        return 0;                    } else {
                        if (features[5] <= -0.39662186801433563f) {
                            return 0;                        } else {
                            if (features[6] <= 0.5455998182296753f) {
                                if (features[15] <= 0.7462623417377472f) {
                                    if (features[6] <= 0.10452218819409609f) {
                                        if (features[20] <= -0.23587750643491745f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[13] <= -0.07896086014807224f) {
                                        return 2;                                    } else {
                                        if (features[0] <= -0.3600143641233444f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            } else {
                                if (features[10] <= -0.3583320379257202f) {
                                    if (features[24] <= -0.39296190440654755f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    if (features[0] <= -0.3762724995613098f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                if (features[3] <= 0.4356025159358978f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[23] <= 0.07367003336548805f) {
                if (features[22] <= -0.006586759351193905f) {
                    return 0;                } else {
                    return 2;                }
            } else {
                if (features[21] <= 0.05592682212591171f) {
                    if (features[11] <= -0.846325010061264f) {
                        return 2;                    } else {
                        if (features[3] <= 3.077317953109741f) {
                            return 2;                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[13] <= -2.4602746963500977f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 112
int predict_tree_112(const float* features) {
    // Max depth: 10
    if (features[9] <= 0.47890934348106384f) {
        if (features[17] <= -0.4503321796655655f) {
            if (features[33] <= -0.7310653924942017f) {
                if (features[23] <= 2.1998538225889206f) {
                    if (features[1] <= -0.46246635913848877f) {
                        if (features[12] <= -0.01882633939385414f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[24] <= 4.233903884887695f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                return 0;            }
        } else {
            if (features[25] <= -0.04812546633183956f) {
                if (features[0] <= -0.3758653551340103f) {
                    if (features[13] <= -0.14555000513792038f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[11] <= 0.2567738965153694f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[3] <= 1.9155997037887573f) {
                    return 2;                } else {
                    if (features[12] <= -0.8670461773872375f) {
                        return 0;                    } else {
                        return 0;                    }
                }
            }
        }
    } else {
        if (features[17] <= -0.24509385973215103f) {
            if (features[8] <= -0.18364539742469788f) {
                if (features[21] <= 0.41768625378608704f) {
                    return 0;                } else {
                    if (features[6] <= -1.7700577974319458f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[24] <= -0.05524385720491409f) {
                    return 0;                } else {
                    if (features[7] <= 0.5165709555149078f) {
                        if (features[9] <= 0.5211441516876221f) {
                            return 0;                        } else {
                            if (features[21] <= 0.4787689596414566f) {
                                if (features[29] <= -0.0025959014892578125f) {
                                    if (features[27] <= 0.5120653212070465f) {
                                        if (features[10] <= -0.5640155375003815f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[23] <= 0.00888574868440628f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                if (features[15] <= 0.7462623417377472f) {
                                    return 1;                                } else {
                                    if (features[30] <= 0.17709434032440186f) {
                                        return 1;                                    } else {
                                        return 2;                                    }
                                }
                            }
                        }
                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[11] <= -9.021832466125488f) {
                return 2;            } else {
                return 2;            }
        }
    }
}

// Tree 113
int predict_tree_113(const float* features) {
    // Max depth: 9
    if (features[17] <= -0.451125368475914f) {
        if (features[7] <= 0.6562467813491821f) {
            if (features[5] <= -0.00588306353893131f) {
                return 0;            } else {
                if (features[2] <= 0.18327444791793823f) {
                    if (features[10] <= -0.5654745101928711f) {
                        return 1;                    } else {
                        return 1;                    }
                } else {
                    if (features[2] <= 0.47420383989810944f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[2] <= -0.05134601891040802f) {
                return 0;            } else {
                return 2;            }
        }
    } else {
        if (features[3] <= 0.28601138293743134f) {
            if (features[10] <= -0.1612759456038475f) {
                if (features[10] <= -0.36010049283504486f) {
                    if (features[9] <= 2.7529090493917465f) {
                        if (features[19] <= -0.5408716201782227f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[7] <= 0.26898618042469025f) {
                        if (features[12] <= -0.3753594160079956f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        return 0;                    }
                }
            } else {
                if (features[26] <= -0.363572895526886f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[2] <= 0.051886988803744316f) {
                if (features[1] <= -0.21131204068660736f) {
                    if (features[0] <= -0.43037086725234985f) {
                        return 0;                    } else {
                        if (features[2] <= -0.14519420638680458f) {
                            if (features[15] <= 0.7462623417377472f) {
                                return 1;                            } else {
                                if (features[1] <= -0.35402555763721466f) {
                                    return 1;                                } else {
                                    if (features[23] <= 0.08724863827228546f) {
                                        return 2;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        } else {
                            if (features[10] <= -0.3553290218114853f) {
                                if (features[20] <= -0.6431598663330078f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    if (features[3] <= 1.9036642611026764f) {
                        return 2;                    } else {
                        return 0;                    }
                }
            } else {
                if (features[6] <= -1.8803272247314453f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 114
int predict_tree_114(const float* features) {
    // Max depth: 8
    if (features[4] <= 0.11837195232510567f) {
        if (features[3] <= 0.3003339469432831f) {
            if (features[0] <= -0.3741089701652527f) {
                return 0;            } else {
                if (features[10] <= -0.12797836679965258f) {
                    return 1;                } else {
                    if (features[13] <= -0.4696887731552124f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[0] <= -0.3758691996335983f) {
                return 0;            } else {
                if (features[18] <= 0.04536956548690796f) {
                    if (features[14] <= 0.26044492423534393f) {
                        return 1;                    } else {
                        return 1;                    }
                } else {
                    if (features[3] <= 1.732589304447174f) {
                        return 2;                    } else {
                        return 0;                    }
                }
            }
        }
    } else {
        if (features[18] <= -0.2300560474395752f) {
            if (features[5] <= 0.38431769609451294f) {
                if (features[18] <= -0.47449998557567596f) {
                    if (features[24] <= -0.03155344631522894f) {
                        if (features[17] <= -0.5895532071590424f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[9] <= 0.8008623421192169f) {
                            return 0;                        } else {
                            if (features[23] <= 0.03949646418914199f) {
                                if (features[22] <= 0.4331102520227432f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    if (features[4] <= 1.1749781370162964f) {
                        if (features[10] <= -0.08813729602843523f) {
                            if (features[11] <= 0.10983680188655853f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            return 2;                        }
                    } else {
                        if (features[8] <= -0.16785796731710434f) {
                            if (features[12] <= 0.034651532769203186f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[4] <= 1.1141574382781982f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[1] <= -0.31455913186073303f) {
                return 1;            } else {
                if (features[7] <= 2.1282087564468384f) {
                    return 2;                } else {
                    if (features[9] <= 1.0130657255649567f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 115
int predict_tree_115(const float* features) {
    // Max depth: 9
    if (features[1] <= -0.42316633462905884f) {
        if (features[4] <= 0.47661183774471283f) {
            return 0;        } else {
            if (features[2] <= -0.013806741684675217f) {
                return 1;            } else {
                if (features[27] <= -0.2943497598171234f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[1] <= -0.16468816250562668f) {
            if (features[21] <= 1.5381214022636414f) {
                if (features[22] <= -0.6401146948337555f) {
                    return 0;                } else {
                    if (features[0] <= -0.4295370876789093f) {
                        return 0;                    } else {
                        if (features[25] <= -0.11155104264616966f) {
                            if (features[0] <= -0.3758653551340103f) {
                                if (features[9] <= -0.765401691198349f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        } else {
                            if (features[15] <= 0.7462623417377472f) {
                                if (features[22] <= 0.12913529574871063f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            } else {
                                if (features[8] <= -0.15049782395362854f) {
                                    return 2;                                } else {
                                    if (features[17] <= -0.347659096121788f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                if (features[15] <= 0.7462623417377472f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[22] <= 0.05498840659856796f) {
                if (features[17] <= 0.7010888159275055f) {
                    if (features[2] <= -0.6613592356443405f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    return 0;                }
            } else {
                if (features[4] <= 0.0009869421774055809f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 116
int predict_tree_116(const float* features) {
    // Max depth: 7
    if (features[17] <= -0.4499865621328354f) {
        if (features[24] <= 0.0017290213145315647f) {
            if (features[23] <= 0.08566152071580291f) {
                return 0;            } else {
                return 1;            }
        } else {
            if (features[22] <= 1.524556040763855f) {
                if (features[10] <= -0.5651594996452332f) {
                    return 1;                } else {
                    return 1;                }
            } else {
                return 2;            }
        }
    } else {
        if (features[9] <= 2.041569471359253f) {
            if (features[20] <= 0.15779217332601547f) {
                if (features[8] <= -0.18651193380355835f) {
                    if (features[7] <= 0.04755820846185088f) {
                        if (features[25] <= -0.1941170785576105f) {
                            if (features[22] <= -0.5769427716732025f) {
                                return 0;                            } else {
                                return 1;                            }
                        } else {
                            if (features[14] <= -1.005473554134369f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        return 0;                    }
                } else {
                    if (features[10] <= -0.36416296660900116f) {
                        if (features[27] <= -0.3165638595819473f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[24] <= 0.03404008038341999f) {
                            if (features[0] <= -0.3758653551340103f) {
                                return 0;                            } else {
                                return 1;                            }
                        } else {
                            if (features[25] <= 0.17493955790996552f) {
                                return 0;                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                if (features[3] <= 0.316247895359993f) {
                    if (features[20] <= 0.19124921411275864f) {
                        if (features[10] <= -0.06736590713262558f) {
                            return 1;                        } else {
                            return 2;                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[23] <= 1.8148414492607117f) {
                        if (features[1] <= -0.21131204068660736f) {
                            if (features[5] <= 0.08889619633555412f) {
                                return 2;                            } else {
                                return 1;                            }
                        } else {
                            if (features[10] <= -0.0810153391212225f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[17] <= -0.38212230801582336f) {
                if (features[24] <= 0.21856091916561127f) {
                    return 1;                } else {
                    return 1;                }
            } else {
                return 2;            }
        }
    }
}

// Tree 117
int predict_tree_117(const float* features) {
    // Max depth: 10
    if (features[0] <= -0.4511742442846298f) {
        if (features[21] <= 0.2762204259634018f) {
            if (features[23] <= -0.006173786081490107f) {
                return 0;            } else {
                return 1;            }
        } else {
            if (features[7] <= 0.26475363969802856f) {
                if (features[13] <= -0.6402429044246674f) {
                    return 0;                } else {
                    if (features[4] <= 0.46065424382686615f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[31] <= 0.16302114725112915f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[18] <= -0.2230272814631462f) {
            if (features[24] <= 0.2986484467983246f) {
                if (features[17] <= -0.43032942712306976f) {
                    return 0;                } else {
                    if (features[10] <= -0.2069772630929947f) {
                        if (features[11] <= 0.4051993191242218f) {
                            if (features[22] <= -0.6407210230827332f) {
                                return 0;                            } else {
                                if (features[1] <= -0.40153978765010834f) {
                                    return 0;                                } else {
                                    if (features[5] <= -0.11750911176204681f) {
                                        if (features[22] <= -0.4068101793527603f) {
                                            return 1;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        if (features[17] <= -0.3787992149591446f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        } else {
                            return 2;                        }
                    } else {
                        if (features[0] <= -0.14370807632803917f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[8] <= -0.22828755527734756f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[20] <= 0.04360669665038586f) {
                if (features[12] <= -1.6263622045516968f) {
                    return 2;                } else {
                    if (features[24] <= 0.024675932771060616f) {
                        return 0;                    } else {
                        return 0;                    }
                }
            } else {
                if (features[3] <= 1.9036642611026764f) {
                    if (features[4] <= 0.1744350865483284f) {
                        if (features[21] <= 0.23083259165287018f) {
                            return 2;                        } else {
                            return 1;                        }
                    } else {
                        if (features[29] <= -0.5031495066359639f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    return 0;                }
            }
        }
    }
}

// Tree 118
int predict_tree_118(const float* features) {
    // Max depth: 8
    if (features[6] <= -0.11601662915199995f) {
        if (features[0] <= -0.21553847193717957f) {
            if (features[0] <= -0.4293685704469681f) {
                if (features[20] <= 0.3998766988515854f) {
                    if (features[10] <= -0.5763672590255737f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[10] <= -0.5308117717504501f) {
                        return 1;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[5] <= 1.2058740556240082f) {
                    if (features[4] <= -0.5949041843414307f) {
                        return 0;                    } else {
                        if (features[26] <= -0.3620714843273163f) {
                            return 1;                        } else {
                            if (features[1] <= -0.3066519647836685f) {
                                if (features[12] <= 0.0766604132950306f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            } else {
                                if (features[1] <= -0.2370987981557846f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        }
                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[27] <= -0.17657306045293808f) {
                if (features[25] <= 0.07346217334270477f) {
                    if (features[22] <= -0.007304277271032333f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    if (features[1] <= 0.9956487119197845f) {
                        if (features[2] <= -0.7458226159214973f) {
                            return 0;                        } else {
                            return 2;                        }
                    } else {
                        if (features[3] <= 1.3625900000333786f) {
                            return 2;                        } else {
                            return 0;                        }
                    }
                }
            } else {
                if (features[2] <= -0.977627620100975f) {
                    if (features[26] <= 1.6835926175117493f) {
                        if (features[0] <= 1.2988569736480713f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 2;                    }
                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[25] <= -0.01735845673829317f) {
            if (features[1] <= -0.35448597371578217f) {
                return 0;            } else {
                if (features[21] <= -0.4118385463953018f) {
                    if (features[0] <= -0.37503020465373993f) {
                        return 0;                    } else {
                        if (features[30] <= 0.17709434032440186f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[5] <= -0.09851683862507343f) {
                        return 0;                    } else {
                        if (features[19] <= 0.5025481581687927f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[1] <= -0.3477524369955063f) {
                if (features[9] <= 1.034142255783081f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                return 2;            }
        }
    }
}

// Tree 119
int predict_tree_119(const float* features) {
    // Max depth: 10
    if (features[0] <= -0.45037148892879486f) {
        if (features[4] <= 0.4563424736261368f) {
            return 0;        } else {
            if (features[21] <= 1.087798148393631f) {
                return 1;            } else {
                return 2;            }
        }
    } else {
        if (features[1] <= -0.1487656682729721f) {
            if (features[4] <= 1.5404009222984314f) {
                if (features[18] <= -0.4300622493028641f) {
                    if (features[0] <= -0.3745678663253784f) {
                        if (features[29] <= -0.5031495066359639f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[5] <= -0.3942515701055527f) {
                        return 0;                    } else {
                        if (features[5] <= -0.11485310643911362f) {
                            if (features[18] <= -0.3978624641895294f) {
                                if (features[10] <= -0.3605532646179199f) {
                                    if (features[17] <= -0.4351768046617508f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                if (features[27] <= -0.3119395524263382f) {
                                    return 0;                                } else {
                                    if (features[25] <= -0.29564523696899414f) {
                                        if (features[17] <= -0.379781037569046f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 0;                                    }
                                }
                            }
                        } else {
                            if (features[17] <= -0.32057516276836395f) {
                                if (features[15] <= 0.7462623417377472f) {
                                    if (features[24] <= -0.0756663903594017f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[19] <= -0.3705357164144516f) {
                                        return 2;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                if (features[4] <= 0.40183075517416f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                }
            } else {
                if (features[30] <= 0.17709434032440186f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[20] <= 0.05283309333026409f) {
                if (features[1] <= 0.8971215784549713f) {
                    if (features[19] <= 0.48500311374664307f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    return 0;                }
            } else {
                if (features[10] <= -0.14788595587015152f) {
                    return 1;                } else {
                    if (features[33] <= -0.7310653924942017f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 120
int predict_tree_120(const float* features) {
    // Max depth: 10
    if (features[17] <= -0.4496292918920517f) {
        if (features[24] <= -0.044267792254686356f) {
            return 0;        } else {
            if (features[7] <= 0.5318563878536224f) {
                if (features[13] <= 0.20629843696951866f) {
                    if (features[27] <= 0.4390525370836258f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    return 1;                }
            } else {
                if (features[22] <= 2.492305874824524f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[17] <= -0.24509385973215103f) {
            if (features[4] <= 1.5368548035621643f) {
                if (features[10] <= -0.41455593705177307f) {
                    if (features[27] <= 1.6233619898557663f) {
                        if (features[23] <= -0.397617444396019f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[4] <= -0.6388984024524689f) {
                        return 0;                    } else {
                        if (features[22] <= 0.09805969521403313f) {
                            if (features[26] <= -0.3477861285209656f) {
                                if (features[21] <= -0.6319604814052582f) {
                                    if (features[17] <= -0.38613441586494446f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[29] <= -0.5031495066359639f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                }
                            } else {
                                if (features[10] <= -0.36409255862236023f) {
                                    if (features[19] <= -0.5367780923843384f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    if (features[0] <= -0.37561240792274475f) {
                                        return 0;                                    } else {
                                        if (features[5] <= -0.29757092893123627f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        } else {
                            if (features[22] <= 1.2460075616836548f) {
                                if (features[10] <= -0.20661623775959015f) {
                                    if (features[15] <= 0.7462623417377472f) {
                                        return 1;                                    } else {
                                        if (features[0] <= -0.3472675681114197f) {
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
                if (features[13] <= -2.401418447494507f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[3] <= 1.88377183675766f) {
                if (features[5] <= -0.1547539010643959f) {
                    return 2;                } else {
                    return 2;                }
            } else {
                return 0;            }
        }
    }
}

// Tree 121
int predict_tree_121(const float* features) {
    // Max depth: 8
    if (features[21] <= 0.11981721967458725f) {
        if (features[17] <= -0.39827775955200195f) {
            return 0;        } else {
            if (features[5] <= -0.23312413692474365f) {
                if (features[10] <= -0.3627457320690155f) {
                    return 0;                } else {
                    if (features[11] <= -0.1604975014925003f) {
                        return 1;                    } else {
                        if (features[0] <= -0.3758691996335983f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[4] <= 0.05423935875296593f) {
                    if (features[3] <= 1.8042020797729492f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[21] <= 1.0637104511260986f) {
            if (features[1] <= -0.15520095080137253f) {
                if (features[10] <= -0.506496399641037f) {
                    if (features[20] <= 0.4011371284723282f) {
                        if (features[7] <= -2.4235033988952637f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[19] <= -0.5794512629508972f) {
                            if (features[31] <= 0.16302114725112915f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[11] <= -0.8329196274280548f) {
                        return 1;                    } else {
                        if (features[19] <= -0.3694869875907898f) {
                            if (features[27] <= 0.3034534677863121f) {
                                return 2;                            } else {
                                if (features[23] <= 0.09881074726581573f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        } else {
                            if (features[25] <= 0.1558913867920637f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    }
                }
            } else {
                if (features[20] <= 0.106557946652174f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[7] <= 0.312751941382885f) {
                if (features[0] <= -0.3721648156642914f) {
                    return 1;                } else {
                    return 2;                }
            } else {
                if (features[9] <= -1.225742518901825f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 122
int predict_tree_122(const float* features) {
    // Max depth: 8
    if (features[0] <= -0.4495924860239029f) {
        if (features[4] <= 0.46065424382686615f) {
            return 0;        } else {
            if (features[19] <= -0.5411057770252228f) {
                return 1;            } else {
                return 2;            }
        }
    } else {
        if (features[10] <= -0.14820684492588043f) {
            if (features[5] <= 0.19622398167848587f) {
                if (features[5] <= -0.10576845705509186f) {
                    if (features[19] <= -0.38985390961170197f) {
                        if (features[0] <= -0.37561240792274475f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        if (features[23] <= -0.34900274872779846f) {
                            if (features[0] <= -0.3758653551340103f) {
                                return 0;                            } else {
                                return 1;                            }
                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[9] <= 1.111545979976654f) {
                        if (features[4] <= 0.4613594263792038f) {
                            return 1;                        } else {
                            return 2;                        }
                    } else {
                        if (features[10] <= -0.349072590470314f) {
                            if (features[2] <= -0.3497832417488098f) {
                                return 1;                            } else {
                                if (features[5] <= 0.09681684523820877f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[34] <= -2.0389932096004486f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[21] <= 0.05521984584629536f) {
                if (features[6] <= -0.9981719255447388f) {
                    return 0;                } else {
                    return 2;                }
            } else {
                return 2;            }
        }
    }
}

// Tree 123
int predict_tree_123(const float* features) {
    // Max depth: 8
    if (features[10] <= -0.4367019236087799f) {
        if (features[20] <= 0.44134001433849335f) {
            return 0;        } else {
            if (features[19] <= -0.5424142181873322f) {
                return 1;            } else {
                return 2;            }
        }
    } else {
        if (features[10] <= -0.14820684492588043f) {
            if (features[22] <= 1.5393915176391602f) {
                if (features[22] <= -0.6408422887325287f) {
                    return 0;                } else {
                    if (features[20] <= 0.08821607194840908f) {
                        if (features[0] <= -0.37585754692554474f) {
                            if (features[11] <= -0.2584531232714653f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[1] <= -0.3074348717927933f) {
                            if (features[0] <= -0.3721648156642914f) {
                                return 1;                            } else {
                                if (features[7] <= -0.2170606404542923f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        } else {
                            if (features[9] <= 1.3782824277877808f) {
                                if (features[2] <= -0.257812038064003f) {
                                    return 2;                                } else {
                                    return 1;                                }
                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                if (features[7] <= 0.8256452679634094f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[3] <= 1.8758148550987244f) {
                if (features[4] <= 0.04248272720724344f) {
                    return 2;                } else {
                    return 2;                }
            } else {
                return 0;            }
        }
    }
}

// Tree 124
int predict_tree_124(const float* features) {
    // Max depth: 9
    if (features[4] <= 0.12157556042075157f) {
        if (features[0] <= -0.37585754692554474f) {
            return 0;        } else {
            if (features[0] <= -0.09205424040555954f) {
                return 1;            } else {
                if (features[22] <= 0.05818186700344086f) {
                    if (features[2] <= -0.6050503328442574f) {
                        return 0;                    } else {
                        if (features[28] <= 0.03392469882965088f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[11] <= -4.450499892234802f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[17] <= -0.23100721091032028f) {
            if (features[23] <= 1.0926437377929688f) {
                if (features[0] <= -0.5286632180213928f) {
                    if (features[10] <= -0.5660090148448944f) {
                        if (features[23] <= -0.0002975715324282646f) {
                            if (features[10] <= -0.569230705499649f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[27] <= -0.3017742931842804f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[23] <= -0.09903440251946449f) {
                        return 0;                    } else {
                        if (features[26] <= -0.20643871277570724f) {
                            return 1;                        } else {
                            if (features[27] <= 0.2897576168179512f) {
                                return 2;                            } else {
                                if (features[22] <= 0.9776255190372467f) {
                                    if (features[1] <= -0.4106298238039017f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 1;                                }
                            }
                        }
                    }
                }
            } else {
                return 2;            }
        } else {
            if (features[9] <= -0.7259405851364136f) {
                return 2;            } else {
                return 2;            }
        }
    }
}

// Tree 125
int predict_tree_125(const float* features) {
    // Max depth: 8
    if (features[23] <= -0.13091780990362167f) {
        if (features[18] <= -0.4146423190832138f) {
            if (features[15] <= 0.7462623417377472f) {
                return 0;            } else {
                if (features[10] <= -0.36158469319343567f) {
                    return 0;                } else {
                    return 1;                }
            }
        } else {
            if (features[25] <= -0.16009333729743958f) {
                if (features[1] <= -0.35448597371578217f) {
                    if (features[6] <= -0.11601662915199995f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[12] <= -0.010361829306930304f) {
                        if (features[3] <= 0.5430216491222382f) {
                            if (features[10] <= -0.36514008045196533f) {
                                return 0;                            } else {
                                if (features[0] <= -0.37641867995262146f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            }
                        } else {
                            return 0;                        }
                    } else {
                        if (features[13] <= -0.03148924559354782f) {
                            if (features[22] <= -0.6208831667900085f) {
                                if (features[21] <= -0.6268197298049927f) {
                                    return 1;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        } else {
                            if (features[2] <= -0.07011565566062927f) {
                                if (features[19] <= -0.38993705809116364f) {
                                    return 0;                                } else {
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
        if (features[10] <= -0.30464795231819153f) {
            if (features[18] <= -0.4243968576192856f) {
                if (features[25] <= 1.1397939324378967f) {
                    if (features[13] <= 0.06001712754368782f) {
                        if (features[25] <= 0.041747692972421646f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        if (features[23] <= -0.04880714416503906f) {
                            if (features[17] <= -0.5886813104152679f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            if (features[20] <= 0.4011371284723282f) {
                                return 0;                            } else {
                                if (features[23] <= 0.0194429368712008f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        }
                    }
                } else {
                    return 2;                }
            } else {
                if (features[24] <= 0.4745195060968399f) {
                    if (features[15] <= 0.7462623417377472f) {
                        return 1;                    } else {
                        if (features[30] <= 0.17709434032440186f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[10] <= 1.0074822306632996f) {
                if (features[26] <= -0.363572895526886f) {
                    if (features[0] <= 0.0015806332230567932f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    return 2;                }
            } else {
                if (features[26] <= 0.26427072286605835f) {
                    if (features[6] <= -0.9981719255447388f) {
                        return 0;                    } else {
                        if (features[22] <= 0.1344105675816536f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[9] <= -0.17099794745445251f) {
                        if (features[20] <= 0.03648775117471814f) {
                            if (features[5] <= 0.06783830374479294f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            if (features[14] <= -1.0917160511016846f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[14] <= -0.5679555833339691f) {
                            if (features[22] <= 0.03349318355321884f) {
                                return 0;                            } else {
                                return 2;                            }
                        } else {
                            if (features[20] <= 0.06830117292702198f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                }
            }
        }
    }
}

// Tree 126
int predict_tree_126(const float* features) {
    // Max depth: 10
    if (features[0] <= -0.4502911865711212f) {
        if (features[25] <= -0.030040491372346878f) {
            if (features[25] <= -0.13482891023159027f) {
                if (features[4] <= 0.26637257635593414f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                if (features[13] <= 0.7596327662467957f) {
                    return 0;                } else {
                    return 1;                }
            }
        } else {
            if (features[21] <= 1.087798148393631f) {
                if (features[21] <= 0.4146563410758972f) {
                    if (features[9] <= 0.4436139911413193f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[24] <= 0.047319223172962666f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[8] <= -0.22858906537294388f) {
            if (features[19] <= -0.44410109519958496f) {
                return 1;            } else {
                if (features[20] <= -0.005782254389487207f) {
                    return 0;                } else {
                    return 2;                }
            }
        } else {
            if (features[1] <= -0.15766572952270508f) {
                if (features[22] <= 1.5410286784172058f) {
                    if (features[10] <= -0.4145737290382385f) {
                        return 0;                    } else {
                        if (features[20] <= -0.6381080448627472f) {
                            return 0;                        } else {
                            if (features[5] <= -0.10315816104412079f) {
                                if (features[11] <= 0.12426622956991196f) {
                                    if (features[0] <= -0.3758691996335983f) {
                                        if (features[22] <= -0.6387200653553009f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[18] <= -0.5108157843351364f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                }
                            } else {
                                if (features[22] <= 0.8704222738742828f) {
                                    if (features[1] <= -0.3066519647836685f) {
                                        if (features[7] <= 0.034531488083302975f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[12] <= -0.3007810339331627f) {
                                        return 2;                                    } else {
                                        if (features[7] <= 0.17218183726072311f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        }
                    }
                } else {
                    if (features[11] <= -0.24767760559916496f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[27] <= -0.1320280134677887f) {
                    if (features[2] <= -0.6895136907696724f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    if (features[2] <= -0.9513501226902008f) {
                        return 0;                    } else {
                        if (features[20] <= 0.0921284668147564f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    }
}

// Tree 127
int predict_tree_127(const float* features) {
    // Max depth: 10
    if (features[21] <= 0.11981721967458725f) {
        if (features[2] <= -0.12642456963658333f) {
            if (features[12] <= 2.1279468536376953f) {
                if (features[0] <= -0.37666836380958557f) {
                    return 0;                } else {
                    if (features[3] <= 1.7445247620344162f) {
                        if (features[27] <= -0.23270035535097122f) {
                            return 1;                        } else {
                            return 2;                        }
                    } else {
                        return 0;                    }
                }
            } else {
                return 2;            }
        } else {
            if (features[26] <= -0.316763699054718f) {
                if (features[21] <= -0.6241534352302551f) {
                    if (features[4] <= -0.634707510471344f) {
                        if (features[19] <= -0.6056037545204163f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[17] <= -0.3749351352453232f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                } else {
                    return 0;                }
            } else {
                if (features[6] <= 1.2072162628173828f) {
                    if (features[19] <= -0.46431271731853485f) {
                        return 0;                    } else {
                        if (features[24] <= -0.06575432699173689f) {
                            if (features[20] <= -0.5762155652046204f) {
                                return 0;                            } else {
                                if (features[0] <= -0.36713381111621857f) {
                                    if (features[9] <= -0.6040797233581543f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    return 1;                                }
                            }
                        } else {
                            if (features[10] <= 0.013516870560124516f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[10] <= -0.35785675048828125f) {
                        if (features[4] <= -0.6475521624088287f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[23] <= -0.3583122491836548f) {
                            if (features[0] <= -0.37448155879974365f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            return 1;                        }
                    }
                }
            }
        }
    } else {
        if (features[17] <= -0.23100721091032028f) {
            if (features[34] <= -2.0389932096004486f) {
                return 2;            } else {
                if (features[23] <= 1.0739642232656479f) {
                    if (features[24] <= -0.06200467422604561f) {
                        if (features[19] <= -0.4360501766204834f) {
                            if (features[31] <= 0.16302114725112915f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[5] <= -0.010426873341202736f) {
                            if (features[0] <= -0.5286632180213928f) {
                                if (features[13] <= -0.30085308104753494f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        } else {
                            if (features[3] <= 0.3039145767688751f) {
                                if (features[3] <= -0.22084787487983704f) {
                                    if (features[6] <= -1.8803272247314453f) {
                                        return 1;                                    } else {
                                        if (features[7] <= -0.7638834118843079f) {
                                            return 1;                                        } else {
                                            return 0;                                        }
                                    }
                                } else {
                                    return 2;                                }
                            } else {
                                if (features[17] <= -0.3210331052541733f) {
                                    if (features[3] <= 0.6647633910179138f) {
                                        if (features[4] <= 0.5986914336681366f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[11] <= -9.655597686767578f) {
                return 2;            } else {
                return 2;            }
        }
    }
}

// Tree 128
int predict_tree_128(const float* features) {
    // Max depth: 9
    if (features[4] <= 0.12460790947079659f) {
        if (features[19] <= -0.41509054601192474f) {
            if (features[0] <= -0.3804066330194473f) {
                return 0;            } else {
                if (features[25] <= -0.37385132908821106f) {
                    return 1;                } else {
                    return 1;                }
            }
        } else {
            if (features[19] <= -0.1366887977346778f) {
                if (features[4] <= -0.5590902864933014f) {
                    if (features[19] <= -0.38985390961170197f) {
                        if (features[2] <= -0.03257638122886419f) {
                            if (features[7] <= -2.649726629257202f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            if (features[1] <= -0.3495969623327255f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[17] <= -0.3802667409181595f) {
                            return 0;                        } else {
                            if (features[10] <= -0.35496382415294647f) {
                                if (features[22] <= -0.6206810474395752f) {
                                    if (features[21] <= -0.6353842318058014f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                if (features[19] <= -0.385247141122818f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        }
                    }
                } else {
                    if (features[8] <= -0.22177016735076904f) {
                        return 0;                    } else {
                        return 0;                    }
                }
            } else {
                if (features[4] <= 0.05113649368286133f) {
                    if (features[26] <= 2.2370940446853638f) {
                        return 0;                    } else {
                        if (features[19] <= 1.8856638073921204f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[4] <= 0.06160362996160984f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[20] <= 1.0608497262001038f) {
            if (features[4] <= 0.1827765554189682f) {
                if (features[0] <= -0.12347234785556793f) {
                    if (features[17] <= -0.4408375173807144f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            } else {
                if (features[19] <= -0.3318302631378174f) {
                    if (features[10] <= -0.1354660429060459f) {
                        if (features[20] <= 0.2787638455629349f) {
                            if (features[12] <= 0.6517410278320312f) {
                                if (features[21] <= 0.13185600563883781f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        } else {
                            if (features[23] <= 0.01652532583102584f) {
                                if (features[7] <= -0.9256266355514526f) {
                                    return 1;                                } else {
                                    return 0;                                }
                            } else {
                                if (features[12] <= 0.08537539001554251f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[7] <= 2.1211910247802734f) {
                        return 2;                    } else {
                        if (features[20] <= 0.40627971291542053f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[5] <= 0.24452663213014603f) {
                if (features[0] <= -0.3712773025035858f) {
                    return 1;                } else {
                    return 2;                }
            } else {
                if (features[24] <= 0.011777028441429138f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 129
int predict_tree_129(const float* features) {
    // Max depth: 10
    if (features[27] <= -0.20718029886484146f) {
        if (features[1] <= -0.40174736082553864f) {
            if (features[21] <= 1.1367511749267578f) {
                return 0;            } else {
                if (features[9] <= -0.8081045746803284f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[18] <= -0.13911354169249535f) {
                if (features[21] <= 1.5837112069129944f) {
                    if (features[21] <= -0.6406360268592834f) {
                        return 0;                    } else {
                        if (features[2] <= 0.30527709424495697f) {
                            if (features[9] <= -0.7545555531978607f) {
                                return 0;                            } else {
                                if (features[18] <= -0.4302047789096832f) {
                                    if (features[1] <= -0.3567028194665909f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[7] <= 0.4375799894332886f) {
                                        if (features[17] <= -0.2536291480064392f) {
                                            return 1;                                        } else {
                                            return 2;                                        }
                                    } else {
                                        if (features[17] <= -0.37529483437538147f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        } else {
                            if (features[5] <= -0.11750911176204681f) {
                                if (features[12] <= -0.3315628170967102f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    return 2;                }
            } else {
                if (features[20] <= 0.06126289442181587f) {
                    return 0;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[26] <= -0.2777607887983322f) {
            if (features[7] <= 0.2488207295536995f) {
                if (features[1] <= -0.2146984599530697f) {
                    if (features[23] <= -0.07826117798686028f) {
                        if (features[21] <= -0.7708710730075836f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[8] <= 0.09102953970432281f) {
                            if (features[21] <= 0.140006422996521f) {
                                return 0;                            } else {
                                if (features[19] <= -0.5022618025541306f) {
                                    if (features[20] <= 0.4714795649051666f) {
                                        if (features[26] <= -0.35704420506954193f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[14] <= -0.9656402170658112f) {
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
                if (features[21] <= 0.18231386318802834f) {
                    return 0;                } else {
                    if (features[13] <= 0.6217288076877594f) {
                        return 2;                    } else {
                        if (features[8] <= -0.12980247288942337f) {
                            return 2;                        } else {
                            if (features[22] <= 1.6647045016288757f) {
                                return 1;                            } else {
                                return 2;                            }
                        }
                    }
                }
            }
        } else {
            if (features[1] <= -0.15344125032424927f) {
                if (features[5] <= 1.0931529700756073f) {
                    if (features[4] <= -0.4554968923330307f) {
                        return 0;                    } else {
                        if (features[0] <= -0.5585103034973145f) {
                            return 0;                        } else {
                            if (features[0] <= -0.34010283648967743f) {
                                if (features[25] <= -0.07670928910374641f) {
                                    if (features[25] <= -0.2956359088420868f) {
                                        return 1;                                    } else {
                                        if (features[18] <= -0.560508131980896f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    }
                                } else {
                                    if (features[3] <= 0.5485915541648865f) {
                                        if (features[1] <= -0.34569376707077026f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                if (features[9] <= 0.8515774309635162f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                } else {
                    return 2;                }
            } else {
                if (features[22] <= 0.038151999935507774f) {
                    if (features[27] <= 0.030027608387172222f) {
                        if (features[31] <= 0.16302114725112915f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[2] <= -0.9710582494735718f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 130
int predict_tree_130(const float* features) {
    // Max depth: 10
    if (features[18] <= -0.449688196182251f) {
        if (features[25] <= 0.9262688048183918f) {
            if (features[9] <= 0.8893032371997833f) {
                return 0;            } else {
                if (features[27] <= 0.11936813592910767f) {
                    return 0;                } else {
                    return 1;                }
            }
        } else {
            if (features[28] <= 0.03392469882965088f) {
                return 2;            } else {
                return 2;            }
        }
    } else {
        if (features[3] <= 0.2887963354587555f) {
            if (features[20] <= 0.19124921411275864f) {
                if (features[5] <= -0.04082770459353924f) {
                    if (features[0] <= -0.3741089701652527f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            } else {
                if (features[8] <= 0.24499931931495667f) {
                    return 2;                } else {
                    return 1;                }
            }
        } else {
            if (features[1] <= -0.26996922492980957f) {
                if (features[23] <= 1.7852794826030731f) {
                    if (features[8] <= -0.19563163816928864f) {
                        return 0;                    } else {
                        if (features[17] <= -0.43032942712306976f) {
                            return 0;                        } else {
                            if (features[6] <= 0.6558692352846265f) {
                                if (features[24] <= -0.18717271462082863f) {
                                    return 1;                                } else {
                                    if (features[4] <= 0.6402174532413483f) {
                                        return 2;                                    } else {
                                        if (features[10] <= -0.3557049334049225f) {
                                            return 1;                                        } else {
                                            return 2;                                        }
                                    }
                                }
                            } else {
                                if (features[0] <= -0.3757518380880356f) {
                                    if (features[19] <= -0.4393478333950043f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    if (features[21] <= -0.6398482620716095f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        }
                    }
                } else {
                    if (features[31] <= 0.16302114725112915f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[27] <= -0.14378774166107178f) {
                    if (features[21] <= 0.0711268000304699f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    if (features[22] <= 0.06999564729630947f) {
                        return 0;                    } else {
                        if (features[7] <= -0.23760446906089783f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    }
}

// Tree 131
int predict_tree_131(const float* features) {
    // Max depth: 10
    if (features[0] <= -0.4493054151535034f) {
        if (features[1] <= -0.47866836190223694f) {
            if (features[4] <= 0.4545391798019409f) {
                return 0;            } else {
                if (features[21] <= 2.4157608449459076f) {
                    return 1;                } else {
                    return 2;                }
            }
        } else {
            if (features[23] <= 0.8726251274347305f) {
                if (features[14] <= -0.5481457114219666f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                return 2;            }
        }
    } else {
        if (features[0] <= -0.21553847193717957f) {
            if (features[5] <= 1.569606214761734f) {
                if (features[26] <= 1.348282814025879f) {
                    if (features[1] <= -0.4018087685108185f) {
                        return 0;                    } else {
                        if (features[22] <= -0.6407210230827332f) {
                            return 0;                        } else {
                            if (features[19] <= -0.4262035936117172f) {
                                if (features[27] <= -0.28034670650959015f) {
                                    return 0;                                } else {
                                    if (features[6] <= 1.2072162628173828f) {
                                        if (features[17] <= -0.42823000252246857f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[4] <= -0.6434519290924072f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    }
                                }
                            } else {
                                if (features[27] <= -0.25685735046863556f) {
                                    if (features[18] <= -0.37966300547122955f) {
                                        if (features[6] <= 0.43533041048794985f) {
                                            return 1;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        if (features[12] <= -0.17160719633102417f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    if (features[5] <= -0.10315816104412079f) {
                                        if (features[0] <= -0.3676583170890808f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[15] <= 0.7462623417377472f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        }
                    }
                } else {
                    return 2;                }
            } else {
                if (features[3] <= 0.19689328223466873f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[20] <= 0.05401286110281944f) {
                if (features[3] <= 1.808180570602417f) {
                    return 2;                } else {
                    return 0;                }
            } else {
                if (features[20] <= 0.06173681654036045f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 132
int predict_tree_132(const float* features) {
    // Max depth: 9
    if (features[10] <= -0.2071150615811348f) {
        if (features[18] <= -0.43003541231155396f) {
            if (features[5] <= -0.004704053630121052f) {
                if (features[1] <= -0.3519475907087326f) {
                    return 0;                } else {
                    if (features[22] <= -0.4119843989610672f) {
                        return 1;                    } else {
                        if (features[1] <= -0.3422154188156128f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                }
            } else {
                if (features[25] <= 0.9393647909164429f) {
                    if (features[12] <= -0.00481413712259382f) {
                        return 0;                    } else {
                        if (features[21] <= 0.21773333847522736f) {
                            return 0;                        } else {
                            if (features[18] <= -0.5820544362068176f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[7] <= 0.6512690186500549f) {
                if (features[0] <= -0.4296617656946182f) {
                    return 0;                } else {
                    if (features[22] <= -0.6411555707454681f) {
                        return 0;                    } else {
                        if (features[5] <= -0.2952832281589508f) {
                            if (features[18] <= -0.3966871500015259f) {
                                if (features[10] <= -0.36250805854797363f) {
                                    if (features[23] <= -0.393032968044281f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                if (features[0] <= -0.37585754692554474f) {
                                    return 0;                                } else {
                                    if (features[2] <= -0.09827011078596115f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        } else {
                            if (features[4] <= 0.5986914336681366f) {
                                if (features[3] <= -0.041815951466560364f) {
                                    if (features[26] <= -0.3202292323112488f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 2;                                }
                            } else {
                                if (features[17] <= -0.32340574264526367f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                }
            } else {
                if (features[9] <= -1.21821129322052f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[7] <= 1.9039512872695923f) {
            if (features[3] <= 0.7061396539211273f) {
                if (features[12] <= -10.438920497894287f) {
                    return 2;                } else {
                    return 2;                }
            } else {
                return 2;            }
        } else {
            if (features[3] <= 1.314848154783249f) {
                return 2;            } else {
                return 0;            }
        }
    }
}

// Tree 133
int predict_tree_133(const float* features) {
    // Max depth: 10
    if (features[1] <= -0.4236069470643997f) {
        if (features[14] <= 0.7223928570747375f) {
            if (features[4] <= 0.4563424736261368f) {
                return 0;            } else {
                if (features[20] <= 1.2466582357883453f) {
                    return 1;                } else {
                    if (features[10] <= -0.4917083978652954f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[4] <= 1.1647628396749496f) {
                return 0;            } else {
                if (features[14] <= 0.891435831785202f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[17] <= -0.22465001046657562f) {
            if (features[0] <= -0.4265829771757126f) {
                if (features[22] <= 1.467387080192566f) {
                    if (features[4] <= 0.6598017439246178f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[30] <= 0.17709434032440186f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[6] <= -1.6597883701324463f) {
                    if (features[25] <= 1.3262500613927841f) {
                        return 1;                    } else {
                        return 2;                    }
                } else {
                    if (features[22] <= 1.53965425491333f) {
                        if (features[11] <= 0.4051993191242218f) {
                            if (features[17] <= -0.42823000252246857f) {
                                return 0;                            } else {
                                if (features[21] <= -0.6407673358917236f) {
                                    return 0;                                } else {
                                    if (features[23] <= -0.11616252362728119f) {
                                        if (features[3] <= -0.40783676505088806f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[19] <= 0.0057551562786102295f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        } else {
                            if (features[10] <= -0.33449801802635193f) {
                                return 0;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[19] <= -0.4277575612068176f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[3] <= 1.9036642611026764f) {
                if (features[2] <= -0.4577086716890335f) {
                    return 2;                } else {
                    return 2;                }
            } else {
                return 0;            }
        }
    }
}

// Tree 134
int predict_tree_134(const float* features) {
    // Max depth: 10
    if (features[10] <= -0.43600042164325714f) {
        if (features[25] <= 0.0031086986418813467f) {
            if (features[23] <= 0.0482862307690084f) {
                return 0;            } else {
                return 1;            }
        } else {
            if (features[21] <= 1.087798148393631f) {
                if (features[4] <= 0.4545391798019409f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                if (features[2] <= 0.08004144579172134f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[8] <= -0.24032963067293167f) {
            return 2;        } else {
            if (features[17] <= -0.23100721091032028f) {
                if (features[22] <= 1.5393915176391602f) {
                    if (features[0] <= -0.4301111698150635f) {
                        return 0;                    } else {
                        if (features[25] <= -0.3899828642606735f) {
                            return 0;                        } else {
                            if (features[9] <= -0.21578223258256912f) {
                                if (features[27] <= -0.31103479862213135f) {
                                    return 0;                                } else {
                                    if (features[4] <= -0.440284788608551f) {
                                        if (features[1] <= -0.3546426594257355f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[29] <= -0.0025959014892578125f) {
                                            return 0;                                        } else {
                                            return 2;                                        }
                                    }
                                }
                            } else {
                                if (features[12] <= 0.0783008374273777f) {
                                    if (features[21] <= 0.084842124953866f) {
                                        return 0;                                    } else {
                                        if (features[8] <= -0.17993415147066116f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    if (features[22] <= 0.3992454260587692f) {
                                        if (features[1] <= -0.31352606415748596f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[18] <= -0.38263633847236633f) {
                                            return 2;                                        } else {
                                            return 2;                                        }
                                    }
                                }
                            }
                        }
                    }
                } else {
                    if (features[7] <= 0.8256452679634094f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[8] <= -0.18766850233078003f) {
                    if (features[7] <= 1.1547736376523972f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    if (features[3] <= 2.0071049332618713f) {
                        return 2;                    } else {
                        if (features[23] <= 0.12359963729977608f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                }
            }
        }
    }
}

// Tree 135
int predict_tree_135(const float* features) {
    // Max depth: 10
    if (features[20] <= 0.12179410457611084f) {
        if (features[18] <= -0.4148929715156555f) {
            if (features[26] <= 0.20619072765111923f) {
                return 0;            } else {
                if (features[14] <= 0.23164886236190796f) {
                    return 0;                } else {
                    return 1;                }
            }
        } else {
            if (features[1] <= -0.09908577799797058f) {
                if (features[9] <= -0.7619737386703491f) {
                    return 0;                } else {
                    if (features[0] <= -0.37597908079624176f) {
                        if (features[5] <= -0.38859643042087555f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                }
            } else {
                if (features[20] <= 0.06350143067538738f) {
                    if (features[9] <= -0.36027762293815613f) {
                        return 2;                    } else {
                        if (features[3] <= 3.0852749347686768f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[5] <= 0.016854056855663657f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[2] <= -0.31036700308322906f) {
            if (features[20] <= 0.7428969740867615f) {
                if (features[17] <= -0.4451965391635895f) {
                    return 0;                } else {
                    if (features[30] <= 0.17709434032440186f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[1] <= -0.32180333137512207f) {
                    if (features[19] <= -0.16870059072971344f) {
                        if (features[2] <= -0.4774167835712433f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[21] <= 0.16735627502202988f) {
                if (features[26] <= 0.15802787244319916f) {
                    if (features[19] <= -0.10167938098311424f) {
                        if (features[23] <= -0.08823026716709137f) {
                            return 0;                        } else {
                            if (features[7] <= -0.6672823429107666f) {
                                return 0;                            } else {
                                if (features[7] <= -0.17792481370270252f) {
                                    if (features[8] <= -0.2158738449215889f) {
                                        return 0;                                    } else {
                                        if (features[19] <= -0.5852668881416321f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    return 0;                                }
                            }
                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[8] <= -0.2802775651216507f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[0] <= -0.5132060647010803f) {
                    if (features[26] <= -0.34920503199100494f) {
                        return 0;                    } else {
                        if (features[24] <= 0.00016413722187280655f) {
                            if (features[2] <= -0.16396384686231613f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            if (features[8] <= 0.0955120101571083f) {
                                return 1;                            } else {
                                return 0;                            }
                        }
                    }
                } else {
                    if (features[4] <= 0.18305863440036774f) {
                        if (features[5] <= -0.04490009695291519f) {
                            return 1;                        } else {
                            if (features[14] <= -0.7049895226955414f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[22] <= 0.19214549660682678f) {
                            if (features[27] <= 1.5360650420188904f) {
                                return 2;                            } else {
                                return 1;                            }
                        } else {
                            if (features[14] <= -16.620059967041016f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                }
            }
        }
    }
}

// Tree 136
int predict_tree_136(const float* features) {
    // Max depth: 10
    if (features[22] <= 0.12021179869771004f) {
        if (features[1] <= -0.35448597371578217f) {
            if (features[27] <= 2.558004856109619f) {
                return 0;            } else {
                return 1;            }
        } else {
            if (features[24] <= -0.2753482013940811f) {
                if (features[17] <= -0.37529483437538147f) {
                    if (features[17] <= -0.39785462617874146f) {
                        return 1;                    } else {
                        return 0;                    }
                } else {
                    if (features[17] <= -0.35726261138916016f) {
                        if (features[3] <= 0.316247895359993f) {
                            return 0;                        } else {
                            if (features[25] <= -0.37507398426532745f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    } else {
                        return 1;                    }
                }
            } else {
                if (features[4] <= 0.05423935875296593f) {
                    if (features[11] <= -1.2184069454669952f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    if (features[8] <= -0.19962451606988907f) {
                        return 2;                    } else {
                        return 0;                    }
                }
            }
        }
    } else {
        if (features[0] <= -0.21553847193717957f) {
            if (features[24] <= 0.2756664752960205f) {
                if (features[0] <= -0.5586678981781006f) {
                    if (features[0] <= -0.5876643359661102f) {
                        if (features[18] <= -0.585340678691864f) {
                            if (features[31] <= 0.16302114725112915f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            if (features[21] <= 0.3170028105378151f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[33] <= -0.7310653924942017f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[5] <= -0.13495303690433502f) {
                        return 0;                    } else {
                        if (features[24] <= -0.10382181778550148f) {
                            return 0;                        } else {
                            if (features[26] <= 1.348282814025879f) {
                                if (features[17] <= -0.30787791311740875f) {
                                    if (features[11] <= 0.12834497168660164f) {
                                        return 1;                                    } else {
                                        if (features[29] <= -0.0025959014892578125f) {
                                            return 2;                                        } else {
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
                if (features[18] <= -0.5053301453590393f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[6] <= -1.8803272247314453f) {
                return 2;            } else {
                return 2;            }
        }
    }
}

// Tree 137
int predict_tree_137(const float* features) {
    // Max depth: 10
    if (features[15] <= 0.7462623417377472f) {
        if (features[17] <= -0.4496259391307831f) {
            if (features[24] <= 0.06724588572978973f) {
                if (features[27] <= 3.301996350288391f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                if (features[23] <= 1.6104379296302795f) {
                    return 1;                } else {
                    return 2;                }
            }
        } else {
            if (features[19] <= -0.20676681399345398f) {
                if (features[23] <= 0.253122515976429f) {
                    if (features[17] <= -0.43032942712306976f) {
                        return 0;                    } else {
                        if (features[22] <= -0.6408422887325287f) {
                            return 0;                        } else {
                            if (features[27] <= -0.31119967997074127f) {
                                return 0;                            } else {
                                if (features[6] <= 0.10452218819409609f) {
                                    return 1;                                } else {
                                    if (features[14] <= 0.29641103744506836f) {
                                        if (features[0] <= -0.377163901925087f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[8] <= -0.14442779123783112f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    }
                                }
                            }
                        }
                    }
                } else {
                    if (features[34] <= -2.0389932096004486f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[10] <= 0.9761940240859985f) {
                    if (features[2] <= -0.4483238458633423f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    if (features[4] <= 0.09921075776219368f) {
                        return 0;                    } else {
                        if (features[11] <= -0.10045238956809044f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    } else {
        if (features[17] <= -0.22465001046657562f) {
            if (features[24] <= -0.07711952179670334f) {
                if (features[5] <= -0.29401667416095734f) {
                    if (features[17] <= -0.40198753774166107f) {
                        if (features[9] <= -1.0217601656913757f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[9] <= -0.6236056685447693f) {
                            return 0;                        } else {
                            if (features[18] <= -0.3480522334575653f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    if (features[13] <= 0.407139889895916f) {
                        if (features[19] <= -0.590792328119278f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[7] <= 0.5617517828941345f) {
                    if (features[22] <= 0.5667100548744202f) {
                        return 1;                    } else {
                        if (features[7] <= -0.03399914037436247f) {
                            return 2;                        } else {
                            if (features[10] <= -0.35763226449489594f) {
                                return 1;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[1] <= -0.4176947772502899f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[22] <= 0.0017505965661257505f) {
                return 0;            } else {
                if (features[23] <= 0.11411232501268387f) {
                    if (features[34] <= -2.0389932096004486f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    if (features[20] <= 0.03790952265262604f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 138
int predict_tree_138(const float* features) {
    // Max depth: 10
    if (features[1] <= -0.425544410943985f) {
        if (features[5] <= -0.030809917487204075f) {
            return 0;        } else {
            if (features[17] <= -0.5243097245693207f) {
                if (features[24] <= -0.03304228652268648f) {
                    return 0;                } else {
                    if (features[8] <= 0.09188399836421013f) {
                        return 1;                    } else {
                        if (features[18] <= -0.5824315547943115f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                }
            } else {
                if (features[5] <= 1.7115232944488525f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[17] <= -0.24509385973215103f) {
            if (features[24] <= 0.4745195060968399f) {
                if (features[2] <= -0.5177714973688126f) {
                    if (features[24] <= -0.2975159287452698f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    if (features[2] <= -0.2549965903162956f) {
                        if (features[21] <= 0.7331589758396149f) {
                            if (features[15] <= 0.7462623417377472f) {
                                return 1;                            } else {
                                if (features[22] <= -0.0003514289855957031f) {
                                    return 0;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[24] <= 0.049794601276516914f) {
                                if (features[12] <= 0.11485183238983154f) {
                                    if (features[3] <= 0.3600112497806549f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 2;                                }
                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[26] <= -0.3074854165315628f) {
                            if (features[24] <= -0.3814724087715149f) {
                                return 0;                            } else {
                                if (features[18] <= -0.37952396273612976f) {
                                    return 0;                                } else {
                                    if (features[1] <= -0.3393575847148895f) {
                                        if (features[23] <= -0.35248376429080963f) {
                                            return 0;                                        } else {
                                            return 2;                                        }
                                    } else {
                                        return 1;                                    }
                                }
                            }
                        } else {
                            if (features[7] <= 0.35731178522109985f) {
                                if (features[7] <= 0.017522362526506186f) {
                                    if (features[3] <= -0.24869727343320847f) {
                                        if (features[18] <= -0.46396638453006744f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[11] <= -0.00110712181776762f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    }
                                } else {
                                    if (features[0] <= -0.3676949441432953f) {
                                        if (features[10] <= -0.44183604419231415f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                if (features[27] <= -0.3098815828561783f) {
                                    return 0;                                } else {
                                    if (features[17] <= -0.38164205849170685f) {
                                        return 0;                                    } else {
                                        if (features[5] <= -0.36427895724773407f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                if (features[17] <= -0.45170360803604126f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[5] <= 0.07066236808896065f) {
                if (features[2] <= -0.958857998251915f) {
                    return 0;                } else {
                    return 2;                }
            } else {
                if (features[2] <= -0.9551040530204773f) {
                    return 0;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 139
int predict_tree_139(const float* features) {
    // Max depth: 8
    if (features[22] <= 0.12049476429820061f) {
        if (features[11] <= 0.04130369983613491f) {
            if (features[0] <= -0.3758691996335983f) {
                if (features[13] <= 1.052195429801941f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                if (features[22] <= -0.25146249681711197f) {
                    return 1;                } else {
                    if (features[22] <= 0.058919595554471016f) {
                        if (features[18] <= 1.081988513469696f) {
                            return 2;                        } else {
                            return 0;                        }
                    } else {
                        if (features[24] <= 0.029854360036551952f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[21] <= -0.5662420094013214f) {
                if (features[26] <= -0.25908225774765015f) {
                    return 0;                } else {
                    if (features[1] <= -0.37303580343723297f) {
                        return 0;                    } else {
                        if (features[23] <= -0.4044880121946335f) {
                            return 0;                        } else {
                            if (features[0] <= -0.376185804605484f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    }
                }
            } else {
                if (features[24] <= 0.2576199769973755f) {
                    if (features[26] <= 1.7288216948509216f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    if (features[19] <= 0.025345993228256702f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[0] <= -0.30052614212036133f) {
            if (features[22] <= 1.5393915176391602f) {
                if (features[0] <= -0.47472700476646423f) {
                    if (features[5] <= -0.00588306353893131f) {
                        if (features[15] <= 0.7462623417377472f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[18] <= -0.22475595772266388f) {
                        if (features[11] <= 0.20739997923374176f) {
                            if (features[9] <= 1.111545979976654f) {
                                if (features[20] <= 0.34843071550130844f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            } else {
                                return 1;                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[33] <= -0.7310653924942017f) {
                            return 2;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                return 2;            }
        } else {
            if (features[24] <= -0.15439129620790482f) {
                return 2;            } else {
                return 2;            }
        }
    }
}

// Tree 140
int predict_tree_140(const float* features) {
    // Max depth: 9
    if (features[4] <= 0.12167630344629288f) {
        if (features[17] <= -0.39827775955200195f) {
            return 0;        } else {
            if (features[6] <= -0.33655544370412827f) {
                if (features[3] <= 1.7365677952766418f) {
                    return 2;                } else {
                    return 0;                }
            } else {
                if (features[0] <= -0.3758653551340103f) {
                    return 0;                } else {
                    if (features[23] <= -0.39186370372772217f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            }
        }
    } else {
        if (features[2] <= -0.3113054931163788f) {
            if (features[8] <= -0.1828179731965065f) {
                if (features[3] <= -0.03306327573955059f) {
                    return 0;                } else {
                    if (features[5] <= 0.1170620433986187f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[22] <= 0.7906160950660706f) {
                    if (features[19] <= -0.4496535360813141f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    if (features[17] <= -0.2942887991666794f) {
                        return 1;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[7] <= -0.35172855854034424f) {
                if (features[26] <= 0.16768828779459f) {
                    if (features[14] <= 0.4570607841014862f) {
                        if (features[19] <= -0.08179069310426712f) {
                            if (features[17] <= -0.5722039937973022f) {
                                if (features[9] <= 0.8008623421192169f) {
                                    if (features[3] <= -0.5431053042411804f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    if (features[5] <= 0.07550491392612457f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                return 1;                            }
                        } else {
                            return 2;                        }
                    } else {
                        if (features[6] <= -1.6597883701324463f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                } else {
                    return 2;                }
            } else {
                if (features[0] <= -0.5131122469902039f) {
                    return 0;                } else {
                    if (features[22] <= 0.19214549660682678f) {
                        if (features[2] <= -0.060730839148163795f) {
                            return 1;                        } else {
                            if (features[23] <= -0.0071996350307017565f) {
                                return 1;                            } else {
                                if (features[9] <= -0.5390594005584717f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        }
                    } else {
                        if (features[19] <= -0.5231368839740753f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    }
}

// Tree 141
int predict_tree_141(const float* features) {
    // Max depth: 10
    if (features[0] <= -0.4491797536611557f) {
        if (features[13] <= 0.2037208005785942f) {
            if (features[20] <= 0.5038374960422516f) {
                return 0;            } else {
                if (features[1] <= -0.48369136452674866f) {
                    return 1;                } else {
                    if (features[7] <= 0.6653272807598114f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[22] <= 1.4638398587703705f) {
                if (features[23] <= -0.04880714416503906f) {
                    if (features[10] <= -0.5756027102470398f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[14] <= 0.7346118539571762f) {
                        if (features[12] <= -0.0048601123271510005f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        return 0;                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[10] <= -0.14812666922807693f) {
            if (features[24] <= 1.5141484290361404f) {
                if (features[17] <= -0.42905163764953613f) {
                    if (features[23] <= -0.13479040935635567f) {
                        if (features[7] <= -2.2412010431289673f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[9] <= -0.7603023648262024f) {
                        return 0;                    } else {
                        if (features[1] <= -0.39720819890499115f) {
                            return 0;                        } else {
                            if (features[17] <= -0.22001521289348602f) {
                                if (features[24] <= -0.1300196424126625f) {
                                    if (features[10] <= -0.36409255862236023f) {
                                        if (features[2] <= -0.23904239013791084f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        if (features[23] <= -0.29870347678661346f) {
                                            return 1;                                        } else {
                                            return 0;                                        }
                                    }
                                } else {
                                    if (features[15] <= 0.7462623417377472f) {
                                        return 1;                                    } else {
                                        if (features[3] <= 0.5887742638587952f) {
                                            return 1;                                        } else {
                                            return 2;                                        }
                                    }
                                }
                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                if (features[30] <= 0.17709434032440186f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[22] <= 0.044326696544885635f) {
                if (features[18] <= 0.307127945125103f) {
                    return 2;                } else {
                    if (features[22] <= 0.04009233042597771f) {
                        return 0;                    } else {
                        return 0;                    }
                }
            } else {
                if (features[20] <= 0.03191992826759815f) {
                    return 0;                } else {
                    if (features[22] <= 0.06001103110611439f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 142
int predict_tree_142(const float* features) {
    // Max depth: 10
    if (features[17] <= -0.4484042674303055f) {
        if (features[4] <= 0.29601098597049713f) {
            return 0;        } else {
            if (features[23] <= 1.0739642232656479f) {
                if (features[26] <= -0.3583330363035202f) {
                    return 0;                } else {
                    if (features[24] <= -0.05656813830137253f) {
                        return 0;                    } else {
                        if (features[23] <= 0.01652532583102584f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[9] <= -1.1303842067718506f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[6] <= -0.11601662915199995f) {
            if (features[17] <= -0.23100721091032028f) {
                if (features[23] <= 1.5812974572181702f) {
                    if (features[5] <= -0.363091304898262f) {
                        return 0;                    } else {
                        if (features[0] <= -0.43235036730766296f) {
                            return 0;                        } else {
                            if (features[19] <= -0.4801723212003708f) {
                                return 1;                            } else {
                                if (features[17] <= -0.30787791311740875f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        }
                    }
                } else {
                    if (features[10] <= -0.43738751113414764f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[23] <= 0.07059157267212868f) {
                    if (features[22] <= -0.002635357901453972f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    if (features[3] <= 1.8996857702732086f) {
                        return 2;                    } else {
                        if (features[28] <= 0.03392469882965088f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                }
            }
        } else {
            if (features[3] <= -0.4050518274307251f) {
                if (features[6] <= 0.10452218819409609f) {
                    return 2;                } else {
                    if (features[0] <= -0.43536923825740814f) {
                        return 0;                    } else {
                        return 0;                    }
                }
            } else {
                if (features[18] <= -0.18383954465389252f) {
                    if (features[1] <= -0.38004255294799805f) {
                        return 0;                    } else {
                        if (features[12] <= 0.2614666298031807f) {
                            if (features[17] <= -0.4160441607236862f) {
                                return 0;                            } else {
                                if (features[6] <= 0.5455998182296753f) {
                                    if (features[12] <= 0.17581263184547424f) {
                                        if (features[27] <= -0.28111347556114197f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[0] <= -0.3758691996335983f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        } else {
                            if (features[4] <= 0.36358895897865295f) {
                                return 0;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 143
int predict_tree_143(const float* features) {
    // Max depth: 8
    if (features[21] <= 0.11980712041258812f) {
        if (features[6] <= 1.2072162628173828f) {
            if (features[17] <= -0.39832252264022827f) {
                return 0;            } else {
                if (features[21] <= -0.27335212379693985f) {
                    if (features[3] <= -0.40783676505088806f) {
                        return 0;                    } else {
                        if (features[17] <= -0.3745017647743225f) {
                            return 1;                        } else {
                            if (features[9] <= -0.5904407799243927f) {
                                if (features[4] <= -0.5668675899505615f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    if (features[10] <= 0.9434992372989655f) {
                        return 2;                    } else {
                        if (features[3] <= 1.4182888269424438f) {
                            return 2;                        } else {
                            return 0;                        }
                    }
                }
            }
        } else {
            if (features[17] <= -0.37916359305381775f) {
                if (features[25] <= -0.45670872926712036f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[20] <= -0.6210366785526276f) {
                    if (features[1] <= -0.33857356011867523f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[26] <= -0.29753918945789337f) {
                        return 0;                    } else {
                        if (features[0] <= -0.32593482732772827f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            }
        }
    } else {
        if (features[18] <= -0.20248916000127792f) {
            if (features[21] <= 1.538383960723877f) {
                if (features[18] <= -0.45296797156333923f) {
                    if (features[23] <= -0.02820945531129837f) {
                        if (features[21] <= 0.12193814665079117f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[4] <= 0.2927066385746002f) {
                            return 0;                        } else {
                            if (features[19] <= -0.5794512629508972f) {
                                return 1;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[26] <= 0.9570896625518799f) {
                        if (features[17] <= -0.31819264590740204f) {
                            if (features[0] <= -0.3681335598230362f) {
                                return 1;                            } else {
                                if (features[18] <= -0.3702927231788635f) {
                                    return 2;                                } else {
                                    return 1;                                }
                            }
                        } else {
                            if (features[23] <= 0.0002763476222753525f) {
                                return 1;                            } else {
                                return 2;                            }
                        }
                    } else {
                        return 2;                    }
                }
            } else {
                return 2;            }
        } else {
            if (features[20] <= 0.106557946652174f) {
                return 2;            } else {
                return 2;            }
        }
    }
}

// Tree 144
int predict_tree_144(const float* features) {
    // Max depth: 10
    if (features[17] <= -0.44954729080200195f) {
        if (features[27] <= 0.0012386281741783023f) {
            if (features[5] <= 1.2621531942859292f) {
                return 0;            } else {
                if (features[13] <= -0.31481532752513885f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[24] <= 0.862622931599617f) {
                if (features[9] <= 0.8412036597728729f) {
                    return 0;                } else {
                    if (features[21] <= 0.4146563410758972f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[10] <= -0.21255208551883698f) {
            if (features[24] <= 0.20459899306297302f) {
                if (features[19] <= -0.42991192638874054f) {
                    if (features[26] <= -0.09942140616476536f) {
                        if (features[1] <= -0.43165354430675507f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[23] <= -0.3986460417509079f) {
                            return 0;                        } else {
                            if (features[3] <= -0.39192281663417816f) {
                                return 1;                            } else {
                                if (features[19] <= -0.4939303696155548f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        }
                    }
                } else {
                    if (features[0] <= -0.4296743869781494f) {
                        return 0;                    } else {
                        if (features[4] <= -0.6400770545005798f) {
                            return 0;                        } else {
                            if (features[6] <= 0.10452218819409609f) {
                                if (features[24] <= -0.2209847830235958f) {
                                    return 0;                                } else {
                                    if (features[8] <= -0.19525185972452164f) {
                                        return 2;                                    } else {
                                        if (features[12] <= 0.0783008374273777f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            } else {
                                if (features[1] <= -0.3429037630558014f) {
                                    if (features[17] <= -0.42432068288326263f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    if (features[17] <= -0.3769413232803345f) {
                                        return 1;                                    } else {
                                        if (features[24] <= -0.3284132331609726f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                if (features[25] <= 0.26158715039491653f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[5] <= 0.07374214753508568f) {
                if (features[3] <= 1.8961051255464554f) {
                    return 2;                } else {
                    return 0;                }
            } else {
                if (features[3] <= 1.9036642611026764f) {
                    return 2;                } else {
                    if (features[25] <= 0.024848751490935683f) {
                        return 0;                    } else {
                        return 0;                    }
                }
            }
        }
    }
}

// Tree 145
int predict_tree_145(const float* features) {
    // Max depth: 10
    if (features[20] <= 0.1223587803542614f) {
        if (features[10] <= -0.36409255862236023f) {
            return 0;        } else {
            if (features[18] <= -0.11484858021140099f) {
                if (features[0] <= -0.3758691996335983f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                if (features[20] <= 0.0383935309946537f) {
                    if (features[12] <= -2.0086837708950043f) {
                        return 2;                    } else {
                        if (features[5] <= 0.2801983803510666f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[22] <= 0.045367601327598095f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[18] <= -0.2300560474395752f) {
            if (features[25] <= 1.052002653479576f) {
                if (features[10] <= -0.5063328742980957f) {
                    if (features[33] <= -0.7310653924942017f) {
                        if (features[10] <= -0.5659065246582031f) {
                            if (features[27] <= 0.07486553490161896f) {
                                return 0;                            } else {
                                return 1;                            }
                        } else {
                            if (features[31] <= 0.16302114725112915f) {
                                return 0;                            } else {
                                return 0;                            }
                        }
                    } else {
                        if (features[3] <= -0.6465460062026978f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[7] <= 0.4214008301496506f) {
                        if (features[17] <= -0.176649060100317f) {
                            if (features[11] <= 0.2016637995839119f) {
                                if (features[25] <= -0.10289609432220459f) {
                                    return 0;                                } else {
                                    if (features[19] <= -0.3812156617641449f) {
                                        return 1;                                    } else {
                                        if (features[7] <= 0.03159811068326235f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            } else {
                                if (features[9] <= 0.9434016942977905f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            return 2;                        }
                    } else {
                        return 2;                    }
                }
            } else {
                return 2;            }
        } else {
            if (features[20] <= 0.12279237061738968f) {
                return 2;            } else {
                return 2;            }
        }
    }
}

// Tree 146
int predict_tree_146(const float* features) {
    // Max depth: 10
    if (features[4] <= 0.121605783700943f) {
        if (features[5] <= -0.35261230170726776f) {
            if (features[22] <= -0.640367329120636f) {
                return 0;            } else {
                if (features[22] <= -0.6041882336139679f) {
                    if (features[24] <= -0.38952840864658356f) {
                        return 0;                    } else {
                        if (features[1] <= -0.35395754873752594f) {
                            if (features[24] <= -0.38730980455875397f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            if (features[2] <= -0.07011565566062927f) {
                                if (features[27] <= -0.2612495422363281f) {
                                    if (features[13] <= -0.04330344870686531f) {
                                        return 0;                                    } else {
                                        if (features[0] <= -0.3759319484233856f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    return 0;                                }
                            } else {
                                if (features[17] <= -0.3832317739725113f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            }
                        }
                    }
                } else {
                    if (features[0] <= -0.3748130053281784f) {
                        if (features[14] <= -0.4109010100364685f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                }
            }
        } else {
            if (features[15] <= 0.7462623417377472f) {
                if (features[8] <= -0.3672599643468857f) {
                    if (features[9] <= 0.3044198453426361f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    if (features[26] <= 0.10260862112045288f) {
                        if (features[23] <= 0.3279709964990616f) {
                            return 0;                        } else {
                            return 2;                        }
                    } else {
                        if (features[4] <= 0.014667754992842674f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[2] <= 0.2114289030432701f) {
                    if (features[12] <= 2.8277417421340942f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    if (features[33] <= -0.7310653924942017f) {
                        return 2;                    } else {
                        if (features[10] <= -0.2815447002649307f) {
                            if (features[8] <= -0.2602558806538582f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    }
                }
            }
        }
    } else {
        if (features[2] <= -0.3084900379180908f) {
            if (features[1] <= -0.3258539289236069f) {
                if (features[25] <= -0.02516584750264883f) {
                    return 0;                } else {
                    if (features[27] <= 0.7233228087425232f) {
                        if (features[7] <= 0.18817488104104996f) {
                            if (features[9] <= 2.050986647605896f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            if (features[17] <= -0.3911600112915039f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[8] <= -0.1226494275033474f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                return 2;            }
        } else {
            if (features[4] <= 0.18312915414571762f) {
                if (features[33] <= -0.7310653924942017f) {
                    if (features[19] <= -0.2216019630432129f) {
                        return 0;                    } else {
                        if (features[24] <= 0.200245663523674f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[10] <= -0.4364655166864395f) {
                        return 0;                    } else {
                        if (features[5] <= -0.04211864713579416f) {
                            return 1;                        } else {
                            if (features[26] <= -0.33965757489204407f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                if (features[10] <= -0.5001237988471985f) {
                    if (features[7] <= -0.6544800102710724f) {
                        if (features[17] <= -0.5702398717403412f) {
                            if (features[5] <= 0.021316302940249443f) {
                                return 0;                            } else {
                                return 1;                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[31] <= 0.16302114725112915f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[21] <= 0.16788145899772644f) {
                        if (features[33] <= -0.7310653924942017f) {
                            return 2;                        } else {
                            return 1;                        }
                    } else {
                        if (features[21] <= 0.17966775596141815f) {
                            return 2;                        } else {
                            if (features[12] <= -10.438920497894287f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                }
            }
        }
    }
}

// Tree 147
int predict_tree_147(const float* features) {
    // Max depth: 10
    if (features[1] <= -0.42361240088939667f) {
        if (features[27] <= -0.012747229542583227f) {
            if (features[20] <= 1.2191706150770187f) {
                return 0;            } else {
                if (features[20] <= 2.2504196166992188f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[19] <= -0.5121001601219177f) {
                if (features[4] <= 0.4469835013151169f) {
                    if (features[0] <= -0.5859940946102142f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    return 1;                }
            } else {
                if (features[7] <= 0.5737298876047134f) {
                    return 0;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[17] <= -0.24509385973215103f) {
            if (features[23] <= 1.2053164839744568f) {
                if (features[17] <= -0.43032942712306976f) {
                    return 0;                } else {
                    if (features[21] <= -0.6415753066539764f) {
                        return 0;                    } else {
                        if (features[20] <= 0.09188646264374256f) {
                            if (features[17] <= -0.379781037569046f) {
                                if (features[24] <= -0.387261226773262f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                if (features[15] <= 0.7462623417377472f) {
                                    if (features[1] <= -0.3375915288925171f) {
                                        if (features[2] <= -0.07011565566062927f) {
                                            return 1;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[3] <= -0.3043960928916931f) {
                                        return 1;                                    } else {
                                        return 2;                                    }
                                }
                            }
                        } else {
                            if (features[20] <= 0.672967940568924f) {
                                if (features[21] <= 0.47575923800468445f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            } else {
                                if (features[10] <= -0.3557049334049225f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                }
            } else {
                if (features[17] <= -0.4498724490404129f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[22] <= 0.05498840659856796f) {
                if (features[4] <= 0.021840613335371017f) {
                    return 0;                } else {
                    if (features[0] <= 0.9808841347694397f) {
                        return 2;                    } else {
                        return 0;                    }
                }
            } else {
                return 2;            }
        }
    }
}

// Tree 148
int predict_tree_148(const float* features) {
    // Max depth: 9
    if (features[21] <= 0.1191304437816143f) {
        if (features[22] <= -0.567423015832901f) {
            if (features[7] <= 0.3598013073205948f) {
                if (features[17] <= -0.3995446264743805f) {
                    return 0;                } else {
                    if (features[31] <= 0.16302114725112915f) {
                        return 0;                    } else {
                        if (features[5] <= -0.3964684009552002f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[17] <= -0.379781037569046f) {
                    if (features[0] <= -0.6066328287124634f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[5] <= -0.34911197423934937f) {
                        if (features[13] <= 0.07440897449851036f) {
                            if (features[19] <= -0.39831720292568207f) {
                                return 1;                            } else {
                                if (features[0] <= -0.3758691996335983f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            }
                        } else {
                            return 0;                        }
                    } else {
                        return 0;                    }
                }
            }
        } else {
            if (features[33] <= -0.7310653924942017f) {
                if (features[26] <= -0.14271435141563416f) {
                    if (features[7] <= -3.775776743888855f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[6] <= -1.1084412932395935f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[24] <= -0.29027557373046875f) {
                    if (features[10] <= -0.2764683812856674f) {
                        if (features[5] <= -0.38616859912872314f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[20] <= 0.09133187308907509f) {
                        if (features[4] <= -0.5465075373649597f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[17] <= -0.056670621037483215f) {
                            if (features[10] <= -0.582628607749939f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    } else {
        if (features[8] <= -0.18651897460222244f) {
            if (features[18] <= -0.5126209855079651f) {
                if (features[17] <= -0.49832864105701447f) {
                    if (features[1] <= -0.5522292256355286f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    return 1;                }
            } else {
                return 2;            }
        } else {
            if (features[1] <= -0.14373307675123215f) {
                if (features[23] <= 0.253122515976429f) {
                    if (features[10] <= -0.5060524940490723f) {
                        if (features[9] <= 0.8893032371997833f) {
                            if (features[30] <= 0.17709434032440186f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            if (features[8] <= 0.07166363298892975f) {
                                return 1;                            } else {
                                return 0;                            }
                        }
                    } else {
                        if (features[12] <= 0.14147628843784332f) {
                            if (features[5] <= -0.09898247942328453f) {
                                return 1;                            } else {
                                if (features[0] <= -0.37147611379623413f) {
                                    return 1;                                } else {
                                    if (features[18] <= -0.22708873450756073f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        } else {
                            if (features[22] <= 0.42588454484939575f) {
                                return 1;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[10] <= -0.44818761944770813f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[17] <= -0.14085877686738968f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 149
int predict_tree_149(const float* features) {
    // Max depth: 8
    if (features[21] <= 0.11981721967458725f) {
        if (features[7] <= 0.36097848415374756f) {
            if (features[10] <= -0.36416296660900116f) {
                return 0;            } else {
                if (features[13] <= 0.05636546574532986f) {
                    if (features[5] <= -0.1531224618665874f) {
                        if (features[17] <= -0.35540181398391724f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        if (features[9] <= -0.5374112725257874f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[23] <= -0.15665871929377317f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[10] <= -0.35785675048828125f) {
                if (features[5] <= -0.4806147664785385f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[23] <= -0.3238670974969864f) {
                    if (features[7] <= 0.5373493432998657f) {
                        if (features[10] <= -0.35496382415294647f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[9] <= -0.32920776307582855f) {
                        return 0;                    } else {
                        return 0;                    }
                }
            }
        }
    } else {
        if (features[20] <= 1.0608497262001038f) {
            if (features[17] <= -0.22465001046657562f) {
                if (features[10] <= -0.5403608679771423f) {
                    if (features[1] <= -0.5501088500022888f) {
                        if (features[20] <= 0.3359574228525162f) {
                            if (features[10] <= -0.5687476694583893f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[14] <= -0.562799870967865f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[5] <= -0.10437352955341339f) {
                        return 0;                    } else {
                        if (features[11] <= 0.4791518300771713f) {
                            if (features[33] <= -0.7310653924942017f) {
                                if (features[20] <= 0.3449922278523445f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            } else {
                                return 1;                            }
                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[20] <= 0.09724079817533493f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[4] <= 1.520453929901123f) {
                if (features[0] <= -0.34861035645008087f) {
                    if (features[2] <= -0.4830476641654968f) {
                        return 1;                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            } else {
                if (features[23] <= 0.04175357148051262f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 150
int predict_tree_150(const float* features) {
    // Max depth: 10
    if (features[23] <= -0.12574809789657593f) {
        if (features[18] <= -0.4176875054836273f) {
            if (features[17] <= -0.40153835713863373f) {
                return 0;            } else {
                return 1;            }
        } else {
            if (features[18] <= 0.367523729801178f) {
                if (features[27] <= -0.3088188171386719f) {
                    return 0;                } else {
                    if (features[5] <= -0.389695942401886f) {
                        return 0;                    } else {
                        if (features[17] <= -0.3792797327041626f) {
                            if (features[14] <= -0.33270828425884247f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            if (features[12] <= -0.371526762843132f) {
                                return 0;                            } else {
                                if (features[2] <= -0.09827011078596115f) {
                                    if (features[5] <= -0.35377320647239685f) {
                                        if (features[1] <= -0.33815522491931915f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 0;                                    }
                                } else {
                                    if (features[5] <= -0.3584032505750656f) {
                                        return 1;                                    } else {
                                        if (features[23] <= -0.3687649220228195f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[20] <= 1.1210985779762268f) {
            if (features[20] <= 0.1530025228857994f) {
                if (features[22] <= 0.12408235296607018f) {
                    if (features[25] <= 0.3135503977537155f) {
                        if (features[8] <= -0.2417709156870842f) {
                            if (features[23] <= -0.029837331734597683f) {
                                return 0;                            } else {
                                return 2;                            }
                        } else {
                            if (features[12] <= -0.888893723487854f) {
                                return 0;                            } else {
                                return 0;                            }
                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[24] <= -0.01228086743503809f) {
                        if (features[1] <= -0.41464538872241974f) {
                            if (features[31] <= 0.16302114725112915f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[17] <= 0.09135923162102699f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[19] <= -0.30770860612392426f) {
                    if (features[27] <= -0.1774354726076126f) {
                        return 0;                    } else {
                        if (features[17] <= -0.23468387126922607f) {
                            if (features[4] <= 0.16557983309030533f) {
                                return 0;                            } else {
                                if (features[9] <= 0.8893032371997833f) {
                                    if (features[12] <= 0.1823613801971078f) {
                                        if (features[33] <= -0.7310653924942017f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        if (features[19] <= -0.5844077467918396f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    if (features[24] <= 0.10345948114991188f) {
                                        if (features[27] <= -0.03810723498463631f) {
                                            return 2;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 1;                                    }
                                }
                            }
                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[1] <= -0.2253611609339714f) {
                        return 1;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[6] <= -1.6597883701324463f) {
                return 2;            } else {
                if (features[18] <= -0.2254994511604309f) {
                    if (features[25] <= 1.859227105975151f) {
                        if (features[22] <= 1.2470080256462097f) {
                            if (features[12] <= 0.12798143550753593f) {
                                return 1;                            } else {
                                return 2;                            }
                        } else {
                            return 1;                        }
                    } else {
                        return 2;                    }
                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 151
int predict_tree_151(const float* features) {
    // Max depth: 8
    if (features[6] <= -0.11601662915199995f) {
        if (features[20] <= 0.11958581954240799f) {
            if (features[25] <= 0.34457114338874817f) {
                if (features[27] <= -0.02160521224141121f) {
                    if (features[9] <= -0.677150547504425f) {
                        if (features[23] <= -0.36065971851348877f) {
                            return 0;                        } else {
                            if (features[1] <= -0.5204715132713318f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[11] <= 0.028282269835472107f) {
                            return 0;                        } else {
                            if (features[9] <= 0.06366164982318878f) {
                                return 0;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[17] <= -0.4200066328048706f) {
                        return 0;                    } else {
                        if (features[21] <= -0.03064739191904664f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                return 2;            }
        } else {
            if (features[8] <= -0.1866254135966301f) {
                if (features[25] <= -0.054677266627550125f) {
                    if (features[10] <= 0.06991666555404663f) {
                        if (features[21] <= 0.19503942131996155f) {
                            if (features[29] <= -0.0025959014892578125f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[18] <= -0.5419743955135345f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[23] <= 0.2037494257092476f) {
                    if (features[3] <= -0.4317076951265335f) {
                        if (features[19] <= 0.2534046471118927f) {
                            if (features[2] <= -0.17334866523742676f) {
                                return 0;                            } else {
                                if (features[26] <= -0.34898190200328827f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            }
                        } else {
                            if (features[0] <= -0.1756696836091578f) {
                                return 1;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[8] <= 0.07127518951892853f) {
                            if (features[4] <= 0.36480794847011566f) {
                                return 0;                            } else {
                                if (features[25] <= -0.06563679233659059f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        } else {
                            if (features[24] <= -0.07960326597094536f) {
                                return 0;                            } else {
                                return 0;                            }
                        }
                    }
                } else {
                    if (features[26] <= -0.3633464425802231f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[20] <= 0.43963590264320374f) {
            if (features[24] <= -0.3942602127790451f) {
                return 0;            } else {
                if (features[3] <= 0.3003339469432831f) {
                    if (features[26] <= -0.2712097465991974f) {
                        if (features[18] <= 0.06187745928764343f) {
                            return 0;                        } else {
                            return 2;                        }
                    } else {
                        if (features[1] <= -0.354820653796196f) {
                            return 0;                        } else {
                            if (features[24] <= -0.2753482013940811f) {
                                if (features[8] <= -0.13810743391513824f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            } else {
                                if (features[23] <= -0.07649043295532465f) {
                                    return 0;                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                } else {
                    if (features[22] <= -0.6404784917831421f) {
                        return 0;                    } else {
                        if (features[0] <= -0.3758691996335983f) {
                            if (features[27] <= -0.3209032416343689f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            if (features[18] <= -0.29435306787490845f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    }
                }
            }
        } else {
            if (features[22] <= 1.0668200850486755f) {
                if (features[19] <= -0.06359457969665527f) {
                    return 1;                } else {
                    if (features[1] <= 0.2448010817170143f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[0] <= -0.37436486780643463f) {
                    return 1;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 152
int predict_tree_152(const float* features) {
    // Max depth: 10
    if (features[24] <= -0.13055173307657242f) {
        if (features[10] <= -0.36409255862236023f) {
            return 0;        } else {
            if (features[20] <= -0.4333425462245941f) {
                if (features[10] <= -0.35785675048828125f) {
                    if (features[6] <= -0.005747221410274506f) {
                        return 1;                    } else {
                        if (features[5] <= -0.3700171709060669f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[8] <= -0.0979369692504406f) {
                        return 1;                    } else {
                        if (features[25] <= -0.36342769861221313f) {
                            if (features[20] <= -0.6323604583740234f) {
                                return 1;                            } else {
                                return 0;                            }
                        } else {
                            if (features[12] <= -0.02640519104897976f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    }
                }
            } else {
                if (features[5] <= -0.23312413692474365f) {
                    return 0;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[17] <= -0.23100721091032028f) {
            if (features[5] <= 1.0675677359104156f) {
                if (features[18] <= -0.5718167722225189f) {
                    if (features[9] <= 0.8882248103618622f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[23] <= -0.08445002138614655f) {
                        return 0;                    } else {
                        if (features[10] <= -0.5104551315307617f) {
                            return 0;                        } else {
                            if (features[21] <= 1.2398685812950134f) {
                                if (features[9] <= 2.391911745071411f) {
                                    if (features[29] <= -0.0025959014892578125f) {
                                        if (features[11] <= 0.08760756440460682f) {
                                            return 1;                                        } else {
                                            return 2;                                        }
                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                if (features[19] <= -0.38922958076000214f) {
                                    return 1;                                } else {
                                    if (features[8] <= -0.16748309135437012f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                if (features[2] <= 0.08004144579172134f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[2] <= -0.958857998251915f) {
                return 0;            } else {
                if (features[19] <= -0.3937806338071823f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 153
int predict_tree_153(const float* features) {
    // Max depth: 10
    if (features[10] <= -0.4359537661075592f) {
        if (features[21] <= 0.4146563410758972f) {
            if (features[4] <= 0.42458847165107727f) {
                return 0;            } else {
                return 1;            }
        } else {
            if (features[21] <= 1.087798148393631f) {
                if (features[26] <= -0.3568793088197708f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                return 2;            }
        }
    } else {
        if (features[17] <= -0.27531395852565765f) {
            if (features[34] <= -2.0389932096004486f) {
                return 2;            } else {
                if (features[17] <= -0.43021655082702637f) {
                    if (features[23] <= -0.13479040935635567f) {
                        if (features[19] <= -0.5272177457809448f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[12] <= -0.3446945548057556f) {
                        if (features[33] <= -0.7310653924942017f) {
                            return 2;                        } else {
                            return 0;                        }
                    } else {
                        if (features[4] <= -0.639714390039444f) {
                            return 0;                        } else {
                            if (features[18] <= -0.4302481859922409f) {
                                if (features[18] <= -0.4550016075372696f) {
                                    if (features[0] <= -0.3745678663253784f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[29] <= -0.0025959014892578125f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                }
                            } else {
                                if (features[0] <= -0.43021006882190704f) {
                                    return 0;                                } else {
                                    if (features[11] <= 0.47158950567245483f) {
                                        if (features[27] <= -0.31103286147117615f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 2;                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else {
            if (features[2] <= -0.968242809176445f) {
                return 0;            } else {
                if (features[9] <= -0.7781490087509155f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 154
int predict_tree_154(const float* features) {
    // Max depth: 9
    if (features[20] <= 0.1218646913766861f) {
        if (features[2] <= -0.12642456963658333f) {
            if (features[4] <= 0.09113121405243874f) {
                if (features[26] <= -0.1420750617980957f) {
                    return 0;                } else {
                    if (features[2] <= -0.3704298585653305f) {
                        return 0;                    } else {
                        if (features[10] <= -0.4154621362686157f) {
                            if (features[25] <= -0.3611103743314743f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[26] <= -0.3345859944820404f) {
                    return 0;                } else {
                    return 2;                }
            }
        } else {
            if (features[1] <= -0.33857356011867523f) {
                return 0;            } else {
                if (features[23] <= -0.29870347678661346f) {
                    if (features[11] <= -0.16733596473932266f) {
                        return 1;                    } else {
                        if (features[8] <= -0.08803584054112434f) {
                            return 1;                        } else {
                            if (features[11] <= 0.025242505595088005f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    if (features[33] <= -0.7310653924942017f) {
                        return 2;                    } else {
                        return 0;                    }
                }
            }
        }
    } else {
        if (features[4] <= 1.1199929118156433f) {
            if (features[20] <= 0.1832025870680809f) {
                if (features[0] <= -0.12347234785556793f) {
                    if (features[1] <= -0.41370876133441925f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            } else {
                if (features[0] <= -0.224639393389225f) {
                    if (features[4] <= 0.29601098597049713f) {
                        if (features[0] <= -0.49790841341018677f) {
                            if (features[6] <= -1.8803272247314453f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[7] <= 0.06920117326080799f) {
                            if (features[25] <= 0.04431643337011337f) {
                                if (features[2] <= 0.1738896295428276f) {
                                    return 1;                                } else {
                                    if (features[1] <= -0.5300284326076508f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                if (features[13] <= -0.4404754787683487f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            return 1;                        }
                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[18] <= -0.32585176825523376f) {
                if (features[24] <= 0.910741850733757f) {
                    if (features[8] <= -0.17866506427526474f) {
                        return 1;                    } else {
                        if (features[17] <= -0.385693684220314f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                } else {
                    return 2;                }
            } else {
                if (features[26] <= -0.36343546211719513f) {
                    return 1;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 155
int predict_tree_155(const float* features) {
    // Max depth: 10
    if (features[18] <= -0.44954901933670044f) {
        if (features[24] <= 0.041595589369535446f) {
            if (features[10] <= -0.3295498788356781f) {
                return 0;            } else {
                return 2;            }
        } else {
            if (features[20] <= 1.244681864976883f) {
                if (features[14] <= -0.4261735528707504f) {
                    return 1;                } else {
                    return 1;                }
            } else {
                if (features[2] <= 0.08004144579172134f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[10] <= -0.14820684492588043f) {
            if (features[4] <= 1.53406423330307f) {
                if (features[10] <= -0.4143046587705612f) {
                    return 0;                } else {
                    if (features[1] <= -0.3829467296600342f) {
                        if (features[4] <= 0.6466145943850279f) {
                            if (features[12] <= -0.10350425913929939f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[9] <= -0.7627458870410919f) {
                            return 0;                        } else {
                            if (features[19] <= -0.45635634660720825f) {
                                return 0;                            } else {
                                if (features[6] <= 0.5455998182296753f) {
                                    if (features[17] <= -0.26600807905197144f) {
                                        if (features[12] <= 0.1761169210076332f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 2;                                    }
                                } else {
                                    if (features[1] <= -0.3429037630558014f) {
                                        return 0;                                    } else {
                                        if (features[9] <= -0.410696417093277f) {
                                            return 1;                                        } else {
                                            return 0;                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                if (features[14] <= -9.670067310333252f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[20] <= 0.053659938275814056f) {
                if (features[3] <= 1.3705469816923141f) {
                    return 2;                } else {
                    return 0;                }
            } else {
                if (features[10] <= 2.2097854614257812f) {
                    return 2;                } else {
                    if (features[1] <= 2.1687204837799072f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 156
int predict_tree_156(const float* features) {
    // Max depth: 9
    if (features[4] <= 0.12223038822412491f) {
        if (features[11] <= -0.029462460428476334f) {
            if (features[20] <= -0.4446158856153488f) {
                if (features[1] <= -0.3566775619983673f) {
                    return 0;                } else {
                    if (features[25] <= -0.3900969922542572f) {
                        return 0;                    } else {
                        if (features[14] <= -0.24630995094776154f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[22] <= 0.08552839607000351f) {
                    if (features[14] <= 0.7286316156387329f) {
                        return 0;                    } else {
                        if (features[17] <= 0.9472299218177795f) {
                            return 2;                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[7] <= -1.8656051307916641f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[20] <= -0.569812536239624f) {
                if (features[17] <= -0.39827775955200195f) {
                    return 0;                } else {
                    if (features[3] <= 0.5708710551261902f) {
                        if (features[1] <= -0.3487269729375839f) {
                            return 0;                        } else {
                            if (features[10] <= -0.3601098656654358f) {
                                return 0;                            } else {
                                if (features[17] <= -0.37341780960559845f) {
                                    if (features[30] <= 0.17709434032440186f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 1;                                }
                            }
                        }
                    } else {
                        return 0;                    }
                }
            } else {
                if (features[5] <= 0.3159918934106827f) {
                    if (features[24] <= 0.2576199769973755f) {
                        if (features[4] <= 0.0918162651360035f) {
                            return 0;                        } else {
                            if (features[10] <= -0.09893904626369476f) {
                                if (features[6] <= -1.8803272247314453f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 2;                            }
                        }
                    } else {
                        return 2;                    }
                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[17] <= -0.24500302970409393f) {
            if (features[20] <= 1.535741925239563f) {
                if (features[4] <= 0.2928275316953659f) {
                    if (features[3] <= -0.9170831143856049f) {
                        return 1;                    } else {
                        return 0;                    }
                } else {
                    if (features[0] <= -0.214971661567688f) {
                        if (features[2] <= 0.1738896295428276f) {
                            if (features[15] <= 0.7462623417377472f) {
                                return 1;                            } else {
                                if (features[13] <= 0.15453075245022774f) {
                                    return 2;                                } else {
                                    if (features[21] <= 0.8600409030914307f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        } else {
                            if (features[19] <= -0.4965563118457794f) {
                                if (features[4] <= 0.4101218581199646f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[18] <= -0.5053326785564423f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[13] <= 2.9811325073242188f) {
                return 2;            } else {
                if (features[26] <= 0.21075062453746796f) {
                    if (features[7] <= 0.810835063457489f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 157
int predict_tree_157(const float* features) {
    // Max depth: 10
    if (features[0] <= -0.4496711492538452f) {
        if (features[24] <= -0.022179621271789074f) {
            return 0;        } else {
            if (features[8] <= -0.11135363951325417f) {
                if (features[27] <= -0.27131715416908264f) {
                    return 2;                } else {
                    return 2;                }
            } else {
                if (features[22] <= 0.4583648592233658f) {
                    if (features[5] <= -0.030809917487204075f) {
                        return 0;                    } else {
                        if (features[31] <= 0.16302114725112915f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                } else {
                    return 0;                }
            }
        }
    } else {
        if (features[0] <= -0.23959659039974213f) {
            if (features[20] <= 1.5383434891700745f) {
                if (features[0] <= -0.4296617656946182f) {
                    return 0;                } else {
                    if (features[5] <= -0.3896474689245224f) {
                        return 0;                    } else {
                        if (features[5] <= -0.11750911176204681f) {
                            if (features[1] <= -0.35448597371578217f) {
                                if (features[21] <= -0.6402219533920288f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                if (features[17] <= -0.3793257921934128f) {
                                    if (features[10] <= -0.36054399609565735f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[17] <= -0.37486056983470917f) {
                                        if (features[18] <= -0.38653288781642914f) {
                                            return 1;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        if (features[24] <= -0.39187461137771606f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        } else {
                            if (features[19] <= -0.2621280178427696f) {
                                if (features[20] <= 0.7112549543380737f) {
                                    if (features[18] <= -0.3690183013677597f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[1] <= -0.34162096679210663f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                if (features[5] <= 0.06673729047179222f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                }
            } else {
                if (features[24] <= 1.4582952558994293f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[25] <= 0.07136457040905952f) {
                if (features[20] <= -0.01673292857594788f) {
                    if (features[11] <= 0.5231444090604782f) {
                        if (features[11] <= -0.26110730320215225f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[22] <= -0.06297760759480298f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[3] <= 1.9036642611026764f) {
                    return 2;                } else {
                    if (features[4] <= -0.08966104313731194f) {
                        return 0;                    } else {
                        return 0;                    }
                }
            }
        }
    }
}

// Tree 158
int predict_tree_158(const float* features) {
    // Max depth: 10
    if (features[1] <= -0.4235561043024063f) {
        if (features[10] <= -0.4887477904558182f) {
            if (features[21] <= 0.43252262473106384f) {
                if (features[7] <= -0.516341358423233f) {
                    if (features[27] <= 2.440556287765503f) {
                        if (features[33] <= -0.7310653924942017f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                } else {
                    return 0;                }
            } else {
                if (features[5] <= 3.2729243598878384f) {
                    if (features[25] <= 0.03188328258693218f) {
                        return 1;                    } else {
                        return 1;                    }
                } else {
                    if (features[17] <= -0.5051828622817993f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[6] <= -0.9981719180941582f) {
                if (features[23] <= 0.8726251274347305f) {
                    return 0;                } else {
                    return 2;                }
            } else {
                if (features[11] <= -0.20382071286439896f) {
                    return 0;                } else {
                    return 0;                }
            }
        }
    } else {
        if (features[0] <= -0.214971661567688f) {
            if (features[2] <= 0.004962893668562174f) {
                if (features[22] <= -0.6407210230827332f) {
                    return 0;                } else {
                    if (features[10] <= -0.414151206612587f) {
                        return 0;                    } else {
                        if (features[11] <= 0.11915373429656029f) {
                            if (features[24] <= -0.07572409382555634f) {
                                if (features[19] <= -0.39547955989837646f) {
                                    if (features[26] <= -0.21518822014331818f) {
                                        if (features[30] <= 0.17709434032440186f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[7] <= 0.351346954703331f) {
                                        return 0;                                    } else {
                                        if (features[17] <= -0.37529483437538147f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            } else {
                                if (features[1] <= -0.3468702882528305f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        } else {
                            if (features[21] <= 0.4195142835378647f) {
                                return 1;                            } else {
                                if (features[24] <= 0.05429166555404663f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                }
            } else {
                if (features[33] <= -0.7310653924942017f) {
                    return 2;                } else {
                    if (features[19] <= -0.41337890923023224f) {
                        if (features[1] <= -0.3567028194665909f) {
                            if (features[6] <= 0.10452218819409609f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            if (features[23] <= -0.29870347678661346f) {
                                return 1;                            } else {
                                return 0;                            }
                        }
                    } else {
                        if (features[17] <= -0.3611677289009094f) {
                            return 0;                        } else {
                            if (features[12] <= -0.371526762843132f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    }
                }
            }
        } else {
            if (features[17] <= 1.1547359228134155f) {
                if (features[7] <= 2.0434001088142395f) {
                    return 2;                } else {
                    if (features[6] <= -0.9981718957424164f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[3] <= 1.4182888194918633f) {
                    if (features[28] <= -0.4683038666844368f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    return 0;                }
            }
        }
    }
}

// Tree 159
int predict_tree_159(const float* features) {
    // Max depth: 10
    if (features[17] <= -0.4498710483312607f) {
        if (features[6] <= -1.8803272247314453f) {
            if (features[2] <= 0.023732532747089863f) {
                if (features[21] <= 0.27114030718803406f) {
                    if (features[12] <= -0.014329752884805202f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[0] <= -0.5859085023403168f) {
                        return 1;                    } else {
                        return 0;                    }
                }
            } else {
                return 2;            }
        } else {
            if (features[20] <= 0.48105888068675995f) {
                return 0;            } else {
                if (features[10] <= -0.4569994807243347f) {
                    return 1;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[15] <= 0.7462623417377472f) {
            if (features[1] <= -0.26992420852184296f) {
                if (features[4] <= 1.53406423330307f) {
                    if (features[4] <= -0.6386364698410034f) {
                        return 0;                    } else {
                        if (features[17] <= -0.43034209311008453f) {
                            return 0;                        } else {
                            if (features[6] <= 0.10452218819409609f) {
                                return 1;                            } else {
                                if (features[9] <= -0.5537236630916595f) {
                                    if (features[19] <= -0.3900596797466278f) {
                                        if (features[25] <= -0.37275731563568115f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[10] <= -0.35496382415294647f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    if (features[14] <= -0.2845187485218048f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                }
                            }
                        }
                    }
                } else {
                    if (features[18] <= -0.44988445937633514f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[7] <= 1.7338817119598389f) {
                    return 2;                } else {
                    if (features[9] <= 0.6638485044240952f) {
                        if (features[1] <= 0.9986796975135803f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[22] <= 0.011189494282007217f) {
                if (features[3] <= -0.29643912613391876f) {
                    if (features[3] <= -0.40783676505088806f) {
                        return 0;                    } else {
                        if (features[18] <= -0.4630401134490967f) {
                            return 0;                        } else {
                            if (features[0] <= -0.3748130053281784f) {
                                if (features[17] <= -0.44400064647197723f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    if (features[11] <= 1.010651558637619f) {
                        return 0;                    } else {
                        return 0;                    }
                }
            } else {
                if (features[8] <= 0.09885989502072334f) {
                    if (features[19] <= 0.00714016129495576f) {
                        if (features[18] <= -0.19727405905723572f) {
                            if (features[8] <= -0.16294047236442566f) {
                                return 2;                            } else {
                                if (features[10] <= -0.3958906829357147f) {
                                    return 0;                                } else {
                                    if (features[11] <= 0.02337712049484253f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        } else {
                            return 2;                        }
                    } else {
                        if (features[7] <= 1.9315642714500427f) {
                            if (features[14] <= -5.380370378494263f) {
                                return 2;                            } else {
                                return 2;                            }
                        } else {
                            if (features[27] <= -0.15011313557624817f) {
                                return 0;                            } else {
                                if (features[22] <= 0.3805697411298752f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                } else {
                    if (features[3] <= -0.960846483707428f) {
                        return 1;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 160
int predict_tree_160(const float* features) {
    // Max depth: 10
    if (features[18] <= -0.449688196182251f) {
        if (features[4] <= 0.29601098597049713f) {
            return 0;        } else {
            if (features[19] <= -0.5734698474407196f) {
                if (features[27] <= 0.30187438428401947f) {
                    return 0;                } else {
                    if (features[5] <= 0.04275062680244446f) {
                        if (features[11] <= -1.4700228348374367e-05f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        return 1;                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[18] <= -0.2300560474395752f) {
            if (features[5] <= 0.9132881239056587f) {
                if (features[0] <= -0.4296617656946182f) {
                    return 0;                } else {
                    if (features[12] <= 0.8247190117835999f) {
                        if (features[4] <= -0.6384954154491425f) {
                            return 0;                        } else {
                            if (features[22] <= -0.6213581562042236f) {
                                if (features[10] <= -0.35469114780426025f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            } else {
                                if (features[18] <= -0.4291777163743973f) {
                                    return 0;                                } else {
                                    if (features[25] <= -0.28447453677654266f) {
                                        if (features[0] <= -0.37811940908432007f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[15] <= 0.7462623417377472f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[15] <= 0.7462623417377472f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[20] <= 0.053317099809646606f) {
                if (features[1] <= 0.8999863266944885f) {
                    if (features[19] <= 1.1312482357025146f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    if (features[21] <= 0.047079527750611305f) {
                        if (features[22] <= -0.10843388363718987f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[18] <= -0.0075117365922778845f) {
                    if (features[7] <= -0.28883692622184753f) {
                        return 1;                    } else {
                        return 2;                    }
                } else {
                    if (features[21] <= 0.29883354902267456f) {
                        if (features[13] <= -0.4153434485197067f) {
                            return 1;                        } else {
                            if (features[13] <= 2.4830029010772705f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[16] <= 3.1667469069361687f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    }
}

// Tree 161
int predict_tree_161(const float* features) {
    // Max depth: 7
    if (features[4] <= 0.12279454246163368f) {
        if (features[4] <= -0.5663437247276306f) {
            if (features[10] <= -0.364113450050354f) {
                return 0;            } else {
                if (features[0] <= -0.3759319484233856f) {
                    return 0;                } else {
                    return 1;                }
            }
        } else {
            if (features[10] <= -0.2815447002649307f) {
                return 0;            } else {
                if (features[2] <= -0.9522886127233505f) {
                    if (features[5] <= 0.04494576156139374f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    if (features[17] <= -0.1644895332865417f) {
                        return 1;                    } else {
                        if (features[13] <= -0.30944521725177765f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    } else {
        if (features[22] <= 1.062707006931305f) {
            if (features[10] <= -0.1354660429060459f) {
                if (features[3] <= -1.028480738401413f) {
                    return 1;                } else {
                    if (features[4] <= 0.47661183774471283f) {
                        if (features[0] <= -0.5893344581127167f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[11] <= 0.10610095411539078f) {
                            if (features[1] <= -0.36821600794792175f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[20] <= 0.11339455842971802f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[21] <= 1.5241737961769104f) {
                if (features[0] <= -0.3721648156642914f) {
                    if (features[14] <= -0.9432811439037323f) {
                        return 1;                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            } else {
                if (features[26] <= -0.3637044131755829f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 162
int predict_tree_162(const float* features) {
    // Max depth: 9
    if (features[20] <= 0.12241927906870842f) {
        if (features[11] <= -0.02843019738793373f) {
            if (features[25] <= -0.35182105004787445f) {
                if (features[18] <= -0.36821965873241425f) {
                    if (features[12] <= -0.20099423825740814f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[22] <= -0.6361834704875946f) {
                        return 1;                    } else {
                        if (features[4] <= -0.567532479763031f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[22] <= 0.08709480985999107f) {
                    if (features[27] <= -0.14335385710000992f) {
                        if (features[25] <= 0.21387702226638794f) {
                            return 0;                        } else {
                            return 2;                        }
                    } else {
                        if (features[24] <= -0.21537573635578156f) {
                            return 1;                        } else {
                            if (features[5] <= 0.21003025025129318f) {
                                if (features[10] <= 1.3132914304733276f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[1] <= -0.24524910585023463f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[0] <= -0.3758691996335983f) {
                return 0;            } else {
                if (features[8] <= -0.18464339524507523f) {
                    if (features[18] <= 0.6365732252597809f) {
                        if (features[17] <= -0.15695103583857417f) {
                            return 1;                        } else {
                            if (features[20] <= -0.041618987917900085f) {
                                return 0;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[2] <= -0.4455084204673767f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[21] <= -0.5713019669055939f) {
                        if (features[20] <= -0.6379466950893402f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        return 1;                    }
                }
            }
        }
    } else {
        if (features[17] <= -0.23100721091032028f) {
            if (features[22] <= 1.5412914156913757f) {
                if (features[6] <= -1.6597883701324463f) {
                    if (features[24] <= 0.035607642494142056f) {
                        if (features[0] <= -0.5893368124961853f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[8] <= -0.19525185972452164f) {
                        if (features[24] <= -0.0054930150508880615f) {
                            return 0;                        } else {
                            return 2;                        }
                    } else {
                        if (features[25] <= -0.09281105175614357f) {
                            return 0;                        } else {
                            if (features[4] <= 0.3298704922199249f) {
                                if (features[0] <= -0.44365622103214264f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            } else {
                                if (features[1] <= -0.3292018324136734f) {
                                    if (features[2] <= 0.08004144346341491f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 1;                                }
                            }
                        }
                    }
                }
            } else {
                if (features[10] <= -0.49386587738990784f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[24] <= -0.15829500555992126f) {
                return 2;            } else {
                return 2;            }
        }
    }
}

// Tree 163
int predict_tree_163(const float* features) {
    // Max depth: 9
    if (features[17] <= -0.4499865621328354f) {
        if (features[22] <= 0.4331102520227432f) {
            if (features[26] <= 0.5131142139434814f) {
                if (features[7] <= -0.516341358423233f) {
                    if (features[21] <= 0.25318311899900436f) {
                        if (features[17] <= -0.5847745835781097f) {
                            return 0;                        } else {
                            if (features[27] <= 3.0443618297576904f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[13] <= 0.126391475321725f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                } else {
                    return 0;                }
            } else {
                return 1;            }
        } else {
            if (features[25] <= 0.9393647909164429f) {
                return 1;            } else {
                return 2;            }
        }
    } else {
        if (features[18] <= -0.0075117365922778845f) {
            if (features[23] <= 1.5812974572181702f) {
                if (features[23] <= -0.10182588174939156f) {
                    if (features[19] <= -0.3904357999563217f) {
                        if (features[1] <= -0.35395754873752594f) {
                            return 0;                        } else {
                            if (features[26] <= -0.21615439653396606f) {
                                return 0;                            } else {
                                if (features[22] <= -0.5529210567474365f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            }
                        }
                    } else {
                        if (features[17] <= -0.37486056983470917f) {
                            return 0;                        } else {
                            if (features[1] <= -0.3417973220348358f) {
                                return 0;                            } else {
                                if (features[1] <= -0.2747403532266617f) {
                                    if (features[10] <= -0.3543672412633896f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 1;                                }
                            }
                        }
                    }
                } else {
                    if (features[10] <= -0.2069772630929947f) {
                        if (features[1] <= -0.3468702882528305f) {
                            return 1;                        } else {
                            if (features[9] <= 1.8479940295219421f) {
                                if (features[25] <= 0.07580612506717443f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            } else {
                                return 2;                            }
                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[27] <= -0.2791447341442108f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[4] <= 0.05423935875296593f) {
                if (features[6] <= -0.9981719255447388f) {
                    return 0;                } else {
                    if (features[19] <= 2.378441572189331f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[3] <= 1.9991479516029358f) {
                    return 2;                } else {
                    return 0;                }
            }
        }
    }
}

// Tree 164
int predict_tree_164(const float* features) {
    // Max depth: 10
    if (features[0] <= -0.4496677815914154f) {
        if (features[20] <= 0.44134001433849335f) {
            return 0;        } else {
            if (features[19] <= -0.5424142181873322f) {
                return 1;            } else {
                return 2;            }
        }
    } else {
        if (features[17] <= -0.23100721091032028f) {
            if (features[21] <= 1.538383960723877f) {
                if (features[10] <= -0.41455593705177307f) {
                    return 0;                } else {
                    if (features[22] <= -0.6411555707454681f) {
                        return 0;                    } else {
                        if (features[21] <= 0.09797167032957077f) {
                            if (features[18] <= -0.38736048340797424f) {
                                if (features[2] <= 0.26773782074451447f) {
                                    if (features[8] <= -0.18471094965934753f) {
                                        return 2;                                    } else {
                                        return 0;                                    }
                                } else {
                                    if (features[23] <= -0.3674847036600113f) {
                                        return 1;                                    } else {
                                        if (features[27] <= -0.16688136756420135f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            } else {
                                if (features[21] <= -0.569918304681778f) {
                                    if (features[18] <= -0.37769815325737f) {
                                        if (features[7] <= 0.5379345417022705f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[8] <= -0.08803584054112434f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    if (features[17] <= -0.3512759953737259f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        } else {
                            if (features[8] <= -0.1951109692454338f) {
                                if (features[2] <= -0.257812038064003f) {
                                    return 2;                                } else {
                                    return 1;                                }
                            } else {
                                if (features[12] <= 0.10926366969943047f) {
                                    if (features[10] <= -0.3557049334049225f) {
                                        return 1;                                    } else {
                                        if (features[26] <= 0.5495418757200241f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    if (features[24] <= -0.00515005923807621f) {
                                        return 1;                                    } else {
                                        return 2;                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                if (features[30] <= 0.17709434032440186f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[5] <= 0.07066236808896065f) {
                if (features[2] <= -0.9485346972942352f) {
                    return 0;                } else {
                    return 2;                }
            } else {
                if (features[7] <= 1.5305007100105286f) {
                    return 2;                } else {
                    if (features[23] <= 0.049097225069999695f) {
                        return 0;                    } else {
                        return 0;                    }
                }
            }
        }
    }
}

// Tree 165
int predict_tree_165(const float* features) {
    // Max depth: 10
    if (features[17] <= -0.4512094110250473f) {
        if (features[4] <= 0.46065424382686615f) {
            return 0;        } else {
            if (features[17] <= -0.524360865354538f) {
                return 1;            } else {
                return 2;            }
        }
    } else {
        if (features[10] <= -0.14820684492588043f) {
            if (features[3] <= 0.6615805923938751f) {
                if (features[20] <= 1.5380812883377075f) {
                    if (features[9] <= -0.7603023648262024f) {
                        if (features[13] <= -0.027407975401729345f) {
                            return 2;                        } else {
                            return 0;                        }
                    } else {
                        if (features[0] <= -0.4296617656946182f) {
                            return 0;                        } else {
                            if (features[20] <= -0.6398020684719086f) {
                                return 0;                            } else {
                                if (features[2] <= -0.14519420638680458f) {
                                    if (features[17] <= -0.32340574264526367f) {
                                        if (features[12] <= 0.07279912009835243f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 2;                                    }
                                } else {
                                    if (features[0] <= -0.3755028545856476f) {
                                        if (features[26] <= -0.3588806092739105f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        return 1;                                    }
                                }
                            }
                        }
                    }
                } else {
                    if (features[6] <= -1.8803272247314453f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[2] <= -0.4455084055662155f) {
                    if (features[0] <= -0.417358860373497f) {
                        if (features[14] <= -0.2845187485218048f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[20] <= 1.9460493326187134f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[20] <= 0.053659938275814056f) {
                if (features[2] <= -0.5956655144691467f) {
                    return 0;                } else {
                    return 2;                }
            } else {
                if (features[13] <= -6.44574236869812f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 166
int predict_tree_166(const float* features) {
    // Max depth: 7
    if (features[24] <= -0.1278594508767128f) {
        if (features[6] <= 1.2072162628173828f) {
            if (features[0] <= -0.37533751130104065f) {
                return 0;            } else {
                if (features[27] <= -0.014548033475875854f) {
                    return 1;                } else {
                    if (features[10] <= 1.0665513277053833f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[3] <= 0.3003339469432831f) {
                if (features[19] <= -0.6061384379863739f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[11] <= -0.030705951154232025f) {
                    if (features[18] <= -0.37286797165870667f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[24] <= -0.38952840864658356f) {
                        return 0;                    } else {
                        if (features[0] <= -0.3758691996335983f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                }
            }
        }
    } else {
        if (features[3] <= 0.2887963354587555f) {
            if (features[22] <= 0.18392940610647202f) {
                if (features[0] <= -0.11414325376972556f) {
                    if (features[0] <= -0.42224667966365814f) {
                        if (features[33] <= -0.7310653924942017f) {
                            if (features[18] <= -0.5788540244102478f) {
                                return 1;                            } else {
                                return 0;                            }
                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            } else {
                if (features[1] <= -0.4814462512731552f) {
                    if (features[4] <= 0.46065424382686615f) {
                        if (features[0] <= -0.5883446633815765f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[20] <= 0.2049022540450096f) {
                        if (features[17] <= -0.07312703505158424f) {
                            return 1;                        } else {
                            if (features[4] <= 0.04411475174129009f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[33] <= -0.7310653924942017f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[2] <= -0.16396384686231613f) {
                if (features[21] <= 0.7641043066978455f) {
                    if (features[21] <= 0.0711268000304699f) {
                        return 0;                    } else {
                        if (features[3] <= 0.49965615570545197f) {
                            if (features[13] <= -1.6659305691719055f) {
                                return 2;                            } else {
                                return 2;                            }
                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[20] <= 0.9998647272586823f) {
                        if (features[10] <= 0.0717039406299591f) {
                            return 1;                        } else {
                            return 2;                        }
                    } else {
                        if (features[16] <= 3.1667469069361687f) {
                            if (features[10] <= -0.35981230437755585f) {
                                return 1;                            } else {
                                return 2;                            }
                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[5] <= 0.5899390578269958f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 167
int predict_tree_167(const float* features) {
    // Max depth: 10
    if (features[17] <= -0.4496259391307831f) {
        if (features[22] <= 0.2708299309015274f) {
            if (features[5] <= 0.06664777360856533f) {
                return 0;            } else {
                return 1;            }
        } else {
            if (features[7] <= 0.1532728374004364f) {
                if (features[3] <= -0.21686939150094986f) {
                    if (features[4] <= 0.46065424382686615f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[28] <= 0.03392469882965088f) {
                        return 0;                    } else {
                        return 0;                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[1] <= -0.14874011278152466f) {
            if (features[22] <= 1.53965425491333f) {
                if (features[25] <= -0.11287467554211617f) {
                    if (features[10] <= -0.36409255862236023f) {
                        if (features[27] <= -0.31897757947444916f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[22] <= -0.40939728915691376f) {
                            if (features[10] <= -0.35469114780426025f) {
                                if (features[22] <= -0.6123032867908478f) {
                                    if (features[6] <= 1.4277551174163818f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                if (features[14] <= -0.33926835656166077f) {
                                    return 1;                                } else {
                                    if (features[11] <= -0.17938543856143951f) {
                                        return 1;                                    } else {
                                        if (features[25] <= -0.38772745430469513f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[26] <= -0.22560621052980423f) {
                        if (features[3] <= 0.7089245915412903f) {
                            if (features[26] <= -0.2646472454071045f) {
                                return 1;                            } else {
                                if (features[14] <= -0.3742825388908386f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[12] <= -0.2025409801863134f) {
                            return 2;                        } else {
                            if (features[19] <= -0.3688044995069504f) {
                                if (features[9] <= 1.0006270110607147f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            } else {
                                return 1;                            }
                        }
                    }
                }
            } else {
                if (features[12] <= -0.9144937694072723f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[8] <= -0.23607772588729858f) {
                if (features[12] <= 0.30624501407146454f) {
                    return 2;                } else {
                    if (features[21] <= 0.06355205923318863f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[3] <= 1.8758148550987244f) {
                    if (features[19] <= -0.3148382157087326f) {
                        return 1;                    } else {
                        return 2;                    }
                } else {
                    return 0;                }
            }
        }
    }
}

// Tree 168
int predict_tree_168(const float* features) {
    // Max depth: 7
    if (features[24] <= -0.1278594508767128f) {
        if (features[18] <= -0.4177286922931671f) {
            return 0;        } else {
            if (features[1] <= -0.35395754873752594f) {
                return 0;            } else {
                if (features[17] <= 0.3925013691186905f) {
                    if (features[0] <= -0.3759712725877762f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[2] <= -0.3244442343711853f) {
            if (features[26] <= -0.2420947104692459f) {
                if (features[21] <= 0.7569941580295563f) {
                    if (features[22] <= 0.13864493370056152f) {
                        if (features[8] <= -0.35224775969982147f) {
                            return 2;                        } else {
                            if (features[33] <= -0.7310653924942017f) {
                                return 0;                            } else {
                                return 0;                            }
                        }
                    } else {
                        if (features[24] <= -0.043106166645884514f) {
                            return 0;                        } else {
                            if (features[17] <= 0.3747604787349701f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[10] <= -0.33502984046936035f) {
                        return 1;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[0] <= 0.9269343912601471f) {
                    if (features[25] <= 0.08246930688619614f) {
                        return 2;                    } else {
                        if (features[8] <= -0.15998519212007523f) {
                            return 2;                        } else {
                            return 1;                        }
                    }
                } else {
                    return 0;                }
            }
        } else {
            if (features[19] <= -0.5131069719791412f) {
                if (features[27] <= 0.3802430033683777f) {
                    return 0;                } else {
                    if (features[24] <= -0.049819864332675934f) {
                        return 0;                    } else {
                        if (features[24] <= 0.26234759390354156f) {
                            if (features[13] <= -0.426942840218544f) {
                                return 0;                            } else {
                                return 1;                            }
                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[7] <= -0.30875109136104584f) {
                    if (features[18] <= 0.020585003308951855f) {
                        if (features[25] <= 0.0046057188883423805f) {
                            return 1;                        } else {
                            return 2;                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[1] <= -0.43980564177036285f) {
                        if (features[25] <= 0.24913374334573746f) {
                            return 0;                        } else {
                            return 2;                        }
                    } else {
                        if (features[17] <= -0.46026602387428284f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    }
}

// Tree 169
int predict_tree_169(const float* features) {
    // Max depth: 9
    if (features[4] <= 0.12167630344629288f) {
        if (features[12] <= -0.03292294777929783f) {
            if (features[1] <= -0.35550278425216675f) {
                return 0;            } else {
                if (features[23] <= -0.29748381674289703f) {
                    if (features[22] <= -0.6374467015266418f) {
                        return 0;                    } else {
                        if (features[4] <= -0.5621629059314728f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[33] <= -0.7310653924942017f) {
                        if (features[21] <= 0.06933916173875332f) {
                            if (features[11] <= -0.2712303400039673f) {
                                return 2;                            } else {
                                return 0;                            }
                        } else {
                            return 2;                        }
                    } else {
                        if (features[20] <= -0.09235912933945656f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                }
            }
        } else {
            if (features[10] <= -0.3601098656654358f) {
                return 0;            } else {
                if (features[5] <= -0.2987911105155945f) {
                    if (features[1] <= -0.33857262134552f) {
                        if (features[18] <= -0.38196417689323425f) {
                            return 1;                        } else {
                            return 0;                        }
                    } else {
                        if (features[30] <= 0.17709434032440186f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[3] <= 1.808180570602417f) {
                        if (features[6] <= 0.32506099343299866f) {
                            return 2;                        } else {
                            return 0;                        }
                    } else {
                        if (features[2] <= -1.6467651724815369f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                }
            }
        }
    } else {
        if (features[0] <= -0.214971661567688f) {
            if (features[19] <= -0.4298344999551773f) {
                if (features[25] <= 1.034637689590454f) {
                    if (features[20] <= 0.2931731641292572f) {
                        if (features[1] <= -0.5529232323169708f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[21] <= 0.26237380504608154f) {
                            return 1;                        } else {
                            if (features[4] <= 0.44084829092025757f) {
                                if (features[19] <= -0.5791662037372589f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        }
                    }
                } else {
                    return 2;                }
            } else {
                if (features[14] <= 1.3240423202514648f) {
                    if (features[6] <= -1.6597883701324463f) {
                        return 2;                    } else {
                        if (features[22] <= 1.5412914156913757f) {
                            if (features[17] <= -0.32056528329849243f) {
                                if (features[12] <= 0.0783008374273777f) {
                                    return 1;                                } else {
                                    if (features[7] <= -0.17806771025061607f) {
                                        return 1;                                    } else {
                                        return 2;                                    }
                                }
                            } else {
                                if (features[9] <= 0.9446179270744324f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            return 2;                        }
                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[7] <= 2.1282087564468384f) {
                return 2;            } else {
                if (features[25] <= 0.012743603670969605f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 170
int predict_tree_170(const float* features) {
    // Max depth: 8
    if (features[4] <= 0.12167630344629288f) {
        if (features[20] <= -0.5613222420215607f) {
            if (features[10] <= -0.3627457320690155f) {
                return 0;            } else {
                if (features[27] <= -0.23396532237529755f) {
                    if (features[1] <= -0.3389909565448761f) {
                        if (features[1] <= -0.3424180597066879f) {
                            if (features[9] <= -0.7384597659111023f) {
                                return 0;                            } else {
                                if (features[0] <= -0.37426820397377014f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        } else {
                            return 0;                        }
                    } else {
                        if (features[5] <= -0.3897176533937454f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[17] <= -0.37697330117225647f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            }
        } else {
            if (features[5] <= 0.3339848816394806f) {
                if (features[12] <= 0.17998208850622177f) {
                    if (features[12] <= -0.31428423523902893f) {
                        if (features[23] <= -0.3071245402097702f) {
                            return 1;                        } else {
                            if (features[20] <= -0.008252710336819291f) {
                                return 0;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[10] <= -0.03872199356555939f) {
                            return 0;                        } else {
                            if (features[22] <= 0.07299709506332874f) {
                                return 0;                            } else {
                                if (features[13] <= -0.05554725951515138f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                } else {
                    if (features[12] <= 0.1828644499182701f) {
                        return 1;                    } else {
                        if (features[27] <= 0.10903248284012079f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[2] <= -0.31036700308322906f) {
            if (features[22] <= 0.8055626749992371f) {
                if (features[3] <= 0.2537856549024582f) {
                    return 0;                } else {
                    if (features[30] <= 0.17709434032440186f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[10] <= -0.349072590470314f) {
                    if (features[19] <= -0.16870059072971344f) {
                        return 1;                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[21] <= 0.14720747619867325f) {
                if (features[3] <= -1.1279429197311401f) {
                    return 1;                } else {
                    if (features[10] <= -0.23178855888545513f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[1] <= -0.48798519372940063f) {
                    if (features[4] <= 0.46065424382686615f) {
                        if (features[30] <= 0.17709434032440186f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[19] <= -0.5455323755741119f) {
                        return 1;                    } else {
                        if (features[5] <= -0.13365476578474045f) {
                            if (features[13] <= -3.2894169092178345f) {
                                return 1;                            } else {
                                return 2;                            }
                        } else {
                            if (features[20] <= 0.18295049667358398f) {
                                if (features[5] <= -0.02574441721662879f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            } else {
                                if (features[18] <= -0.5053301453590393f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

// Tree 171
int predict_tree_171(const float* features) {
    // Max depth: 10
    if (features[23] <= -0.13091780990362167f) {
        if (features[26] <= -0.3166653513908386f) {
            if (features[26] <= -0.33475227653980255f) {
                if (features[26] <= -0.3516470789909363f) {
                    return 0;                } else {
                    if (features[7] <= 0.5707660019397736f) {
                        if (features[1] <= -0.3385603576898575f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        if (features[12] <= -0.005168277770280838f) {
                            if (features[8] <= -0.12571139261126518f) {
                                return 1;                            } else {
                                return 0;                            }
                        } else {
                            if (features[4] <= -0.6412759125232697f) {
                                return 0;                            } else {
                                return 0;                            }
                        }
                    }
                }
            } else {
                if (features[7] <= 0.3778693526983261f) {
                    return 0;                } else {
                    if (features[1] <= -0.3418329209089279f) {
                        if (features[28] <= 0.03392469882965088f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                }
            }
        } else {
            if (features[18] <= -0.41466024518013f) {
                if (features[17] <= -0.5940680205821991f) {
                    return 0;                } else {
                    return 0;                }
            } else {
                if (features[6] <= -0.4468248710036278f) {
                    return 2;                } else {
                    if (features[17] <= -0.38373395800590515f) {
                        return 0;                    } else {
                        if (features[11] <= -0.21372312307357788f) {
                            return 0;                        } else {
                            if (features[0] <= -0.37585754692554474f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    }
                }
            }
        }
    } else {
        if (features[17] <= -0.24509385973215103f) {
            if (features[5] <= 1.0807428658008575f) {
                if (features[21] <= 0.12445295974612236f) {
                    return 0;                } else {
                    if (features[1] <= -0.48993125557899475f) {
                        if (features[4] <= 0.46065424382686615f) {
                            if (features[2] <= -0.6425895988941193f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[12] <= 0.3445146232843399f) {
                            if (features[19] <= -0.03341257572174072f) {
                                if (features[10] <= -0.4567337930202484f) {
                                    return 1;                                } else {
                                    if (features[9] <= 1.111545979976654f) {
                                        if (features[0] <= -0.359319806098938f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                return 1;                            }
                        } else {
                            if (features[22] <= 0.3992454260587692f) {
                                return 1;                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                if (features[10] <= -0.492420956492424f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[21] <= 0.05533094331622124f) {
                if (features[7] <= 0.9329872466623783f) {
                    return 2;                } else {
                    return 0;                }
            } else {
                if (features[31] <= 0.16302114725112915f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 172
int predict_tree_172(const float* features) {
    // Max depth: 10
    if (features[17] <= -0.44954729080200195f) {
        if (features[21] <= 0.27017073333263397f) {
            if (features[26] <= 0.4329804480075836f) {
                if (features[11] <= -0.009219523053616285f) {
                    if (features[6] <= -1.8803272247314453f) {
                        if (features[20] <= 0.2152680903673172f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        return 0;                    }
                } else {
                    return 0;                }
            } else {
                return 1;            }
        } else {
            if (features[25] <= 0.34840767458081245f) {
                if (features[4] <= 0.48632340133190155f) {
                    if (features[29] <= -0.5031495066359639f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    return 1;                }
            } else {
                if (features[11] <= -0.021465600468218327f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[17] <= -0.22705212235450745f) {
            if (features[23] <= 1.0255287662148476f) {
                if (features[27] <= -0.3072219789028168f) {
                    return 0;                } else {
                    if (features[0] <= -0.43021006882190704f) {
                        return 0;                    } else {
                        if (features[4] <= -0.639714390039444f) {
                            return 0;                        } else {
                            if (features[10] <= -0.4145737290382385f) {
                                return 0;                            } else {
                                if (features[9] <= -0.7627458870410919f) {
                                    return 0;                                } else {
                                    if (features[11] <= 0.41737060248851776f) {
                                        if (features[18] <= -0.46300387382507324f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[0] <= -0.2833756357431412f) {
                                            return 2;                                        } else {
                                            return 2;                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                if (features[10] <= -0.43738751113414764f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[11] <= -0.7352625727653503f) {
                if (features[2] <= -0.708283320069313f) {
                    return 0;                } else {
                    if (features[27] <= -0.2975814640522003f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[6] <= -0.9981719255447388f) {
                    if (features[9] <= -0.034901480190455914f) {
                        if (features[4] <= 1.1553131993860006f) {
                            return 0;                        } else {
                            if (features[14] <= -3.7550151348114014f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[19] <= 1.0010339319705963f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 173
int predict_tree_173(const float* features) {
    // Max depth: 9
    if (features[21] <= 0.11981721967458725f) {
        if (features[17] <= -0.379781037569046f) {
            return 0;        } else {
            if (features[7] <= 1.23102205991745f) {
                if (features[23] <= -0.29748381674289703f) {
                    if (features[0] <= -0.3758653551340103f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[22] <= 0.0015686905826441944f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[13] <= -0.23705638200044632f) {
                    return 0;                } else {
                    return 0;                }
            }
        }
    } else {
        if (features[0] <= -0.27408580482006073f) {
            if (features[5] <= 1.0675677359104156f) {
                if (features[19] <= -0.4742763936519623f) {
                    if (features[20] <= 0.276928648352623f) {
                        if (features[24] <= -0.14108745008707047f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[19] <= -0.5770379900932312f) {
                            if (features[26] <= -0.3584635555744171f) {
                                return 0;                            } else {
                                if (features[27] <= -0.05951352044939995f) {
                                    return 0;                                } else {
                                    if (features[22] <= 0.43679890036582947f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[18] <= -0.16881216317415237f) {
                        if (features[11] <= 0.11159082874655724f) {
                            return 1;                        } else {
                            if (features[23] <= -0.004255577921867371f) {
                                return 1;                            } else {
                                return 2;                            }
                        }
                    } else {
                        return 1;                    }
                }
            } else {
                if (features[24] <= 0.9223911464214325f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[12] <= -10.438920497894287f) {
                return 2;            } else {
                return 2;            }
        }
    }
}

// Tree 174
int predict_tree_174(const float* features) {
    // Max depth: 10
    if (features[17] <= -0.23100721091032028f) {
        if (features[19] <= -0.4298344999551773f) {
            if (features[23] <= -0.046037863940000534f) {
                if (features[0] <= -0.37561240792274475f) {
                    return 0;                } else {
                    if (features[1] <= -0.34938380122184753f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[24] <= 0.8370117098093033f) {
                    if (features[33] <= -0.7310653924942017f) {
                        if (features[12] <= -0.0026427072007209063f) {
                            return 0;                        } else {
                            if (features[2] <= 0.18327444791793823f) {
                                if (features[8] <= 0.09475210309028625f) {
                                    if (features[7] <= -0.6137725114822388f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 0;                                }
                            } else {
                                return 0;                            }
                        }
                    } else {
                        if (features[13] <= -0.1341654136776924f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[22] <= 1.5393915176391602f) {
                if (features[18] <= -0.4300442039966583f) {
                    return 0;                } else {
                    if (features[17] <= -0.43032942712306976f) {
                        return 0;                    } else {
                        if (features[0] <= -0.43021006882190704f) {
                            return 0;                        } else {
                            if (features[7] <= 0.4344060719013214f) {
                                if (features[21] <= -0.6406461298465729f) {
                                    return 0;                                } else {
                                    if (features[8] <= -0.20013562589883804f) {
                                        return 1;                                    } else {
                                        if (features[12] <= 0.07887047529220581f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            } else {
                                if (features[0] <= -0.3759319484233856f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            }
                        }
                    }
                }
            } else {
                if (features[22] <= 1.5992284417152405f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[3] <= 1.88377183675766f) {
            if (features[2] <= -0.4577086716890335f) {
                return 2;            } else {
                return 2;            }
        } else {
            return 0;        }
    }
}

// Tree 175
int predict_tree_175(const float* features) {
    // Max depth: 10
    if (features[1] <= -0.4235561043024063f) {
        if (features[24] <= 0.041595589369535446f) {
            if (features[24] <= -0.03155344631522894f) {
                return 0;            } else {
                if (features[27] <= 0.4433354586362839f) {
                    return 0;                } else {
                    return 1;                }
            }
        } else {
            if (features[4] <= 1.2261149287223816f) {
                return 1;            } else {
                return 2;            }
        }
    } else {
        if (features[18] <= -0.2300560474395752f) {
            if (features[22] <= 1.53965425491333f) {
                if (features[17] <= -0.43034209311008453f) {
                    if (features[19] <= -0.5750927031040192f) {
                        return 1;                    } else {
                        if (features[6] <= -0.11601662915199995f) {
                            return 0;                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[4] <= -0.6392812132835388f) {
                        return 0;                    } else {
                        if (features[10] <= -0.41471871733665466f) {
                            return 0;                        } else {
                            if (features[1] <= -0.06982173025608063f) {
                                if (features[22] <= 0.08806497044861317f) {
                                    if (features[26] <= -0.31692826747894287f) {
                                        if (features[0] <= -0.37542736530303955f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[0] <= -0.3755028545856476f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    if (features[10] <= -0.13474924862384796f) {
                                        if (features[9] <= 1.111545979976654f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 2;                                    }
                                }
                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                if (features[5] <= 3.371909022331238f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[19] <= 1.174082338809967f) {
                if (features[3] <= 1.9394706785678864f) {
                    return 2;                } else {
                    return 0;                }
            } else {
                if (features[7] <= 1.9035120010375977f) {
                    if (features[21] <= 0.029516234062612057f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    if (features[24] <= 0.03683311678469181f) {
                        return 2;                    } else {
                        return 0;                    }
                }
            }
        }
    }
}

// Tree 176
int predict_tree_176(const float* features) {
    // Max depth: 10
    if (features[0] <= -0.44988109171390533f) {
        if (features[4] <= 0.46065424382686615f) {
            return 0;        } else {
            if (features[4] <= 0.789006382226944f) {
                return 1;            } else {
                return 2;            }
        }
    } else {
        if (features[17] <= -0.23100721091032028f) {
            if (features[20] <= 1.535479724407196f) {
                if (features[18] <= -0.43015874922275543f) {
                    if (features[11] <= 0.2148733139038086f) {
                        if (features[6] <= -0.11601662915199995f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[7] <= -0.03987821890041232f) {
                            return 0;                        } else {
                            if (features[8] <= -0.15781807154417038f) {
                                return 1;                            } else {
                                return 0;                            }
                        }
                    }
                } else {
                    if (features[10] <= -0.41471871733665466f) {
                        if (features[3] <= 0.41968855261802673f) {
                            return 0;                        } else {
                            return 2;                        }
                    } else {
                        if (features[33] <= -0.7310653924942017f) {
                            if (features[25] <= -0.21441298816353083f) {
                                return 0;                            } else {
                                if (features[0] <= -0.3681335598230362f) {
                                    if (features[5] <= 0.01515510119497776f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[27] <= -0.31103286147117615f) {
                                return 0;                            } else {
                                if (features[0] <= -0.37585754692554474f) {
                                    if (features[4] <= 0.5277285240590572f) {
                                        if (features[15] <= 0.7462623417377472f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        if (features[9] <= 2.203365921974182f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    return 1;                                }
                            }
                        }
                    }
                }
            } else {
                if (features[3] <= 0.2008717730641365f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[22] <= 0.05568571202456951f) {
                if (features[2] <= -0.6519744247198105f) {
                    return 0;                } else {
                    return 2;                }
            } else {
                if (features[4] <= 0.0009869421774055809f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 177
int predict_tree_177(const float* features) {
    // Max depth: 10
    if (features[19] <= 0.007266389031428844f) {
        if (features[18] <= -0.4295092672109604f) {
            if (features[27] <= -0.05730712600052357f) {
                if (features[12] <= 0.22428177297115326f) {
                    if (features[25] <= 1.429160824045539f) {
                        return 0;                    } else {
                        if (features[21] <= 1.7077046632766724f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[26] <= 0.13206683658063412f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[17] <= -0.516372412443161f) {
                    if (features[5] <= -0.004704053630121052f) {
                        if (features[12] <= -0.041283171623945236f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[4] <= 0.44439442455768585f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[21] <= 0.27140289545059204f) {
                        if (features[4] <= -0.3464634269475937f) {
                            return 0;                        } else {
                            return 1;                        }
                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[23] <= 0.259522020816803f) {
                if (features[18] <= -0.19727405905723572f) {
                    if (features[17] <= -0.2325241044163704f) {
                        if (features[6] <= 0.5455998182296753f) {
                            if (features[21] <= -0.5855626463890076f) {
                                return 0;                            } else {
                                if (features[22] <= 1.2450575828552246f) {
                                    if (features[14] <= 0.5008151829242706f) {
                                        if (features[12] <= 0.1761169210076332f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[15] <= 0.7462623417377472f) {
                                            return 1;                                        } else {
                                            return 2;                                        }
                                    }
                                } else {
                                    if (features[8] <= -0.1814926341176033f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        } else {
                            if (features[1] <= -0.3429037630558014f) {
                                if (features[17] <= -0.44218920171260834f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                if (features[17] <= -0.3835477977991104f) {
                                    return 0;                                } else {
                                    if (features[11] <= -0.12209660187363625f) {
                                        return 1;                                    } else {
                                        if (features[26] <= -0.31301671266555786f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[31] <= 0.16302114725112915f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[28] <= -0.4683038666844368f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[3] <= 1.8797933459281921f) {
            if (features[26] <= 8.874895095825195f) {
                if (features[0] <= -0.32749904692173004f) {
                    return 1;                } else {
                    if (features[7] <= -1.5758530497550964f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                return 1;            }
        } else {
            return 0;        }
    }
}

// Tree 178
int predict_tree_178(const float* features) {
    // Max depth: 10
    if (features[0] <= -0.45196448266506195f) {
        if (features[20] <= 0.4714694768190384f) {
            return 0;        } else {
            if (features[21] <= 1.5235274732112885f) {
                return 1;            } else {
                return 2;            }
        }
    } else {
        if (features[1] <= -0.15344125032424927f) {
            if (features[7] <= 0.6561440229415894f) {
                if (features[18] <= -0.429835706949234f) {
                    if (features[23] <= 0.10674125701189041f) {
                        if (features[5] <= -0.4149068146944046f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[7] <= -1.444762647151947f) {
                        return 0;                    } else {
                        if (features[2] <= -0.05134601891040802f) {
                            if (features[12] <= 0.08023474738001823f) {
                                if (features[20] <= -0.6356476545333862f) {
                                    return 0;                                } else {
                                    if (features[6] <= 0.6558692352846265f) {
                                        if (features[0] <= -0.3686157912015915f) {
                                            return 1;                                        } else {
                                            return 2;                                        }
                                    } else {
                                        if (features[22] <= -0.634516030550003f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            } else {
                                if (features[27] <= -0.16493838280439377f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            if (features[27] <= -0.3113083839416504f) {
                                return 0;                            } else {
                                if (features[10] <= -0.3540896624326706f) {
                                    return 0;                                } else {
                                    if (features[8] <= 0.27278121560811996f) {
                                        if (features[1] <= -0.32576440274715424f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 1;                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                if (features[23] <= 2.9498584270477295f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[20] <= 0.053659938275814056f) {
                if (features[26] <= 1.7288216948509216f) {
                    return 0;                } else {
                    if (features[21] <= -0.004388297558762133f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[0] <= -0.17664708942174911f) {
                    return 1;                } else {
                    if (features[0] <= -0.1477125883102417f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 179
int predict_tree_179(const float* features) {
    // Max depth: 10
    if (features[23] <= -0.13091780990362167f) {
        if (features[0] <= -0.37561240792274475f) {
            return 0;        } else {
            if (features[26] <= 0.35370853543281555f) {
                return 1;            } else {
                return 2;            }
        }
    } else {
        if (features[17] <= -0.22465001046657562f) {
            if (features[23] <= 1.0670694708824158f) {
                if (features[24] <= -0.052663858979940414f) {
                    if (features[10] <= -0.3839317262172699f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[18] <= -0.572355180978775f) {
                        if (features[13] <= 0.26128819584846497f) {
                            if (features[13] <= -0.24221166968345642f) {
                                return 1;                            } else {
                                if (features[31] <= 0.16302114725112915f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[20] <= 0.6230344772338867f) {
                            if (features[4] <= 0.5456505715847015f) {
                                if (features[21] <= 0.14697518199682236f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            } else {
                                return 2;                            }
                        } else {
                            if (features[25] <= 0.007195530459284782f) {
                                return 1;                            } else {
                                if (features[22] <= 1.1835834980010986f) {
                                    if (features[13] <= 0.6023964583873749f) {
                                        return 1;                                    } else {
                                        if (features[8] <= -0.12913857772946358f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    if (features[21] <= 1.161808431148529f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                if (features[16] <= 3.1667469069361687f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[22] <= 0.05463469959795475f) {
                if (features[9] <= -0.01785858627408743f) {
                    return 0;                } else {
                    return 2;                }
            } else {
                if (features[0] <= -0.2677386701107025f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 180
int predict_tree_180(const float* features) {
    // Max depth: 10
    if (features[17] <= -0.45116911828517914f) {
        if (features[33] <= -0.7310653924942017f) {
            if (features[21] <= 1.4984601438045502f) {
                if (features[20] <= 0.2787638455629349f) {
                    if (features[7] <= -3.8034608364105225f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[22] <= 0.3349214643239975f) {
                        return 1;                    } else {
                        if (features[14] <= 0.13360182227916084f) {
                            return 0;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                return 2;            }
        } else {
            return 0;        }
    } else {
        if (features[20] <= 1.0700861811637878f) {
            if (features[18] <= -0.0075117365922778845f) {
                if (features[4] <= -0.6390192806720734f) {
                    return 0;                } else {
                    if (features[10] <= -0.3627457320690155f) {
                        if (features[27] <= -0.31897757947444916f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[17] <= -0.23004907369613647f) {
                            if (features[10] <= -0.3602023273706436f) {
                                if (features[1] <= -0.3468419015407562f) {
                                    return 1;                                } else {
                                    if (features[1] <= -0.34640641510486603f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                }
                            } else {
                                if (features[23] <= 0.004395144060254097f) {
                                    if (features[17] <= -0.3735552728176117f) {
                                        if (features[30] <= 0.17709434032440186f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[20] <= -0.6307773590087891f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    return 1;                                }
                            }
                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[23] <= 0.07348424941301346f) {
                    if (features[6] <= -0.9981719255447388f) {
                        if (features[21] <= 0.02595105767250061f) {
                            return 0;                        } else {
                            return 2;                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[2] <= -0.9551040530204773f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[2] <= -0.2587505131959915f) {
                if (features[10] <= -0.35981230437755585f) {
                    return 1;                } else {
                    return 2;                }
            } else {
                if (features[4] <= 1.0035951733589172f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 181
int predict_tree_181(const float* features) {
    // Max depth: 9
    if (features[17] <= -0.45113205909729004f) {
        if (features[13] <= -0.21686483174562454f) {
            if (features[17] <= -0.5142451524734497f) {
                if (features[4] <= 0.415138840675354f) {
                    if (features[14] <= -1.6223284006118774f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    return 1;                }
            } else {
                if (features[18] <= -0.5051217079162598f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[23] <= 0.03949646418914199f) {
                if (features[20] <= 0.410686194896698f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                if (features[10] <= -0.530687153339386f) {
                    return 1;                } else {
                    if (features[10] <= -0.441230908036232f) {
                        return 2;                    } else {
                        return 1;                    }
                }
            }
        }
    } else {
        if (features[1] <= -0.15344125032424927f) {
            if (features[4] <= 1.5368548035621643f) {
                if (features[1] <= -0.40189267694950104f) {
                    if (features[21] <= 0.05095779336988926f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    if (features[22] <= -0.6407210230827332f) {
                        return 0;                    } else {
                        if (features[24] <= -0.11450402438640594f) {
                            if (features[0] <= -0.3756202161312103f) {
                                if (features[1] <= -0.40130217373371124f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        } else {
                            if (features[11] <= 0.4791518300771713f) {
                                if (features[1] <= -0.3068893104791641f) {
                                    if (features[11] <= 0.08123112097382545f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                return 1;                            }
                        }
                    }
                }
            } else {
                if (features[24] <= 1.0352266728878021f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[4] <= 0.05254688858985901f) {
                if (features[3] <= 1.8042020797729492f) {
                    return 2;                } else {
                    return 0;                }
            } else {
                if (features[7] <= 2.1282087564468384f) {
                    return 2;                } else {
                    if (features[20] <= 0.21743603982031345f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 182
int predict_tree_182(const float* features) {
    // Max depth: 7
    if (features[22] <= 0.1199793629348278f) {
        if (features[17] <= -0.39827775955200195f) {
            return 0;        } else {
            if (features[6] <= -0.33655544370412827f) {
                if (features[0] <= 0.9643030166625977f) {
                    if (features[20] <= -0.05829708557575941f) {
                        return 2;                    } else {
                        return 2;                    }
                } else {
                    if (features[5] <= 0.34472353756427765f) {
                        if (features[12] <= 2.7325830459594727f) {
                            return 0;                        } else {
                            return 2;                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[10] <= -0.3651351183652878f) {
                    return 0;                } else {
                    if (features[1] <= -0.3389909565448761f) {
                        if (features[26] <= -0.22918149828910828f) {
                            if (features[31] <= 0.16302114725112915f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[0] <= -0.3758691996335983f) {
                            return 0;                        } else {
                            if (features[11] <= -0.10904501751065254f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    }
                }
            }
        }
    } else {
        if (features[0] <= -0.20697776973247528f) {
            if (features[0] <= -0.43098363280296326f) {
                if (features[25] <= 0.34840767458081245f) {
                    if (features[5] <= -0.030809917487204075f) {
                        if (features[27] <= -0.31475067138671875f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[9] <= 0.9852831959724426f) {
                            if (features[6] <= -0.116016685962677f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    }
                } else {
                    return 2;                }
            } else {
                if (features[3] <= 0.6615805923938751f) {
                    if (features[4] <= 1.53406423330307f) {
                        if (features[0] <= -0.3407296985387802f) {
                            if (features[12] <= 0.0783008374273777f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            if (features[21] <= 0.47575923800468445f) {
                                return 1;                            } else {
                                return 2;                            }
                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[5] <= 1.4453314021229744f) {
                        return 1;                    } else {
                        if (features[22] <= 1.9566130638122559f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[27] <= -0.316541463136673f) {
                return 2;            } else {
                return 2;            }
        }
    }
}

// Tree 183
int predict_tree_183(const float* features) {
    // Max depth: 10
    if (features[0] <= -0.4505611062049866f) {
        if (features[23] <= -0.04481179267168045f) {
            return 0;        } else {
            if (features[21] <= 1.5235274732112885f) {
                if (features[14] <= 0.024377312831347808f) {
                    if (features[24] <= 0.016343690920621157f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[20] <= 0.3588671237230301f) {
                        return 0;                    } else {
                        if (features[5] <= 0.021054591634310782f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[2] <= -0.0034834432881325483f) {
            if (features[3] <= 0.9607628285884857f) {
                if (features[18] <= -0.19727405905723572f) {
                    if (features[9] <= -0.7603023648262024f) {
                        return 0;                    } else {
                        if (features[0] <= -0.4305008202791214f) {
                            return 0;                        } else {
                            if (features[0] <= -0.214971661567688f) {
                                if (features[9] <= 1.1694889068603516f) {
                                    if (features[20] <= 0.4343017488718033f) {
                                        if (features[0] <= -0.3758691996335983f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 2;                                    }
                                } else {
                                    if (features[5] <= 0.19622398167848587f) {
                                        if (features[15] <= 0.7462623417377472f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    if (features[8] <= -0.3855358809232712f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                return 0;            }
        } else {
            if (features[25] <= -0.20719843357801437f) {
                if (features[21] <= -0.5756044089794159f) {
                    return 0;                } else {
                    if (features[0] <= -0.37533751130104065f) {
                        if (features[24] <= -0.37228162586688995f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                }
            } else {
                if (features[21] <= 0.16735627502202988f) {
                    if (features[17] <= -0.12364368978887796f) {
                        if (features[1] <= -0.36032718420028687f) {
                            return 0;                        } else {
                            if (features[31] <= 0.16302114725112915f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[13] <= -3.575750231742859f) {
                        if (features[1] <= 1.1804737448692322f) {
                            return 1;                        } else {
                            return 2;                        }
                    } else {
                        if (features[1] <= -0.4295928627252579f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    }
}

// Tree 184
int predict_tree_184(const float* features) {
    // Max depth: 10
    if (features[17] <= -0.45113205909729004f) {
        if (features[5] <= -0.004704053630121052f) {
            return 0;        } else {
            if (features[22] <= 1.498361587524414f) {
                if (features[20] <= 0.43963590264320374f) {
                    return 0;                } else {
                    return 1;                }
            } else {
                return 2;            }
        }
    } else {
        if (features[15] <= 0.7462623417377472f) {
            if (features[23] <= 0.26517751067876816f) {
                if (features[2] <= -0.0034834432881325483f) {
                    if (features[0] <= 0.04078778624534607f) {
                        if (features[25] <= -0.39004001021385193f) {
                            return 0;                        } else {
                            if (features[5] <= -0.0805713664740324f) {
                                if (features[22] <= -0.5912628173828125f) {
                                    if (features[26] <= -0.3566969931125641f) {
                                        return 0;                                    } else {
                                        if (features[0] <= -0.37645822763442993f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    if (features[3] <= -0.08955779299139977f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                }
                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[9] <= 0.17985650897026062f) {
                            return 0;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[17] <= -0.2004275619983673f) {
                        if (features[9] <= -0.5914397835731506f) {
                            return 0;                        } else {
                            if (features[18] <= -0.3912973254919052f) {
                                if (features[20] <= -0.5601223111152649f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[3] <= -1.9395542740821838f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[6] <= -1.8803272247314453f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[19] <= 0.00714016129495576f) {
                if (features[13] <= -0.14189834892749786f) {
                    if (features[7] <= -0.23708489537239075f) {
                        return 1;                    } else {
                        if (features[24] <= 0.04692091420292854f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[1] <= -0.3769363760948181f) {
                        return 0;                    } else {
                        if (features[18] <= -0.18709474802017212f) {
                            if (features[21] <= -0.5762911736965179f) {
                                return 0;                            } else {
                                if (features[2] <= -0.38919949531555176f) {
                                    return 1;                                } else {
                                    if (features[21] <= -0.43020981550216675f) {
                                        if (features[20] <= -0.5040480047464371f) {
                                            return 1;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        if (features[26] <= -0.04783183895051479f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[4] <= 0.03227752260863781f) {
                    if (features[10] <= 0.8915399312973022f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    if (features[18] <= 0.46114927530288696f) {
                        if (features[26] <= 3.719063639640808f) {
                            if (features[2] <= -0.39295342564582825f) {
                                return 2;                            } else {
                                return 2;                            }
                        } else {
                            return 1;                        }
                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 185
int predict_tree_185(const float* features) {
    // Max depth: 10
    if (features[21] <= 0.11981721967458725f) {
        if (features[26] <= -0.31181974709033966f) {
            if (features[6] <= 1.2072162628173828f) {
                if (features[10] <= -0.030807986855506897f) {
                    return 0;                } else {
                    if (features[4] <= 0.0660866629332304f) {
                        if (features[5] <= 0.09597526490688324f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[1] <= -0.33700644969940186f) {
                    if (features[22] <= -0.7380811274051666f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    return 1;                }
            }
        } else {
            if (features[25] <= -0.3492935299873352f) {
                if (features[0] <= -0.37585754692554474f) {
                    return 0;                } else {
                    if (features[15] <= 0.7462623417377472f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[22] <= 0.0742502249777317f) {
                    if (features[4] <= 0.07578815147280693f) {
                        if (features[33] <= -0.7310653924942017f) {
                            if (features[7] <= 0.19780846312642097f) {
                                if (features[25] <= -0.08123681787401438f) {
                                    return 0;                                } else {
                                    return 2;                                }
                            } else {
                                return 0;                            }
                        } else {
                            if (features[8] <= 0.568744957447052f) {
                                if (features[26] <= 1.1816735863685608f) {
                                    return 0;                                } else {
                                    return 2;                                }
                            } else {
                                if (features[30] <= 0.17709434032440186f) {
                                    return 0;                                } else {
                                    return 1;                                }
                            }
                        }
                    } else {
                        if (features[7] <= 0.016645457595586777f) {
                            return 2;                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[25] <= -0.004400089383125305f) {
                        return 0;                    } else {
                        if (features[21] <= 0.06678394600749016f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    } else {
        if (features[22] <= 1.064687728881836f) {
            if (features[21] <= 0.16735627502202988f) {
                if (features[18] <= -0.11723041161894798f) {
                    if (features[19] <= -0.43967123329639435f) {
                        if (features[21] <= 0.12176645174622536f) {
                            return 1;                        } else {
                            if (features[5] <= -0.1386665403842926f) {
                                return 0;                            } else {
                                return 0;                            }
                        }
                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            } else {
                if (features[17] <= -0.2092769369482994f) {
                    if (features[20] <= 0.1823253184556961f) {
                        return 0;                    } else {
                        if (features[23] <= -0.05316363088786602f) {
                            return 0;                        } else {
                            if (features[1] <= -0.550446093082428f) {
                                return 0;                            } else {
                                if (features[27] <= 0.025372730568051338f) {
                                    if (features[2] <= -0.332890585064888f) {
                                        return 1;                                    } else {
                                        return 0;                                    }
                                } else {
                                    if (features[20] <= 0.5761663913726807f) {
                                        if (features[24] <= -0.06204034946858883f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 1;                                    }
                                }
                            }
                        }
                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[21] <= 1.5196693539619446f) {
                if (features[18] <= -0.3142048269510269f) {
                    if (features[10] <= -0.2809253856539726f) {
                        return 1;                    } else {
                        return 2;                    }
                } else {
                    return 2;                }
            } else {
                return 2;            }
        }
    }
}

// Tree 186
int predict_tree_186(const float* features) {
    // Max depth: 10
    if (features[27] <= -0.21701335161924362f) {
        if (features[19] <= -0.4298432916402817f) {
            if (features[1] <= -0.3282569944858551f) {
                if (features[20] <= 1.1550093740224838f) {
                    return 0;                } else {
                    if (features[3] <= 0.49925829470157623f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                return 1;            }
        } else {
            if (features[15] <= 0.7462623417377472f) {
                if (features[17] <= -0.2515076547861099f) {
                    if (features[4] <= 1.5751368403434753f) {
                        if (features[27] <= -0.3075890988111496f) {
                            return 0;                        } else {
                            if (features[10] <= -0.4132811427116394f) {
                                return 0;                            } else {
                                if (features[20] <= -0.6376946270465851f) {
                                    return 0;                                } else {
                                    if (features[17] <= -0.37529483437538147f) {
                                        if (features[3] <= 0.3078930675983429f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[1] <= -0.3375915288925171f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        return 2;                    }
                } else {
                    if (features[22] <= 0.08541722968220711f) {
                        return 0;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[20] <= 0.05346835218369961f) {
                    if (features[24] <= -0.35822999477386475f) {
                        if (features[18] <= -0.34238389134407043f) {
                            if (features[21] <= -0.5822398662567139f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    } else {
                        return 0;                    }
                } else {
                    if (features[19] <= -0.07417653128504753f) {
                        return 1;                    } else {
                        if (features[27] <= -0.316541463136673f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    } else {
        if (features[17] <= -0.22305692732334137f) {
            if (features[24] <= 0.41741394996643066f) {
                if (features[19] <= -0.43103255331516266f) {
                    if (features[4] <= 0.29601098597049713f) {
                        if (features[26] <= 0.07481144554913044f) {
                            return 0;                        } else {
                            if (features[1] <= -0.19327174872159958f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[20] <= 0.44134001433849335f) {
                            if (features[21] <= 0.26237380504608154f) {
                                return 1;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[20] <= 0.6230344772338867f) {
                        if (features[24] <= 0.0273135625757277f) {
                            return 1;                        } else {
                            return 2;                        }
                    } else {
                        if (features[11] <= -0.34819934517145157f) {
                            return 2;                        } else {
                            if (features[7] <= -0.04740867577493191f) {
                                if (features[26] <= -0.08413562178611755f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            } else {
                                return 1;                            }
                        }
                    }
                }
            } else {
                if (features[13] <= -10.051007747650146f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[3] <= 1.8877503275871277f) {
                if (features[34] <= -2.0389932096004486f) {
                    return 2;                } else {
                    return 2;                }
            } else {
                return 0;            }
        }
    }
}

// Tree 187
int predict_tree_187(const float* features) {
    // Max depth: 10
    if (features[18] <= -0.4494751989841461f) {
        if (features[23] <= -0.04481179267168045f) {
            if (features[26] <= 0.4462607130408287f) {
                return 0;            } else {
                return 2;            }
        } else {
            if (features[24] <= 0.8370117098093033f) {
                if (features[9] <= 0.8893032371997833f) {
                    if (features[22] <= 0.11227867752313614f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[20] <= 0.4714795649051666f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[11] <= -0.01886919606477022f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[6] <= -0.11601662915199995f) {
            if (features[1] <= -0.07243609055876732f) {
                if (features[23] <= 0.253122515976429f) {
                    if (features[24] <= -0.11853359267115593f) {
                        return 0;                    } else {
                        if (features[1] <= -0.1487656682729721f) {
                            if (features[33] <= -0.7310653924942017f) {
                                if (features[10] <= -0.34496551752090454f) {
                                    return 1;                                } else {
                                    return 2;                                }
                            } else {
                                return 1;                            }
                        } else {
                            if (features[24] <= 0.004609771189279854f) {
                                return 1;                            } else {
                                return 2;                            }
                        }
                    }
                } else {
                    return 2;                }
            } else {
                if (features[22] <= 0.05428099445998669f) {
                    if (features[2] <= -0.6519744247198105f) {
                        return 0;                    } else {
                        if (features[7] <= -0.2622087672352791f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[3] <= -2.1822421550750732f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[10] <= -0.13474046159535646f) {
                if (features[17] <= -0.4213597923517227f) {
                    return 0;                } else {
                    if (features[0] <= -0.4173680990934372f) {
                        return 0;                    } else {
                        if (features[3] <= -0.40783676505088806f) {
                            return 0;                        } else {
                            if (features[1] <= -0.3797040432691574f) {
                                return 0;                            } else {
                                if (features[22] <= -0.6213581562042236f) {
                                    if (features[18] <= -0.3790943920612335f) {
                                        return 0;                                    } else {
                                        if (features[14] <= 0.3145386725664139f) {
                                            return 1;                                        } else {
                                            return 0;                                        }
                                    }
                                } else {
                                    if (features[2] <= 0.08942626044154167f) {
                                        if (features[9] <= -0.7410311996936798f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        if (features[17] <= -0.3568754494190216f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                return 2;            }
        }
    }
}

// Tree 188
int predict_tree_188(const float* features) {
    // Max depth: 10
    if (features[21] <= 0.11981721967458725f) {
        if (features[0] <= -0.37597908079624176f) {
            return 0;        } else {
            if (features[6] <= -0.33655544370412827f) {
                if (features[6] <= -0.9981719255447388f) {
                    if (features[7] <= 0.875248059630394f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    if (features[28] <= 0.03392469882965088f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                return 1;            }
        }
    } else {
        if (features[0] <= -0.23563377559185028f) {
            if (features[9] <= 0.34558792412281036f) {
                if (features[19] <= -0.5121001601219177f) {
                    return 1;                } else {
                    return 2;                }
            } else {
                if (features[23] <= 0.259522020816803f) {
                    if (features[18] <= -0.47449998557567596f) {
                        if (features[23] <= -0.04481179267168045f) {
                            if (features[28] <= -0.4683038666844368f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            if (features[2] <= -0.21088793873786926f) {
                                return 0;                            } else {
                                if (features[7] <= -0.5071292072534561f) {
                                    if (features[24] <= 0.026980919763445854f) {
                                        if (features[31] <= 0.16302114725112915f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[30] <= 0.17709434032440186f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                }
                            }
                        }
                    } else {
                        if (features[26] <= 0.16826480627059937f) {
                            if (features[12] <= 0.1761169210076332f) {
                                return 1;                            } else {
                                return 1;                            }
                        } else {
                            return 1;                        }
                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[23] <= -0.15862611681222916f) {
                return 2;            } else {
                return 2;            }
        }
    }
}

// Tree 189
int predict_tree_189(const float* features) {
    // Max depth: 10
    if (features[19] <= -0.10302284732460976f) {
        if (features[20] <= 0.12302429229021072f) {
            if (features[0] <= -0.3758653551340103f) {
                return 0;            } else {
                if (features[26] <= 0.1657436080276966f) {
                    return 1;                } else {
                    return 1;                }
            }
        } else {
            if (features[6] <= -1.6597883701324463f) {
                if (features[19] <= -0.5743699073791504f) {
                    if (features[27] <= 0.7166362702846527f) {
                        if (features[4] <= 0.12178711965680122f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            } else {
                if (features[20] <= 1.5383434891700745f) {
                    if (features[24] <= -0.09318647906184196f) {
                        return 0;                    } else {
                        if (features[17] <= -0.23004907369613647f) {
                            if (features[17] <= -0.5700828731060028f) {
                                return 0;                            } else {
                                if (features[25] <= -0.10029497742652893f) {
                                    return 0;                                } else {
                                    if (features[0] <= -0.2660100758075714f) {
                                        if (features[26] <= -0.2378256469964981f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 1;                                    }
                                }
                            }
                        } else {
                            return 2;                        }
                    }
                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[2] <= -0.968242809176445f) {
            return 0;        } else {
            if (features[1] <= -0.35608771443367004f) {
                return 1;            } else {
                if (features[18] <= -0.08746041730046272f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 190
int predict_tree_190(const float* features) {
    // Max depth: 10
    if (features[1] <= -0.4236069470643997f) {
        if (features[5] <= -0.00588306353893131f) {
            return 0;        } else {
            if (features[23] <= 0.8726251274347305f) {
                if (features[8] <= -0.07864552922546864f) {
                    return 0;                } else {
                    if (features[26] <= -0.3549315333366394f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            } else {
                return 2;            }
        }
    } else {
        if (features[6] <= -0.11601662915199995f) {
            if (features[3] <= 0.30829092860221863f) {
                if (features[1] <= -0.14874011278152466f) {
                    if (features[22] <= 0.09805969521403313f) {
                        return 0;                    } else {
                        if (features[24] <= -0.03472746443003416f) {
                            return 1;                        } else {
                            return 1;                        }
                    }
                } else {
                    if (features[8] <= 0.15209679305553436f) {
                        if (features[4] <= 0.016440822277218103f) {
                            return 2;                        } else {
                            return 2;                        }
                    } else {
                        return 1;                    }
                }
            } else {
                if (features[4] <= 1.538960337638855f) {
                    if (features[0] <= -0.3483507037162781f) {
                        if (features[10] <= -0.4222528785467148f) {
                            return 2;                        } else {
                            if (features[4] <= -0.5965160727500916f) {
                                return 0;                            } else {
                                if (features[1] <= -0.4000733643770218f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        }
                    } else {
                        if (features[22] <= 0.0716934371739626f) {
                            if (features[27] <= 0.6659863591194153f) {
                                return 0;                            } else {
                                return 2;                            }
                        } else {
                            return 2;                        }
                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[2] <= 0.5671135187149048f) {
                if (features[18] <= -0.2254994511604309f) {
                    if (features[17] <= -0.41780413687229156f) {
                        return 0;                    } else {
                        if (features[10] <= -0.3994574099779129f) {
                            return 0;                        } else {
                            if (features[22] <= -0.620701253414154f) {
                                if (features[17] <= -0.37529176473617554f) {
                                    if (features[19] <= -0.4290240406990051f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    if (features[0] <= -0.3758691996335983f) {
                                        return 0;                                    } else {
                                        if (features[27] <= -0.3076992928981781f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            } else {
                                if (features[10] <= -0.22362533956766129f) {
                                    if (features[1] <= -0.3806186765432358f) {
                                        return 0;                                    } else {
                                        if (features[6] <= 0.5455998182296753f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                } else {
                    return 2;                }
            } else {
                if (features[25] <= -0.07732213381677866f) {
                    return 0;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 191
int predict_tree_191(const float* features) {
    // Max depth: 8
    if (features[20] <= 0.1218646913766861f) {
        if (features[19] <= -0.4057866781949997f) {
            if (features[10] <= -0.36416296660900116f) {
                return 0;            } else {
                if (features[19] <= -0.47108471393585205f) {
                    return 0;                } else {
                    if (features[10] <= -0.3606458306312561f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            }
        } else {
            if (features[23] <= -0.3167472183704376f) {
                if (features[17] <= -0.37529483437538147f) {
                    if (features[14] <= -0.333983913064003f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[0] <= -0.3758653551340103f) {
                        return 0;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[4] <= 0.05639524757862091f) {
                    if (features[27] <= -0.02160521224141121f) {
                        if (features[26] <= 2.2370940446853638f) {
                            return 0;                        } else {
                            return 2;                        }
                    } else {
                        if (features[7] <= 0.992752842605114f) {
                            return 2;                        } else {
                            return 0;                        }
                    }
                } else {
                    if (features[21] <= 0.038929108530282974f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[18] <= -0.2300560474395752f) {
            if (features[34] <= -2.0389932096004486f) {
                return 2;            } else {
                if (features[14] <= -1.445028007030487f) {
                    return 2;                } else {
                    if (features[0] <= -0.4526994973421097f) {
                        if (features[19] <= -0.5077037215232849f) {
                            if (features[9] <= 0.8893032371997833f) {
                                if (features[22] <= 0.03772755153477192f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                if (features[0] <= -0.5826310813426971f) {
                                    return 1;                                } else {
                                    return 0;                                }
                            }
                        } else {
                            if (features[2] <= 0.6337457299232483f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    } else {
                        if (features[10] <= -0.2069772630929947f) {
                            if (features[17] <= -0.32025274634361267f) {
                                if (features[1] <= -0.30040043592453003f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            } else {
                                return 1;                            }
                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[0] <= -0.33585691452026367f) {
                return 1;            } else {
                if (features[28] <= -0.4683038666844368f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 192
int predict_tree_192(const float* features) {
    // Max depth: 9
    if (features[22] <= 0.12270794808864594f) {
        if (features[11] <= -0.030767304822802544f) {
            if (features[21] <= -0.5649189651012421f) {
                if (features[2] <= -0.08888529241085052f) {
                    return 0;                } else {
                    if (features[8] <= -0.22702737897634506f) {
                        return 0;                    } else {
                        if (features[22] <= -0.6139303147792816f) {
                            if (features[0] <= -0.38184063136577606f) {
                                return 0;                            } else {
                                return 1;                            }
                        } else {
                            if (features[0] <= -0.3966195434331894f) {
                                if (features[4] <= -0.591468870639801f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        }
                    }
                }
            } else {
                if (features[7] <= -0.14999626576900482f) {
                    if (features[0] <= -0.2302743881009519f) {
                        return 0;                    } else {
                        return 2;                    }
                } else {
                    return 0;                }
            }
        } else {
            if (features[6] <= 1.2072162628173828f) {
                if (features[23] <= 0.2331559956073761f) {
                    if (features[26] <= -0.05159951560199261f) {
                        if (features[27] <= 3.301996350288391f) {
                            if (features[18] <= 0.39944832026958466f) {
                                return 0;                            } else {
                                if (features[20] <= 0.0910192858427763f) {
                                    return 0;                                } else {
                                    return 2;                                }
                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[21] <= -0.4161309003829956f) {
                            if (features[27] <= -0.26542089879512787f) {
                                return 0;                            } else {
                                if (features[5] <= -0.401108980178833f) {
                                    return 0;                                } else {
                                    if (features[1] <= -0.24324754625558853f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        } else {
                            if (features[8] <= -0.2317803055047989f) {
                                return 2;                            } else {
                                return 0;                            }
                        }
                    }
                } else {
                    return 2;                }
            } else {
                if (features[17] <= -0.3792797327041626f) {
                    if (features[14] <= -0.5805152356624603f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[23] <= -0.35829006135463715f) {
                        if (features[12] <= -0.012569549959152937f) {
                            return 0;                        } else {
                            if (features[0] <= -0.3731534332036972f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    } else {
                        return 0;                    }
                }
            }
        }
    } else {
        if (features[10] <= -0.2171178013086319f) {
            if (features[22] <= 1.5422616004943848f) {
                if (features[23] <= -0.08271623030304909f) {
                    return 0;                } else {
                    if (features[17] <= -0.5722039937973022f) {
                        if (features[4] <= 0.4563424736261368f) {
                            if (features[12] <= -0.014113027602434158f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[12] <= 0.1761169210076332f) {
                            if (features[17] <= -0.24509385973215103f) {
                                if (features[0] <= -0.3681335598230362f) {
                                    if (features[25] <= -0.002321228967048228f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[31] <= 0.16302114725112915f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                return 2;                            }
                        } else {
                            return 1;                        }
                    }
                }
            } else {
                if (features[23] <= 1.7231106758117676f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[23] <= -0.16121145337820053f) {
                return 2;            } else {
                return 2;            }
        }
    }
}

// Tree 193
int predict_tree_193(const float* features) {
    // Max depth: 10
    if (features[19] <= -0.45461083948612213f) {
        if (features[24] <= -0.022179621271789074f) {
            if (features[26] <= 0.1883242279291153f) {
                return 0;            } else {
                if (features[12] <= 1.214646816253662f) {
                    return 1;                } else {
                    return 2;                }
            }
        } else {
            if (features[17] <= -0.524360865354538f) {
                if (features[9] <= 0.9006536304950714f) {
                    if (features[21] <= 0.2211066260933876f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[4] <= 0.4787375032901764f) {
                        return 1;                    } else {
                        return 1;                    }
                }
            } else {
                if (features[17] <= -0.40279820561408997f) {
                    return 2;                } else {
                    return 1;                }
            }
        }
    } else {
        if (features[3] <= 0.2887963354587555f) {
            if (features[20] <= 0.19124921411275864f) {
                if (features[25] <= -0.030388778541237116f) {
                    if (features[21] <= -0.42960384488105774f) {
                        if (features[17] <= -0.3497269004583359f) {
                            if (features[4] <= -0.7683019638061523f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[26] <= -0.353474959731102f) {
                            return 0;                        } else {
                            if (features[9] <= -0.4805224537849426f) {
                                return 0;                            } else {
                                if (features[11] <= -0.08054055273532867f) {
                                    return 0;                                } else {
                                    if (features[18] <= -0.3684898763895035f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            }
                        }
                    }
                } else {
                    return 2;                }
            } else {
                if (features[0] <= -0.21389878541231155f) {
                    if (features[34] <= -2.0389932096004486f) {
                        return 2;                    } else {
                        if (features[7] <= 0.20590877532958984f) {
                            return 1;                        } else {
                            return 2;                        }
                    }
                } else {
                    return 2;                }
            }
        } else {
            if (features[3] <= 0.6436773836612701f) {
                if (features[0] <= -0.2530488148331642f) {
                    if (features[22] <= 1.547173023223877f) {
                        if (features[0] <= -0.4301494359970093f) {
                            return 0;                        } else {
                            if (features[12] <= 0.08114364370703697f) {
                                if (features[21] <= -0.6203054487705231f) {
                                    if (features[1] <= -0.33887341618537903f) {
                                        if (features[22] <= -0.6412869393825531f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[19] <= -0.10314782819477841f) {
                                        if (features[15] <= 0.7462623417377472f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                if (features[8] <= -0.09794314950704575f) {
                                    return 2;                                } else {
                                    return 0;                                }
                            }
                        }
                    } else {
                        if (features[25] <= 3.4259382486343384f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[6] <= -1.6597883701324463f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[22] <= 0.43201880902051926f) {
                    if (features[18] <= -0.45435261726379395f) {
                        return 0;                    } else {
                        return 0;                    }
                } else {
                    if (features[24] <= 0.2361520603299141f) {
                        if (features[0] <= -0.3939318060874939f) {
                            return 1;                        } else {
                            return 1;                        }
                    } else {
                        return 2;                    }
                }
            }
        }
    }
}

// Tree 194
int predict_tree_194(const float* features) {
    // Max depth: 10
    if (features[10] <= -0.4356302320957184f) {
        if (features[4] <= 0.4563424736261368f) {
            return 0;        } else {
            if (features[17] <= -0.524360865354538f) {
                return 1;            } else {
                return 2;            }
        }
    } else {
        if (features[0] <= -0.21553847193717957f) {
            if (features[7] <= 0.661191999912262f) {
                if (features[10] <= -0.4145737290382385f) {
                    return 0;                } else {
                    if (features[5] <= -0.39662623405456543f) {
                        return 0;                    } else {
                        if (features[8] <= 0.2307741492986679f) {
                            if (features[22] <= 0.09228923358023167f) {
                                if (features[0] <= -0.37642648816108704f) {
                                    if (features[2] <= -0.3704298585653305f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                if (features[1] <= -0.3468702882528305f) {
                                    if (features[24] <= -0.009363007731735706f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[6] <= -0.11601662915199995f) {
                                        if (features[13] <= 0.8739083707332611f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 2;                                    }
                                }
                            }
                        } else {
                            if (features[17] <= -0.38756826519966125f) {
                                return 0;                            } else {
                                return 1;                            }
                        }
                    }
                }
            } else {
                if (features[1] <= -0.423930361866951f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[20] <= 0.05435569956898689f) {
                if (features[11] <= -1.1218975186347961f) {
                    return 2;                } else {
                    if (features[0] <= 0.6005583107471466f) {
                        return 2;                    } else {
                        return 0;                    }
                }
            } else {
                return 2;            }
        }
    }
}

// Tree 195
int predict_tree_195(const float* features) {
    // Max depth: 8
    if (features[20] <= 0.12261087074875832f) {
        if (features[17] <= -0.3799618184566498f) {
            return 0;        } else {
            if (features[4] <= -0.3649798631668091f) {
                if (features[14] <= -0.2219841331243515f) {
                    if (features[10] <= -0.35418741405010223f) {
                        return 0;                    } else {
                        return 1;                    }
                } else {
                    if (features[23] <= -0.35829006135463715f) {
                        if (features[10] <= -0.3555326610803604f) {
                            if (features[8] <= -0.11639589443802834f) {
                                return 1;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    } else {
                        return 1;                    }
                }
            } else {
                if (features[4] <= 0.05113649368286133f) {
                    if (features[2] <= -0.6144351437687874f) {
                        if (features[27] <= 0.41745896730571985f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[26] <= 5.83961820602417f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[27] <= 0.4469941109418869f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        }
    } else {
        if (features[17] <= -0.27531395852565765f) {
            if (features[22] <= 1.53965425491333f) {
                if (features[18] <= -0.5740087330341339f) {
                    if (features[9] <= 0.9334932565689087f) {
                        if (features[18] <= -0.5889121294021606f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        return 1;                    }
                } else {
                    if (features[10] <= -0.4567337930202484f) {
                        return 0;                    } else {
                        if (features[15] <= 0.7462623417377472f) {
                            return 1;                        } else {
                            if (features[13] <= 0.18267003074288368f) {
                                return 2;                            } else {
                                if (features[21] <= 0.7648819833993912f) {
                                    return 1;                                } else {
                                    return 1;                                }
                            }
                        }
                    }
                }
            } else {
                if (features[9] <= -1.1982933282852173f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[34] <= -2.0389932096004486f) {
                return 2;            } else {
                return 2;            }
        }
    }
}

// Tree 196
int predict_tree_196(const float* features) {
    // Max depth: 9
    if (features[17] <= -0.45113205909729004f) {
        if (features[7] <= 0.6593850255012512f) {
            if (features[21] <= 0.44222840666770935f) {
                return 0;            } else {
                return 1;            }
        } else {
            if (features[22] <= 1.0077814608812332f) {
                return 0;            } else {
                return 2;            }
        }
    } else {
        if (features[6] <= -0.11601662915199995f) {
            if (features[1] <= -0.15344125032424927f) {
                if (features[17] <= -0.4303564876317978f) {
                    if (features[24] <= 1.6620526909828186f) {
                        return 0;                    } else {
                        if (features[4] <= 1.692270040512085f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[25] <= 1.5124974697828293f) {
                        if (features[23] <= -0.3629760891199112f) {
                            return 0;                        } else {
                            if (features[12] <= 0.10762324556708336f) {
                                if (features[27] <= -0.29474034905433655f) {
                                    return 1;                                } else {
                                    if (features[6] <= -0.9981718957424164f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                if (features[31] <= 0.16302114725112915f) {
                                    return 2;                                } else {
                                    return 1;                                }
                            }
                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[22] <= 0.05345231108367443f) {
                    if (features[2] <= -0.6144351437687874f) {
                        if (features[4] <= -0.09064831957221031f) {
                            return 2;                        } else {
                            return 0;                        }
                    } else {
                        if (features[2] <= 0.26773782074451447f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[0] <= -0.17557867616415024f) {
                        return 1;                    } else {
                        if (features[21] <= 0.05034171603620052f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            }
        } else {
            if (features[19] <= 0.07130791881354526f) {
                if (features[1] <= -0.3800498843193054f) {
                    return 0;                } else {
                    if (features[10] <= -0.22362533956766129f) {
                        if (features[9] <= -0.7689004838466644f) {
                            return 0;                        } else {
                            if (features[22] <= 0.32649314403533936f) {
                                if (features[0] <= -0.3756202161312103f) {
                                    if (features[13] <= -0.13180257007479668f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                return 1;                            }
                        }
                    } else {
                        return 2;                    }
                }
            } else {
                return 2;            }
        }
    }
}

// Tree 197
int predict_tree_197(const float* features) {
    // Max depth: 10
    if (features[5] <= -0.1309334635734558f) {
        if (features[7] <= 0.3601919710636139f) {
            if (features[0] <= -0.37463347613811493f) {
                return 0;            } else {
                if (features[10] <= -0.14855615235865116f) {
                    return 1;                } else {
                    if (features[31] <= 0.16302114725112915f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[21] <= -0.6379899382591248f) {
                return 0;            } else {
                if (features[8] <= -0.1732967272400856f) {
                    return 0;                } else {
                    if (features[0] <= -0.3750685006380081f) {
                        if (features[23] <= -0.3884044736623764f) {
                            return 0;                        } else {
                            return 0;                        }
                    } else {
                        if (features[17] <= 0.469489261507988f) {
                            return 1;                        } else {
                            return 2;                        }
                    }
                }
            }
        }
    } else {
        if (features[0] <= -0.21553847193717957f) {
            if (features[5] <= 1.0675677359104156f) {
                if (features[21] <= 0.12535182386636734f) {
                    return 0;                } else {
                    if (features[7] <= -0.43111881613731384f) {
                        if (features[9] <= 0.8998923599720001f) {
                            if (features[0] <= -0.4310908317565918f) {
                                if (features[17] <= -0.5897114872932434f) {
                                    return 0;                                } else {
                                    return 0;                                }
                            } else {
                                return 1;                            }
                        } else {
                            if (features[26] <= -0.3278781771659851f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    } else {
                        if (features[17] <= -0.49844835698604584f) {
                            return 0;                        } else {
                            if (features[15] <= 0.7462623417377472f) {
                                return 1;                            } else {
                                if (features[29] <= -0.0025959014892578125f) {
                                    return 2;                                } else {
                                    if (features[6] <= -0.11601662915199995f) {
                                        if (features[20] <= 0.5563220828771591f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    } else {
                                        return 2;                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                if (features[12] <= -0.14214306697249413f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[24] <= 0.07331399619579315f) {
                if (features[21] <= -0.025435972143895924f) {
                    return 0;                } else {
                    return 2;                }
            } else {
                if (features[22] <= 0.054978299885988235f) {
                    if (features[3] <= 3.077317953109741f) {
                        return 2;                    } else {
                        return 0;                    }
                } else {
                    return 2;                }
            }
        }
    }
}

// Tree 198
int predict_tree_198(const float* features) {
    // Max depth: 10
    if (features[9] <= 2.0291956663131714f) {
        if (features[9] <= 0.48778799176216125f) {
            if (features[10] <= -0.4359981566667557f) {
                if (features[27] <= 0.06872780248522758f) {
                    if (features[25] <= 1.999479248188436f) {
                        return 0;                    } else {
                        if (features[24] <= 3.924169898033142f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                } else {
                    if (features[7] <= 0.6964074373245239f) {
                        return 0;                    } else {
                        if (features[11] <= -0.020230617374181747f) {
                            return 2;                        } else {
                            return 2;                        }
                    }
                }
            } else {
                if (features[24] <= -0.04028925858438015f) {
                    if (features[2] <= -0.5862806737422943f) {
                        if (features[9] <= -0.5007360428571701f) {
                            return 0;                        } else {
                            return 2;                        }
                    } else {
                        if (features[19] <= -0.39606814086437225f) {
                            if (features[11] <= 0.07970638945698738f) {
                                if (features[0] <= -0.37592414021492004f) {
                                    if (features[24] <= -0.39421193301677704f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                } else {
                                    return 1;                                }
                            } else {
                                if (features[6] <= 0.5455998182296753f) {
                                    if (features[7] <= -0.09195602312684059f) {
                                        return 0;                                    } else {
                                        if (features[17] <= -0.4076954424381256f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    if (features[2] <= -0.013806743547320366f) {
                                        return 1;                                    } else {
                                        if (features[12] <= 0.09182912483811378f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    }
                                }
                            }
                        } else {
                            if (features[15] <= 0.7462623417377472f) {
                                if (features[1] <= -0.3436245322227478f) {
                                    return 0;                                } else {
                                    if (features[0] <= -0.37597908079624176f) {
                                        return 0;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                if (features[22] <= -0.5668267607688904f) {
                                    if (features[7] <= -0.10962048918008804f) {
                                        return 0;                                    } else {
                                        if (features[1] <= -0.3451023995876312f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                } else {
                                    if (features[12] <= -0.3315628170967102f) {
                                        return 0;                                    } else {
                                        return 0;                                    }
                                }
                            }
                        }
                    }
                } else {
                    if (features[6] <= -0.9981719255447388f) {
                        if (features[2] <= -0.9522886127233505f) {
                            if (features[22] <= -0.10968701541423798f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            if (features[2] <= -0.16396384686231613f) {
                                if (features[27] <= 0.1775611713528633f) {
                                    return 2;                                } else {
                                    return 1;                                }
                            } else {
                                return 2;                            }
                        }
                    } else {
                        return 2;                    }
                }
            }
        } else {
            if (features[18] <= -0.0075117365922778845f) {
                if (features[34] <= -2.0389932096004486f) {
                    return 2;                } else {
                    if (features[24] <= -0.08112133666872978f) {
                        return 0;                    } else {
                        if (features[20] <= 2.2306358218193054f) {
                            if (features[10] <= -0.11437703669071198f) {
                                if (features[4] <= 0.24741285294294357f) {
                                    if (features[10] <= -0.42971666157245636f) {
                                        if (features[4] <= 0.15564662963151932f) {
                                            return 0;                                        } else {
                                            return 0;                                        }
                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[2] <= 0.11758071696385741f) {
                                        if (features[26] <= 0.019933544099330902f) {
                                            return 1;                                        } else {
                                            return 2;                                        }
                                    } else {
                                        if (features[18] <= -0.451386421918869f) {
                                            return 0;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            } else {
                                return 2;                            }
                        } else {
                            if (features[2] <= 0.6619001924991608f) {
                                return 2;                            } else {
                                return 2;                            }
                        }
                    }
                }
            } else {
                if (features[17] <= 0.03713602107018232f) {
                    return 1;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[8] <= -0.1975339725613594f) {
            return 2;        } else {
            if (features[10] <= -0.35988423228263855f) {
                if (features[21] <= 2.043063521385193f) {
                    if (features[31] <= 0.16302114725112915f) {
                        return 1;                    } else {
                        return 1;                    }
                } else {
                    return 2;                }
            } else {
                return 2;            }
        }
    }
}

// Tree 199
int predict_tree_199(const float* features) {
    // Max depth: 10
    if (features[18] <= -0.44898782670497894f) {
        if (features[5] <= -0.004704053630121052f) {
            return 0;        } else {
            if (features[22] <= 1.2560325860977173f) {
                if (features[11] <= 0.00929222907871008f) {
                    return 0;                } else {
                    if (features[13] <= 0.7914237082004547f) {
                        if (features[27] <= -0.05951352044939995f) {
                            return 0;                        } else {
                            if (features[20] <= 0.29305216670036316f) {
                                return 1;                            } else {
                                return 1;                            }
                        }
                    } else {
                        return 2;                    }
                }
            } else {
                if (features[10] <= -0.49386587738990784f) {
                    return 2;                } else {
                    return 2;                }
            }
        }
    } else {
        if (features[1] <= -0.06946076825261116f) {
            if (features[5] <= 0.3195102885365486f) {
                if (features[22] <= -0.6407210230827332f) {
                    return 0;                } else {
                    if (features[24] <= -0.10536117106676102f) {
                        if (features[0] <= -0.3758653551340103f) {
                            if (features[20] <= -0.6440068781375885f) {
                                return 0;                            } else {
                                return 0;                            }
                        } else {
                            return 1;                        }
                    } else {
                        if (features[26] <= -0.28540121018886566f) {
                            if (features[23] <= 0.19379392266273499f) {
                                if (features[27] <= -0.2911965847015381f) {
                                    if (features[18] <= -0.41041311621665955f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                } else {
                                    if (features[10] <= -0.31565435230731964f) {
                                        return 1;                                    } else {
                                        return 1;                                    }
                                }
                            } else {
                                return 1;                            }
                        } else {
                            if (features[0] <= -0.2271149605512619f) {
                                if (features[15] <= 0.7462623417377472f) {
                                    return 1;                                } else {
                                    if (features[6] <= -0.9981718957424164f) {
                                        return 2;                                    } else {
                                        if (features[9] <= 1.579354852437973f) {
                                            return 1;                                        } else {
                                            return 1;                                        }
                                    }
                                }
                            } else {
                                if (features[13] <= -0.11934395506978035f) {
                                    return 2;                                } else {
                                    return 2;                                }
                            }
                        }
                    }
                }
            } else {
                if (features[13] <= -3.9852198362350464f) {
                    return 2;                } else {
                    return 2;                }
            }
        } else {
            if (features[7] <= 1.9035120010375977f) {
                if (features[4] <= 0.020974229089915752f) {
                    return 2;                } else {
                    if (features[19] <= -0.36759214103221893f) {
                        return 2;                    } else {
                        return 2;                    }
                }
            } else {
                if (features[20] <= 0.16974110901355743f) {
                    return 0;                } else {
                    return 2;                }
            }
        }
    }
}

// ════════════════════════════════════════════════════════════════════════
// ENSEMBLE PREDICTION (Vote across all 200 trees)
// ════════════════════════════════════════════════════════════════════════

int predict(float* features) {
    normalize_features(features);
    
    int votes[NUM_CLASSES] = {0};
    
    votes[predict_tree_0(features)]++;
    votes[predict_tree_1(features)]++;
    votes[predict_tree_2(features)]++;
    votes[predict_tree_3(features)]++;
    votes[predict_tree_4(features)]++;
    votes[predict_tree_5(features)]++;
    votes[predict_tree_6(features)]++;
    votes[predict_tree_7(features)]++;
    votes[predict_tree_8(features)]++;
    votes[predict_tree_9(features)]++;
    votes[predict_tree_10(features)]++;
    votes[predict_tree_11(features)]++;
    votes[predict_tree_12(features)]++;
    votes[predict_tree_13(features)]++;
    votes[predict_tree_14(features)]++;
    votes[predict_tree_15(features)]++;
    votes[predict_tree_16(features)]++;
    votes[predict_tree_17(features)]++;
    votes[predict_tree_18(features)]++;
    votes[predict_tree_19(features)]++;
    votes[predict_tree_20(features)]++;
    votes[predict_tree_21(features)]++;
    votes[predict_tree_22(features)]++;
    votes[predict_tree_23(features)]++;
    votes[predict_tree_24(features)]++;
    votes[predict_tree_25(features)]++;
    votes[predict_tree_26(features)]++;
    votes[predict_tree_27(features)]++;
    votes[predict_tree_28(features)]++;
    votes[predict_tree_29(features)]++;
    votes[predict_tree_30(features)]++;
    votes[predict_tree_31(features)]++;
    votes[predict_tree_32(features)]++;
    votes[predict_tree_33(features)]++;
    votes[predict_tree_34(features)]++;
    votes[predict_tree_35(features)]++;
    votes[predict_tree_36(features)]++;
    votes[predict_tree_37(features)]++;
    votes[predict_tree_38(features)]++;
    votes[predict_tree_39(features)]++;
    votes[predict_tree_40(features)]++;
    votes[predict_tree_41(features)]++;
    votes[predict_tree_42(features)]++;
    votes[predict_tree_43(features)]++;
    votes[predict_tree_44(features)]++;
    votes[predict_tree_45(features)]++;
    votes[predict_tree_46(features)]++;
    votes[predict_tree_47(features)]++;
    votes[predict_tree_48(features)]++;
    votes[predict_tree_49(features)]++;
    votes[predict_tree_50(features)]++;
    votes[predict_tree_51(features)]++;
    votes[predict_tree_52(features)]++;
    votes[predict_tree_53(features)]++;
    votes[predict_tree_54(features)]++;
    votes[predict_tree_55(features)]++;
    votes[predict_tree_56(features)]++;
    votes[predict_tree_57(features)]++;
    votes[predict_tree_58(features)]++;
    votes[predict_tree_59(features)]++;
    votes[predict_tree_60(features)]++;
    votes[predict_tree_61(features)]++;
    votes[predict_tree_62(features)]++;
    votes[predict_tree_63(features)]++;
    votes[predict_tree_64(features)]++;
    votes[predict_tree_65(features)]++;
    votes[predict_tree_66(features)]++;
    votes[predict_tree_67(features)]++;
    votes[predict_tree_68(features)]++;
    votes[predict_tree_69(features)]++;
    votes[predict_tree_70(features)]++;
    votes[predict_tree_71(features)]++;
    votes[predict_tree_72(features)]++;
    votes[predict_tree_73(features)]++;
    votes[predict_tree_74(features)]++;
    votes[predict_tree_75(features)]++;
    votes[predict_tree_76(features)]++;
    votes[predict_tree_77(features)]++;
    votes[predict_tree_78(features)]++;
    votes[predict_tree_79(features)]++;
    votes[predict_tree_80(features)]++;
    votes[predict_tree_81(features)]++;
    votes[predict_tree_82(features)]++;
    votes[predict_tree_83(features)]++;
    votes[predict_tree_84(features)]++;
    votes[predict_tree_85(features)]++;
    votes[predict_tree_86(features)]++;
    votes[predict_tree_87(features)]++;
    votes[predict_tree_88(features)]++;
    votes[predict_tree_89(features)]++;
    votes[predict_tree_90(features)]++;
    votes[predict_tree_91(features)]++;
    votes[predict_tree_92(features)]++;
    votes[predict_tree_93(features)]++;
    votes[predict_tree_94(features)]++;
    votes[predict_tree_95(features)]++;
    votes[predict_tree_96(features)]++;
    votes[predict_tree_97(features)]++;
    votes[predict_tree_98(features)]++;
    votes[predict_tree_99(features)]++;
    votes[predict_tree_100(features)]++;
    votes[predict_tree_101(features)]++;
    votes[predict_tree_102(features)]++;
    votes[predict_tree_103(features)]++;
    votes[predict_tree_104(features)]++;
    votes[predict_tree_105(features)]++;
    votes[predict_tree_106(features)]++;
    votes[predict_tree_107(features)]++;
    votes[predict_tree_108(features)]++;
    votes[predict_tree_109(features)]++;
    votes[predict_tree_110(features)]++;
    votes[predict_tree_111(features)]++;
    votes[predict_tree_112(features)]++;
    votes[predict_tree_113(features)]++;
    votes[predict_tree_114(features)]++;
    votes[predict_tree_115(features)]++;
    votes[predict_tree_116(features)]++;
    votes[predict_tree_117(features)]++;
    votes[predict_tree_118(features)]++;
    votes[predict_tree_119(features)]++;
    votes[predict_tree_120(features)]++;
    votes[predict_tree_121(features)]++;
    votes[predict_tree_122(features)]++;
    votes[predict_tree_123(features)]++;
    votes[predict_tree_124(features)]++;
    votes[predict_tree_125(features)]++;
    votes[predict_tree_126(features)]++;
    votes[predict_tree_127(features)]++;
    votes[predict_tree_128(features)]++;
    votes[predict_tree_129(features)]++;
    votes[predict_tree_130(features)]++;
    votes[predict_tree_131(features)]++;
    votes[predict_tree_132(features)]++;
    votes[predict_tree_133(features)]++;
    votes[predict_tree_134(features)]++;
    votes[predict_tree_135(features)]++;
    votes[predict_tree_136(features)]++;
    votes[predict_tree_137(features)]++;
    votes[predict_tree_138(features)]++;
    votes[predict_tree_139(features)]++;
    votes[predict_tree_140(features)]++;
    votes[predict_tree_141(features)]++;
    votes[predict_tree_142(features)]++;
    votes[predict_tree_143(features)]++;
    votes[predict_tree_144(features)]++;
    votes[predict_tree_145(features)]++;
    votes[predict_tree_146(features)]++;
    votes[predict_tree_147(features)]++;
    votes[predict_tree_148(features)]++;
    votes[predict_tree_149(features)]++;
    votes[predict_tree_150(features)]++;
    votes[predict_tree_151(features)]++;
    votes[predict_tree_152(features)]++;
    votes[predict_tree_153(features)]++;
    votes[predict_tree_154(features)]++;
    votes[predict_tree_155(features)]++;
    votes[predict_tree_156(features)]++;
    votes[predict_tree_157(features)]++;
    votes[predict_tree_158(features)]++;
    votes[predict_tree_159(features)]++;
    votes[predict_tree_160(features)]++;
    votes[predict_tree_161(features)]++;
    votes[predict_tree_162(features)]++;
    votes[predict_tree_163(features)]++;
    votes[predict_tree_164(features)]++;
    votes[predict_tree_165(features)]++;
    votes[predict_tree_166(features)]++;
    votes[predict_tree_167(features)]++;
    votes[predict_tree_168(features)]++;
    votes[predict_tree_169(features)]++;
    votes[predict_tree_170(features)]++;
    votes[predict_tree_171(features)]++;
    votes[predict_tree_172(features)]++;
    votes[predict_tree_173(features)]++;
    votes[predict_tree_174(features)]++;
    votes[predict_tree_175(features)]++;
    votes[predict_tree_176(features)]++;
    votes[predict_tree_177(features)]++;
    votes[predict_tree_178(features)]++;
    votes[predict_tree_179(features)]++;
    votes[predict_tree_180(features)]++;
    votes[predict_tree_181(features)]++;
    votes[predict_tree_182(features)]++;
    votes[predict_tree_183(features)]++;
    votes[predict_tree_184(features)]++;
    votes[predict_tree_185(features)]++;
    votes[predict_tree_186(features)]++;
    votes[predict_tree_187(features)]++;
    votes[predict_tree_188(features)]++;
    votes[predict_tree_189(features)]++;
    votes[predict_tree_190(features)]++;
    votes[predict_tree_191(features)]++;
    votes[predict_tree_192(features)]++;
    votes[predict_tree_193(features)]++;
    votes[predict_tree_194(features)]++;
    votes[predict_tree_195(features)]++;
    votes[predict_tree_196(features)]++;
    votes[predict_tree_197(features)]++;
    votes[predict_tree_198(features)]++;
    votes[predict_tree_199(features)]++;
    
    int max_votes = votes[0];
    int predicted_class = 0;
    for (int i = 1; i < NUM_CLASSES; i++) {
        if (votes[i] > max_votes) {
            max_votes = votes[i];
            predicted_class = i;
        }
    }
    
    return predicted_class;
}

// Get confidence as fraction of votes for predicted class
float get_confidence(float* features) {
    normalize_features(features);
    
    int votes[NUM_CLASSES] = {0};
    
    votes[predict_tree_0(features)]++;
    votes[predict_tree_1(features)]++;
    votes[predict_tree_2(features)]++;
    votes[predict_tree_3(features)]++;
    votes[predict_tree_4(features)]++;
    votes[predict_tree_5(features)]++;
    votes[predict_tree_6(features)]++;
    votes[predict_tree_7(features)]++;
    votes[predict_tree_8(features)]++;
    votes[predict_tree_9(features)]++;
    votes[predict_tree_10(features)]++;
    votes[predict_tree_11(features)]++;
    votes[predict_tree_12(features)]++;
    votes[predict_tree_13(features)]++;
    votes[predict_tree_14(features)]++;
    votes[predict_tree_15(features)]++;
    votes[predict_tree_16(features)]++;
    votes[predict_tree_17(features)]++;
    votes[predict_tree_18(features)]++;
    votes[predict_tree_19(features)]++;
    votes[predict_tree_20(features)]++;
    votes[predict_tree_21(features)]++;
    votes[predict_tree_22(features)]++;
    votes[predict_tree_23(features)]++;
    votes[predict_tree_24(features)]++;
    votes[predict_tree_25(features)]++;
    votes[predict_tree_26(features)]++;
    votes[predict_tree_27(features)]++;
    votes[predict_tree_28(features)]++;
    votes[predict_tree_29(features)]++;
    votes[predict_tree_30(features)]++;
    votes[predict_tree_31(features)]++;
    votes[predict_tree_32(features)]++;
    votes[predict_tree_33(features)]++;
    votes[predict_tree_34(features)]++;
    votes[predict_tree_35(features)]++;
    votes[predict_tree_36(features)]++;
    votes[predict_tree_37(features)]++;
    votes[predict_tree_38(features)]++;
    votes[predict_tree_39(features)]++;
    votes[predict_tree_40(features)]++;
    votes[predict_tree_41(features)]++;
    votes[predict_tree_42(features)]++;
    votes[predict_tree_43(features)]++;
    votes[predict_tree_44(features)]++;
    votes[predict_tree_45(features)]++;
    votes[predict_tree_46(features)]++;
    votes[predict_tree_47(features)]++;
    votes[predict_tree_48(features)]++;
    votes[predict_tree_49(features)]++;
    votes[predict_tree_50(features)]++;
    votes[predict_tree_51(features)]++;
    votes[predict_tree_52(features)]++;
    votes[predict_tree_53(features)]++;
    votes[predict_tree_54(features)]++;
    votes[predict_tree_55(features)]++;
    votes[predict_tree_56(features)]++;
    votes[predict_tree_57(features)]++;
    votes[predict_tree_58(features)]++;
    votes[predict_tree_59(features)]++;
    votes[predict_tree_60(features)]++;
    votes[predict_tree_61(features)]++;
    votes[predict_tree_62(features)]++;
    votes[predict_tree_63(features)]++;
    votes[predict_tree_64(features)]++;
    votes[predict_tree_65(features)]++;
    votes[predict_tree_66(features)]++;
    votes[predict_tree_67(features)]++;
    votes[predict_tree_68(features)]++;
    votes[predict_tree_69(features)]++;
    votes[predict_tree_70(features)]++;
    votes[predict_tree_71(features)]++;
    votes[predict_tree_72(features)]++;
    votes[predict_tree_73(features)]++;
    votes[predict_tree_74(features)]++;
    votes[predict_tree_75(features)]++;
    votes[predict_tree_76(features)]++;
    votes[predict_tree_77(features)]++;
    votes[predict_tree_78(features)]++;
    votes[predict_tree_79(features)]++;
    votes[predict_tree_80(features)]++;
    votes[predict_tree_81(features)]++;
    votes[predict_tree_82(features)]++;
    votes[predict_tree_83(features)]++;
    votes[predict_tree_84(features)]++;
    votes[predict_tree_85(features)]++;
    votes[predict_tree_86(features)]++;
    votes[predict_tree_87(features)]++;
    votes[predict_tree_88(features)]++;
    votes[predict_tree_89(features)]++;
    votes[predict_tree_90(features)]++;
    votes[predict_tree_91(features)]++;
    votes[predict_tree_92(features)]++;
    votes[predict_tree_93(features)]++;
    votes[predict_tree_94(features)]++;
    votes[predict_tree_95(features)]++;
    votes[predict_tree_96(features)]++;
    votes[predict_tree_97(features)]++;
    votes[predict_tree_98(features)]++;
    votes[predict_tree_99(features)]++;
    votes[predict_tree_100(features)]++;
    votes[predict_tree_101(features)]++;
    votes[predict_tree_102(features)]++;
    votes[predict_tree_103(features)]++;
    votes[predict_tree_104(features)]++;
    votes[predict_tree_105(features)]++;
    votes[predict_tree_106(features)]++;
    votes[predict_tree_107(features)]++;
    votes[predict_tree_108(features)]++;
    votes[predict_tree_109(features)]++;
    votes[predict_tree_110(features)]++;
    votes[predict_tree_111(features)]++;
    votes[predict_tree_112(features)]++;
    votes[predict_tree_113(features)]++;
    votes[predict_tree_114(features)]++;
    votes[predict_tree_115(features)]++;
    votes[predict_tree_116(features)]++;
    votes[predict_tree_117(features)]++;
    votes[predict_tree_118(features)]++;
    votes[predict_tree_119(features)]++;
    votes[predict_tree_120(features)]++;
    votes[predict_tree_121(features)]++;
    votes[predict_tree_122(features)]++;
    votes[predict_tree_123(features)]++;
    votes[predict_tree_124(features)]++;
    votes[predict_tree_125(features)]++;
    votes[predict_tree_126(features)]++;
    votes[predict_tree_127(features)]++;
    votes[predict_tree_128(features)]++;
    votes[predict_tree_129(features)]++;
    votes[predict_tree_130(features)]++;
    votes[predict_tree_131(features)]++;
    votes[predict_tree_132(features)]++;
    votes[predict_tree_133(features)]++;
    votes[predict_tree_134(features)]++;
    votes[predict_tree_135(features)]++;
    votes[predict_tree_136(features)]++;
    votes[predict_tree_137(features)]++;
    votes[predict_tree_138(features)]++;
    votes[predict_tree_139(features)]++;
    votes[predict_tree_140(features)]++;
    votes[predict_tree_141(features)]++;
    votes[predict_tree_142(features)]++;
    votes[predict_tree_143(features)]++;
    votes[predict_tree_144(features)]++;
    votes[predict_tree_145(features)]++;
    votes[predict_tree_146(features)]++;
    votes[predict_tree_147(features)]++;
    votes[predict_tree_148(features)]++;
    votes[predict_tree_149(features)]++;
    votes[predict_tree_150(features)]++;
    votes[predict_tree_151(features)]++;
    votes[predict_tree_152(features)]++;
    votes[predict_tree_153(features)]++;
    votes[predict_tree_154(features)]++;
    votes[predict_tree_155(features)]++;
    votes[predict_tree_156(features)]++;
    votes[predict_tree_157(features)]++;
    votes[predict_tree_158(features)]++;
    votes[predict_tree_159(features)]++;
    votes[predict_tree_160(features)]++;
    votes[predict_tree_161(features)]++;
    votes[predict_tree_162(features)]++;
    votes[predict_tree_163(features)]++;
    votes[predict_tree_164(features)]++;
    votes[predict_tree_165(features)]++;
    votes[predict_tree_166(features)]++;
    votes[predict_tree_167(features)]++;
    votes[predict_tree_168(features)]++;
    votes[predict_tree_169(features)]++;
    votes[predict_tree_170(features)]++;
    votes[predict_tree_171(features)]++;
    votes[predict_tree_172(features)]++;
    votes[predict_tree_173(features)]++;
    votes[predict_tree_174(features)]++;
    votes[predict_tree_175(features)]++;
    votes[predict_tree_176(features)]++;
    votes[predict_tree_177(features)]++;
    votes[predict_tree_178(features)]++;
    votes[predict_tree_179(features)]++;
    votes[predict_tree_180(features)]++;
    votes[predict_tree_181(features)]++;
    votes[predict_tree_182(features)]++;
    votes[predict_tree_183(features)]++;
    votes[predict_tree_184(features)]++;
    votes[predict_tree_185(features)]++;
    votes[predict_tree_186(features)]++;
    votes[predict_tree_187(features)]++;
    votes[predict_tree_188(features)]++;
    votes[predict_tree_189(features)]++;
    votes[predict_tree_190(features)]++;
    votes[predict_tree_191(features)]++;
    votes[predict_tree_192(features)]++;
    votes[predict_tree_193(features)]++;
    votes[predict_tree_194(features)]++;
    votes[predict_tree_195(features)]++;
    votes[predict_tree_196(features)]++;
    votes[predict_tree_197(features)]++;
    votes[predict_tree_198(features)]++;
    votes[predict_tree_199(features)]++;
    
    int max_votes = votes[0];
    int predicted_class = 0;
    for (int i = 1; i < NUM_CLASSES; i++) {
        if (votes[i] > max_votes) {
            max_votes = votes[i];
            predicted_class = i;
        }
    }
    
    return (float)max_votes / NUM_TREES;
}

#endif  // MODEL_H
