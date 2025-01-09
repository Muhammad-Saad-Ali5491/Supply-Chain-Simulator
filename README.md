# Supply Chain Simulator

## Overview
The Supply Chain Simulator is a C++ console application designed to help manage orders and inventory in a supply chain. It simulates order management, including order entry, detailed order display, raw material management, and order completion. The system uses data structures such as queues and stacks for order and history management.

## Features
- **Order Management:**
  - Enter new orders with details like name, order ID, delivery time, and priority.
  - Manage raw materials for orders.
  - Display orders based on priority.
- **Order Details Management:**
  - View order details and raw material data.
  - Display specific orders using order ID.
- **Order Completion:**
  - Mark orders as complete and move them to the history stack.
- **History Management:**
  - View and clear order history.
- **Data Management:**
  - Clear the entire order list.

## Usage
1. **Starting the Program:**
   - Run the program and follow the on-screen instructions.
2. **Entering Orders:**
   - Select option `01` to enter a new order and input the required details.
3. **Viewing Orders:**
   - Choose options `02` to `05` to view orders and details.
4. **Completing Orders:**
   - Select option `06` to mark an order as complete.
5. **Managing History:**
   - Use option `07` to view or clear the history.
6. **Clearing Orders:**
   - Select option `08` to clear all orders.
7. **Exiting:**
   - Press `9` to exit the simulator.

## Project Structure
- **main.cpp:** The main driver program containing the console application logic.
- **OrderQueue:** Manages order priority and statistics.
- **OrderDetailsList:** Handles order details and raw materials.
- **OrderHistoryStack:** Stores completed orders for history management.

## Dependencies
- C++ Standard Library
- Console-based C++ environment (e.g., Visual Studio, Code::Blocks)

## Compilation
```bash
g++ main.cpp -o SupplyChainSimulator
./SupplyChainSimulator
```

## Contributing
Contributions are welcome! Please ensure code follows proper C++ coding standards and includes comments where necessary.

## License
This project is open-source and available under the MIT License.

