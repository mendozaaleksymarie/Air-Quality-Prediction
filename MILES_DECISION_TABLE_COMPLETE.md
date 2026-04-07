# MILES COMPLETE DECISION TABLE
## All Training Scenarios + Sensor Escalation + Wet-Bulb Temperature

---

## 🏛️ ARCHITECTURAL DECISION: Dynamic Field Deployment Remarks

**Why Field Deployment (Scenario 8) has NO generic remarks:**

Field deployment data live on construction sites with constantly-changing conditions. Generic remarks like "CONTINUE OPERATIONS" provide no actionable intelligence. Instead:

- **All Field Deployment readings** (Safe, Caution, Hazardous) are classified using the **sensor escalation/combination logic** 
- **Remarks are DYNAMIC** - derived from the actual sensor pattern detected (misting, dust storm, smoke, CO spike, heat stress, etc.)
- **Workers see the REASON** - not a generic status, but a specific cause + action (e.g., "HAZARDOUS: DUST STORM → Wear N95/FFP2, minimize outdoor exposure")
- **Traceability** - links back to training scenarios (if field readings match Scenario 2 pattern = dust, Scenario 4 pattern = fire, etc.)

This ensures Field Deployment readings are fully integrated into the training protocol—no separate "field-only" remarks, just sensor-driven decision logic that applies universally.

---

# 📊 COMPLETE CLASSIFICATION TABLE

## CLASS 0: SAFE ✅
| Scenario/Condition | Sensor Profile | Wet-Bulb Range | Remark | Reasoning | Worker Action |
|---|---|---|---|---|---|
| **Scenario 1: Baseline** | PM2.5: 3-10<br/>PM10: 5-20<br/>Gas: <100<br/>Humidity: 49-65% | Tw ≤ 26°C | **SAFE: NORMAL OPERATIONS** | All sensors in normal range; no hazards detected | Continue normal operations; monitor periodically |
| **Scenario 3: Misting** | PM2.5: 355-816 (HIGH!)<br/>PM10: High<br/>Gas: 86-117 (normal)<br/>**Humidity: 96-100%** | Tw ≤ 26°C | **SAFE: MISTING DETECTED** | Pattern matching: Extreme PM + Extreme humidity + Normal gas = water droplets, NOT pollution | Water spray is not a health hazard; system working correctly |
| **Scenario 7: High Humidity** | PM2.5: Normal<br/>PM10: Normal<br/>Gas: Normal<br/>Humidity: 60-95% | Tw 27-30°C OK | **SAFE: COOL HUMID AIR** | Elevated humidity alone is not hazardous (aircon condensation, tropical climate) | Normal operations; elevated humidity provides cooling relief |
| **Field Deployment - Dynamic** | All sensors activate sensor escalation/combination logic<br/>Misting detection applied<br/>Wet-bulb escalation applied | Tw ≤ 26°C | **DYNAMIC: From sensor pattern detection** | Field readings classified via sensor escalation logic (NOT generic); remarks based on actual sensor combinations or training patterns detected | Remarks trace to specific causes: misting, dust storm, smoke, CO, heat stress, etc.

| **Decision Rule** | **Trigger** | **Remark** |
|---|---|---|
| Misting Override (Highest Priority) | Humidity ≥ 95% AND Gas < 100 ppm | **SAFE: MISTING DETECTED** |
| All Sensors Normal | PM2.5 < 51 AND PM10 < 151 AND Gas < 131 AND CO < 10 | **SAFE: ALL SENSORS NORMAL** |

---

## CLASS 1: CAUTION ⚠️
| Scenario/Condition | Sensor Profile | Wet-Bulb Range | Remark | Reasoning | Worker Action |
|---|---|---|---|---|---|
| **Single PM2.5 Elevated** | PM2.5: 51-100 μg/m³<br/>Other sensors normal | 27-30°C | **CAUTION: ELEVATED DUST** | Dust level rising but not critical; trending toward hazard | Monitor air quality; consider N95 if heavy work; reduce exertion |
| **Single PM10 Elevated** | PM10: 151-230 μg/m³<br/>Other sensors normal | 27-30°C | **CAUTION: COARSE PARTICLES** | Coarse particles detected; ventilation recommended | Increase ventilation; monitor work pace |
| **Single Gas Elevated** | Gas (MQ-2): 131-175 ppm<br/>Other sensors normal | 27-30°C | **CAUTION: COMBUSTIBLES DETECTED** | Potential smoke/VOC at low levels; check for sources | Check for machinery exhaust/fire; increase ventilation |
| **Single CO Elevated** | CO (MQ-7): 10-30 ppm<br/>Other sensors normal | 27-30°C | **CAUTION: ELEVATED CO** | Carbon monoxide present; check for combustion sources | Verify fire status; check generator/machinery exhaust |
| **PM10 + Gas (Combination)** | PM10: 151-230<br/>Gas: 131-175<br/>PM2.5: < 51 | 27-30°C | **CAUTION: COMBINED HAZARD RISKING** | Multiple sensor categories triggered; risk escalating | Increase monitoring; reduce work intensity; prepare PPE |
| **PM10 + CO (Combination)** | PM10: 151-230<br/>CO: 10-30<br/>Others moderate | 27-30°C | **CAUTION: CHECK FOR FIRE** | Coarse particles + carbon monoxide suggests developing fire | Investigate fire potential; increase ventilation; be ready to evacuate |
| **3+ Sensors in Caution Range** | Any 3+ sensors at caution level<br/>But none hazardous | Tw > 30°C (heat stress escal.) | **CAUTION: MULTI-SENSOR ALERT** | Multiple systems showing stress; coordination effect dangerous | Initiate protective measures; reduce exertion; monitor closely |
| **Heat Stress Escalation** | Sensors: Safe or low caution<br/>**Wet-Bulb: 27-30°C** | **27-30°C** | **CAUTION: HEAT STRESS RISING** | Heat stress from temperature + humidity climbing; body cooling stressed | Increase hydration frequency; reduce work intensity; take breaks |

| **Decision Rule** | **Trigger** | **Remark** |
|---|---|---|
| Single Caution Sensor | One sensor 51-100 (PM2.5), 151-230 (PM10), 131-175 (Gas), 10-30 (CO) | **CAUTION: [SENSOR] ELEVATED** |
| Dangerous Combination (Non-Hazardous) | PM10+Gas OR PM10+CO at caution levels | **CAUTION: COMBINED HAZARD RISKING** |
| Three+ Caution Sensors | 3+ sensors in caution ranges | **CAUTION: MULTI-SENSOR ALERT** |
| Heat Stress Escalation | Tw 27-30°C + any concern | **CAUTION: HEAT STRESS RISING** |

---

## CLASS 2: HAZARDOUS 🚨
| Scenario/Condition | Sensor Profile | Wet-Bulb Range | Remark | Reasoning | Worker Action |
|---|---|---|---|---|---|
| **ANY SINGLE HAZARDOUS SENSOR** | **PM2.5 > 100** | Any | **HAZARDOUS: EXTREME DUST - USE RESPIRATOR, RELOCATE** | Particle level critical; immediate respiratory hazard | **IMMEDIATE**: Stop dust work, use HEPA/N95+ mask, move to ventilated area |
| | **PM10 > 230** | Any | **HAZARDOUS: PARTICLES CRITICAL - SUPPRESS DUST SOURCE** | Coarse particle emergency; visibility/breathing compromised | **IMMEDIATE**: Activate dust suppression (water spray), increase ventilation |
| | **Gas ≥ 176 ppm** | Any | **HAZARDOUS: COMBUSTIBLES EXTREME - IDENTIFY SOURCE NOW** | Combustible gas at critical level; fire/explosion risk | **IMMEDIATE**: Check for welding/cutting/leaks, STOP ALL IGNITION SOURCES |
| | **CO > 30 ppm** | Any | **HAZARDOUS: CO CRITICAL - CHECK MACHINERY/ENGINES** | Carbon monoxide critical; immediate poisoning risk | **IMMEDIATE**: Identify source (generator/exhaust), SHUT DOWN if safe, move upwind |
| **Scenario 2: Pure Dust** | PM2.5: 50-200<br/>PM10: 100-300<br/>Humidity: 36-51% (LOW)<br/>Gas: normal | Tw ≤ 26°C | **HAZARDOUS: WEAR FACE MASK** | High particles + low humidity = genuine dust/excavation hazard | Wear N95/FFP2 mask immediately; reduce work pace |
| **Scenario 4: Fire** | PM2.5: Extreme<br/>Gas: High<br/>Temp: High<br/>**All spiking together** | Any | **HAZARDOUS: EVACUATE AREA NOW** | Multi-sensor fire signature detected; critical danger | **IMMEDIATE EVACUATION - FIRE DETECTED** |
| **Scenario 5: Combustion** | PM2.5: Gradual rise<br/>Gas: Gradual rise<br/>Over 30-60 min pattern<br/>Temp: Slow increase | Tw ≤ 30°C | **HAZARDOUS: CHECK FOR FIRE** | Sustained combustion pattern; developing fire risk | Verify fire/smoke; increase ventilation; prepare evacuation |
| **Scenario 6: VOC/Chemical** | PM2.5: Moderate (22-339)<br/>Gas: HIGH (139-348)<br/>CO: Elevated<br/>PM10: Moderate | Tw ≤ 30°C | **HAZARDOUS: IMPROVE VENTILATION** | High gas + CO regardless of visible PM = chemical/VOC hazard | Improve ventilation immediately; wear respirator; check chemical sources |
| **PM2.5 + PM10 (Dust Storm)** | PM2.5: Caution+ (>51)<br/>PM10: Caution+ (>151)<br/>Humidity: < 95% (not misting) | Tw ≤ 30°C | **HAZARDOUS: DUST STORM** | Both particle sizes elevated simultaneously = genuine dust storm | Wear N95/FFP2; minimize outdoor exposure; shelter if possible |
| **PM2.5 + Gas (Smoke Detected)** | PM2.5: Elevated (>51)<br/>Gas: Elevated (>131)<br/>Temp: Normal/high | Tw ≤ 30°C | **HAZARDOUS: SMOKE DETECTED** | Particles + combustible gases = active combustion/smoke | Investigate fire source; increase ventilation; be ready to evacuate |
| **PM2.5 + CO (Fire Hazard)** | PM2.5: Elevated (>51)<br/>CO: Elevated (>10)<br/>Temp: Rising | Tw ≤ 30°C | **HAZARDOUS: FIRE HAZARD** | Particles + CO signature = fire risk; products of incomplete combustion | Verify fire status; prepare evacuation routes; call emergency if needed |
| **Gas + CO (Chemical Vapors)** | Gas: Elevated (>131)<br/>CO: Elevated (>10)<br/>PM sensors: Any level | Tw ≤ 30°C | **HAZARDOUS: CHEMICAL VAPORS** | High combustible + CO = dangerous vapor/gas accumulation | **MANDATORY EVACUATION** - hazmat situation; call emergency services |
| **3+ Sensors Triggered** | Any combination of 3+ sensors<br/>At caution or higher levels | Any | **HAZARDOUS: MULTI-SENSOR ALERT** | Multiple hazard dimensions present; coordinated danger | **MANDATORY PROTECTIVE ACTION** - Mask/Ventilate/Evacuate per hierarchy |
| **Extreme Heat Stress** | All sensors normal or safe<br/>**Wet-Bulb: > 30°C** | **> 30°C** | **HAZARDOUS: HEAT STRESS CRITICAL** | Body cannot maintain safe core temperature; stop non-essential work | **MANDATORY BREAK** - cease non-essential work; hydrate; cool down |
| **Critical Heat Stress** | Any condition present<br/>**Wet-Bulb: > 35°C** | **> 35°C** | **HAZARDOUS: EXTREME HEAT - EVACUATE** | Survivability limit reached; immediate life threat | **IMMEDIATE EVACUATION** - move to cool environment; emergency medical standby |

| **Decision Rule** | **Trigger** | **Remark** | **Priority** |
|---|---|---|---|
| **CRITICAL: Single Hazardous PM2.5** | PM2.5 > 100 | **HAZARDOUS: EXTREME DUST - USE RESPIRATOR, RELOCATE** | 🔴 HIGHEST |
| **CRITICAL: Single Hazardous PM10** | PM10 > 230 | **HAZARDOUS: PARTICLES CRITICAL - SUPPRESS DUST SOURCE** | 🔴 HIGHEST |
| **CRITICAL: Single Hazardous Gas** | Gas ≥ 176 | **HAZARDOUS: COMBUSTIBLES EXTREME - IDENTIFY SOURCE NOW** | 🔴 HIGHEST |
| **CRITICAL: Single Hazardous CO** | CO > 30 | **HAZARDOUS: CO CRITICAL - CHECK MACHINERY/ENGINES** | 🔴 HIGHEST |
| Dangerous Combination (Smoke) | PM2.5 + Gas both elevated | **HAZARDOUS: SMOKE DETECTED** | 🔴 CRITICAL |
| Dangerous Combination (Fire) | PM2.5 + CO both elevated | **HAZARDOUS: FIRE HAZARD** | 🔴 CRITICAL |
| Dangerous Combination (Vapors) | Gas + CO both elevated | **HAZARDOUS: CHEMICAL VAPORS** | 🔴 CRITICAL |
| Multi-Particle (Dust Storm) | PM2.5 + PM10 both elevated | **HAZARDOUS: DUST STORM** | 🟠 HIGH |
| Multi-Sensor Alert | 3+ sensors at caution/hazardous | **HAZARDOUS: MULTI-SENSOR ALERT** | 🟠 HIGH |
| Extreme Heat Stress | Tw > 30°C | **HAZARDOUS: HEAT STRESS CRITICAL** | 🟠 HIGH |
| Critical Heat Stress | Tw > 35°C | **HAZARDOUS: EXTREME HEAT - EVACUATE** | 🔴 CRITICAL |

---

# 🌡️ WET-BULB TEMPERATURE ESCALATION MATRIX

## Heat Stress Thresholds (Stull 2011 Formula)

### Wet-Bulb Interpretation Table

| Tw Range | LED | Classification | Physiological Impact | Worker Capability |
|----------|-----|---|---|---|
| **Tw ≤ 26°C** | 🟢 GREEN | SAFE | Body cooling effective; sweat evaporates normally | Full work capacity; extended shifts OK |
| **Tw 27-30°C** | 🟡 YELLOW | CAUTION | Heat stress rising; sweat evaporation slowing | Reduced work intensity; more frequent breaks |
| **Tw > 30°C** | 🔴 RED | HAZARDOUS | Body cannot cool; heat exhaustion risk | **Stop non-essential work; mandatory breaks** |
| **Tw > 35°C** | 🔴 RED (BLINK) | CRITICAL | Survivability limit; core body temp uncontrollable | **IMMEDIATE EVACUATION; emergency medical standby** |

### Escalation Logic with Sensors

```
IF Tw ≤ 26°C:
   → Use sensor-based classification (0/1/2)
   
IF Tw 27-30°C:
   → Escalate "Safe" → "Caution"
   → Keep "Caution" → "Caution"
   → Keep "Hazardous" → "Hazardous"
   → Add CAUTION remark: "HEAT STRESS RISING"
   
IF Tw > 30°C:
   → Escalate "Safe" → "Caution"
   → Escalate "Caution" → "Hazardous"
   → Keep "Hazardous" → "Hazardous"
   → Add HAZARDOUS remark: "HEAT STRESS CRITICAL"
   
IF Tw > 35°C:
   → ALWAYS "Hazardous" regardless of sensors
   → Override all other logic
   → Remark: "HAZARDOUS: EXTREME HEAT - EVACUATE"
```

### Example Scenarios

| Temp | Humidity | Tw | Sensors Say | Final Class | Remark |
|---|---|---|---|---|---|
| 25°C | 40% | 14°C | Safe | **Safe** | NORMAL OPERATIONS |
| 25°C | 40% | 14°C | Caution | **Caution** | ELEVATED DUST |
| 28°C | 65% | 23°C | Safe | **Safe** | NORMAL OPERATIONS |
| 28°C | 65% | 23°C | Caution | **Caution** | ELEVATED DUST |
| 32°C | 60% | 27°C | Safe | **Caution** | HEAT STRESS RISING |
| 32°C | 60% | 27°C | Caution | **Hazardous** | HEAT STRESS CRITICAL + ELEVATED DUST |
| 35°C | 70% | 30.5°C | Safe | **Hazardous** | HEAT STRESS CRITICAL |
| 35°C | 70% | 30.5°C | Caution | **Hazardous** | HEAT STRESS CRITICAL + ELEVATED DUST |
| 38°C | 75% | 34°C | Any | **Hazardous** | EXTREME HEAT - EVACUATE |
| 40°C | 80% | 36°C | Any | **Hazardous** | EXTREME HEAT - EVACUATE |

---

# 🔄 COMPLETE DECISION FLOW (Priority Order)

## Step 1: MISTING CHECK (Highest Priority Override)
```
IF Humidity ≥ 95% AND Gas < 100 ppm:
   → CLASS 0 (SAFE)
   → Remark: "SAFE: MISTING DETECTED"
   → STOP - Skip all other checks
```

## Step 2: CRITICAL HAZARDOUS SENSOR CHECK (Life Safety)
```
IF ANY sensor exceeds hazardous threshold:
   IF PM2.5 > 100:
      → CLASS 2 (HAZARDOUS)
      → Remark: "HAZARDOUS: EXTREME DUST - USE RESPIRATOR, RELOCATE"
      → Action: Stop dust work, use HEPA/N95+ mask, move to ventilated area
   
   IF PM10 > 230:
      → CLASS 2 (HAZARDOUS)
      → Remark: "HAZARDOUS: PARTICLES CRITICAL - SUPPRESS DUST SOURCE"
      → Action: Activate dust suppression (water spray), increase ventilation
   
   IF Gas ≥ 176 ppm:
      → CLASS 2 (HAZARDOUS)
      → Remark: "HAZARDOUS: COMBUSTIBLES EXTREME - IDENTIFY SOURCE NOW"
      → Action: Check for welding/cutting/leaks, STOP ALL IGNITION SOURCES
   
   IF CO > 30 ppm:
      → CLASS 2 (HAZARDOUS)
      → Remark: "HAZARDOUS: CO CRITICAL - CHECK MACHINERY/ENGINES"
      → Action: Identify source (generator/exhaust), SHUT DOWN if safe, move upwind
   
   → STOP after first hazardous sensor found
```

## Step 3: DANGEROUS MULTI-SENSOR COMBINATIONS
```
IF (PM2.5 ≥ 51 AND PM10 ≥ 151) AND NOT misting:
   → CLASS 2 (HAZARDOUS)
   → Remark: "HAZARDOUS: DUST STORM"

IF PM2.5 ≥ 51 AND Gas ≥ 131:
   → CLASS 2 (HAZARDOUS)
   → Remark: "HAZARDOUS: SMOKE DETECTED"

IF PM2.5 ≥ 51 AND CO ≥ 10:
   → CLASS 2 (HAZARDOUS)
   → Remark: "HAZARDOUS: FIRE HAZARD"

IF Gas ≥ 131 AND CO ≥ 10:
   → CLASS 2 (HAZARDOUS)
   → Remark: "HAZARDOUS: CHEMICAL VAPORS"

IF 3+ sensors in caution/hazardous range:
   → CLASS 2 (HAZARDOUS)
   → Remark: "HAZARDOUS: MULTI-SENSOR ALERT"
```

## Step 4: HEAT STRESS EVALUATION
```
Compute Wet-Bulb Temperature (Stull 2011)

IF Tw > 35°C:
   → CLASS 2 (HAZARDOUS)
   → Remark: "HAZARDOUS: EXTREME HEAT - EVACUATE"
   → OVERRIDE all sensor readings

IF Tw > 30°C:
   IF Current Class 1 (Caution):
      → ESCALATE to CLASS 2 (HAZARDOUS)
      → Remark: [Previous + "HEAT STRESS CRITICAL"]
   IF Current Class 0 (Safe):
      → ESCALATE to CLASS 1 (CAUTION)
      → Remark: "CAUTION: HEAT STRESS RISING"

IF Tw 27-30°C:
   IF Current Class 0 (Safe):
      → KEEP CLASS 0 but add heat warning
      → Remark: [Sensor safe + "HEAT STRESS RISING"]
```

## Step 5: SINGLE SENSOR CAUTION RANGE
```
IF PM2.5 in 51-100 but no dangerous combos:
   → CLASS 1 (CAUTION)
   → Remark: "CAUTION: ELEVATED DUST"

IF PM10 in 151-230 but no dangerous combos:
   → CLASS 1 (CAUTION)
   → Remark: "CAUTION: COARSE PARTICLES"

IF Gas in 131-175 but no dangerous combos:
   → CLASS 1 (CAUTION)
   → Remark: "CAUTION: COMBUSTIBLES DETECTED"

IF CO in 10-30 but no dangerous combos:
   → CLASS 1 (CAUTION)
   → Remark: "CAUTION: ELEVATED CO"

IF PM10+Gas combo (both in 151-230, 131-175 respectively):
   → CLASS 1 (CAUTION)
   → Remark: "CAUTION: COMBINED HAZARD RISKING"

IF PM10+CO combo (both in 151-230, 10-30 respectively):
   → CLASS 1 (CAUTION)
   → Remark: "CAUTION: CHECK FOR FIRE"
```

## Step 6: DEFAULT SAFE
```
IF all sensors normal AND Tw ≤ 26°C:
   → CLASS 0 (SAFE)
   → Remark: "SAFE: ALL SENSORS NORMAL"
```

---

# 📈 FEATURE IMPORTANCE IN MODEL

| Sensor | Importance | Role in Decision | Training Scenarios |
|--------|-----------|---|---|
| **Gas (MQ-2)** | 21.8% | Primary hazard detection | 4, 5, 6 (smoke/combustion/VOC) |
| **CO (MQ-7)** | 21.4% | Fire/combustion signature | 4, 5, 6 (fire indicators) |
| **PM2.5** | 16.4% | Particulate hazard | 2, 3, 4 (dust/misting/fire) |
| **PM10** | 14.0% | Large particle hazard | 2 (excavation dust) |
| **Wet-Bulb Temp** | ~12% (learned) | Heat stress escalation | 7 (humidity context) |
| **Humidity** | ~8% (via wet-bulb) | Misting detector | 3, 7 |
| **Temperature** | ~6% (via wet-bulb) | Context/heat stress | All scenarios |

---

# 🎯 TRAINING SCENARIOS SUMMARY

| Scenario | Rows | Primary Hazard | Sensor Signature | Output Class | Remark | Key Learning |
|----------|------|---|---|---|---|---|
| 1: Baseline | 622 | None | All normal | 0 | SAFE: NORMAL OPERATIONS | Reference point |
| 2: Pure Dust | 730 | Excavation | High PM, low humidity | 2 | HAZARDOUS: WEAR FACE MASK | Dust pattern recognition |
| 3: Misting ⭐ | 1,054 | False alarm | Extreme PM + extreme humidity + normal gas | 0 | SAFE: MISTING DETECTED | False alarm defense (critical!) |
| 4: Fire | 700 | Emergency | Multi-sensor spike (all sensors extreme) | 2 | HAZARDOUS: EVACUATE AREA NOW | Emergency pattern |
| 5: Combustion | 996 | Developing | Gradual rise (PM + Gas over 30-60 min) | 2 | HAZARDOUS: CHECK FOR FIRE | Trajectory recognition |
| 6: VOC | 804 | Chemical | High Gas + High CO regardless of PM | 2 | HAZARDOUS: IMPROVE VENTILATION | Invisible hazards |
| 7: High Humidity | 673 | None | Normal PM/Gas + elevated humidity | 0 | SAFE: COOL HUMID AIR | Humidity context |
| 8: Field Deploy | 14,989 | Mixed | Real-world variations | Mixed | Dynamic per conditions | Generalization |
| **TOTAL** | **20,568** | — | — | — | — | Complete protocol |

---

# ✅ SENSOR THRESHOLDS REFERENCE

| Sensor | Caution Threshold | Hazardous Threshold | Unit | Standard | Device |
|--------|---|---|---|---|---|
| **PM2.5** | 51-100 | >100 | μg/m³ | DENR/RA 8749 IRR | PMS5003 |
| **PM10** | 151-230 | >230 | μg/m³ | DENR/RA 8749 IRR | PMS5003 |
| **Gas (MQ-2)** | 131-175 | ≥176 | ppm | NIOSH REL/OSHA | MQ-2 Sensor |
| **CO (MQ-7)** | 10-30 | >30 | ppm | OSHA PEL (8-hr) | MQ-7 Sensor |
| **Wet-Bulb Temp** | 27-30 | >30 | °C | Heat Stress | DHT-22 computed |

---

# 🏗️ FIELD DEPLOYMENT SITE DISTRIBUTION (Scenario 8)

| Site | Rows | Location | Description | Conditions |
|------|------|---|---|---|
| Temfacil Inside | 2,945 | Interior workspace | Warehouse-like | Mixed dust + indoor climate |
| Warehouse | 2,943 | Large enclosed | Storage area | Stable temperature, variable dust |
| Outside Temfacil | 3,096 | Outdoor area | Construction site exposure | Weather-dependent, natural variation |
| Fabrication Area | 3,125 | Manufacturing | Equipment-intensive | Machinery exhaust, targeted hazards |
| Active Floor Area | 2,880 | Production zone | High activity | Worker movement, dust generation |
| **Total Field** | **14,989** | — | — | Real-world complexity |

---

**GENERATED:** April 7, 2026  
**BASED ON:** MILES Random Forest Classifier with 8-scenario training protocol  
**INCLUDES:** All 20,568 training rows, 3-class output, dynamic remarks system, wet-bulb escalation logic
