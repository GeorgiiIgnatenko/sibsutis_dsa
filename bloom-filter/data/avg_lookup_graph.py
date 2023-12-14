import pandas as pd
import matplotlib.pyplot as plt
from datetime import datetime

data = pd.read_csv("./data/lookup_time.csv")
sub_data = data[data['t'] < 0.000001]

print(len(data)-len(sub_data))

plt.plot(sub_data['n'], sub_data['t'], color='b', label='Время поиска')
plt.xlabel('Количество элементов')
plt.ylabel('Время поиска')
plt.title('Время поиска в фильтре Блума')
plt.legend()
plt.grid()

now = datetime.now().strftime("%H:%M:%S")

plt.savefig(f"./graph/avg_lookup_graph{now}.png", dpi=300)
