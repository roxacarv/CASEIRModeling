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

plt.title("SEIR Evolution Over Time")
plt.xlabel("Iteration")
plt.ylabel("Population")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig("seir_evolution.png", dpi=300)
plt.show()

# Epidemic duration
first_infection = iterations_df[iterations_df['infectious'] > 0]['iteration'].min()
last_infection = iterations_df[iterations_df['infectious'] > 0]['iteration'].max()
duration = last_infection - first_infection
print(f"Epidemic duration: {duration} iterations (from {first_infection} to {last_infection})")

# AUC (Area under the curve), get the cumulative impact of each SEIR group
auc_infectious = simpson(iterations_df["infectious"], iterations_df["iteration"])
print(f"AUC of Infectious curve: {auc_infectious:.2f}")

# Approximate R₀
early = iterations_df.iloc[1:10]
avg_exposures = early["total_exposures"].diff().mean()
avg_infectious = early["infectious"].mean()
approx_r0 = avg_exposures / avg_infectious if avg_infectious else 0

# Print and collect results
print(f"📌 Peak Infection: {int(peak['infectious'])} at iteration {int(peak['iteration'])}")
print(f"⏱️ Epidemic Duration: {duration} iterations")
print(f"📐 Area Under Infectious Curve: {auc_infectious:.2f}")
print(f"🧪 Approximate R₀: {approx_r0:.2f}")

# Bar chart for final SEIR states
seir_final = final[["susceptible", "exposed", "infectious", "recovered"]]
total = seir_final.sum()
ratios = seir_final / total

plt.figure(figsize=(6, 5))
bars = plt.bar(seir_final.index, seir_final.values, color=["blue", "orange", "red", "green"])
plt.title("Final SEIR States")
plt.ylabel("Population")

# Annotate ratios
for bar, value, ratio in zip(bars, seir_final.values, ratios):
    plt.text(bar.get_x() + bar.get_width()/2, value + 10,
             f"{ratio:.1%}", ha='center', fontsize=10)

plt.tight_layout()
plt.savefig("final_seir_state.png", dpi=300)
plt.show()