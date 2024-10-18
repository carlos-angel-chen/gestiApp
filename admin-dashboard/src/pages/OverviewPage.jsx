import { useEffect, useState } from 'react';
import { BarChart2, ShoppingBag, Zap, Users } from 'lucide-react'
import Header from '../components/common/Header'
import StatCard from '../components/common/StatCard'
import SalesOverviewChart from '../components/overview/SalesOverviewChart'
import CategoryDistributionChart from '../components/overview/CategoryDistributionChart'
import SalesChannelChart from '../components/overview/SalesChannelChart'

import { motion } from 'framer-motion'

const OverviewPage = () => {
    const [totalSales, setTotalSales] = useState(0);
    const [totalProducts, setTotalProducts] = useState(0);
    const [totalClients, setTotalClients] = useState(0);
    const [stockAlert, setStockAlert] = useState(0);
    const [salesData, setSalesData] = useState([]);

    const fetchDataSequentially = async () => {
        try {
            // Llamada para obtener total de ventas
            const salesResponse = await fetch('http://localhost:9080/calculus/total_sales');
            const salesData = await salesResponse.json();
            setTotalSales(salesData.totalSales);

            // Llamada para obtener total de productos
            const productsResponse = await fetch('http://localhost:9080/calculus/total_products');
            const productsData = await productsResponse.json();
            setTotalProducts(productsData.totalProducts);

            // Llamada para obtener total de clientes
            const clientsResponse = await fetch('http://localhost:9080/calculus/total_clients');
            const clientsData = await clientsResponse.json();
            setTotalClients(clientsData.totalClients);

            // Llamada para obtener alertas de stock
            const stockResponse = await fetch('http://localhost:9080/calculus/stock_alert');
            const stockData = await stockResponse.json();
            setStockAlert(stockData.stockAlert);

            // Llamada para obtener datos de ventas
            const monthlySalesResponse = await fetch('http://localhost:9080/calculus/monthly_sales');
            const monthlySalesData = await monthlySalesResponse.json();
            setSalesData(monthlySalesData);

        } catch (error) {
            console.error('Error fetching data:', error);
        }
    };

    useEffect(() => {
        fetchDataSequentially();
    }, []);

    return (
        <div className="flex-1 overflow-auto relative z-10">
            <Header title="Overview" />

            <main className='max-w-7x1 mx-auto py-6 px-4 lg:px-8'>
                {/* STATS */}
                <motion.div
                    className='grid grid-cols-1 gap-5 sm:grid-cols-2 lg:grid-cols-4 mb-8'
                    initial={{ opacity: 0, y: 20 }}
                    animate={{ opacity: 1, y: 0 }}
                    transition={{ duration: 1 }}
                >
                    <StatCard name="Total Sales" icon={Zap} value={`$ ${totalSales.toFixed(2)}`} color="#6366F1" />
                    <StatCard name="Total Products" icon={ShoppingBag} value={totalProducts} color="#EC4899" />
                    <StatCard name="Total Clients" icon={Users} value={totalClients} color="#8B5CF6" />
                    <StatCard name="Stock Alert" icon={BarChart2} value={`${stockAlert}`} color="##10B981" />
                    
                </motion.div>

                {/* CHARTS */}
                <div className='grid grid-col-1 lg:grid-col-2 gap-8'>
                    <SalesOverviewChart salesData={salesData}/>
                    <CategoryDistributionChart />
                    <SalesChannelChart />
                </div>
            </main>
        </div>
    )
} 

export default OverviewPage