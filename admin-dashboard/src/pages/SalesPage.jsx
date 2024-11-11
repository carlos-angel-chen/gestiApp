import {motion} from 'framer-motion';
import {useState, useEffect} from 'react';
import Header from '../components/common/Header';
import StatCard from "../components/common/StatCard";
import SalesOverviewChart from "../components/sales/SalesOverviewChart";
import SalesByCategoryChart from "../components/sales/SalesByCategoryChart";
import DailySalesTrend from "../components/sales/DailySalesTrend";
import SalesTable from '../components/sales/SalesTable';
import { useNavigate } from "react-router-dom";
import { CreditCard, DollarSign, ShoppingCart, TrendingUp, CirclePlus } from "lucide-react";

const salesStats = {
	totalRevenue: "$1,234,567",
	averageOrderValue: "$78.90",
	conversionRate: "3.45%",
	salesGrowth: "12.3%",
};

const SalesPage = () => {
    const [totalSales, setTotalSales] = useState(0);
    const [salesData, setSalesData] = useState([]);
    const [salesTable, setSalesTable] = useState([]);
    const [avgPesos, setAvgPesos] = useState(0);
    const [avgUsd, setAvgUsd] = useState(0);
    const navigate = useNavigate();

    const fetchData = async () => {
        // Llamada para obtener total de ventas
        const salesResponse = await fetch('http://localhost:9080/calculus/total_sales');
        const salesData = await salesResponse.json();
        setTotalSales(salesData.totalSales);

        // Llamada para obtener datos de ventas
        const monthlySalesResponse = await fetch('http://localhost:9080/calculus/monthly_sales');
        const monthlySalesData = await monthlySalesResponse.json();
        setSalesData(monthlySalesData);

        // Llamada para obtener datos de ventas
        const salesTableResponse = await fetch('http://localhost:9080/ventas');
        const salesTableData = await salesTableResponse.json();
        setSalesTable(salesTableData);

        // Llamada para obtener promedio de ventas pesos
        const avgPesosResponse = await fetch('http://localhost:9080/calculus/avg_precio_final_pesos');
        const avgPesosData = await avgPesosResponse.json();
        setAvgPesos(avgPesosData.avgPrecioFinalPesos);

        // Llamada para obtener promedio de ventas usd
        const avgUsdResponse = await fetch('http://localhost:9080/calculus/avg_precio_final_usd');
        const avgUsdData = await avgUsdResponse.json();
        setAvgUsd(avgUsdData.avgPrecioFinalUsd);
    };

    useEffect(() => {
        fetchData();
    }, []);

    return (
        <div className='flex-1 overflow-auto relative z-10'>
            <Header title="Ventas" />

            <main className='max-w-7x1 mx-auto py-6 px-4 lg:px-8'>
                <motion.div
                    className='grid grid-cols-1 gap-5 sm:grid-cols-2 lg:grid-cols-4 mb-8'
                    initial={{ opacity: 0, y: 20 }}
                    animate={{ opacity: 1, y: 0 }}
                    transition={{ duration: 1}}
                >
                    <StatCard name='Total Ingresos' icon={DollarSign} value={`$ ${totalSales.toFixed(2)}`} color='#6366F1' />
					<StatCard
						name='Promedio de ventas Pesos'
						icon={ShoppingCart}
						value={avgPesos.toFixed(2)}
						color='#10B981'
					/>
                    <StatCard
						name='Promedio de ventas USD'
						icon={ShoppingCart}
						value={avgUsd.toFixed(2)}
						color='#10B981'
					/>
                    <StatCard
						name='Nueva venta'
						icon={CirclePlus}
						value="Agregar venta"
						color='#F59E0B'
                        onClick={() => navigate('/nueva-venta')}
					/>
					{/* <StatCard
						name='Conversion Rate'
						icon={TrendingUp}
						value={salesStats.conversionRate}
						color='#F59E0B'
					/>
					<StatCard name='Sales Growth' icon={CreditCard} value={salesStats.salesGrowth} color='#EF4444' /> */}
                </motion.div>

                <SalesOverviewChart salesData={salesData}/>

                <SalesTable salesTable={salesTable}/>

                {/* <div className='grid grid-cols-1 lg:grid-cols-2 gap-8 mb-8'>
					<SalesByCategoryChart />
					<DailySalesTrend />
				</div> */}
            </main>
        </div>
    );
};

export default SalesPage;