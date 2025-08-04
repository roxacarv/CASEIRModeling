import pandas as pd
import matplotlib.pyplot as plt
from numpy import trapezoid
from scipy.integrate import simpson

iterations_df = pd.read_csv("iterations_statistics.csv")
final_df = pd.read_csv("statistics.csv")
final = final_df.iloc[0]

# Plot SEIR evolution
plt.figure(figsize=(12, 6))
plt.plot(iterations_df["iteration"], iterations_df["susceptible"], label="Susceptible")
plt.plot(iterations_df["iteration"], iterations_df["exposed"], label="Exposed")
plt.plot(iterations_df["iteration"], iterations_df["infectious"], label="Infectious")
plt.plot(iterations_df["iteration"], iterations_df["recovered"], label="Recovered")


# Find and annotate peak infection
peak = iterations_df.loc[iterations_df['infectious'].idxmax()]
plt.axvline(peak['iteration'], color='red', linestyle='--', alpha=0.6)
plt.annotate(f"Peak: {int(peak['infectious'])}\nIter: {int(peak['iteration'])}",
             (peak['iteration'], peak['infectious']),
             textcoords="offset points", xytext=(-10,10), ha='center', fontsize=9,
             bbox=dict(boxstyle="round,pad=0.3", edgecolor='red', facecolor='white'))

# Peak detection
peak = iterations_df.loc[iterations_df["infectious"].idxmax()]
print(f"Peak infectious at iteration {peak['iteration']}: {int(peak['infectious'])} individuals")

# Epidemic duration
first_infection = iterations_df[iterations_df['infectious'] > 0]['iteration'].min()
last_infection = iterations_df[iterations_df['infectious'] > 0]['iteration'].max()
duration = last_infection - first_infection
print(f"Epidemic duration: {duration} iterations (from {first_infection} to {last_infection})")

# AUC (Area under the curve), get the cumulative impact of each SEIR group
auc_infectious = simpson(iterations_df["infectious"], iterations_df["iteration"])
print(f"AUC of Infectious curve: {auc_infectious:.2f}")

# Rate of change
iterations_df["infectious_growth_rate"] = iterations_df["infectious"].diff() / iterations_df["infectious"].shift()

plt.figure(figsize=(14, 10))

# 1. SEIR dynamics over time
plt.subplot(2, 2, 1)
plt.plot(iterations_df["iteration"], iterations_df["susceptible"], label="Susceptible")
plt.plot(iterations_df["iteration"], iterations_df["exposed"], label="Exposed")
plt.plot(iterations_df["iteration"], iterations_df["infectious"], label="Infectious")
plt.plot(iterations_df["iteration"], iterations_df["recovered"], label="Recovered")
plt.title("SEIR Population Over Iterations")
plt.xlabel("Iteration")
plt.ylabel("Population")
plt.legend()
plt.grid(True)

# 2. Total counts over time
plt.subplot(2, 2, 2)
plt.plot(iterations_df["iteration"], iterations_df["total_moves"], label="Total Moves")
plt.plot(iterations_df["iteration"], iterations_df["total_exposures"], label="Total Exposures")
plt.plot(iterations_df["iteration"], iterations_df["total_infectious"], label="Total Infectious")
plt.title("Total Counts Over Iterations")
plt.xlabel("Iteration")
plt.ylabel("Total Count")
plt.legend()
plt.grid(True)

# 3. Average per-cell statistics
plt.subplot(2, 2, 3)
plt.plot(iterations_df["iteration"], iterations_df["avg_susceptible_count"], label="Avg Susceptible Count")
plt.plot(iterations_df["iteration"], iterations_df["avg_infection_count"], label="Avg Infection Count")
plt.plot(iterations_df["iteration"], iterations_df["avg_exposed_count"], label="Avg Exposed Count")
plt.title("Average Counts Per Cell")
plt.xlabel("Iteration")
plt.ylabel("Average")
plt.legend()
plt.grid(True)

# 4. Average movement
plt.subplot(2, 2, 4)
plt.plot(iterations_df["iteration"], iterations_df["avg_move_count"], label="Avg Move Count", color="orange")
plt.title("Average Move Count Per Cell")
plt.xlabel("Iteration")
plt.ylabel("Average Moves")
plt.legend()
plt.grid(True)
plt.savefig("avg_iteration_analysis.png", dpi=300)

plt.tight_layout()
plt.show()

final = final_df.iloc[0]
seir_final = final[["susceptible", "exposed", "infectious", "recovered"]]

plt.figure(figsize=(6, 5))
seir_final.plot(kind="bar", color=["blue", "orange", "red", "green"])
plt.title("Final SEIR State")
plt.ylabel("Population")
plt.grid(axis='y')
plt.tight_layout()
plt.savefig("final_state.png", dpi=300)
plt.show()