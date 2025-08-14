# BrainwaveVST

BrainwaveVST is a simple synthesizer plug‑in built with [JUCE](https://juce.com/). It generates a sine wave whose frequency and gain can be adjusted.

## Building

1. Obtain the JUCE library as a sibling folder:
   ```bash
   git clone --depth 1 https://github.com/juce-framework/JUCE.git ../JUCE
   ```
2. Configure and build the project:
   ```bash
   cmake -S . -B build
   cmake --build build
   ```

The project produces a VST3 plug‑in and a standalone application.

## License

This project is released under the [MIT License](LICENSE).
