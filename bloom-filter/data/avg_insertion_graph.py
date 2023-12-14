import pandas as pd
import matplotlib.pyplot as plt
from datetime import datetime

data = pd.read_csv("./data/insertion_time.csv");
sub_data = data[data['t'] < 0.000001]

print(len(data)-len(sub_data))

plt.plot(sub_data['n'], sub_data['t'], color='b', label='Время добавления')
plt.xlabel('Количество добавленных ключей')
plt.ylabel('Время добавления')
plt.title('Время добавления ключей в фильтр Блума')
plt.legend()
plt.grid()

now = datetime.now().strftime("%H:%M:%S")

plt.savefig(f"./graph/avg_insertion_graph{now}.png", dpi=300)

