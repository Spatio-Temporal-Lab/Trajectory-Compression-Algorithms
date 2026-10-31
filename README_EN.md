# Trajectory Compression Algorithms: Code and Experiments

This repository is linked to the paper *Research Progress on Trajectory Compression Methods: A Classification System, Performance Evaluation, and Future Trends*. It contains the algorithm implementations, experiment settings, and results used in the paper.

To keep the paper readable while covering the main cases, the paper reports compression quality and processing efficiency under representative parameter settings. It also compares methods within the same category and across different categories. This repository provides the full parameter experiments, complete results, and related figures for reference and reproduction.

The repository contains 34 algorithm directories. Each directory keeps source code, a small test case, and a run script. The experiments use six datasets: T-Drive, Geolife, Wuxi, Chengdu, AIS, and TrajAir. For algorithms with a common parameter setup, five error thresholds or target compression ratios are tested on each dataset, giving about `6 × 5 = 30` results per algorithm. Threshold, Persistence, GraCT, PRESS, TRACE, and other methods with their own parameters are tested separately.

The repository reproduces SEB, CFPF, TrajStore, and TRACE. It also provides C++ versions of Angular, MRPA, PILOT-C, CISEDS, and CISEDW.

## What the code is for

The code is used to:

1. Run different algorithms on the six trajectory datasets;
2. Compare algorithms with the same error threshold by compression ratio and compression speed;
3. Compare algorithms with the same target compression ratio by compression error and processing speed;
4. Record compression ratio, compression error, compression throughput, and, where supported, decompression throughput.

Each algorithm directory contains source code, a small input/output example, and a shell script for running the example.

## Project structure

```text
algorithms/
├── trajectory_information/
│   ├── trajectory_simplification/
│   │   ├── geometry_error/
│   │   ├── spatiotemporal_error/
│   │   ├── motion_feature/
│   │   └── multi_feature/
│   └── trajectory_coding/
│       ├── reference_coding/
│       └── point_coding/
└── external_information/
    └── road_network_compression/
        ├── path_derivation/
        └── reference_road_network/
```

Typical algorithm directory:

```text
Algorithm/
├── source code
├── sample_input.txt
├── sample_output.txt
└── run script (.sh)
```

## Algorithm groups

The groups below follow the algorithms kept in this repository. `Online` means that the algorithm processes a trajectory online.

### Methods using trajectory information only

#### Trajectory simplification

**Geometric-error methods**

- Bellman, DP, DPhull, OPW (Online), CDR (Online), BQS (Online), and OPERB (Online).
- These methods mainly control spatial shape error. PED is a common error measure.

**Spatiotemporal-error methods**

- TD-TR, OPW-TR (Online), STTrace (Online), SQUISH (Online), MRPA, DOTS (Online), CISEDS (Online), CISEDW (Online), VOLTCom (Online), and DimWeaver (Online).
- These methods also consider time consistency. SED is a common error measure.

**Motion-feature methods**

- Angular, Threshold (Online), SP and Intersect in DPTS, Persistence (Online), Interval (Online), and CASC.
- They preserve direction, speed, turns, and motion continuity.

**Multi-feature methods**

- RLTS, MARL4TS (Online), and SEB.
- They combine spatial, temporal, motion, or learned features to select important points.

#### Trajectory coding

**Reference coding**

- TrajStore, CFPF, and GraCT.
- These methods reduce storage by using reference trajectories, shared segments, quantization, or indexes.

**Point coding**

- Trajic, PILOT-C, and CoST.
- These methods use compact representations of points, prediction residuals, or code sequences.

### Methods using external information

#### Road-network compression

- PRESS and TRACE (Online).
- These methods use map matching, road topology, and shared paths in a road network.

## Experiment settings and comparisons

### Datasets

The experiments use six real-world trajectory datasets. They cover taxis, city vehicles, personal movement, ships, and aircraft, with different trajectory sizes, lengths, and sampling intervals.

- [T-Drive](https://www.microsoft.com/en-us/research/publication/t-drive-trajectory-data-sample/): about 1.57 million points and 1,000 trajectories; sampling interval about 300 seconds.
- [Geolife](https://www.microsoft.com/en-us/download/details.aspx?id=52367): about 23.31 million points and 17,784 trajectories; sampling interval about 1–5 seconds.
- [Wuxi](https://www.nbsdc.cn/general/dataLinks/16666.11.nbsdc.iaTZ0vFX): about 39.70 million points and 15,820 trajectories; sampling interval about 1–3 seconds.
- [Chengdu](https://gaia.didichuxing.com): about 5.34 million points and 20,000 trajectories; sampling interval about 3 seconds.
- [AIS](https://zenodo.org/records/6323416): about 2.82 million points and 6,000 trajectories; average sampling interval about 39 seconds.
- [TrajAir](https://kilthub.cmu.edu/articles/dataset/TrajAir_A_General_Aviation_Trajectory_Dataset/14866251): about 1.61 million points and 4,000 trajectories; sampling interval about 1 second.

The datasets used in the experiments are also available from [Baidu Netdisk](https://pan.baidu.com/s/1VMvX2danYI4LxNi8anexEQ?pwd=nqb2). Extraction code: `nqb2`.

### How to use the datasets

1. Download and extract the needed dataset from the links above or from Baidu Netdisk.
2. Keep the raw data in a local data directory. Large raw datasets do not need to be committed to this repository.
3. Prepare the input file according to the run script. Different algorithms may require coordinates, timestamps, trajectory IDs, or map-matching results.
4. Run the sample input first to check the program, then replace the sample path with the real data path.
5. Run the `.sh` script. The output files and runtime metrics are written according to the script settings.

### Common metrics

- **Compression ratio**: compressed output file size divided by original input file size. A smaller value means stronger compression.
- **Compression error**: PED, SED, direction error, or an error defined by the algorithm. Different error measures should only be compared within the same measure.
- **Compression throughput**: measured in `MB/s`, calculated as original input size divided by compression time. Total compression time and time per point are also recorded.
- **Decompression throughput**: for algorithms that output a binary stream and support recovery, decompressed data size divided by decompression time, also measured in `MB/s`.

### Two main experiment types

- **Error-threshold input**: algorithms receive an error threshold. Under the same error requirement, we compare compression ratio and processing speed. The representative values used in the common experiments are `1e-5`, `5e-5`, `1e-4`, `5e-4`, and `1e-3`; these values do not apply to every algorithm.
- **Compression-ratio input**: algorithms receive `2`, `5`, `10`, `20`, or `50`, corresponding to target ratios `0.5`, `0.2`, `0.1`, `0.05`, and `0.02` (`50%`, `20%`, `10%`, `5%`, and `2%`). Under the same target ratio, we compare compression error and processing speed.

Some algorithms use special parameters. Threshold uses speed and direction thresholds, Persistence uses distance-related parameters, GraCT uses snapshot intervals, and PRESS/TRACE use road-network parameters.

### Comparisons by algorithm group

- **Geometric error**: DP, DPhull, OPW, CDR, BQS, and OPERB use error thresholds and are compared by compression ratio and throughput. Bellman uses a target compression ratio and is compared by PED and processing speed.
- **Spatiotemporal error**: TD-TR, MRPA, OPW-TR, DOTS, CISEDS, CISEDW, VOLTCom, and DimWeaver use error thresholds and are compared under the same SED constraint. SQUISH and STTrace use target ratios and are compared by SED and processing speed.
- **Motion features**: SP, Intersect, and Interval use error inputs. Angular, CASC, Persistence, and Threshold use their own direction, speed, or distance parameters.
- **Multi-feature methods**: RLTS, MARL4TS, and SEB run with target ratios or error constraints and are compared by compression error, compression ratio, and model efficiency.
- **Reference coding methods**: TrajStore, CFPF, and GraCT use reference trajectories, shared segments, or snapshot indexes.
- **Point coding methods**: Trajic, PILOT-C, and CoST mainly use error thresholds and are compared by encoded size, compression ratio, and throughput.
- **Road-network methods**: PRESS and TRACE are compared separately by storage cost and processing efficiency because they depend on map matching and road topology.

## Requirements

### Operating systems

- Linux, macOS, or Windows 10/11;
- On Windows, Git Bash or WSL is recommended for running `.sh` scripts.

### C/C++ build tools

- A C++17 compiler: GCC 9+, Clang 10+, or Apple Clang 15+;
- On Windows, use MinGW-w64, GCC in WSL, or another C++17-compatible toolchain;
- CMake 3.15+ for algorithms such as GraCT and DimWeaver;
- GNU Make for algorithms using Makefiles;
- No specific IDE is required. Build commands are included in the run scripts.

### Shell and Python

- Bash for the `.sh` scripts;
- Python 3.8+ for learning-based methods such as RLTS, MARL4TS, and SEB;
- Python package versions may differ between algorithms. Follow the requirements of the algorithm you run.

## Quick start

Most algorithms can be run from their own directory. For example:

```bash
cd algorithms/trajectory_information/trajectory_simplification/geometry_error/DP
bash DP.sh
```

Another example:

```bash
cd algorithms/trajectory_information/trajectory_coding/point_coding/trajic
bash run.sh
```

On Linux or macOS, add execute permission if needed:

```bash
chmod +x *.sh
./DP.sh
```

On Windows, use Git Bash or WSL. The scripts use the local `sample_input.txt` and, when supported, create `sample_output.txt`.

## Input and output samples

The sample files are small and show the input/output format:

- `sample_input.txt`: trajectory or coding input;
- `sample_output.txt`: output generated by the sample run.

Formats differ between algorithms. Some methods also need configuration files or road-network data; the required commands are included in the related scripts.

## Notes

- **DPTS**: choose the batch simplification method in its configuration file before running `DPTS.sh`.
- **Trajic, TrajStore, and GraCT**: need their build tools. Trajic uses Make and Boost; GraCT uses CMake.
- **PRESS and TRACE**: need road-network data or preprocessing; small test cases are included.
- **CFPF**: the full workflow may need feature-point preprocessing.
- **MARL4TS, RLTS, and SEB**: full training may need extra Python packages and trajectory data.

## Python dependencies

Learning-based algorithms need a Python environment. Common packages include:

```bash
pip install numpy pandas matplotlib tensorflow keras sortedcontainers
```

## Reproducibility

Enter an algorithm directory, check its `.sh` script, and run it with the included sample input. Source code, samples, and run scripts are kept together so that each algorithm can be checked and reproduced separately.
