# MILES ACTION-BASED DECISION TABLE
## Complete Action Remarks in Decision-Table Layout

---

## CLASS 0: SAFE

| Scenario/Condition | Sensor Profile | Wet-Bulb Range | Remark | Reasoning | Worker Action |
|---|---|---|---|---|---|
| Scenario 1: Baseline | PM2.5: 3-10; PM10: 5-20; Gas: <100; Humidity: 49-65% | Tw <= 26 C | SAFE: CONTINUE OPERATIONS | All hazard sensors are in normal range; no immediate risk. | Continue normal operations and monitor periodically. |
| Scenario 3: Misting | PM2.5: 355-816 (high); PM10: high; Gas: 86-117 (normal); Humidity: 96-100% | Tw <= 26 C | SAFE: CONTINUE WORK, NO EVACUATION | Extreme PM with extreme humidity and normal gas indicates water droplets, not combustion. | Continue work; verify visibility and keep area dry. |
| Scenario 7: High Humidity | PM and gas sensors normal; Humidity elevated | Tw 27-30 C acceptable if pollutants normal | SAFE: CONTINUE TASKS WITH HYDRATION | Humidity alone is not a pollutant hazard when PM/Gas/CO remain normal. | Continue tasks, hydrate regularly, and monitor comfort. |
| Field Deployment: Safe | Real-world mixed readings classified as class 0 | Tw depends on live conditions | SAFE: CONTINUE WITH ROUTINE PPE | Site is currently stable under decision rules and does not require escalation. | Continue operations with routine PPE and periodic sensor checks. |

| Decision Rule | Trigger | Action Remark |
|---|---|---|
| Misting Override | Humidity >= 95 and Gas < 100 | SAFE: CONTINUE WORK, NO EVACUATION |
| All Sensors Normal | PM2.5 < 51, PM10 < 151, Gas < 131, CO < 10 | SAFE: CONTINUE OPERATIONS |
| Safe Fallback | No higher-risk trigger active | SAFE: CONTINUE OPERATIONS AND PERFORM ROUTINE CHECKS |

---

## CLASS 1: CAUTION

| Scenario/Condition | Sensor Profile | Wet-Bulb Range | Remark | Reasoning | Worker Action |
|---|---|---|---|---|---|
| Single PM2.5 Elevated | PM2.5 in caution range only | Usually Tw 27-30 C | CAUTION: REDUCE DUST EXPOSURE NOW | Fine particles are rising but not yet critical. | Wear dust mask, reduce dust-generating activity, recheck in 5 minutes. |
| Single PM10 Elevated | PM10 in caution range only | Usually Tw 27-30 C | CAUTION: IMPROVE VENTILATION NOW | Coarse particles indicate worsening local air quality. | Increase airflow and reduce movement that stirs dust. |
| Single Gas Elevated | Gas in caution range only | Usually Tw 27-30 C | CAUTION: CHECK COMBUSTION SOURCES NOW | Combustible gas trend suggests possible source buildup. | Inspect nearby sources and increase fresh-air flow. |
| Single CO Elevated | CO in caution range only | Usually Tw 27-30 C | CAUTION: MOVE TO CLEANER AIR ZONE | CO exposure risk is present and can escalate quickly. | Check engines/exhaust and move workers to better-ventilated area. |
| PM10 + Gas Combination | PM10 and Gas in caution ranges | Usually Tw 27-30 C | CAUTION: PREPARE RESPIRATORY PROTECTION | Multi-factor stress increases likelihood of hazardous escalation. | Lower work intensity, prepare respirators, monitor continuously. |
| PM10 + CO Combination | PM10 and CO in caution ranges | Usually Tw 27-30 C | CAUTION: START FIRE-SOURCE CHECK | Combined particle and CO pattern can indicate developing combustion. | Begin fire-source inspection and keep evacuation path clear. |
| Three Sensors in Caution | Any 3 caution-level sensors | Tw may be <=30 C | CAUTION: ACTIVATE PROTECTIVE PROTOCOL | Multi-sensor concern signals unstable environment. | Start mask + ventilation + close-supervision protocol. |
| Heat Stress Rising | Sensors may be safe or caution | Tw 27-30 C | CAUTION: SLOW WORK AND HYDRATE | Heat load raises physiological stress and lowers tolerance to pollutants. | Increase hydration breaks, reduce exertion, rotate workers. |
| Field Deployment: Caution | Real-world mixed readings classified as class 1 | Tw depends on live conditions | CAUTION: APPLY PPE AND REASSESS | Risk is manageable but requires active mitigation and monitoring. | Apply PPE, reduce exposure time, reassess before full activity. |

| Decision Rule | Trigger | Action Remark |
|---|---|---|
| Single Caution Sensor | One of PM2.5, PM10, Gas, CO in caution range | CAUTION: TAKE TARGETED REDUCTION ACTION |
| Caution Combinations | PM10+Gas or PM10+CO in caution range | CAUTION: PREPARE FOR POSSIBLE ESCALATION |
| Heat Caution | Tw 27-30 C | CAUTION: SLOW WORK AND HYDRATE |
| Caution Fallback | Class 1 with no exact pattern match | CAUTION: REDUCE EXPOSURE AND INCREASE MONITORING |

---

## CLASS 2: HAZARDOUS

| Scenario/Condition | Sensor Profile | Wet-Bulb Range | Remark | Reasoning | Worker Action |
|---|---|---|---|---|---|
| PM2.5 Hazardous | PM2.5 above hazardous threshold | Any | HAZARDOUS: STOP DUST WORK NOW | Fine particulate load is at immediate respiratory risk level. | Stop dust-producing work, wear N95 or better, relocate to cleaner air. |
| PM10 Hazardous | PM10 above hazardous threshold | Any | HAZARDOUS: ACTIVATE DUST SUPPRESSION NOW | Coarse particle concentration is critically high. | Activate suppression immediately and clear source area. |
| Gas Hazardous | Gas at or above hazardous threshold | Any | HAZARDOUS: STOP IGNITION ACTIVITIES NOW | Gas concentration may support combustion or explosion. | Stop ignition sources, isolate area, inspect source urgently. |
| CO Hazardous | CO above hazardous threshold | Any | HAZARDOUS: MOVE UPWIND IMMEDIATELY | CO toxicity risk is acute and time-sensitive. | Move workers upwind and shut down suspect engines if safe. |
| PM2.5 + PM10 Dangerous Combination | Both PM channels elevated (non-misting context) | Typically Tw <= 30 C | HAZARDOUS: ENFORCE RESPIRATORS IMMEDIATELY | Simultaneous fine and coarse particle elevation indicates real dust hazard. | Enforce respirators and minimize exposed work. |
| PM2.5 + Gas Dangerous Combination | PM2.5 and Gas elevated together | Typically Tw <= 30 C | HAZARDOUS: CHECK COMBUSTION AND PREPARE EVACUATION | Combined smoke and gas signature suggests active combustion risk. | Begin combustion-source check and prepare evacuation. |
| PM2.5 + CO Dangerous Combination | PM2.5 and CO elevated together | Typically Tw <= 30 C | HAZARDOUS: TREAT AS FIRE RISK NOW | Particle + CO pattern is consistent with fire products. | Move non-essential workers and verify fire status immediately. |
| Gas + CO Dangerous Combination | Gas and CO elevated together | Typically Tw <= 30 C | HAZARDOUS: EVACUATE AFFECTED ZONE NOW | Chemical vapor/combustion exposure risk is critical. | Evacuate affected zone and call emergency or hazmat response. |
| Three or More Sensors Triggered | Any 3+ sensors in caution/hazardous ranges | Any | HAZARDOUS: EXECUTE FULL EMERGENCY PROTOCOL | Multi-sensor trigger indicates broad and unstable hazard condition. | Execute mask, ventilation, and evacuation controls as needed. |
| Heat Stress Critical | Sensors may be safe/caution/hazardous | Tw > 30 C | HAZARDOUS: STOP NON-ESSENTIAL PHYSICAL WORK | Heat stress is severe enough to require immediate workload control. | Stop non-essential work and cool down workers immediately. |
| Extreme Heat Emergency | Any sensor state | Tw > 35 C | HAZARDOUS: EVACUATE TO COOLING AREA NOW | Extreme heat is life-threatening and overrides normal operation. | Immediate heat evacuation and emergency heat-response protocol. |
| Field Deployment: Hazardous | Real-world mixed readings classified as class 2 | Tw depends on live conditions | HAZARDOUS: PAUSE OPERATIONS UNTIL STABLE | Current field state requires intervention before safe continuation. | Pause operations until controls are applied and readings stabilize. |

| Decision Rule | Trigger | Action Remark | Priority |
|---|---|---|---|
| Single Hazardous Sensor | PM2.5, PM10, Gas, or CO in hazardous range | HAZARDOUS: STOP WORK AND APPLY IMMEDIATE CONTROL | Highest |
| Dangerous Two-Sensor Combination | PM2.5+PM10, PM2.5+Gas, PM2.5+CO, Gas+CO | HAZARDOUS: PREPARE OR EXECUTE EVACUATION ACTIONS | Critical |
| Multi-Sensor Alert | Three or more sensors triggered | HAZARDOUS: EXECUTE FULL EMERGENCY PROTOCOL | High |
| Heat Critical | Tw > 30 C | HAZARDOUS: STOP NON-ESSENTIAL PHYSICAL WORK | High |
| Heat Emergency Override | Tw > 35 C | HAZARDOUS: EVACUATE TO COOLING AREA NOW | Highest |

---

## Wet-Bulb Escalation Table

| Wet-Bulb Range | Classification Effect | Required Action Message |
|---|---|---|
| Tw <= 26 C | No heat-based escalation | Follow sensor-based action. |
| Tw 27-30 C | Escalate safe behavior into caution controls | CAUTION: SLOW WORK, HYDRATE, ROTATE WORKERS. |
| Tw > 30 C | Escalate caution behavior into hazardous controls | HAZARDOUS: STOP NON-ESSENTIAL PHYSICAL WORK NOW. |
| Tw > 35 C | Override to emergency hazardous | HAZARDOUS: EVACUATE TO COOLING AREA IMMEDIATELY. |

