# MILES COMPLETE DECISION TABLE

## All Training Scenarios + Sensor Escalation + Wet-Bulb Temperature

\---

## 🏛️ ARCHITECTURAL DECISION: Dynamic Field Deployment Remarks

**Why Field Deployment (Scenario 8) has NO generic remarks:**

Field deployment data live on construction sites with constantly-changing conditions. Generic remarks like "CONTINUE OPERATIONS" provide no actionable intelligence. Instead:

* **All Field Deployment readings** (Safe, Caution, Hazardous) are classified using the **sensor escalation/combination logic**
* **Remarks are DYNAMIC** - derived from the actual sensor pattern detected (misting, dust storm, smoke, CO spike, heat stress, etc.)
* **Workers see the REASON** - not a generic status, but a specific cause + action (e.g., "HAZARDOUS: COMBUSTION RISK. EQUIP MASKS \& SUSPEND HOT WORKS")
* **Traceability** - links back to training scenarios (if field readings match Scenario 2 pattern = dust, Scenario 4 pattern = fire, etc.)

This ensures Field Deployment readings are fully integrated into the training protocol—no separate "field-only" remarks, just sensor-driven decision logic that applies universally.

\---

# 📊 COMPLETE CLASSIFICATION TABLE

## CLASS 0: SAFE ✅

|Scenario/Condition|Sensor Profile|Wet-Bulb Range|Remark|Reasoning|Worker Action|
|-|-|-|-|-|-|
|**Scenario 1: Baseline**|PM2.5: 3-10<br/>PM10: 5-20<br/>Gas: <40<br/>Humidity: 49-65%|Tw ≤ 26°C|**SAFE: AIR QUALITY OPTIMAL. CONTINUE OPERATIONS**|All sensors in normal range; no hazards detected|Continue normal operations; monitor periodically|
|**Scenario 3: Misting**|PM2.5: 355-816 (HIGH!)<br/>PM10: High<br/>Gas: <40 (normal)<br/>**Humidity: 96-100%**|Tw ≤ 26°C|**SAFE: HIGH HUMIDITY MIST DETECTED. CONTINUE OPERATIONS**|Pattern matching: Extreme PM + Extreme humidity + Normal gas = water droplets, NOT pollution|Extreme PM with extreme humidity indicates mist; water spray is not a health hazard|
|**Scenario 7: High Humidity**|PM2.5: Normal<br/>PM10: Normal<br/>Gas: Normal<br/>Humidity: 60-95%|Tw 27-30°C OK|**SAFE: ELEVATED HUMIDITY ONLY. CONTINUE OPERATIONS WITH HYDRATION**|Elevated humidity alone is not hazardous (aircon condensation, tropical climate)|Normal operations; elevated humidity context recognized; increase hydration|
|**Field Deployment - Dynamic**|All sensors activate sensor escalation/combination logic<br/>Misting detection applied<br/>Wet-bulb escalation applied|Tw ≤ 26°C|**DYNAMIC: From sensor pattern detection**|Field readings classified via sensor escalation logic (NOT generic); remarks based on actual sensor combinations or training patterns detected|Remarks trace to specific causes: misting, dust storm, smoke, CO, heat stress, etc.|

|**Decision Rule**|**Trigger**|**Remark**|
|-|-|-|
|Misting Override (Highest Priority)|Humidity ≥ 95% AND Gas ≤ 40 ppm AND Tw ≤ 35°C|**SAFE: HIGH HUMIDITY MIST DETECTED. CONTINUE OPERATIONS**|
|All Sensors Normal|PM2.5 < 51 AND PM10 < 151 AND Gas < 40 AND CO < 10|**SAFE: AIR QUALITY OPTIMAL. CONTINUE OPERATIONS**|

\---

## CLASS 1: CAUTION ⚠️

|Scenario/Condition|Sensor Profile|Wet-Bulb Range|Remark|Reasoning|Worker Action|
|-|-|-|-|-|-|
|**Single PM2.5 Elevated**|PM2.5: 51-100 μg/m³<br/>Other sensors normal|27-30°C|**CAUTION: FINE DUST DETECTED. EQUIP N95 MASKS**|Dust level rising but not critical; trending toward hazard|Monitor air quality; reduce dust exposure; increase ventilation|
|**Single PM10 Elevated**|PM10: 151-230 μg/m³<br/>Other sensors normal|27-30°C|**CAUTION: HIGH DUST LEVELS. EQUIP N95 MASKS \& DAMPEN THE GROUND**|Coarse particles detected; ventilation recommended|Increase ventilation; monitor work pace; activate dust suppression|
|**Single Gas Elevated**|Gas (MQ-2): 40-62 ppm<br/>Other sensors normal|27-30°C|**CAUTION: TRACE GAS DETECTED. CHECK THE SOURCE**|Potential smoke/VOC at low levels; check for sources|Check for machinery exhaust/fire; increase ventilation|
|**Single CO Elevated**|CO (MQ-7): 10-30 ppm<br/>Other sensors normal|27-30°C|**CAUTION: ELEVATED CO. EQUIP N95 MASKS \& MONITOR EXPOSURE**|Carbon monoxide present; check for combustion sources|Verify fire status; check generator/machinery exhaust|
|**PM10 + Gas (Combination)**|PM10: 151-230<br/>Gas: 40-62<br/>PM2.5: < 51|27-30°C|**CAUTION: DUST \& GAS TRACES. EQUIP N95 MASKS**|Multiple sensor categories triggered; risk escalating|Increase monitoring; reduce work intensity; prepare PPE|
|**PM10 + CO (Combination)**|PM10: 151-230<br/>CO: 10-30<br/>Others moderate|27-30°C|**CAUTION: FINE DUST + CO DETECTED. EQUIP MASKS \& STANDBY**|Coarse particles + carbon monoxide suggests developing fire|Investigate fire potential; increase ventilation; be ready to evacuate|
|**3+ Sensors in Caution Range**|Any 3+ sensors at caution level<br/>But none hazardous|Tw > 30°C (heat stress escal.)|**CAUTION: DECLINING AIR QUALITY. REQUIRE BASIC PPE**|Multiple systems showing stress; coordination effect dangerous|Initiate protective measures; reduce exertion; monitor closely|
|**Heat Stress Escalation**|Sensors: Safe or low caution<br/>**Wet-Bulb: 27-30°C**|**27-30°C**|**CAUTION: HIGH TEMPERATURE. REQUIRE HYDRATION BREAKS**|Heat stress from temperature + humidity climbing; body cooling stressed|Increase hydration frequency; reduce work intensity; take breaks|

|**Decision Rule**|**Trigger**|**Remark**|
|-|-|-|
|Single Caution Sensor|One sensor 51-100 (PM2.5), 151-230 (PM10), 40-62 (Gas), 10-30 (CO)|**CAUTION: \[SENSOR] ELEVATED**|
|Dangerous Combination (Dust+Gas)|PM10 151-230 AND Gas 40-62 ppm|**CAUTION: DUST \& GAS TRACES. EQUIP N95 MASKS**|
|Dangerous Combination (Dust+CO)|PM10 151-230 AND CO 9-30 ppm|**CAUTION: FINE DUST + CO DETECTED. EQUIP MASKS \& STANDBY**|
|Three+ Caution Sensors|3+ sensors in caution ranges|**CAUTION: DECLINING AIR QUALITY. REQUIRE BASIC PPE**|
|Heat Stress Escalation|Tw 27-30°C + any concern|**CAUTION: HIGH TEMPERATURE. REQUIRE HYDRATION BREAKS**|

\---

## CLASS 2: HAZARDOUS 🚨

|Scenario/Condition|Sensor Profile|Wet-Bulb Range|Remark|Reasoning|Worker Action|
|-|-|-|-|-|-|
|**ANY SINGLE HAZARDOUS SENSOR**|**PM2.5 > 100**|Any|**HAZARDOUS: HEAVY FINE DUST. REQUIRE N95 MASKS \& ACTIVATE WATER SPRAY**|Particle level critical; immediate respiratory hazard|**IMMEDIATE**: Stop dust work, use HEPA/N95+ mask, move to ventilated area|
||**PM10 > 230**|Any|**HAZARDOUS: HEAVY COARSE DUST. REQUIRE N95 MASKS \& ACTIVATE WATER SPRAY**|Coarse particle emergency; visibility/breathing compromised|**IMMEDIATE**: Activate dust suppression (water spray), increase ventilation|
||**Gas ≥ 63 ppm**|Any|**HAZARDOUS: CRITICAL GAS LEVELS. SUSPEND ALL WELDING \& HOT WORKS**|Combustible gas at critical level; fire/explosion risk|**IMMEDIATE**: Check for welding/cutting/leaks, STOP ALL IGNITION SOURCES|
||**CO > 30 ppm**|Any|**HAZARDOUS: CRITICAL CO LEVELS. EQUIP RESPIRATORS**|Carbon monoxide critical; immediate poisoning risk|**IMMEDIATE**: Identify source (generator/exhaust), SHUT DOWN if safe, move upwind|
|**Scenario 2: Pure Dust**|PM2.5: 50-200<br/>PM10: 100-300<br/>Humidity: 36-51% (LOW)<br/>Gas: normal|Tw ≤ 26°C|**HAZARDOUS: SEVERE DUST. REQUIRE N95 MASKS \& SUPPRESS DUST SOURCE**|High particles + low humidity = genuine dust/excavation hazard|Wear N95/FFP2 mask immediately; reduce work pace|
|**Scenario 4: Fire**|PM2.5: Extreme<br/>Gas: High<br/>Temp: High<br/>**All spiking together**|Any|**HAZARDOUS: TOXIC ATMOSPHERE. REQUIRE FULL PPE \& SECURE ZONE**|Multi-sensor fire signature detected; critical danger|**IMMEDIATE EVACUATION - FIRE DETECTED**|
|**Scenario 5: Combustion**|PM2.5: Gradual rise<br/>Gas: Gradual rise<br/>Over 30-60 min pattern<br/>Temp: Slow increase|Tw ≤ 30°C|**HAZARDOUS: COMBUSTION RISK. EQUIP MASKS \& SUSPEND HOT WORKS**|Sustained combustion pattern; developing fire risk|Verify fire/smoke; increase ventilation; prepare evacuation|
|**Scenario 6: VOC/Chemical**|PM2.5: Moderate (22-339)<br/>Gas: HIGH (≥63)<br/>CO: Elevated<br/>PM10: Moderate|Tw ≤ 30°C|**HAZARDOUS: POISONOUS GAS. EQUIP RESPIRATORS \& CLEAR THE ZONE**|High gas + CO regardless of visible PM = chemical/VOC hazard|Improve ventilation immediately; wear respirator; check chemical sources|
|**PM2.5 + PM10 (Dust Storm)**|PM2.5: Caution+ (>51)<br/>PM10: Caution+ (>151)<br/>Humidity: < 95% (not misting)|Tw ≤ 30°C|**HAZARDOUS: SEVERE DUST. REQUIRE N95 MASKS \& SUPPRESS DUST SOURCE**|Both particle sizes elevated simultaneously = genuine dust storm|Wear N95/FFP2; minimize outdoor exposure; shelter if possible|
|**PM2.5 + Gas (Smoke Detected)**|PM2.5: Elevated (>51)<br/>Gas: Elevated (≥63)<br/>Temp: Normal/high|Tw ≤ 30°C|**HAZARDOUS: COMBUSTION RISK. EQUIP MASKS \& SUSPEND HOT WORKS**|Particles + combustible gases = active combustion/smoke|Investigate fire source; increase ventilation; be ready to evacuate|
|**PM2.5 + CO (Fire Hazard)**|PM2.5: Elevated (>51)<br/>CO: Elevated (>10)<br/>Temp: Rising|Tw ≤ 30°C|**HAZARDOUS: FINE DUST + CO DETECTED. EQUIP MASKS \& INSPECT FOR FIRE**|Particles + CO signature = fire risk; products of incomplete combustion|Verify fire status; prepare evacuation routes; call emergency if needed|
|**Gas + CO (Chemical Vapors)**|Gas: Elevated (≥63)<br/>CO: Elevated (>10)<br/>PM sensors: Any level|Tw ≤ 30°C|**HAZARDOUS: POISONOUS GAS. EQUIP RESPIRATORS \& CLEAR THE ZONE**|High combustible + CO = dangerous vapor/gas accumulation|**MANDATORY EVACUATION** - hazmat situation; call emergency services|
|**3+ Sensors Triggered**|Any combination of 3+ sensors<br/>At caution or higher levels|Any|**HAZARDOUS: TOXIC ATMOSPHERE. REQUIRE FULL PPE \& SECURE ZONE**|Multiple hazard dimensions present; coordinated danger|**MANDATORY PROTECTIVE ACTION** - Mask/Ventilate/Evacuate per hierarchy|
|**Extreme Heat Stress**|All sensors normal or safe<br/>**Wet-Bulb: > 30°C**|**> 30°C**|**HAZARDOUS: HIGH HEAT INDEX. ROTATE WORKERS \& REQUIRE HYDRATION**|Body cannot maintain safe core temperature; stop non-essential work|**MANDATORY BREAK** - cease non-essential work; hydrate; cool down|
|**Critical Heat Stress**|Any condition present<br/>**Wet-Bulb: > 35°C**|**> 35°C**|**HAZARDOUS: EXTREME HEAT. REQUIRE SHADED REST \& MONITOR WORKERS**|Survivability limit reached; immediate life threat|**IMMEDIATE EVACUATION** - move to cool environment; emergency medical standby|

|**Decision Rule**|**Trigger**|**Remark**|**Priority**|
|-|-|-|-|
|**CRITICAL: Single Hazardous PM2.5**|PM2.5 > 100|**HAZARDOUS: HEAVY FINE DUST. REQUIRE N95 MASKS \& ACTIVATE WATER SPRAY**|🔴 HIGHEST|
|**CRITICAL: Single Hazardous PM10**|PM10 > 230|**HAZARDOUS: HEAVY COARSE DUST. REQUIRE N95 MASKS \& ACTIVATE WATER SPRAY**|🔴 HIGHEST|
|**CRITICAL: Single Hazardous Gas**|Gas ≥ 63|**HAZARDOUS: CRITICAL GAS LEVELS. SUSPEND ALL WELDING \& HOT WORKS**|🔴 HIGHEST|
|**CRITICAL: Single Hazardous CO**|CO > 30|**HAZARDOUS: CRITICAL CO LEVELS. EQUIP RESPIRATORS**|🔴 HIGHEST|
|Dangerous Combination (Smoke)|PM2.5 + Gas both elevated|**HAZARDOUS: COMBUSTION RISK. EQUIP MASKS \& SUSPEND HOT WORKS**|🔴 CRITICAL|
|Dangerous Combination (Fire)|PM2.5 + CO both elevated|**HAZARDOUS: FINE DUST + CO DETECTED. EQUIP MASKS \& INSPECT FOR FIRE**|🔴 CRITICAL|
|Dangerous Combination (Vapors)|Gas + CO both elevated|**HAZARDOUS: POISONOUS GAS. EQUIP RESPIRATORS \& CLEAR THE ZONE**|🔴 CRITICAL|
|Multi-Particle (Dust Storm)|PM2.5 + PM10 both elevated|**HAZARDOUS: SEVERE DUST. REQUIRE N95 MASKS \& SUPPRESS DUST SOURCE**|🟠 HIGH|
|Multi-Sensor Alert|3+ sensors at caution/hazardous|**HAZARDOUS: TOXIC ATMOSPHERE. REQUIRE FULL PPE \& SECURE ZONE**|🟠 HIGH|
|Extreme Heat Stress|Tw > 30°C|**HAZARDOUS: HIGH HEAT INDEX. ROTATE WORKERS \& REQUIRE HYDRATION**|🟠 HIGH|
|Critical Heat Stress|Tw > 35°C|**HAZARDOUS: EXTREME HEAT. REQUIRE SHADED REST \& MONITOR WORKERS**|🔴 CRITICAL|
|---|---|---||
|Single Caution Sensor|One sensor 51-100 (PM2.5), 151-230 (PM10), 40-62 (Gas), 10-30 (CO)|**CAUTION: \[SENSOR] ELEVATED**||
|Dangerous Combination (Non-Hazardous)|PM10+Gas OR PM10+CO at caution levels|**CAUTION: COMBINED HAZARD RISKING**||
|Three+ Caution Sensors|3+ sensors in caution ranges|**CAUTION: DECLINING AIR QUALITY. REQUIRE BASIC PPE**||
|Heat Stress Escalation|Tw 27-30°C + any concern|**CAUTION: HIGH TEMPERATURE. REQUIRE HYDRATION BREAKS**||

\---

## CLASS 2: HAZARDOUS 🚨

|Scenario/Condition|Sensor Profile|Wet-Bulb Range|Remark|Reasoning|Worker Action|
|-|-|-|-|-|-|
|**ANY SINGLE HAZARDOUS SENSOR**|**PM2.5 > 100**|Any|**HAZARDOUS: HEAVY FINE DUST. REQUIRE N95 MASKS \& ACTIVATE WATER SPRAY**|Particle level critical; immediate respiratory hazard|**IMMEDIATE**: Stop dust work, use HEPA/N95+ mask, move to ventilated area|
||**PM10 > 230**|Any|**HAZARDOUS: HEAVY COARSE DUST. REQUIRE N95 MASKS \& ACTIVATE WATER SPRAY**|Coarse particle emergency; visibility/breathing compromised|**IMMEDIATE**: Activate dust suppression (water spray), increase ventilation|
||**Gas ≥ 63 ppm**|Any|**HAZARDOUS: CRITICAL GAS LEVELS. SUSPEND ALL WELDING \& HOT WORKS**|Combustible gas at critical level; fire/explosion risk|**IMMEDIATE**: Check for welding/cutting/leaks, STOP ALL IGNITION SOURCES|
||**CO > 30 ppm**|Any|**HAZARDOUS: CRITICAL CO LEVELS. EQUIP RESPIRATORS**|Carbon monoxide critical; immediate poisoning risk|**IMMEDIATE**: Identify source (generator/exhaust), SHUT DOWN if safe, move upwind|
|**Scenario 2: Pure Dust**|PM2.5: 50-200<br/>PM10: 100-300<br/>Humidity: 36-51% (LOW)<br/>Gas: normal|Tw ≤ 26°C|**HAZARDOUS: SEVERE DUST. REQUIRE N95 MASKS \& SUPPRESS DUST SOURCE**|High particles + low humidity = genuine dust/excavation hazard|Wear N95/FFP2 mask immediately; reduce work pace|
|**Scenario 4: Fire**|PM2.5: Extreme<br/>Gas: High<br/>Temp: High<br/>**All spiking together**|Any|**HAZARDOUS: TOXIC ATMOSPHERE. REQUIRE FULL PPE \& SECURE ZONE**|Multi-sensor fire signature detected; critical danger|**IMMEDIATE EVACUATION - FIRE DETECTED**|
|**Scenario 5: Combustion**|PM2.5: Gradual rise<br/>Gas: Gradual rise<br/>Over 30-60 min pattern<br/>Temp: Slow increase|Tw ≤ 30°C|**HAZARDOUS: COMBUSTION RISK. EQUIP MASKS \& SUSPEND HOT WORKS**|Sustained combustion pattern; developing fire risk|Verify fire/smoke; increase ventilation; prepare evacuation|
|**Scenario 6: VOC/Chemical**|PM2.5: Moderate (22-339)<br/>Gas: HIGH (≥63)<br/>CO: Elevated<br/>PM10: Moderate|Tw ≤ 30°C|**HAZARDOUS: POISONOUS GAS. EQUIP RESPIRATORS \& CLEAR THE ZONE**|High gas + CO regardless of visible PM = chemical/VOC hazard|Improve ventilation immediately; wear respirator; check chemical sources|
|**PM2.5 + PM10 (Dust Storm)**|PM2.5: Caution+ (>51)<br/>PM10: Caution+ (>151)<br/>Humidity: < 95% (not misting)|Tw ≤ 30°C|**HAZARDOUS: SEVERE DUST. REQUIRE N95 MASKS \& SUPPRESS DUST SOURCE**|Both particle sizes elevated simultaneously = genuine dust storm|Wear N95/FFP2; minimize outdoor exposure; shelter if possible|
|**PM2.5 + Gas (Smoke Detected)**|PM2.5: Elevated (>51)<br/>Gas: Elevated (≥63)<br/>Temp: Normal/high|Tw ≤ 30°C|**HAZARDOUS: COMBUSTION RISK. EQUIP MASKS \& SUSPEND HOT WORKS**|Particles + combustible gases = active combustion/smoke|Investigate fire source; increase ventilation; be ready to evacuate|
|**PM2.5 + CO (Fire Hazard)**|PM2.5: Elevated (>51)<br/>CO: Elevated (>10)<br/>Temp: Rising|Tw ≤ 30°C|**HAZARDOUS: FINE DUST + CO DETECTED. EQUIP MASKS \& INSPECT FOR FIRE**|Particles + CO signature = fire risk; products of incomplete combustion|Verify fire status; prepare evacuation routes; call emergency if needed|
|**Gas + CO (Chemical Vapors)**|Gas: Elevated (≥63)<br/>CO: Elevated (>10)<br/>PM sensors: Any level|Tw ≤ 30°C|**HAZARDOUS: POISONOUS GAS. EQUIP RESPIRATORS \& CLEAR THE ZONE**|High combustible + CO = dangerous vapor/gas accumulation|**MANDATORY EVACUATION** - hazmat situation; call emergency services|
|**3+ Sensors Triggered**|Any combination of 3+ sensors<br/>At caution or higher levels|Any|**HAZARDOUS: TOXIC ATMOSPHERE. REQUIRE FULL PPE \& SECURE ZONE**|Multiple hazard dimensions present; coordinated danger|**MANDATORY PROTECTIVE ACTION** - Mask/Ventilate/Evacuate per hierarchy|
|**Extreme Heat Stress**|All sensors normal or safe<br/>**Wet-Bulb: > 30°C**|**> 30°C**|**HAZARDOUS: HIGH HEAT INDEX. ROTATE WORKERS \& REQUIRE HYDRATION**|Body cannot maintain safe core temperature; stop non-essential work|**MANDATORY BREAK** - cease non-essential work; hydrate; cool down|
|**Critical Heat Stress**|Any condition present<br/>**Wet-Bulb: > 35°C**|**> 35°C**|**HAZARDOUS: EXTREME HEAT. REQUIRE SHADED REST \& MONITOR WORKERS**|Survivability limit reached; immediate life threat|**IMMEDIATE EVACUATION** - move to cool environment; emergency medical standby|

|**Decision Rule**|**Trigger**|**Remark**|**Priority**|
|-|-|-|-|
|**CRITICAL: Single Hazardous PM2.5**|PM2.5 > 100|**HAZARDOUS: HEAVY FINE DUST. REQUIRE N95 MASKS \& ACTIVATE WATER SPRAY**|🔴 HIGHEST|
|**CRITICAL: Single Hazardous PM10**|PM10 > 230|**HAZARDOUS: HEAVY COARSE DUST. REQUIRE N95 MASKS \& ACTIVATE WATER SPRAY**|🔴 HIGHEST|
|**CRITICAL: Single Hazardous Gas**|Gas ≥ 63|**HAZARDOUS: CRITICAL GAS LEVELS. SUSPEND ALL WELDING \& HOT WORKS**|🔴 HIGHEST|
|**CRITICAL: Single Hazardous CO**|CO > 30|**HAZARDOUS: CRITICAL CO LEVELS. EQUIP RESPIRATORS**|🔴 HIGHEST|
|Dangerous Combination (Smoke)|PM2.5 + Gas both elevated|**HAZARDOUS: COMBUSTION RISK. EQUIP MASKS \& SUSPEND HOT WORKS**|🔴 CRITICAL|
|Dangerous Combination (Fire)|PM2.5 + CO both elevated|**HAZARDOUS: FINE DUST + CO DETECTED. EQUIP MASKS \& INSPECT FOR FIRE**|🔴 CRITICAL|
|Dangerous Combination (Vapors)|Gas + CO both elevated|**HAZARDOUS: POISONOUS GAS. EQUIP RESPIRATORS \& CLEAR THE ZONE**|🔴 CRITICAL|
|Multi-Particle (Dust Storm)|PM2.5 + PM10 both elevated|**HAZARDOUS: SEVERE DUST. REQUIRE N95 MASKS \& SUPPRESS DUST SOURCE**|🟠 HIGH|
|Multi-Sensor Alert|3+ sensors at caution/hazardous|**HAZARDOUS: TOXIC ATMOSPHERE. REQUIRE FULL PPE \& SECURE ZONE**|🟠 HIGH|
|Extreme Heat Stress|Tw > 30°C|**HAZARDOUS: HIGH HEAT INDEX. ROTATE WORKERS \& REQUIRE HYDRATION**|🟠 HIGH|
|Critical Heat Stress|Tw > 35°C|**HAZARDOUS: EXTREME HEAT. REQUIRE SHADED REST \& MONITOR WORKERS**|🔴 CRITICAL|



\---

# 🌡️ WET-BULB TEMPERATURE ESCALATION MATRIX

## Heat Stress Thresholds (Stull 2011 Formula)

### Wet-Bulb Interpretation Table

|Tw Range|LED|Classification|Physiological Impact|Worker Capability|
|-|-|-|-|-|
|**Tw ≤ 26°C**|🟢 GREEN|SAFE|Body cooling effective; sweat evaporates normally|Full work capacity; extended shifts OK|
|**Tw 27-30°C**|🟡 YELLOW|CAUTION|Heat stress rising; sweat evaporation slowing|Reduced work intensity; more frequent breaks|
|**Tw > 30°C**|🔴 RED|HAZARDOUS|Body cannot cool; heat exhaustion risk|**Stop non-essential work; mandatory breaks**|
|**Tw > 35°C**|🔴 RED (BLINK)|CRITICAL|Survivability limit; core body temp uncontrollable|**IMMEDIATE EVACUATION; emergency medical standby**|

### Escalation Logic with Sensors

```
IF Tw ≤ 26°C:
   → Use sensor-based classification (0/1/2)
   
IF Tw 27-30°C:
   → Escalate "Safe" → "Caution"
   → Keep "Caution" → "Caution"
   → Keep "Hazardous" → "Hazardous"
   → Add CAUTION remark: "HIGH TEMPERATURE. REQUIRE HYDRATION BREAKS"
   
IF Tw > 30°C:
   → Escalate "Safe" → "Caution"
   → Escalate "Caution" → "Hazardous"
   → Keep "Hazardous" → "Hazardous"
   → Add HAZARDOUS remark: "HIGH HEAT INDEX. ROTATE WORKERS \& REQUIRE HYDRATION"
   
IF Tw > 35°C:
   → ALWAYS "Hazardous" regardless of sensors
   → Override all other logic
   → Remark: "HAZARDOUS: EXTREME HEAT. REQUIRE SHADED REST \& MONITOR WORKERS"
```

### Example Scenarios

|Temp|Humidity|Tw|Sensors Say|Final Class|Remark|
|-|-|-|-|-|-|
|25°C|40%|14°C|Safe|**Safe**|SAFE: AIR QUALITY OPTIMAL. CONTINUE OPERATIONS|
|25°C|40%|14°C|Caution|**Caution**|CAUTION: FINE DUST DETECTED. EQUIP N95 MASKS|
|28°C|65%|23°C|Safe|**Safe**|SAFE: AIR QUALITY OPTIMAL. CONTINUE OPERATIONS|
|28°C|65%|23°C|Caution|**Caution**|CAUTION: FINE DUST DETECTED. EQUIP N95 MASKS|
|32°C|60%|27°C|Safe|**Caution**|CAUTION: HIGH TEMPERATURE. REQUIRE HYDRATION BREAKS|
|32°C|60%|27°C|Caution|**Hazardous**|HAZARDOUS: HIGH HEAT INDEX. ROTATE WORKERS \& REQUIRE HYDRATION|
|35°C|70%|30.5°C|Safe|**Hazardous**|HAZARDOUS: HIGH HEAT INDEX. ROTATE WORKERS \& REQUIRE HYDRATION|
|35°C|70%|30.5°C|Caution|**Hazardous**|HAZARDOUS: HIGH HEAT INDEX. ROTATE WORKERS \& REQUIRE HYDRATION|
|38°C|75%|34°C|Any|**Hazardous**|HAZARDOUS: EXTREME HEAT. REQUIRE SHADED REST \& MONITOR WORKERS|
|40°C|80%|36°C|Any|**Hazardous**|HAZARDOUS: EXTREME HEAT. REQUIRE SHADED REST \& MONITOR WORKERS|

\---

# 🔄 COMPLETE DECISION FLOW (Priority Order - Matches Firmware Implementation)

## Step 1: COMPUTE WET-BULB TEMPERATURE (Stull 2011 Formula)

```
Tw = T \* atan(0.151977 \* sqrt(RH + 8.313659)) + atan(T + RH) - atan(RH - 1.676331) 
     + 0.00391838 \* RH^1.5 \* atan(0.023101 \* RH) - 4.686035
```

## Step 2: EXTREME HEAT CHECK (Highest Priority Override)

```
IF Tw > 35°C:
   → FORCE CLASS 2 (HAZARDOUS)
   → Remark: "HAZARDOUS: EXTREME HEAT. REQUIRE SHADED REST \& MONITOR WORKERS"
   → STOP - Override all sensor logic
```

## Step 3: CRITICAL HAZARDOUS SENSOR CHECK + HEAT STRESS ESCALATION

```
Define Hazardous Thresholds:
   PM2.5\_Haz = (pm25 > 100)
   PM10\_Haz = (pm10 > 230)
   Gas\_Haz = (gas >= 63)
   CO\_Haz = (co > 30)

Define Caution Thresholds:
   PM2.5\_Cau = (pm25 >= 51)
   PM10\_Cau = (pm10 >= 151)
   Gas\_Cau = (gas >= 40)
   CO\_Cau = (co >= 10 AND co <= 30)

Count\_Hazard = PM2.5\_Haz + PM10\_Haz + Gas\_Haz + CO\_Haz
Count\_Caution = PM2.5\_Cau + PM10\_Cau + Gas\_Cau + CO\_Cau

IF (Count\_Hazard >= 1):
   → FORCE CLASS 2 (HAZARDOUS)
   
ELSE IF (Count\_Caution >= 1) AND (cls from model == 0):
   → ESCALATE to CLASS 1 (CAUTION)
```

## Step 4: MISTING DETECTION (Override - Prevents False Alarms)

```
IF Humidity >= 95% AND Gas <= 40 ppm AND Tw <= 35°C:
   → FORCE CLASS 0 (SAFE)
   → Remark: "SAFE: HIGH HUMIDITY OR MIST. CONTINUE OPERATIONS"
   → STOP - Misting is NOT a health hazard
```

## Step 5: GENERATE REMARK BASED ON CLASS

### CLASS 2 (HAZARDOUS) - Generated Remarks:

```
IF Tw > 35°C:
   status = "HAZARDOUS: EXTREME HEAT. REQUIRE SHADED REST \& MONITOR WORKERS"
   
ELSE IF Tw > 30°C:
   status = "HAZARDOUS: HIGH HEAT INDEX. ROTATE WORKERS \& REQUIRE HYDRATION"
   
ELSE IF Count\_Hazard >= 3:
   status = "HAZARDOUS: TOXIC ATMOSPHERE. REQUIRE FULL PPE \& SECURE ZONE"
   
ELSE IF Gas\_Haz AND CO\_Haz:
   status = "HAZARDOUS: POISONOUS GAS. EQUIP RESPIRATORS \& CLEAR THE ZONE"
   
ELSE IF PM2.5\_Haz AND CO\_Haz:
   status = "HAZARDOUS: FINE DUST + CO DETECTED. EQUIP MASKS \& INSPECT FOR FIRE"
   
ELSE IF PM2.5\_Haz AND Gas\_Haz:
   status = "HAZARDOUS: COMBUSTION RISK. EQUIP MASKS \& SUSPEND HOT WORKS"
   
ELSE IF PM2.5\_Haz AND PM10\_Haz:
   status = "HAZARDOUS: SEVERE DUST. REQUIRE N95 MASKS \& SUPPRESS DUST SOURCE"
   
ELSE IF CO\_Haz:
   status = "HAZARDOUS: CRITICAL CO LEVELS. EQUIP RESPIRATORS"
   
ELSE IF Gas\_Haz:
   status = "HAZARDOUS: CRITICAL GAS LEVELS. SUSPEND ALL WELDING \& HOT WORKS"
   
ELSE IF PM10\_Haz:
   status = "HAZARDOUS: HEAVY COARSE DUST. REQUIRE N95 MASKS \& ACTIVATE WATER SPRAY"
   
ELSE IF PM2.5\_Haz:
   status = "HAZARDOUS: HEAVY FINE DUST. REQUIRE N95 MASKS \& ACTIVATE WATER SPRAY"
   
ELSE:
   status = "HAZARDOUS: ANOMALY DETECTED, PAUSE OPERATIONS UNTIL STABLE"
```

### CLASS 1 (CAUTION) - Generated Remarks:

```
IF Tw >= 27.0 AND Tw <= 30.0 AND Count\_Caution == 0:
   status = "CAUTION: HIGH TEMPERATURE. REQUIRE HYDRATION BREAKS"
   
ELSE IF Count\_Caution >= 3:
   status = "CAUTION: DECLINING AIR QUALITY. REQUIRE BASIC PPE"
   
ELSE IF PM10\_Cau AND CO\_Cau:
   status = "CAUTION: FINE DUST + CO DETECTED. EQUIP MASKS \& STANDBY"
   
ELSE IF PM10\_Cau AND Gas\_Cau:
   status = "CAUTION: DUST \& GAS TRACES. EQUIP N95 MASKS"
   
ELSE IF CO\_Cau:
   status = "CAUTION: ELEVATED CO. EQUIP N95 MASKS \& MONITOR EXPOSURE"
   
ELSE IF Gas\_Cau:
   status = "CAUTION: TRACE GAS DETECTED. CHECK THE SOURCE"
   
ELSE IF PM10\_Cau:
   status = "CAUTION: HIGH DUST LEVELS. EQUIP N95 MASKS \& DAMPEN THE GROUND"
   
ELSE IF PM2.5\_Cau:
   status = "CAUTION: FINE DUST DETECTED. EQUIP N95 MASKS"
   
ELSE:
   status = "CAUTION: AIR QUALITY DROPPING. EQUIP MASKS \& STANDBY"
```

### CLASS 0 (SAFE) - Generated Remarks:

```
IF Humidity >= 95.0 AND Gas <= 40:
   status = "SAFE: HIGH HUMIDITY OR MIST. CONTINUE OPERATIONS"
   
ELSE IF Humidity > 70.0:
   status = "SAFE: NORMAL CONDITIONS. MAINTAIN STANDARD HYDRATION"
   
ELSE:
   status = "SAFE: AIR QUALITY OPTIMAL. CONTINUE OPERATIONS"
```

\---

# 📈 FEATURE IMPORTANCE IN MODEL

|Sensor|Importance|Role in Decision|Training Scenarios|
|-|-|-|-|
|**Gas (MQ-2)**|21.8%|Primary hazard detection|4, 5, 6 (smoke/combustion/VOC)|
|**CO (MQ-7)**|21.4%|Fire/combustion signature|4, 5, 6 (fire indicators)|
|**PM2.5**|16.4%|Particulate hazard|2, 3, 4 (dust/misting/fire)|
|**PM10**|14.0%|Large particle hazard|2 (excavation dust)|
|**Wet-Bulb Temp**|\~12% (learned)|Heat stress escalation|7 (humidity context)|
|**Humidity**|\~8% (via wet-bulb)|Misting detector|3, 7|
|**Temperature**|\~6% (via wet-bulb)|Context/heat stress|All scenarios|

\---

# 🎯 TRAINING SCENARIOS SUMMARY

|Scenario|Rows|Primary Hazard|Sensor Signature|Output Class|Remark|Key Learning|
|-|-|-|-|-|-|-|
|1: Baseline|622|None|All normal|0|SAFE: AIR QUALITY OPTIMAL. CONTINUE OPERATIONS|Reference point|
|2: Pure Dust|730|Excavation|High PM, low humidity|2|HAZARDOUS: SEVERE DUST. REQUIRE N95 MASKS \& SUPPRESS DUST SOURCE|Dust pattern recognition|
|3: Misting ⭐|1,054|False alarm|Extreme PM + extreme humidity + normal gas|0|SAFE: HIGH HUMIDITY OR MIST. CONTINUE OPERATIONS|False alarm defense (critical!)|
|4: Fire|700|Emergency|Multi-sensor spike (all sensors extreme)|2|HAZARDOUS: TOXIC ATMOSPHERE. REQUIRE FULL PPE \& SECURE ZONE|Emergency pattern|
|5: Combustion|996|Developing|Gradual rise (PM + Gas over 30-60 min)|2|HAZARDOUS: COMBUSTION RISK. EQUIP MASKS \& SUSPEND HOT WORKS|Trajectory recognition|
|6: VOC|804|Chemical|High Gas + High CO regardless of PM|2|HAZARDOUS: POISONOUS GAS. EQUIP RESPIRATORS \& CLEAR THE ZONE|Invisible hazards|
|7: High Humidity|673|None|Normal PM/Gas + elevated humidity|0|SAFE: NORMAL CONDITIONS. MAINTAIN STANDARD HYDRATION|Humidity context|
|→ Remark: "HAZARDOUS: EXTREME HEAT. REQUIRE SHADED REST \& MONITOR WORKERS"|||||||
|→ STOP - Override all sensor logic|||||||

```

## Step 3: CRITICAL HAZARDOUS SENSOR CHECK + HEAT STRESS ESCALATION
```

Define Hazardous Thresholds:
PM2.5\_Haz = (pm25 > 100)
PM10\_Haz = (pm10 > 230)
Gas\_Haz = (gas >= 63)
CO\_Haz = (co > 30)

Define Caution Thresholds:
PM2.5\_Cau = (pm25 >= 51)
PM10\_Cau = (pm10 >= 151)
Gas\_Cau = (gas >= 40)
CO\_Cau = (co >= 10 AND co <= 30)

Count\_Hazard = PM2.5\_Haz + PM10\_Haz + Gas\_Haz + CO\_Haz
Count\_Caution = PM2.5\_Cau + PM10\_Cau + Gas\_Cau + CO\_Cau

IF (Count\_Hazard >= 1) OR (Tw > 30°C AND cls from model indicates hazard):
→ FORCE CLASS 2 (HAZARDOUS)

ELSE IF (Count\_Caution >= 1) AND (cls from model == 0):
→ ESCALATE to CLASS 1 (CAUTION)

```

## Step 4: MISTING DETECTION (Override - Prevents False Alarms)
```

IF Humidity >= 95% AND Gas <= 40 ppm AND Tw <= 35°C:
→ FORCE CLASS 0 (SAFE)
→ Remark: "SAFE: HIGH HUMIDITY OR MIST. CONTINUE OPERATIONS"
→ STOP - Misting is NOT a health hazard

```

## Step 5: GENERATE REMARK BASED ON CLASS

### CLASS 2 (HAZARDOUS) - Generated Remarks:
```

IF Tw > 35°C:
status = "HAZARDOUS: EXTREME HEAT. REQUIRE SHADED REST \& MONITOR WORKERS"

ELSE IF Tw > 30°C:
status = "HAZARDOUS: HIGH HEAT INDEX. ROTATE WORKERS \& REQUIRE HYDRATION"

ELSE IF Count\_Hazard >= 3:
status = "HAZARDOUS: TOXIC ATMOSPHERE. REQUIRE FULL PPE \& SECURE ZONE"

ELSE IF Gas\_Haz AND CO\_Haz:
status = "HAZARDOUS: POISONOUS GAS. EQUIP RESPIRATORS \& CLEAR THE ZONE"

ELSE IF PM2.5\_Haz AND CO\_Haz:
status = "HAZARDOUS: FINE DUST + CO DETECTED. EQUIP MASKS \& INSPECT FOR FIRE"

ELSE IF PM2.5\_Haz AND Gas\_Haz:
status = "HAZARDOUS: COMBUSTION RISK. EQUIP MASKS \& SUSPEND HOT WORKS"

ELSE IF PM2.5\_Haz AND PM10\_Haz:
status = "HAZARDOUS: SEVERE DUST. REQUIRE N95 MASKS \& SUPPRESS DUST SOURCE"

ELSE IF CO\_Haz:
status = "HAZARDOUS: CRITICAL CO LEVELS. EQUIP RESPIRATORS"

ELSE IF Gas\_Haz:
status = "HAZARDOUS: CRITICAL GAS LEVELS. SUSPEND ALL WELDING \& HOT WORKS"

ELSE IF PM10\_Haz:
status = "HAZARDOUS: HEAVY COARSE DUST. REQUIRE N95 MASKS \& ACTIVATE WATER SPRAY"

ELSE IF PM2.5\_Haz:
status = "HAZARDOUS: HEAVY FINE DUST. REQUIRE N95 MASKS \& ACTIVATE WATER SPRAY"

ELSE:
status = "HAZARDOUS: UNSTABLE AIR QUALITY. REQUIRE FULL PPE \& ASSESS AREA"

```

### CLASS 1 (CAUTION) - Generated Remarks:
```

IF Tw >= 27.0 AND Tw <= 30.0 AND Count\_Caution == 0:
status = "CAUTION: HIGH TEMPERATURE. REQUIRE HYDRATION BREAKS"

ELSE IF Count\_Caution >= 3:
status = "CAUTION: DECLINING AIR QUALITY. REQUIRE BASIC PPE"

ELSE IF PM10\_Cau AND CO\_Cau:
status = "CAUTION: FINE DUST + CO DETECTED. EQUIP MASKS \& STANDBY"

ELSE IF PM10\_Cau AND Gas\_Cau:
status = "CAUTION: DUST \& GAS TRACES. EQUIP N95 MASKS"

ELSE IF CO\_Cau:
status = "CAUTION: ELEVATED CO. EQUIP N95 MASKS \& MONITOR EXPOSURE"

ELSE IF Gas\_Cau:
status = "CAUTION: TRACE GAS DETECTED. CHECK THE SOURCE"

ELSE IF PM10\_Cau:
status = "CAUTION: HIGH DUST LEVELS. EQUIP N95 MASKS \& DAMPEN THE GROUND"

ELSE IF PM2.5\_Cau:
status = "CAUTION: FINE DUST DETECTED. EQUIP N95 MASKS"

ELSE:
status = "CAUTION: AIR QUALITY DROPPING. EQUIP MASKS \& STANDBY"

```

### CLASS 0 (SAFE) - Generated Remarks:
```

IF Humidity >= 95.0 AND Gas <= 40:
status = "SAFE: HIGH HUMIDITY OR MIST. CONTINUE OPERATIONS"
note = "Extreme PM with extreme humidity indicates mist"

ELSE IF Humidity > 70.0:
status = "SAFE: NORMAL CONDITIONS. MAINTAIN STANDARD HYDRATION"
note = "Elevated humidity alone is not a pollutant hazard"

ELSE:
status = "SAFE: AIR QUALITY OPTIMAL. CONTINUE OPERATIONS"
note = "All sensors normal"

```

---

# 📈 FEATURE IMPORTANCE IN MODEL

| Sensor | Importance | Role in Decision | Training Scenarios |
|--------|-----------|---|---|
| \*\*Gas (MQ-2)\*\* | 21.8% | Primary hazard detection | 4, 5, 6 (smoke/combustion/VOC) |
| \*\*CO (MQ-7)\*\* | 21.4% | Fire/combustion signature | 4, 5, 6 (fire indicators) |
| \*\*PM2.5\*\* | 16.4% | Particulate hazard | 2, 3, 4 (dust/misting/fire) |
| \*\*PM10\*\* | 14.0% | Large particle hazard | 2 (excavation dust) |
| \*\*Wet-Bulb Temp\*\* | \~12% (learned) | Heat stress escalation | 7 (humidity context) |
| \*\*Humidity\*\* | \~8% (via wet-bulb) | Misting detector | 3, 7 |
| \*\*Temperature\*\* | \~6% (via wet-bulb) | Context/heat stress | All scenarios |

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
| 7: High Humidity | 673 | None | Normal PM/Gas + elevated humidity | 0 | SAFE: NORMAL CONDITIONS. MAINTAIN STANDARD HYDRATION | Humidity context |
| 8: Field Deploy | 14,989 | Mixed | Real-world variations | Mixed | Dynamic per conditions | Generalization |
| \*\*TOTAL\*\* | \*\*20,568\*\* | — | — | — | — | Complete protocol |

---

# ✅ SENSOR THRESHOLDS REFERENCE

| Sensor | Caution Threshold | Hazardous Threshold | Unit | Standard | Device |
|--------|---|---|---|---|---|
| \*\*PM2.5\*\* | 51-100 | >100 | μg/m³ | DENR/RA 8749 IRR | PMS5003 |
| \*\*PM10\*\* | 151-230 | >230 | μg/m³ | DENR/RA 8749 IRR | PMS5003 |
| \*\*Gas (MQ-2)\*\* | 40-62 | ≥63 | ppm | Construction Site Safety | MQ-2 Sensor |
| \*\*CO (MQ-7)\*\* | 10-30 | >30 | ppm | OSHA PEL (8-hr) | MQ-7 Sensor |
| \*\*Wet-Bulb Temp\*\* | 27-30 | >30 | °C | Heat Stress | DHT-22 computed |

---

# 🏗️ FIELD DEPLOYMENT SITE DISTRIBUTION (Scenario 8)

| Site | Rows | Location | Description | Conditions |
|------|------|---|---|---|
| Temfacil Inside | 2,945 | Interior workspace | Warehouse-like | Mixed dust + indoor climate |
| Warehouse | 2,943 | Large enclosed | Storage area | Stable temperature, variable dust |
| Outside Temfacil | 3,096 | Outdoor area | Construction site exposure | Weather-dependent, natural variation |
| Fabrication Area | 3,125 | Manufacturing | Equipment-intensive | Machinery exhaust, targeted hazards |
| Active Floor Area | 2,880 | Production zone | High activity | Worker movement, dust generation |
| \*\*Total Field\*\* | \*\*14,989\*\* | — | — | Real-world complexity |

---

\*\*GENERATED:\*\* May 25, 2026  
\*\*UPDATED:\*\* Synchronized with firmware implementation (esp32\_embedded\_ml.ino v11.5)  
\*\*BASED ON:\*\* MILES Random Forest Classifier with 8-scenario training protocol  
\*\*FIRMWARE VERSION:\*\* Calibration v3.0 (2026-05-25)  
\*\*INCLUDES:\*\* All 20,568 training rows, 3-class output, dynamic remarks system (23+ combinations), wet-bulb escalation logic, firmware-validated decision rules

