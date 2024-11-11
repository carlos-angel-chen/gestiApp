import { CheckCircle, Clock, DollarSign, ShoppingBag } from "lucide-react";
import { motion } from "framer-motion";
import { useState, useEffect } from "react";

import Header from "../components/common/Header";
import StatCard from "../components/common/StatCard";
import DailyOrders from "../components/orders/DailyOrders";
import OrderDistribution from "../components/orders/OrderDistribution";
import OrdersTable from "../components/orders/OrdersTable";

// const orderStats = {
// 	totalOrders: "1,234",
// 	pendingOrders: "56",
// 	completedOrders: "1,178",
// 	totalRevenue: "$98,765",
// };

const OrdersPage = () => {
	const [totalOrders, setTotalOrders] = useState(0);
	const [orders, setOrders] = useState([]);

	const fetchData = async () => {
		// Llamada para obtener total de pedidos
		const totalOrderResponse = await fetch("http://localhost:9080/calculus/total_pedidos");
		const data = await totalOrderResponse.json();
		setTotalOrders(data.totalPedidos);

		// Llamada para obtener datos de pedidos
		const ordersResponse = await fetch("http://localhost:9080/pedidos");
		const ordersData = await ordersResponse.json();
		setOrders(ordersData);
	};

	useEffect(() => {
        fetchData();
    }, []);

    return (
        <div className="flex-1 relative z-10 overflow-auto">
            <Header title="Pedidos" />

            <main className="max-w-10xl mx-auto py-6 px-4 lg:px-8">
                <motion.div
                    className='grid grid-cols-1 gap-5 sm:grid-cols-2 lg:grid-cols-1 mb-8'
					initial={{ opacity: 0, y: 20 }}
					animate={{ opacity: 1, y: 0 }}
					transition={{ duration: 1 }}
                >
                    <StatCard name='Total Orders' icon={ShoppingBag} value={totalOrders} color='#6366F1' />
					{/* <StatCard name='Pending Orders' icon={Clock} value={orderStats.pendingOrders} color='#F59E0B' />
					<StatCard
						name='Completed Orders'
						icon={CheckCircle}
						value={orderStats.completedOrders}
						color='#10B981'
					/>
					<StatCard name='Total Revenue' icon={DollarSign} value={orderStats.totalRevenue} color='#EF4444' /> */}
                </motion.div>

                {/* <div className='grid grid-cols-1 lg:grid-cols-2 gap-8 mb-8'>
					<DailyOrders />
					<OrderDistribution />
				</div> */}

				<OrdersTable orders={orders}/>
            </main>
        </div>
    );
};

export default OrdersPage;