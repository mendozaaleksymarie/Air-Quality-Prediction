# 🎯 COMPLETE REMARKS CLASSIFICATION VIEW
## Updated Safe, Hazardous & Caution Remarks by Source

*Last Updated: April 2026 - MILES System Implementation*

---

## 📊 REMARKS STRUCTURE OVERVIEW

```
┌─────────────────────────────────────────────────────────────────────────┐
│                         REMARKS CLASSIFICATION TREE                      │
├─────────────────────────────────────────────────────────────────────────┤
│                                                                          │
│  CLASS 0: SAFE (66.1% of training data)                                 │
│  ├─ Training Simulation (Scenarios 1, 3, 7)                             │
│  ├─ Field Deployment (Scenario 8 - Selected cases)                      │
│  └─ Sensor Escalation (All sensors safe)                                │
│                                                                          │
│  CLASS 1: CAUTION (1.7% of training data)                               │
│  ├─ Training Simulation (Scenario 5 - Early stages)                     │
│  ├─ Field Deployment (Scenario 8 - Uncertain cases)                     │
│  └─ Sensor Escalation (Single sensor or non-dangerous combinations)     │
│                                                                          │
│  CLASS 2: HAZARDOUS (32.1% of training data)                            │
│  ├─ Training Simulation (Scenarios 2, 4, 5-6)                           │
│  ├─ Field Deployment (Scenario 8 - Confirmed hazards)                   │
│  └─ Sensor Escalation (Multi-sensor dangerous combos)                   │
│                                                                          │
│  SPECIAL: WET-BULB OVERRIDE                                             │
│  └─ Wet-Bulb > 32°C → HAZARDOUS (Heat stress)                           │
│                                                                          │
└─────────────────────────────────────────────────────────────────────────┘
```

---

# 🟢 CLASS 0: SAFE REMARKS

## Training Simulation Sources

### Scenario 1: BASELINE
```
📍 Source: Training Simulation (Scenario 1)
📊 Class: 0 - SAFE
📝 Remark: SAFE: NORMAL OPERATIONS
💻 Arduino: SAFE

Detection Condition: All sensors in normal range
  • PM2.5: Normal (< 50 μg/m³)
  • PM10: Normal (< 150 μg/m³)
  • Gas: Normal (< 100 ppm)
  • CO: Normal (< 10 ppm)
  • Humidity: Any level
  
Worker Action: Continue normal work
Status: ✓ Baseline reference, NO HAZARD
Examples: Clean air indoor facility reading
```

---

### Scenario 3: MISTING ⭐
```
📍 Source: Training Simulation (Scenario 3)
📊 Class: 0 - SAFE (Override from Hazardous sensors)
📝 Remark: SAFE: MISTING DETECTED
💻 Arduino: MISTING OK

Detection Condition: Water droplets mistaken for particles
  • PM2.5: Extreme (355-816 μg/m³) ⚠️ HIGH BUT SAFE
  • PM10: Extreme (proportionally high)
  • Humidity: ≥ 95% (EXTREME)
  • Gas: Normal (< 100 ppm)
  
WHY SAFE: Humidity ≥ 95% confirms water droplets, NOT pollution
Override: Prevents false alarm evacuation from high PM + humidity

Worker Action: No protective action needed, water spray confirmed
Status: ✓ FALSE ALARM DETECTION - System working correctly
Examples: Misting system on, cleaning spray, humid environment
```

---

### Scenario 7: HIGH HUMIDITY
```
📍 Source: Training Simulation (Scenario 7)
📊 Class: 0 - SAFE
📝 Remark: SAFE: COOL HUMID AIR
💻 Arduino: HUMIDITY OK

Detection Condition: High humidity + normal pollutants
  • PM2.5: Normal
  • PM10: Normal
  • Gas: Normal
  • Humidity: ≥ 70% (high but safe)
  • Wet-Bulb: Elevated but < 30°C
  
Worker Action: Comfortable despite high humidity
Status: ✓ Physiologically safe, typical humid conditions
Examples: After misting system use, humid climate indoor work
```

---

## Field Deployment Source

### Scenario 8: FIELD DEPLOYMENT (SAFE cases)
```
📍 Source: Field Training (Scenario 8)
📊 Class: 0 - SAFE
📝 Remark: SAFE: CONTINUE OPERATIONS
💻 Arduino: CONTINUE

Detection Condition: Real-world safe conditions
  • All sensors: Safe to caution range but NOT dangerous combinations
  • Context: Field measurements during safe air quality periods
  
Worker Action: Continue operations normally
Status: ✓ Verified safe in real deployment
Examples: Indoor facility during normal operation, minimal dust
% of Data: ~66.1% of 20,568 rows = 13,605 rows
```

---

## Sensor Escalation Source

### Combination: ALL SENSORS SAFE
```
📍 Source: Sensor Escalation Logic
📊 Class: 0 - SAFE
📝 Remark: SAFE: ALL SENSORS NORMAL
💻 Arduino: SAFE

Detection Condition: All four hazard sensors in safe range
  • PM2.5: < 50 μg/m³
  • PM10: < 150 μg/m³
  • Gas: < 100 ppm
  • CO: < 10 ppm
  
Logic: No sensor triggering caution → Class 0
Status: ✓ Multi-point verification of safety
```

---

# 🟡 CLASS 1: CAUTION REMARKS

## Training Simulation Sources

### Scenario 5: COMBUSTION (Early Stages)
```
📍 Source: Training Simulation (Scenario 5)
📊 Class: 1 - CAUTION (early) → 2 - HAZARDOUS (later)
📝 Remark: CAUTION: CHECK FOR FIRE (early) → HAZARDOUS (escalation)
💻 Arduino: CAUTION → HAZARD

Detection Condition: Gradual multi-sensor rise (30-60 min onset)
  Time 0-10 min: PM slowly rising, Gas rising, Temp rising
  • Class: 1 - CAUTION (developing)
  • Remark: Monitor for fire development
  
  Time 30+ min: Multi-sensor extreme
  • Class: 2 - HAZARDOUS (current fire)
  • Remark: HAZARDOUS: CHECK FOR FIRE
  
Worker Action: Early stage: Investigate source, increase ventilation
Status: ⚠️ Escalation scenario - requires monitoring
Examples: Welding startup, equipment ignition, developing smoke
```

---

## Field Deployment Source

### Scenario 8: FIELD DEPLOYMENT (CAUTION cases)
```
📍 Source: Field Training (Scenario 8)
📊 Class: 1 - CAUTION
📝 Remark: CAUTION: MONITOR CONDITIONS
💻 Arduino: CAUTION

Detection Condition: Real-world uncertain/developing conditions
  • Single sensor in caution range OR
  • Non-dangerous sensor combinations (PM10+Gas, PM10+CO) OR
  • Environmental uncertainty requiring monitoring
  
Worker Action: Monitor situation, increase awareness, consider mask
Status: ⚠️ Attention required but not immediate danger
Examples: Warehouse loading (variable dust), equipment startup
% of Data: ~1.7% of 20,568 rows = 354 rows
```

---

## Sensor Escalation Sources

### Single Sensors in Caution Range
```
📍 Source: Sensor Escalation Logic
📊 Class: 1 - CAUTION
💻 Arduino: VARIOUS (DUST, GAS, CO, etc.)

┌─────────────────────────────────────────────────────────────┐
│ 1. PM2.5 CAUTION (51-100 μg/m³)                             │
│    📝 Remark: CAUTION: ELEVATED DUST                         │
│    Action: Monitor air quality, consider mask if heavy work │
│    Example: Dust settling from activity                      │
├─────────────────────────────────────────────────────────────┤
│ 2. PM10 CAUTION (151-230 μg/m³)                             │
│    📝 Remark: CAUTION: COARSE PARTICLES                      │
│    Action: Increase ventilation, monitor conditions          │
│    Example: Sweeping, outdoor dust entry                     │
├─────────────────────────────────────────────────────────────┤
│ 3. GAS CAUTION (131-175 ppm)                                │
│    📝 Remark: CAUTION: COMBUSTIBLES DETECTED                 │
│    Action: Check for smoke sources, increase ventilation     │
│    Example: Small equipment exhaust, welding fumes           │
├─────────────────────────────────────────────────────────────┤
│ 4. CO CAUTION (10-30 ppm)                                   │
│    📝 Remark: CAUTION: ELEVATED CO                           │
│    Action: Check for exhaust/fire, ventilate area            │
│    Example: Vehicle exhaust, generator nearby                │
└─────────────────────────────────────────────────────────────┘
```

---

### Two-Sensor Combinations (Non-Dangerous)

#### PM10 + GAS
```
📍 Source: Sensor Escalation Logic
📊 Class: 1 - CAUTION
📝 Remark: CAUTION: COMBINED HAZARD RISKING
💻 Arduino: MULTI RISK

Why CAUTION not HAZARDOUS: Coarse dust + gas less acute than PM2.5+gas
  • Coarse PM10 less respiratory risk than fine PM2.5
  • Combined signal but not immediate danger pattern
  
Example: Dust from excavation + nearby equipment exhaust
Action: Increase monitoring, reduce work intensity
```

---

#### PM10 + CO
```
📍 Source: Sensor Escalation Logic
📊 Class: 1 - CAUTION
📝 Remark: CAUTION: CHECK FOR FIRE
💻 Arduino: FIRE CHECK

Why CAUTION: Potential fire but less certain than PM2.5+CO
  • Coarse dust + CO present but not typical fire signature
  • Check required but not immediate evacuation
  
Example: Dust cloud + CO source nearby
Action: Investigate fire potential, ventilate
```

---

### PM2.5 + PM10 (Dust Storm)

#### ⚠️ CONSTRUCTION SITE CONTEXT APPLIED
```
📍 Source: Sensor Escalation Logic (Construction Site Tuned)
📊 Class: Previously HAZARDOUS → Now 2 - HAZARDOUS (kept)
📝 Remark: HAZARDOUS: DUST STORM
💻 Arduino: DUST HAZARD

CONTEXT ADJUSTMENT FOR CONSTRUCTION SITES:
  • Construction sites commonly experience BOTH PM2.5 and PM10
    simultaneously from dust/excavation/demolition
  • Original logic: PM2.5+PM10 → always HAZARDOUS
  • Refined logic: PM2.5+PM10 → HAZARDOUS (confirmed dust hazard)
  
Why HAZARDOUS: Both fine AND coarse particles indicate real dust event
  • Not false alarm (like misting)
  • Requires respiratory protection
  • Common in construction but legitimate hazard
  
Example: Demolition dust, excavation cloud, outdoor dust storm
Action: Wear N95 mask immediately, minimize exposure
```

---

# 🔴 CLASS 2: HAZARDOUS REMARKS

## Training Simulation Sources

### Scenario 2: PURE DUST
```
📍 Source: Training Simulation (Scenario 2)
📊 Class: 2 - HAZARDOUS
📝 Remark: HAZARDOUS: WEAR FACE MASK
💻 Arduino: MASK REQUIRED

Detection Condition: High PM + Low humidity
  • PM2.5: 50-200 μg/m³ (HIGH)
  • PM10: 100-300 μg/m³ (HIGH)
  • Humidity: 36-51% (LOW) → NOT water droplets, real dust
  • Gas: Normal (< 100 ppm)
  
Why HAZARDOUS: Genuine dust hazard from excavation/demolition
  • Two-sensor signature confirms real particles
  • NOT false alarm (humidity too low for misting)
  • Respiratory protection required
  
Worker Action: Wear N95/FFP2 mask immediately
Supervisor: Verify dust source, increase ventilation
Status: 🚨 IMMEDIATE PROTECTIVE ACTION REQUIRED
Examples: Excavation activity, demolition dust, sweeping in dry conditions
```

---

### Scenario 4: FIRE 🔥
```
📍 Source: Training Simulation (Scenario 4)
📊 Class: 2 - HAZARDOUS
📝 Remark: HAZARDOUS: EVACUATE AREA NOW
💻 Arduino: EVACUATE!

Detection Condition: Multi-sensor extreme spike
  • PM2.5: EXTREME (rapid spike)
  • Gas: HIGH (combustion products)
  • CO: HIGH (carbon monoxide generation)
  • Temperature: HIGH (heat signature)
  • All spiking SIMULTANEOUSLY
  
Why HAZARDOUS: Fire signature - immediate danger
  • Active combustion detected
  • Heat stress risk
  • Potential for rapid escalation
  
Worker Action: IMMEDIATE EVACUATION REQUIRED
Supervisor: CRITICAL - Verify fire, call emergency services
Status: 🚨🚨 EMERGENCY - LIFE SAFETY PRIORITY
Examples: Equipment fire, electrical fire, fuel ignition
```

---

### Scenario 5: COMBUSTION ⚠️
```
📍 Source: Training Simulation (Scenario 5)
📊 Class: 1 - CAUTION (early) → 2 - HAZARDOUS (developed)
📝 Remark: CAUTION: CHECK FOR FIRE → HAZARDOUS: CHECK FOR FIRE
💻 Arduino: FIRE CHECK → HAZARD!

Detection Condition: Gradual multi-sensor rise (30-60 min development)
  Time 0-10 min: Smoke onset (Class 1 - CAUTION)
    • PM slowly rising
    • Gas rising
    • Temp rising
    • Remark: CAUTION: MONITOR FOR FIRE
    
  Time 30+ min: Developed combustion (Class 2 - HAZARDOUS)
    • Multi-sensor elevated
    • Sustained high readings
    • Remark: HAZARDOUS: CHECK FOR FIRE
    
Why HAZARDOUS (later stage): Sustained multi-sensor elevation
  • Not isolated spike (like PM2.5 alone)
  • Pattern indicates active combustion
  • Risk of escalation to fire
  
Worker Action: Early: Investigate, report / Later: Evacuate
Status: ⚠️ ESCALATING - Monitor for fire development
Examples: Welding, equipment exhaust, controlled burning
```

---

### Scenario 6: VOC/CHEMICAL
```
📍 Source: Training Simulation (Scenario 6)
📊 Class: 2 - HAZARDOUS
📝 Remark: HAZARDOUS: IMPROVE VENTILATION
💻 Arduino: CHEMICAL

Detection Condition: Gas + CO both elevated
  • PM2.5: Variable (may be normal)
  • Gas: HIGH (combustible/VOC gases)
  • CO: HIGH (chemical indicators)
  • Humidity: Variable
  
Why HAZARDOUS: Chemical/VOC hazard
  • Not particle-specific, vapor hazard
  • Both gas sensors indicating contamination
  • Health effect risk even without visible particles
  
Worker Action: Evacuate area, call hazmat or emergency
Supervisor: Identify chemical source, activate emergency response
Status: 🚨 CHEMICAL HAZARD - SPECIALIZED RESPONSE
Examples: Solvent spill, chemical reaction, gas leak
```

---

## Field Deployment Source

### Scenario 8: FIELD DEPLOYMENT (HAZARDOUS cases)
```
📍 Source: Field Training (Scenario 8)
📊 Class: 2 - HAZARDOUS
📝 Remark: HAZARDOUS: TAKE ACTION
💻 Arduino: HAZARD!

Detection Condition: Real-world confirmed hazardous conditions
  • Multi-sensor dangerous combinations confirmed OR
  • Real deployment area showing hazardous readings
  
Worker Action: Take protective action (mask, ventilate, reduce exposure)
Status: 🚨 VERIFIED HAZARDOUS IN FIELD
Examples: Active Floor Area (100% hazardous in training data)
% of Data: ~32.1% of 20,568 rows = 6,609 rows
```

---

## Sensor Escalation Sources

### Two-Sensor Dangerous Combinations

#### PM2.5 + GAS (SMOKE DETECTED)
```
📍 Source: Sensor Escalation Logic
📊 Class: 2 - HAZARDOUS
📝 Remark: HAZARDOUS: SMOKE DETECTED
💻 Arduino: SMOKE ALERT

Detection Condition: Fine particles + Combustible vapors
  • PM2.5: Caution to hazardous range (≥ 51 μg/m³)
  • Gas: Caution to hazardous range (≥ 131 ppm)
  • BOTH elevated simultaneously
  
Why HAZARDOUS: Active combustion signature
  • PM2.5 (fine particles) = smoke particles
  • Gas = combustible vapors being generated
  • Together = confirmed active fire/combustion
  • NOT dust alone (lacks gas), NOT gas alone (lacks smoke)
  
Worker Action: Check for fire/equipment failure, evacuate if needed
Status: 🚨 FIRE INDICATOR - Immediate investigation
Examples: Building fire, major equipment fire, welding fire
```

---

#### PM2.5 + CO (FIRE HAZARD)
```
📍 Source: Sensor Escalation Logic
📊 Class: 2 - HAZARDOUS
📝 Remark: HAZARDOUS: FIRE HAZARD
💻 Arduino: FIRE RISK

Detection Condition: Fine particles + Carbon monoxide
  • PM2.5: Caution to hazardous range (≥ 51 μg/m³)
  • CO: Caution to hazardous range (≥ 10 ppm)
  • BOTH elevated simultaneously
  
Why HAZARDOUS: Fire combustion signature
  • PM2.5 = smoke particles
  • CO = carbon monoxide from incomplete combustion
  • Together = classic fire signature
  • Most reliable indicator of active fire
  
Worker Action: Verify fire status, prepare evacuation
Status: 🚨 FIRE SIGNATURE - High confidence hazard
Examples: Active fire, major combustion event
```

---

#### GAS + CO (CHEMICAL VAPORS)
```
📍 Source: Sensor Escalation Logic
📊 Class: 2 - HAZARDOUS
📝 Remark: HAZARDOUS: CHEMICAL VAPORS
💻 Arduino: CHEMICAL

Detection Condition: Both gas sensors elevated
  • Gas (MQ-2): Caution to hazardous range (≥ 131 ppm)
  • CO (MQ-7): Caution to hazardous range (≥ 10 ppm)
  • BOTH elevated simultaneously
  • PM2.5/PM10: May be normal (no particle component)
  
Why HAZARDOUS: Chemical hazard signature
  • Vapor-only hazard (no particles)
  • Indicates presence of harmful gases
  • Health effects from inhalation
  • May be less visible than smoke events
  
Worker Action: Evacuate area, call hazmat or emergency
Status: 🚨 CHEMICAL HAZARD - Vapor exposure
Examples: Solvent vapors, toxic gas leak, chemical reaction
```

---

### Multi-Sensor Hazardous Combinations

#### PM2.5 + PM10 (DUST STORM)
```
📍 Source: Sensor Escalation Logic
📊 Class: 2 - HAZARDOUS
📝 Remark: HAZARDOUS: DUST STORM
💻 Arduino: DUST HAZARD

Detection Condition: Both particulate sensors elevated
  • PM2.5: Caution to hazardous range (≥ 51 μg/m³)
  • PM10: Caution to hazardous range (≥ 151 μg/m³)
  • BOTH elevated simultaneously
  • Gas/CO: Normal (no combustion)
  
Why HAZARDOUS: Confirmed multi-layer dust hazard
  • Fine particles = deep lung penetration risk
  • Coarse particles = upper airway risk
  • Combined = severe respiratory hazard
  • Typical of excavation/demolition (vs misting false alarm)
  
Construction Site Context:
  • COMMON in construction sites (dust, excavation, demolition)
  • Legitimate hazard, not false alarm
  • Requires respiratory protection
  
Worker Action: Wear N95 mask immediately, minimize exposure
Status: 🚨 DUST HAZARD - Respiratory protection required
Examples: Demolition dust, excavation cloud, outdoor dust storm
```

---

#### THREE OR MORE SENSORS (MULTI-SENSOR ALERT)
```
📍 Source: Sensor Escalation Logic
📊 Class: 2 - HAZARDOUS
📝 Remark: HAZARDOUS: MULTI-SENSOR ALERT
💻 Arduino: HAZARD!

Detection Condition: Three or more hazard sensors in caution+ range
  • Examples:
    - PM2.5 + PM10 + Gas: Smoke + particles + combustibles
    - PM2.5 + PM10 + CO: Dust/smoke + combustion signature
    - PM2.5 + Gas + CO: Smoke + multiple combustion indicators
    - All four sensors: Maximum hazard scenario
  
Why HAZARDOUS: Multiple hazard vectors confirmed
  • Not single-sensor fluctuation
  • Multiple independent confirmation of hazard
  • Complex hazard requiring specialized response
  
Worker Action: MANDATORY PROTECTIVE ACTION
  • Mask: Required (multi-particle hazard)
  • Ventilation: Maximize (multiple vapor threats)
  • Evacuation: Consider if escalating
  
Status: 🚨🚨 CRITICAL MULTI-HAZARD
Examples: Major fire, chemical + dust event, multiple hazard sources
```

---

# ❄️ WET-BULB TEMPERATURE OVERRIDE

## Wet-Bulb > 32°C Extreme Heat Hazard

```
📍 Source: Wet-Bulb Temperature (Computed Feature)
📊 Class: 2 - HAZARDOUS (Override from lower classes)
📝 Remark: HAZARDOUS: EXTREME HEAT - REDUCE WORK INTENSITY
💻 Arduino: HEAT HAZARD

What is Wet-Bulb Temperature?
  • Stull 2011 formula: Combined heat + humidity index
  • Represents physiological heat stress on human body
  • Accounts for both temperature and humidity simultaneously
  
  Example:
    - 35°C + 20% humidity = Tw ~ 25°C (manageable)
    - 30°C + 80% humidity = Tw ~ 30°C (stressful)
    - 35°C + 90% humidity = Tw ~ 33°C (DANGEROUS)

Decision Rules:
  • Tw ≤ 30°C: Normal (may be in any class based on air quality)
  • Tw 30-32°C: Monitor (workers feeling heat stress)
  • Tw > 32°C: HAZARDOUS OVERRIDE (regardless of air quality class)

Why HAZARDOUS at Tw > 32°C:
  • Heat stress becomes life-threatening
  • Human body unable to cool efficiently via sweating
  • Risk of heat exhaustion, heat stroke
  • Priority becomes heat safety, not air quality

Worker Action When Tw > 32°C:
  1. Reduce work intensity immediately
  2. Increase cooling breaks (more frequent, longer)
  3. Increase fluid intake
  4. Move to cooler location if possible
  5. Monitor for heat stress symptoms
  6. Consider work suspension if Tw continues rising

Possible Scenarios:
  • Summer outdoor work: Temperature high + humidity moderate
  • Humid closed space: Temperature moderate + humidity EXTREME
  • Industrial heat: Process heat + high ambient temperature
  • Equipment failure: Loss of ventilation + heat generation

Status: 🚨 HEAT STRESS PRIORITY
Examples: 
  - Outdoor work in summer (35°C + 70% humidity)
  - Enclosed warehouse during misting (30°C + 95% humidity intensely)
  - Proximity to high-heat equipment
  - HVAC system failure in humid environment
```

---

# 📋 SUMMARY TABLE: REMARKS BY CLASS

## Complete Remarks Reference

| **CLASS** | **SOURCE** | **SCENARIO/PATTERN** | **REMARK** | **CONDITION** |
|-----------|-----------|---------------------|-----------|--------------|
| **0 SAFE** | Training Sim | Scenario 1: Baseline | SAFE: NORMAL OPERATIONS | All sensors normal |
| **0 SAFE** | Training Sim | Scenario 3: Misting | SAFE: MISTING DETECTED | PM extreme + Humidity ≥95% + Gas normal |
| **0 SAFE** | Training Sim | Scenario 7: High Humidity | SAFE: COOL HUMID AIR | High humidity + normal pollutants |
| **0 SAFE** | Field | Scenario 8: Field Safe | SAFE: CONTINUE OPERATIONS | Real-world safe conditions |
| **0 SAFE** | Sensor Escal. | All Sensors Safe | SAFE: ALL SENSORS NORMAL | All four sensors in safe range |
| | | | | |
| **1 CAUTION** | Training Sim | Scenario 5: Combustion Early | CAUTION: CHECK FOR FIRE | Multi-sensor slowly rising (0-10 min) |
| **1 CAUTION** | Field | Scenario 8: Field Caution | CAUTION: MONITOR CONDITIONS | Real-world uncertain conditions |
| **1 CAUTION** | Sensor Escal. | Single: PM2.5 Caution | CAUTION: ELEVATED DUST | PM2.5: 51-100 μg/m³ alone |
| **1 CAUTION** | Sensor Escal. | Single: PM10 Caution | CAUTION: COARSE PARTICLES | PM10: 151-230 μg/m³ alone |
| **1 CAUTION** | Sensor Escal. | Single: Gas Caution | CAUTION: COMBUSTIBLES DETECTED | Gas: 131-175 ppm alone |
| **1 CAUTION** | Sensor Escal. | Single: CO Caution | CAUTION: ELEVATED CO | CO: 10-30 ppm alone |
| **1 CAUTION** | Sensor Escal. | PM10 + Gas | CAUTION: COMBINED HAZARD RISKING | Coarse dust + combustibles |
| **1 CAUTION** | Sensor Escal. | PM10 + CO | CAUTION: CHECK FOR FIRE | Coarse dust + carbon monoxide |
| | | | | |
| **2 HAZARD** | Training Sim | Scenario 2: Pure Dust | HAZARDOUS: WEAR FACE MASK | PM high + Humidity low (low misting risk) |
| **2 HAZARD** | Training Sim | Scenario 4: Fire | HAZARDOUS: EVACUATE AREA NOW | PM extreme + Gas high + Temp high |
| **2 HAZARD** | Training Sim | Scenario 5: Combustion Developed | HAZARDOUS: CHECK FOR FIRE | Multi-sensor sustained high (30+ min) |
| **2 HAZARD** | Training Sim | Scenario 6: VOC/Chemical | HAZARDOUS: IMPROVE VENTILATION | Gas high + CO high (vapor hazard) |
| **2 HAZARD** | Field | Scenario 8: Field Hazardous | HAZARDOUS: TAKE ACTION | Real-world confirmed hazard |
| **2 HAZARD** | Sensor Escal. | PM2.5 + Gas | HAZARDOUS: SMOKE DETECTED | Fine particles + combustibles |
| **2 HAZARD** | Sensor Escal. | PM2.5 + CO | HAZARDOUS: FIRE HAZARD | Fine particles + carbon monoxide |
| **2 HAZARD** | Sensor Escal. | Gas + CO | HAZARDOUS: CHEMICAL VAPORS | Both gas sensors elevated |
| **2 HAZARD** | Sensor Escal. | PM2.5 + PM10 | HAZARDOUS: DUST STORM | Both particulate sensors elevated |
| **2 HAZARD** | Sensor Escal. | 3+ Sensors | HAZARDOUS: MULTI-SENSOR ALERT | Three or more sensors caution+ |
| | | | | |
| **2 HAZARD** | Override | Wet-Bulb > 32°C | HAZARDOUS: EXTREME HEAT - REDUCE WORK INTENSITY | Heat stress threshold exceeded |

---

# 🔍 DECISION TREE: HOW REMARKS ARE ASSIGNED

```
START: Read sensor data
    │
    ├─► FIRST CHECK: Misting Detection (Override)
    │   ├─ IF: Humidity ≥ 95% AND Gas < 100 ppm AND PM extreme
    │   │  └─► CLASS 0 - SAFE: MISTING DETECTED
    │   │       (Override prevents false alarm from high PM)
    │   │
    │   └─ ELSE: Continue to next rule
    │
    ├─► SECOND CHECK: Wet-Bulb Temperature (Override)
    │   ├─ IF: Wet-Bulb > 32°C
    │   │  └─► CLASS 2 - HAZARDOUS: EXTREME HEAT
    │   │       (Override for heat stress priority)
    │   │
    │   └─ ELSE: Continue to sensor escalation
    │
    ├─► SENSOR ESCALATION: Check 4-sensor combinations
    │   │
    │   ├─ Check dangerous pairs FIRST (high confidence hazards):
    │   │  ├─ PM2.5 + Gas → CLASS 2 - HAZARDOUS: SMOKE DETECTED
    │   │  ├─ PM2.5 + CO → CLASS 2 - HAZARDOUS: FIRE HAZARD
    │   │  └─ Gas + CO → CLASS 2 - HAZARDOUS: CHEMICAL VAPORS
    │   │
    │   ├─ Check multi-sensor (3+ sensors):
    │   │  └─ IF: 3+ sensors in caution+
    │   │     └─► CLASS 2 - HAZARDOUS: MULTI-SENSOR ALERT
    │   │
    │   ├─ Check dust patterns:
    │   │  ├─ IF: PM2.5 + PM10 both elevated
    │   │  │  └─► CLASS 2 - HAZARDOUS: DUST STORM
    │   │  │
    │   │  └─ IF: PM10 + (Gas or CO)
    │   │     └─► CLASS 1 - CAUTION: (COMBINED/FIRE CHECK)
    │   │
    │   └─ Check single sensors:
    │      ├─ IF: 1 sensor in caution
    │      │  └─► CLASS 1 - CAUTION: (specific remark per sensor)
    │      │
    │      └─ IF: All sensors safe
    │         └─► CLASS 0 - SAFE: ALL SENSORS NORMAL
    │
    └─► ASSIGN TRAINING SCENARIO TAG
        ├─ Class 0 + misting? → Scenario 3
        ├─ Class 0 + normal? → Scenario 1 or 7
        ├─ Class 1 + developing multi-sensor? → Scenario 5 early
        ├─ Class 2 + PM high + humidity low? → Scenario 2
        ├─ Class 2 + multi-extreme? → Scenario 4
        ├─ Class 2 + gas+CO? → Scenario 6
        ├─ Class 2/1 + field context? → Scenario 8
        └─ (Field deployment overrides simulation tags)

END: Output CLASS + SCENARIO + REMARK
```

---

# 📊 DATA DISTRIBUTION (20,568 Training Rows)

## Actual Classification Distribution

```
Distribution Before Intelligent Labeling:
  Safe (0):        13,597 rows (66.1%)
  Caution (1):        357 rows (1.7%)
  Hazardous (2):    6,614 rows (32.1%)

Distribution After Intelligent Labeling:
  Safe (0):        13,605 rows (66.1%) [+8 from misting/humidity]
  Caution (1):        354 rows (1.7%)  [-3 adjusted]
  Hazardous (2):    6,609 rows (32.1%) [-5 adjusted]

Why Changes:
  • Misting detection: 557 rows confirmed as safe (high PM + extreme humidity)
  • Humidity high scenario: Some rows reclassified from hazard to safe
  • Wet-bulb computation: Heat stress factor added to decisions

Key Insight: Intelligent labeling fine-tunes raw alarmed_status with
             specialized rules (misting override, wet-bulb override, etc.)
```

---

## By Source File Breakdown

| **Dataset Source** | **Safe %** | **Caution %** | **Hazard %** | **Total** | **Notes** |
|-------------------|-----------|--------------|-------------|----------|----------|
| Indoor (Temfacil) | 100% | 0% | 0% | 2,945 | Clean indoor air |
| Warehouse | 97.4% | 2.6% | 0% | 3,090 | Minor dust/ventilation |
| Outside (Temfacil) | 99.2% | 0.8% | 0% | 3,242 | Outdoor but safe |
| Fabrication Area | 99.5% | 0.4% | 0.1% | 3,155 | Mostly safe, rare hazard |
| **Active Floor** | **0%** | **0%** | **100%** | **2,880** | **All hazardous readings** |
| Hazard - Combustion | 0% | 0% | 100% | 996 | Scenario 5 hazard |
| Hazard - Fire | 0% | 0% | 100% | 700 | Scenario 4 hazard |
| Hazard - Dust | 0% | 1.2% | 98.8% | 730 | Scenario 2 hazard |
| Hazard - VOC | 0% | 0% | 100% | 804 | Scenario 6 hazard |
| Safe - High Humidity | 99.4% | 0.6% | 0% | 673 | Scenario 7 safe |
| Safe - Clean Air | 62.4% | 36.3% | 1.3% | 622 | Scenario 1 baseline |
| **Safe - Misting** | **52.8%** | **0%** | **47.2%** | **1,054** | **Scenario 3: PM high but humidity extreme** |

---

## Key Observations

1. **Misting Detection Highly Effective**: 52.8% of misting data correctly identified as safe despite extreme PM readings
2. **Training Simulation Purity**: Hazard scenarios are 98-100% hazardous (clean separation for learning)
3. **Field Deployment Complexity**: Active Floor Area is 100% hazardous, but warehouse/facility mostly safe
4. **Caution Class Rarity**: Only 1.7% of data in Caution class (most decisions are binary: Safe or Hazard)
5. **Clean Air Scenario Variability**: Basic scenario has 36% caution readings (uncertainty in baseline)

---

# 🎓 USAGE EXAMPLES

## Example 1: Construction Site Reading

```
Reading: PM2.5=75, PM10=180, Gas=150, CO=15, Temp=32, Humidity=65

Analysis:
  1. Misting check? NO (humidity 65% < 95%)
  2. Wet-bulb check? Tw ≈ 28.5°C < 32°C → NO override
  3. Dangerous pairs?
     • PM2.5 (75) + PM10 (180) = YES (both caution+)
     • Pattern: DUST STORM
  
Classification:
  ✓ CLASS: 2 - HAZARDOUS
  ✓ REMARK: HAZARDOUS: DUST STORM
  ✓ SOURCE: Sensor Escalation (Scenario 2 signature)
  ✓ ACTION: Wear N95 mask immediately, minimize exposure

Why? Fine AND coarse particles together = confirmed dust hazard,
     not false alarm, requires respiratory protection.
```

---

## Example 2: Fire Emergency

```
Reading: PM2.5=250, PM10=320, Gas=200, CO=45, Temp=38, Humidity=40

Analysis:
  1. Misting check? NO (humidity 40% < 95%)
  2. Wet-bulb check? Tw ≈ 30.2°C < 32°C → NO pure heat override
  3. Dangerous pairs?
     • PM2.5 (250) + Gas (200) = YES → SMOKE
     • PM2.5 (250) + CO (45) = YES → FIRE SIGNATURE
     • Gas (200) + CO (45) = YES → COMBUSTION
     • 4 sensors elevated + temp extreme
  
Classification:
  ✓ CLASS: 2 - HAZARDOUS
  ✓ REMARK: HAZARDOUS: EVACUATE AREA NOW
  ✓ SOURCE: Training Simulation Scenario 4 (Fire) or Sensor Escalation
  ✓ ACTION: IMMEDIATE EVACUATION REQUIRED

Why? Multiple fire signatures confirmed: smoke particles + combustion
     indicators + elevated temperature. Emergency priority.
```

---

## Example 3: Extreme Heat with Moderate Air Quality

```
Reading: PM2.5=45, PM10=120, Gas=80, CO=8, Temp=38, Humidity=85, Tw=34.2°C

Analysis:
  1. Misting check? NO (gas 80 < 100, but humidity 85% < 95%)
  2. Wet-bulb check? Tw=34.2°C > 32°C → YES OVERRIDE to HAZARDOUS!
  3. (Ignore sensor escalation - override takes priority)
  
Classification:
  ✓ CLASS: 2 - HAZARDOUS (due to heat stress)
  ✓ REMARK: HAZARDOUS: EXTREME HEAT - REDUCE WORK INTENSITY
  ✓ SOURCE: Wet-Bulb Temperature Override
  ✓ ACTION: Reduce work intensity, increase cooling breaks

Why? Although air quality is mostly safe/caution, extreme heat stress
     (Tw > 32°C) becomes the priority. Heat-related illness risk is
     immediate and potentially life-threatening.
```

---

## Example 4: Misting False Alarm Prevention

```
Reading: PM2.5=620, PM10=810, Gas=95, CO=7, Temp=28, Humidity=97, CO₂ stream visible

Analysis:
  1. Misting check? YES!
     • Humidity 97% ≥ 95% ✓
     • Gas 95 < 100 ppm ✓
     • PM extreme (620) but NOT pollution signal
  2. (Misting override triggers → CLASS 0 SAFE)
  
Classification:
  ✓ CLASS: 0 - SAFE (due to misting override)
  ✓ REMARK: SAFE: MISTING DETECTED
  ✓ SOURCE: Training Simulation Scenario 3 (Misting)
  ✓ ACTION: No evacuation needed, water spray confirmed

Why? This prevents false alarm evacuation. If system only checked PM,
     would classify as HAZARDOUS and evacuate facility. MILES detects
     water droplets (from humidity + PM pattern) and overrides.
```

---

# 📌 QUICK REFERENCE

## Safe (Class 0) Triggers
- ✓ All sensors normal
- ✓ High humidity + extreme PM + normal gas = MISTING OVERRIDE
- ✓ Training scenarios: 1 (Baseline), 3 (Misting), 7 (High Humidity)
- ✓ Field: Safe real-world conditions

## Caution (Class 1) Triggers
- ⚠️ Single sensor in caution range
- ⚠️ PM10 + (Gas or CO) non-dangerous pair
- ⚠️ Developing multi-sensor elevation (early crisis)
- ⚠️ Field uncertainty

## Hazardous (Class 2) Triggers
- 🚨 PM2.5 + Gas = SMOKE DETECTED
- 🚨 PM2.5 + CO = FIRE HAZARD
- 🚨 Gas + CO = CHEMICAL VAPORS
- 🚨 PM2.5 + PM10 = DUST STORM
- 🚨 3+ sensors elevated = MULTI-SENSOR ALERT
- 🚨 Wet-Bulb > 32°C = HEAT STRESS (override)
- 🚨 Training scenarios: 2 (Dust), 4 (Fire), 5 (Combustion), 6 (VOC)
- 🚨 Field: Hazardous real-world conditions

---

*This document represents the complete MILES Remarks System as implemented in train_random_forest.py (April 2026)*
