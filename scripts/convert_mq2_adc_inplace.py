#!/usr/bin/env python3
"""Convert MQ2 ADC readings to PPM in-place for CSV files in dataset/.

This script replaces the values in the `MQ2_ADC` column with the computed
PPM using constants from the project PDF. It writes a temporary file next to
each original then replaces the original file (atomic replace).

Usage: python scripts/convert_mq2_adc_inplace.py
"""
import csv
from pathlib import Path
import tempfile
import os

# Constants (from project PDF) — UPDATED: RL changed to 10kΩ, R0 recalibrated
ADC_MAX = 4095.0
VIN = 5.0
RL = 10000.0  # Load resistor changed from 20kΩ to 10kΩ
R0 = 24539.77  # R0 recalibrated (halved proportionally: 49,079.54 ÷ 2)
A = 3616.1
B = -2.675

DATASET_DIR = Path('dataset')

def convert_adc_to_ppm(adc_value):
    try:
        adc = float(adc_value)
    except Exception:
        return None

    vout = (adc / ADC_MAX) * VIN
    if vout <= 0:
        return 0.0

    rs = ((VIN - vout) / vout) * RL
    ratio = rs / R0
    try:
        ppm = A * (ratio ** B)
    except Exception:
        return None
    return ppm

def process_file_inplace(path: Path):
    fd, tmpname = tempfile.mkstemp(prefix=path.stem + '_tmp_', suffix=path.suffix, dir=path.parent)
    os.close(fd)
    tmp_path = Path(tmpname)

    processed = 0
    with path.open('r', newline='', encoding='utf-8') as fr:
        reader = csv.reader(fr)
        rows = list(reader)
        if not rows:
            tmp_path.unlink(missing_ok=True)
            return 0

        header = rows[0]
        try:
            idx = header.index('MQ2_ADC')
        except ValueError:
            tmp_path.unlink(missing_ok=True)
            return 0

        with tmp_path.open('w', newline='', encoding='utf-8') as fw:
            writer = csv.writer(fw)
            writer.writerow(header)

            for row in rows[1:]:
                # extend row if short
                if idx >= len(row):
                    # nothing to convert; write row unchanged
                    writer.writerow(row)
                    continue

                adc_val = row[idx].strip()
                if adc_val == '':
                    writer.writerow(row)
                    continue

                ppm = convert_adc_to_ppm(adc_val)
                if ppm is None:
                    # if conversion fails, keep original ADC value
                    writer.writerow(row)
                else:
                    row[idx] = f"{ppm:.6f}"
                    writer.writerow(row)
                    processed += 1

    # Replace original with tmp file
    tmp_path.replace(path)
    return processed

def main():
    ds = DATASET_DIR
    if not ds.exists() or not ds.is_dir():
        print('dataset/ folder not found')
        return

    csvs = list(ds.glob('*.csv'))
    total = 0
    for f in csvs:
        n = process_file_inplace(f)
        if n:
            print(f'Updated {n} MQ2 values in {f.name}')
            total += n
        else:
            print(f'Skipped {f.name} (no MQ2_ADC column or empty)')

    print(f'Done. Total MQ2 values converted: {total}')

if __name__ == '__main__':
    main()
