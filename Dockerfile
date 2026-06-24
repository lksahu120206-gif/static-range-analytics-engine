# ==========================================
# STAGE 1: Build Environment (Heavy Compiler)
# ==========================================
FROM gcc:14 AS builder

# Set internal working directory inside the container
WORKDIR /app

# Copy the local source files into the container
COPY src/ ./src/

# Compile as a 100% SELF-CONTAINED STATIC BINARY with maximum speed optimizations (-O3)
RUN g++ -std=c++17 -O3 -static src/main.cpp -o range_engine

# ==========================================
# STAGE 2: Minimal Runtime Environment (Tiny Footprint)
# ==========================================
FROM alpine:latest

# Set running directory inside Alpine
WORKDIR /root/

# Pull ONLY the compiled static binary from Stage 1
COPY --from=builder /app/range_engine .

# Execute the binary when the container kicks off
ENTRYPOINT ["./range_engine"]