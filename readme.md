# High-Performance Range-Query & Search Engine

A low-latency, zero-dependency Command Line Interface (CLI) data analytics engine written in C++17. This project implements pre-computation invariants and search-space optimizations to handle sequential analytical metrics queries in constant and linear time boundaries. 

The entire runtime environment is containerized using a micro-footprint, multi-stage DevOps pipeline.

---

## 🚀 Key Engineering Features

* **Prefix Sum Analytics Core:** Leverages a pre-computed contiguous memory map to resolve any slicing subarray range-query in constant time: $\mathcal{O}(1)$.
* **Two-Pointer Optimization:** Sweeps a sorted search space workspace using inward-closing bounds to locate target threshold metric pairs in linear time: $\mathcal{O}(N)$.
* **Low-Latency Stream Ingestion:** Completely desynchronizes standard C++ I/O streams from native C standard structures (`stdio`) to optimize buffer execution throughput.
* **Multi-Stage DevOps Containerization:** Uses a distinct build-and-discard multi-stage pipeline configuration, stripping away compilation bloat to deploy a self-contained static binary inside a minimal (~17MB) Alpine Linux wrapper.

---

## 🛠️ Project Workspace Layout

```text
RangeEngine/
├── src/
│   └── main.cpp           # Engine Core (CLI routing & Data pipelines)
├── set_distro_paths.bat   # Local environment isolation script
└── Dockerfile             # Multi-stage optimized static build blueprint