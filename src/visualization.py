import os
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import matplotlib.ticker as ticker


data_types = {
    "avg_time": "Cреднее время выполнения по всем тестам",
    "descending_array": "Отсортированные в обратном порядке массивы",
    "random_array": "Случайно сгенерированные массивы",
    "semisorted_array": "«Почти» отсортированные массивы"
}

ru_to_eng = {
    "Cреднее время выполнения по всем тестам": "avg_time",
    "Отсортированные в обратном порядке массивы": "descending_array",
    "Случайно сгенерированные массивы": "random_array",
    "«Почти» отсортированные массивы": "semisorted_array"
}


def read_data(directory):
    data = []
    for root, _, files in os.walk(directory):
        for file in files:
            if file.endswith(".txt"):
                parent_folder = os.path.basename(root)
                algo_name = parent_folder
                if "threshold_" in parent_folder:
                    threshold = parent_folder.split('_')[-1]
                    algo_name = "HybridMergeSort"
                else:
                    threshold = None

                file_path = os.path.join(root, file)
                file_type = file.split('_res')[0]

                with open(file_path, 'r') as f:
                    for line in f:
                        size, time = map(float, line.strip().split())
                        data.append({
                            "Кол-во элементов": size,
                            "Время выполнения (микросекунды)": time,
                            "Algorithm": algo_name,
                            "Threshold": threshold,
                            "Data Type": data_types[file_type]
                        })
    return pd.DataFrame(data)


def plot_performance(df):
    sns.set(style="whitegrid")
    unique_data_types = df["Data Type"].unique()

    for data_type in unique_data_types:
        plt.figure(figsize=(12, 7))
        data_subset = df[df["Data Type"] == data_type].copy()
        data_subset.loc[:, "Threshold"] = data_subset["Threshold"].fillna("")

        sns.lineplot(
            data=data_subset,
            x="Кол-во элементов",
            y="Время выполнения (микросекунды)",
            hue="Algorithm",
            style="Threshold",
            markers=True,
            dashes=False,
        )
        plt.title(data_type, fontsize=18)
        plt.xlabel("Кол-во элементов в массиве", fontsize=14)
        plt.ylabel("Время выполнения (микросекунды)", fontsize=14)

        ax = plt.gca()
        ax.xaxis.set_major_locator(ticker.MultipleLocator(2000))
        ax.yaxis.set_major_locator(ticker.MultipleLocator(400))
        ax.xaxis.set_minor_locator(ticker.MultipleLocator(1000))
        ax.yaxis.set_minor_locator(ticker.MultipleLocator(200))
        ax.grid(which="both", linestyle="--", linewidth=0.8, alpha=0.8)

        # Настройка шрифта для осей и легенды
        ax.tick_params(axis='both', which='major', labelsize=12)
        ax.tick_params(axis='both', which='minor', labelsize=10)

        handles, labels = plt.gca().get_legend_handles_labels()
        filtered_handles_labels = [
            (h, l) for h, l in zip(handles, labels) if l != ""
        ]
        plt.legend(
            *zip(*filtered_handles_labels), title="Algorithm / Threshold", fontsize=12
        )

        plt.tight_layout()
        plt.savefig(f"../images/performance_{ru_to_eng[data_type]}.png", dpi=300)


df = read_data("../data")
print(f"Загружено {len(df)} строк данных.")
print(df["Algorithm"].value_counts())
plot_performance(df)
