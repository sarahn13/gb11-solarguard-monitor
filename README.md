# GB11 SolarGuard Monitor

A front-end prototype for the GB11 project: **IoT-Based Solar Storage Battery Compatibility Monitoring and Condition Assessment System**.

## What's included
- `index.html` — responsive dashboard that runs locally in a browser.
- Simulated voltage, current, battery temperature and lamp-OFF branch current.
- Trend chart, threshold-based demo alerts, test controls and CSV export.
- `esp32_demo.ino` — an ESP32 Arduino starter that prints example sensor estimates to Serial.

## Run the dashboard
1. Download or clone this repository.
2. Open `index.html` in Chrome, Edge, Firefox or Safari. No build step or dependencies are required.
3. Use **Low battery**, **High temperature**, **Unexpected drain**, and **Leakage alert demo** to demonstrate the rule-based alerts.
4. Use **Export CSV** to save the simulated readings.

You can also serve it locally with Python:

```bash
python -m http.server 8000
```

Then visit `http://localhost:8000` in your browser.

## Put it on GitHub
1. Create a new repository, e.g. `gb11-solarguard-monitor`.
2. Upload `index.html`, `esp32_demo.ino`, and `README.md` to the repository root.
3. In the repository, open **Settings → Pages**.
4. Under build/deployment, choose **Deploy from a branch**, select `main` and `/ (root)`, then save.
5. Wait for GitHub Pages to publish the site; the published URL appears in Settings → Pages.

## Connect real hardware later
The dashboard currently uses simulated data. The ESP32 sketch is a sensor-reading starting point only and is not connected to the web UI. A real integration needs a transport/backend such as MQTT or an authenticated HTTP API, a defined JSON schema, and a dashboard data client.

Before connecting sensors, identify the exact battery chemistry and nominal voltage, charge controller, current sensor model/range, temperature sensor, residual-current or insulation-monitoring device, and load-disconnect hardware. Calibrate every channel against reference instruments. The example constants and pin assignments in the sketch are placeholders and must be adapted to the hardware datasheets.

**Safety and scope:** Unexpected current while a lamp is commanded OFF does not by itself prove electrical leakage. Leakage/insulation fault detection depends on an appropriate sensor, wiring, grounding and validated test procedure. Do not use this software demo as a battery protection system or to control a real load. Use properly rated fusing, wiring, enclosure and supervised low-voltage testing.

## Suggested next milestones
1. Confirm circuit diagram and sensor part numbers with your supervisor.
2. Validate voltage, current and temperature readings against reference instruments.
3. Add Wi-Fi transport and send timestamped readings to an API/MQTT broker.
4. Replace the dashboard's demo generator with real authenticated readings.
5. Test alerts, lamp-OFF drain detection, data availability and false alarms under controlled conditions.
