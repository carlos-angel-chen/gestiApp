import { motion } from 'framer-motion';
import { useEffect, useState } from 'react';
import { AlertTriangle, DollarSign, Package, TrendingUp } from 'lucide-react';

import Header from '../components/common/Header'
import StatCard from '../components/common/StatCard'
import ProductsTable from '../components/products/ProductsTable'
import SalesTrendChart from '../components/products/SalesTrendChart'
import CategoryDistributionChart from '../components/overview/CategoryDistributionChart'

const ProductsPage = () => {
    const [totalProducts, setTotalProducts] = useState(0);
    const [topSelling, setTopSelling] = useState(0);
    const [lowStock, setLowStock] = useState(0);
    // const [totalRevenue, setTotalRevenue] = useState(0);
    const [categoryData, setCategoryData] = useState([]);
    const [salesData, setSalesData] = useState([]);
    const [allProducts, setAllProducts] = useState([]);


    const fetchDataSequentially = async () => {
        const delay = (ms) => new Promise(resolve => setTimeout(resolve, ms));
        try{
            // Llamada para obtener total de productos
            const productsResponse = await fetch('http://localhost:9080/calculus/total_products');
            const productsData = await productsResponse.json();
            setTotalProducts(productsData.totalProducts);
            await delay(100);

            // Llamada para obtener total de ventas
            const salesResponse = await fetch('http://localhost:9080/calculus/total_sales');
            const salesData = await salesResponse.json();
            setTopSelling(salesData.totalSales);
            await delay(100);

            // Llamada para obtener alertas de stock
            const stockResponse = await fetch('http://localhost:9080/calculus/stock_alert');
            const stockData = await stockResponse.json();
            setLowStock(stockData.stockAlert);
            await delay(100);

            // Llamada para obtener datos de categorias
            const categoryResponse = await fetch('http://localhost:9080/calculus/category_sales');
            const categoryData = await categoryResponse.json();
            setCategoryData(categoryData);
            await delay(100);

            // Llamada para obtener datos de ventas
            const monthlySalesResponse = await fetch('http://localhost:9080/calculus/monthly_sales');
            const monthlySalesData = await monthlySalesResponse.json();
            setSalesData(monthlySalesData);
            await delay(100);

            const allProductsResponse = await fetch('http://localhost:9080/productos');
            const allProductsData = await allProductsResponse.json();
            setAllProducts(allProductsData);
            await delay(100);

        } catch (error) {
            console.error('Error fetching data:', error);
        }
    };

    useEffect(() => {
        fetchDataSequentially();
    }, []);

    return (
        <div className="flex-1 overflow-auto relative z-10">
            <Header title="Products" /> 
            <main className='max-w-7x1 mx-auto py-6 px-4 lg:px-8'>
                {/* STATS */}
                <motion.div
                    className='grid grid-cols-1 gap-5 sm:grid-cols-2 lg:grid-cols-3 mb-8'
                    initial={{ opacity: 0, y: 20 }}
                    animate={{ opacity: 1, y: 0 }}
                    transition={{ duration: 1 }}
                >
                    <StatCard name="Total Products" icon={Package} value={totalProducts} color="#6366F1" />
                    {/* <StatCard name="Top Selling" icon={TrendingUp} value={1} color="#EC4899" /> */}
                    <StatCard name="Low Stock" icon={AlertTriangle} value={lowStock} color="#8B5CF6" />
                    <StatCard name="Total Revenue" icon={DollarSign} value={`$ ${topSelling.toFixed(2)}`} color="#10B981" />
                    
                </motion.div>
                
                <ProductsTable allProducts={allProducts} />

                {/* CHARTS */}
                {/* <div className='grid grid-col-1 lg:grid-col-2 gap-8'>
                    <SalesTrendChart  salesData={salesData}/>
                    <CategoryDistributionChart categoryData={categoryData}/>
                </div> */}
            </main>
        </div>
    );
}

export default ProductsPage